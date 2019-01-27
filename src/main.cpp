#include <Arduino.h>

//You can not remap pins without touching the code below
#define RGB_DP   GPIOA
#define RGB_PR1  PA0
#define RGB_PG1  PA1
#define RGB_PB1  PA2
#define RGB_PR2  PA3
#define RGB_PG2  PA4
#define RGB_PB2  PA5
#define RGB_CLK  PA6

#define A    PB3
#define B    PB4
#define C    PB5
#define D    PB6
#define OE   PB7
#define LAT  PB8

#define LED  PC13

#include "logo.h"

bool ledneu = HIGH;
unsigned long start;

void panel_selectAddr(byte addr) {
  GPIOB->BRR = 0b1111000;
  GPIOB->BSRR = addr << 3;
}

void panel_write(byte idata) {
  digitalWrite(RGB_CLK, LOW); //@todo replace with direct GPIO registers
  RGB_DP->ODR = idata;
  digitalWrite(RGB_CLK, HIGH); //@todo replace with direct GPIO registers
}

void panel_latch(void) {
  digitalWrite(LAT, HIGH); //@todo replace with direct GPIO registers
  digitalWrite(LAT, LOW);  //@todo replace with direct GPIO registers
}

void setup(void) {
  Serial.begin(115200);
  pinMode(PC13, OUTPUT);

  for(byte dly=0; dly <= 20; dly++) {
    //Blink LED PC13 vie ODR
    GPIOC->ODR = 0b00010000000000000;
    delay(100);
    GPIOC->ODR = 0b00000000000000000;
    delay(100);
  }
  Serial.print("Setup...\nModes...");

  pinMode(RGB_PR1, OUTPUT);
  pinMode(RGB_PG1, OUTPUT);
  pinMode(RGB_PB1, OUTPUT);
  pinMode(RGB_PR2, OUTPUT);
  pinMode(RGB_PG2, OUTPUT);
  pinMode(RGB_PB2, OUTPUT);
  pinMode(RGB_CLK, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(LAT, OUTPUT);
  pinMode(LED, OUTPUT);

  Serial.print("out...");

  digitalWrite(RGB_PR1, LOW);
  digitalWrite(RGB_PG1, LOW);
  digitalWrite(RGB_PB1, LOW);
  digitalWrite(RGB_PR2, LOW);
  digitalWrite(RGB_PG2, LOW);
  digitalWrite(RGB_PB2, LOW);
  digitalWrite(RGB_CLK, LOW);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(OE, HIGH);
  digitalWrite(LAT, LOW);

  Serial.println("OK");
}

void panelLine(byte addr, const byte *data) {
  digitalWrite(OE, HIGH); //@todo replace with direct GPIO registers
  panel_selectAddr(addr);
  for(byte i=0; i<64; i++) panel_write(data[i]);
  panel_latch();
  digitalWrite(OE, LOW); //@todo replace with direct GPIO registers
  //Slower but more precise timing
  //delay_us(50);
  //digitalWrite(OE, HIGH); //@todo replace with direct GPIO registers
}

void draw3() {
  panelLine(0, line_0_s1);
  panelLine(1, line_1_s1);
  panelLine(2, line_2_s1);
  panelLine(3, line_3_s1);
  panelLine(4, line_4_s1);
  panelLine(5, line_5_s1);
  panelLine(6, line_6_s1);
  panelLine(7, line_7_s1);
  panelLine(8, line_8_s1);
  panelLine(9, line_9_s1);
  panelLine(10, line_10_s1);
  panelLine(11, line_11_s1);
  panelLine(12, line_12_s1);
  panelLine(13, line_13_s1);
  panelLine(14, line_14_s1);
  panelLine(15, line_15_s1);
}

void draw2() {
  panelLine(0, line_0_s2);
  panelLine(1, line_1_s2);
  panelLine(2, line_2_s2);
  panelLine(3, line_3_s2);
  panelLine(4, line_4_s2);
  panelLine(5, line_5_s2);
  panelLine(6, line_6_s2);
  panelLine(7, line_7_s2);
  panelLine(8, line_8_s2);
  panelLine(9, line_9_s2);
  panelLine(10, line_10_s2);
  panelLine(11, line_11_s2);
  panelLine(12, line_12_s2);
  panelLine(13, line_13_s2);
  panelLine(14, line_14_s2);
  panelLine(15, line_15_s2);

}

void draw1() {
  panelLine(0, line_0_s3);
  panelLine(1, line_1_s3);
  panelLine(2, line_2_s3);
  panelLine(3, line_3_s3);
  panelLine(4, line_4_s3);
  panelLine(5, line_5_s3);
  panelLine(6, line_6_s3);
  panelLine(7, line_7_s3);
  panelLine(8, line_8_s3);
  panelLine(9, line_9_s3);
  panelLine(10, line_10_s3);
  panelLine(11, line_11_s3);
  panelLine(12, line_12_s3);
  panelLine(13, line_13_s3);
  panelLine(14, line_14_s3);
  panelLine(15, line_15_s3);
}

void panelTest(void) {
  draw3();
  draw2();
  draw3();
  draw1();
  draw3();
  draw2();
  draw3();
}

void loop() {
  start = millis();
  panelTest();
  digitalWrite(LED, ledneu); //@todo replace with direct GPIO registers
  ledneu = !ledneu;
  start = millis() - start;

  /*
  //Output timing on serial
  Serial.print(F("Took "));
  Serial.println(start);
  Serial.print(F("ms  (Per Subframe: "));
  Serial.print(round(start/7));
  Serial.println(F("ms)"));
  */

  /*
  //Dynamically change image via UART. Never tested.
  while(Serial.available() >= 4) {
    switch(Serial.read()) {
      case '1':
        switch(Serial.read()) {
          case '0': line_0_s1[Serial.read()] = Serial.parseInt(); break;
          case '1': line_1_s1[Serial.read()] = Serial.parseInt(); break;
          case '2': line_2_s1[Serial.read()] = Serial.parseInt(); break;
          case '3': line_3_s1[Serial.read()] = Serial.parseInt(); break;
          case '4': line_4_s1[Serial.read()] = Serial.parseInt(); break;
          case '5': line_5_s1[Serial.read()] = Serial.parseInt(); break;
          case '6': line_6_s1[Serial.read()] = Serial.parseInt(); break;
          case '7': line_7_s1[Serial.read()] = Serial.parseInt(); break;
          case '8': line_8_s1[Serial.read()] = Serial.parseInt(); break;
          case '9': line_9_s1[Serial.read()] = Serial.parseInt(); break;
          case 'A': line_10_s1[Serial.read()] = Serial.parseInt(); break;
          case 'B': line_11_s1[Serial.read()] = Serial.parseInt(); break;
          case 'C': line_12_s1[Serial.read()] = Serial.parseInt(); break;
          case 'D': line_13_s1[Serial.read()] = Serial.parseInt(); break;
          case 'E': line_14_s1[Serial.read()] = Serial.parseInt(); break;
          case 'F': line_15_s1[Serial.read()] = Serial.parseInt(); break;
        }
        break;
      case '2':
        switch(Serial.read()) {
          case '0': line_0_s2[Serial.read()] = Serial.parseInt(); break;
          case '1': line_1_s2[Serial.read()] = Serial.parseInt(); break;
          case '2': line_2_s2[Serial.read()] = Serial.parseInt(); break;
          case '3': line_3_s2[Serial.read()] = Serial.parseInt(); break;
          case '4': line_4_s2[Serial.read()] = Serial.parseInt(); break;
          case '5': line_5_s2[Serial.read()] = Serial.parseInt(); break;
          case '6': line_6_s2[Serial.read()] = Serial.parseInt(); break;
          case '7': line_7_s2[Serial.read()] = Serial.parseInt(); break;
          case '8': line_8_s2[Serial.read()] = Serial.parseInt(); break;
          case '9': line_9_s2[Serial.read()] = Serial.parseInt(); break;
          case 'A': line_10_s2[Serial.read()] = Serial.parseInt(); break;
          case 'B': line_11_s2[Serial.read()] = Serial.parseInt(); break;
          case 'C': line_12_s2[Serial.read()] = Serial.parseInt(); break;
          case 'D': line_13_s2[Serial.read()] = Serial.parseInt(); break;
          case 'E': line_14_s2[Serial.read()] = Serial.parseInt(); break;
          case 'F': line_15_s2[Serial.read()] = Serial.parseInt(); break;
        }
        break;
      case '3':
        switch(Serial.read()) {
          case '0': line_0_s3[Serial.read()] = Serial.parseInt(); break;
          case '1': line_1_s3[Serial.read()] = Serial.parseInt(); break;
          case '2': line_2_s3[Serial.read()] = Serial.parseInt(); break;
          case '3': line_3_s3[Serial.read()] = Serial.parseInt(); break;
          case '4': line_4_s3[Serial.read()] = Serial.parseInt(); break;
          case '5': line_5_s3[Serial.read()] = Serial.parseInt(); break;
          case '6': line_6_s3[Serial.read()] = Serial.parseInt(); break;
          case '7': line_7_s3[Serial.read()] = Serial.parseInt(); break;
          case '8': line_8_s3[Serial.read()] = Serial.parseInt(); break;
          case '9': line_9_s3[Serial.read()] = Serial.parseInt(); break;
          case 'A': line_10_s3[Serial.read()] = Serial.parseInt(); break;
          case 'B': line_11_s3[Serial.read()] = Serial.parseInt(); break;
          case 'C': line_12_s3[Serial.read()] = Serial.parseInt(); break;
          case 'D': line_13_s3[Serial.read()] = Serial.parseInt(); break;
          case 'E': line_14_s3[Serial.read()] = Serial.parseInt(); break;
          case 'F': line_15_s3[Serial.read()] = Serial.parseInt(); break;
        }
      break;
    }
  }
  */
}
