#include <Arduino.h>
#include <RF24.h>

uint8_t address[] = {0x00, 0xFD, 0xEA, 0xDB, 0xEE};
RF24 radio(49,53);
int i;
int motor1switch = 34;
int motor1pwm = 2;
int motor1power = 127;

// void interruptRoutine(void){
//     Serial.println("hi");
// }

void setup() {
    pinMode(A15, INPUT);
    pinMode(motor1switch, OUTPUT);
    digitalWrite(motor1switch, LOW);
    pinMode(motor1pwm, OUTPUT);
    analogWrite(motor1pwm, motor1power);
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
            if (motor1power<127){
                motor1power++;
                Serial.println(motor1power);
            }
            analogWrite(motor1pwm, motor1power);
        } else if (input == 'w'){ // Speed up means lower pwm
            if (motor1power>1){
                motor1power--;
                Serial.println(motor1power);
            }
            analogWrite(motor1pwm, motor1power);
        } else if (input == 'i'){
            digitalWrite(motor1switch, HIGH);
            Serial.println("Motor on");
        } else if (input == 'u'){
            digitalWrite(motor1switch, LOW);
            motor1power = 127;
            analogWrite(motor1pwm, motor1power);
            Serial.println("Motor off");
        }
    }
    delay(10);
    // if (i<=105){
    //     radio.stopListening();
    //     radio.setChannel(i);
    //     radio.startListening();
    //     Serial.print(i);
    //     Serial.print("\t");
    //     Serial.println(radio.testCarrier());
    // // radio.flush_rx();
    //     i++;
    //     delay(100);
    // }
}