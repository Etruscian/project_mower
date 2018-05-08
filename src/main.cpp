#include <Arduino.h>
#include <RF24.h>
#include <controller.hpp>

uint8_t address[] = {0x00, 0xFD, 0xEA, 0xDB, 0xEE};
RF24 radio(49,53);
float i = 0;
Controller controller;

// void interruptRoutine(void){
//     Serial.println("hi");
// }

void setup() {
    pinMode(A15, INPUT);
    
    // attachInterrupt(A15, interruptRoutine, FALLING);
    // radio.begin();
    Serial.begin(9600);
    Serial.println("Ready");
    Serial.println("Motor off");
    // Serial.println(radio.get_status());
    // radio.openReadingPipe(0, address);
    // radio.setCRCLength(RF24_CRC_16);
    // radio.setPayloadSize(17);
    // radio.setChannel(101);
    // radio.setAutoAck(0,true);
    // radio.startListening();
}

void loop() {
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