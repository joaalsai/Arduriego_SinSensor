/*
  LiquidCrystal Library - display() and noDisplay()
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD and uses the 
 display() and noDisplay() functions to turn on and off
 the display.
 
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe 
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://arduino.cc/en/Tutorial/LiquidCrystalDisplay

 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// set pin numbers:
const int relayPin =  10;      // the number of the RELAY_1 pin

// Valores de las variables de la version anterior
// const int buttonA = 6;            // the number of the button A pin
// const int buttonB = 7;            // the number of the button B pin
// const int buttonMAS = 8;          // the number of the button MAS pin
// const int buttonMENOS = 9;        // the number of the button MENOS pin
// const int analogInSMS = A1;        // the number of Soil Moisture Sensor pin

// int readingA;           // the current reading from the input pin
// int readingB;           // the current reading from the input pin
// int readingMAS;           // the current reading from the input pin
// int readingMENOS;           // the current reading from the input pin

// int sensorValue=0;              // set de sensorValue variable to 0
// int dryValue=700;                // set de dryValue variable to 700. If the readings from the soil sensor drop below this number, then turn on the pump

int irrigationTime=30;           // set the time of irrigation in minutes  
int numRiegos=2;                 // set the number of irrigations
int minutos=60000;              // set the minutos variable to 60000 ms for conversions
int minuto=00;                  // set the minuto variable to 59'
int hora=12;                   // set the hora variable to 24'
const int botonForzarRiego = 6;            // the number of the button ForzarRiego pin

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  //Set buttonA and buttonB as input
  //  pinMode(buttonA, INPUT);
  //  pinMode(buttonB, INPUT);
  //  pinMode(buttonMAS, INPUT);
  //  pinMode(buttonMENOS, INPUT);
  
  //Set Pin 10 as output 
  pinMode(relayPin, OUTPUT); 
 
  //Set Pin 6 as input 
  pinMode(botonForzarRiego, INPUT); 
 
  // Print a message to the LCD.
  lcd.setCursor(4,0);
  lcd.print("ArduRiego");
  lcd.setCursor(5,1);
  lcd.print("V 2.0");
  delay(2000);
}

void loop() {
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print("Falta para riego");
  lcd.setCursor(4,1);
  lcd.print(hora);
  lcd.print("h ");
  lcd.print(minuto);
  lcd.print("m ");
  if (digitalRead(botonForzarRiego)==HIGH){
    regar();
  }  
  
  
  if (hora==0 && minuto==0){
    regar();
  }else{
    digitalWrite(relayPin,LOW);
    esperarMinutos(1);
    }
  switch(minuto){
    case 0:
      minuto=59;
      switch(hora){
        case 0:
        hora=23;
        break;
        default:
        hora=hora-1;
        break;
      }
      break;
    default:
      minuto=minuto-1;
      break;
   }  
}

void esperarMinutos(int tiempoEnMinutos){
  while(tiempoEnMinutos>0){
    for(int i=1;i<=59;i++){
      delay(1000);
    }
   tiempoEnMinutos--; 
  } 
}

void regar(){
  digitalWrite(relayPin,HIGH);
    esperarMinutos(irrigationTime);
    minuto=60-irrigationTime;
    hora=23/numRiegos;
}
