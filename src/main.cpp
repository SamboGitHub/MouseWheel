#include <Arduino.h>
#include <Mouse.h>

int pinA = 2;
int pinB = 3;
int pinS = 7;

int clicked = 0;

volatile int previous = 0;
volatile int counter = 0;

volatile int buttonpress = 0;

void button() {
  
   int S = digitalRead(pinS); 
   
   
   if(S==1) {
    buttonpress = 1;
   }
   else
   {
    buttonpress=0;
   }
  }

void changed() {

  int A = digitalRead(pinA); 
  int B = digitalRead(pinB);


  int current = (A << 1) | B;
  int combined  = (previous << 2) | current;
   
  if(combined == 0b0010 || 
     combined == 0b1011 ||
     combined == 0b1101 || 
     combined == 0b0100) {
    counter++;
  }
   
  if(combined == 0b0001 ||
     combined == 0b0111 ||
     combined == 0b1110 ||
     combined == 0b1000) {
    counter--;
  }

  previous = current;
}
void setup() {
  pinMode(pinA, INPUT_PULLUP); 
  pinMode(pinB, INPUT_PULLUP);

  pinMode(pinS, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), changed, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(pinB), changed, CHANGE);

  attachInterrupt(digitalPinToInterrupt(pinS), button, CHANGE);


  Mouse.begin();
}
void loop(){ 
  if(counter >= 2) {
    Mouse.move(0,0,-1000);
    counter -= 2;
  } else if(counter <= -2) {
    Mouse.move(0,0,1000);
    counter += 2;
  } 

  if(buttonpress== 1) {
    Mouse.press();
    Mouse.release();
    buttonpress = 0;
  } 

  

}