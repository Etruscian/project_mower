#include <Arduino.h>
#include <RF24.h>
#include <motor.hpp>

uint8_t address[] = {0x00, 0xFD, 0xEA, 0xDB, 0xEE};
RF24 radio(49,53);
int i = 127;
Motor leftMotor(34, 2);

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
    // i = 0;
}

void loop() {
    if (Serial.available()){
        char input = Serial.read();
        if (input == 's'){ // Slow down means higher pwm
            if (i<127){
                i++;
                Serial.println(i);
            }
            leftMotor.setSpeed(i);
        } else if (input == 'w'){ // Speed up means lower pwm
            if (i>1){
                i--;
                Serial.println(i);
            }
            leftMotor.setSpeed(i);
        } else if (input == 'i'){
            leftMotor.enableMotor(true);
            Serial.println("Motor on");
        } else if (input == 'u'){
            leftMotor.enableMotor(false);
            Serial.println("Motor off");
        }
    }
    delay(10);
}