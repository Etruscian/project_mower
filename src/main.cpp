#include <Arduino.h>
#include <SPI.h>
#include "nRF24L01P.hpp"
#include <controller.hpp>
#include <canons.hpp>

union transferBuffer {
    float f;
    char c[4];
};

nRF24L01P radio(49, 53);
float i = 0;
Controller controller;
Canons canons;
uint8_t status;
char rxBuffer[17];
transferBuffer rxData[4];
bool switch1 = false, switch2 = false;

void interruptRoutine(void)
{
    status = radio.getStatusRegister();

    if (status == 0)
    { //data not ready?
        while (status == 0)
        {
            status = radio.getStatusRegister();
        }
    }
    if (status & 1)
    { // TX FIFO full
        radio.disable();
        radio.flushTX();
    }
    if (status & 16)
    { // max TX retransmits
        radio.disable();
        radio.flushTX();
        radio.setRegister(0x07, 16);
    }
    if (status & 32)
    { // TX sent (ACK package available if autoAck is enabled)
        radio.disable();
        radio.flushTX();
        radio.setRegister(0x07, 32);
    }
    if (status & 64)
    { // RX received
        radio.read(0, rxBuffer, 17);
        radio.setRegister(0x07, 64);
        for (int i = 0; i <= 15; i++)
        {
            rxData[i / 4].c[i & 3] = rxBuffer[i];
        }
        switch1 = (rxBuffer[16] >> 1) & 1;
        switch2 = rxBuffer[16] & 1;
        controller.enableMotors(switch1);
        controller.update(rxData[0].f*100, rxData[1].f/100.0);
    }
}

void setup()
{
    TCCR4A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    TCCR4B = TCCR4B & (0b11111000 | 0x03);

    Serial.begin(9600);
    SPI.begin();
    radio.initialize();
    attachInterrupt(digitalPinToInterrupt(2), interruptRoutine, FALLING);
    radio.setRfFrequency(2400 + 101);
    radio.setTransferSize(17);
    radio.setCrcWidth(16);
    radio.setTxAddress(0x007DEADBEE);
    radio.setRxAddress(0x007DEADBEE);
    radio.setAirDataRate(NRF24L01P_DATARATE_250_KBPS);
    radio.enableAutoRetransmit(1000, 3);
    radio.enableAutoAcknowledge();
    radio.setReceiveMode();
    radio.powerUp();
    radio.enable();
    Serial.println(canons.fire());
    Serial.println(canons.fire());
    Serial.println(canons.fire());
    Serial.println(canons.fire());
}

void loop()
{
}