#include <Arduino.h>
#include <SPI.h>
// #include "nRF24L01P.hpp"
#include <controller.hpp>

// nRF24L01P radio(49,47);
float i = 0;
Controller controller;

void interruptRoutine(void){
    Serial.println("hi");
    // while(true){Serial.println(radio.get_status());}
}

void setup() {
    Serial.begin(9600);
    // SPI.begin();
    Serial.println("h i");
    // radio.initialize();
    // attachInterrupt(digitalPinToInterrupt(20), interruptRoutine, FALLING);
    Serial.println("Motor off");
    // Serial.println(radio.getStatusRegister());
    // radio.powerUp();
    // radio.setRfFrequency(2400 + 101);
    // radio.setTransferSize(17);
    // radio.setCrcWidth(16);
    // radio.setTxAddress(0x007DEADBEE);
    // radio.setRxAddress(0x007DEADBEE);
    // radio.enableAutoAcknowledge(NRF24L01P_PIPE_P0);
    // radio.setAirDataRate(NRF24L01P_DATARATE_250_KBPS);
    // radio.enableAutoRetransmit(1000, 3);
    // radio.setReceiveMode();
    }

void loop() {
    char data[17];
    // radio.write(0,data, 17);
    // Serial.println(radio.testRPD());
    if (Serial.available()){
        char input = Serial.read();
        if (input == 's'){
            if (i>0){
                i = i-5;
                controller.update(i,0);
                Serial.println((int)(i));
            }
        } else if (input == 'w'){
            if (i<100){
                i = i+5;
                controller.update(i,0);
                Serial.println((int)(i));
            }
        } else if (input == 'i'){
            controller.enableMotors(true);
            Serial.println("Motor on");
        } else if (input == 'u'){
            controller.enableMotors(false);
            Serial.println("Motor off");
        }
    }
    delay(10);
}