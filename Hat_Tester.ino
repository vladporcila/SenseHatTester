#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp0;
Adafruit_MCP23017 mcp1;

void allbacktoinputs (){
  int i=8;
  for(i=0;i<=15;i++)
  {
     mcp0.pinMode(i, INPUT);
  }

    for(i=0;i<=15;i++)
  {
     mcp1.pinMode(i, INPUT);
  }
}

void ic2internalpullups(){
  int i=8;
  for(i=8;i<=15;i++)
  {
    mcp0.pullUp(i, HIGH);  // turn on a 100K pullup internally
  }
}

void ic3internalpullups(){
 mcp1.pullUp(0, HIGH);  // turn on a 100K pullup internally
 mcp1.pullUp(1, HIGH);  // turn on a 100K pullup internally
 mcp1.pullUp(2, HIGH);  // turn on a 100K pullup internally
 mcp1.pullUp(8, HIGH);  // turn on a 100K pullup internally
}

void setup() {
 Serial.begin(9600);
 mcp0.begin(0);//IC2
 mcp1.begin(1);//IC3

 allbacktoinputs ();

 ic2internalpullups();
 ic3internalpullups();

  uint16_t Test=0;
  uint16_t Test1=0;

  mcp1.pinMode(14, OUTPUT); //5V Test Pin
  mcp1.digitalWrite(14, 0);

  delay(1000);

  Test=mcp0.readGPIOAB();
  Test1=mcp1.readGPIOAB();

  Serial.print(Test,BIN);
  Serial.print("\n");
  Serial.print(Test1,BIN); 
  Serial.print("\n\n");

  if (Test != 0b1111111111110111 | Test1 != 0b1011111101111111) // 5V Test Rpi
  {
    Serial.print("5V Error \n");
    allbacktoinputs (); 
    while(1){};//Do nothing
  }

  allbacktoinputs ();

  mcp1.pinMode(15, OUTPUT); //3.3V Test Pin
  mcp1.digitalWrite(15, 0);

  delay(1000);

  Test=mcp0.readGPIOAB();
  Test1=mcp1.readGPIOAB();

  Serial.print(Test,BIN);
  Serial.print("\n");
  Serial.print(Test1,BIN); 
  Serial.print("\n\n");

  if (Test != 0b1111111111011111 | Test1 != 0b0111111111101111) // 3.3V Test Rpi
  {
    Serial.print("3.3V Error \n");
    allbacktoinputs (); 
    while(1){};//Do nothing
  }

  allbacktoinputs ();

  mcp1.pinMode(11, OUTPUT); //GND Test Pin
  mcp1.digitalWrite(11, 0); 

  delay(1000);

  Test=mcp0.readGPIOAB();
  Test1=mcp1.readGPIOAB();

  Serial.print(Test,BIN);
  Serial.print("\n");
  Serial.print(Test1,BIN); 
  Serial.print("\n\n");

  if (Test != 0b1111111111101011 | Test1 != 0b1111011111110111) // GND Test Rpi
  {
    Serial.print("GND Error \n");
    allbacktoinputs (); 
    while(1){};//Do nothing
  }

  allbacktoinputs ();

  Serial.print("5V, 3.3V, GND Tests Passed \n");

  
}

void loop() {
 
  delay(1000);
}
