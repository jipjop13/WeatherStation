#include "DHT.h"
#include <TM1637Display.h>
#include <Servo.h>


Servo tempServo;
DHT dht;
float temperature;
String valueType = "C";
String lightStatus = "ON";
String Blink = "";

const int sensor=A1; // Assigning analog pin A1 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;  //temporary variable to hold sensor reading

const int CLK = A2; //Set the CLK pin connection to the display
const int DIO = A3; //Set the DIO pin connection to the display

TM1637Display display(CLK, DIO);  //set up the 4-Digit Display.


void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);

  dht.setup(A0); // data pin 2
  tempServo.attach(11); //PWM pin 10

  display.setBrightness(0x0a);  //set the diplay to maximum brightness


  initShow();
}

void loop()
{

  measureTemperature();
  Serial.println(temperature);
  setServoPosition();
  setTempLight();
  setDisplay();
  
  blinkcheck();
  delay(900);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
}

void measureTemperature()
{ 
  dht.setup(A0); 
  if (!isnan(dht.getTemperature()) || dht.getTemperature() <0 )
  {
    if (valueType == "C");
    {
      temperature = dht.getTemperature();
    } 
    if (valueType == "F")
    {
      temperature = (1.8 * dht.getTemperature()) + 32;
    }
    if (valueType == "K")
    {
      temperature = 273.15 + dht.getTemperature();
    }
    

  digitalWrite(A4, LOW);
  digitalWrite(A5, HIGH);
  }else if(analogRead(A1) < 1010)
  {

  vout=analogRead(sensor);
  vout=(vout*500)/1023;
  tempc=vout; // Storing value in Degree Celsius
  temperature = vout - 257;
  
  
  delay(100); //Delay of 1 second for ease of viewing 
    
    digitalWrite(A5, LOW);
    digitalWrite(A4, HIGH);
    delay(500);
  }else{
    temperature = 0.0;
    digitalWrite(A4, LOW);
    digitalWrite(A5, LOW);
  }
}

void setServoPosition()
{
  int temp = 0;
  if (temperature < 50 && temperature > 0)
  {
    temp = temperature;
  }
  int servoPosition = map(temp, 0, 50, 180, 0);
  tempServo.write(servoPosition);
}

void setDisplay(){
   display.showNumberDec(temperature); //Display the Variable value;
}

void blinkcheck(){
  if (temperature == 0)
  {
    Blink = "";
  }
  if (Blink == "LL"){
    digitalWrite(2, HIGH);
    Blink = "LH";
  }
  else if (Blink == "LH"){
    digitalWrite(2, LOW);
    Blink = "LL";
  }
  else if (Blink == "HL"){
    digitalWrite(12, HIGH);
    Blink = "HH";
  }
  else if (Blink == "HH"){
    digitalWrite(12, LOW);
    Blink = "HL";
  }
  
}

void serialEvent() {
  while (Serial.available()) {
  char temp =(char)Serial.read();
  if ( temp == 'C'){
    valueType = "C";
    Serial.println("Temperature value : Celcius");
  }
  if ( temp == 'F'){
    valueType = "F";
    Serial.println("Temperature value : Fahrenheit");
  }
  if ( temp == 'K'){
    valueType = "K";
    Serial.println("Temperature value : Kelvin");
  }
  if ( temp == 'L'){
    if (lightStatus == "OFF"){
      lightStatus = "ON";
      Serial.println("Lights switched ON");
    }
    else if (lightStatus == "ON"){
      lightStatus = "OFF";
      Blink = "";
      Serial.println("Lights switched OFF");
    }
    
  }
  }
}

void initShow()
{ 

  const uint8_t SEG_I[] = {
  SEG_F | SEG_E,              
  SEG_SPACE,   
  SEG_SPACE,                           
  SEG_SPACE,            
  };
  const uint8_t SEG_IN[] = {
  SEG_F | SEG_E,           
  SEG_C | SEG_E | SEG_G,   
  SEG_SPACE,                          
  SEG_SPACE,            
  };
  const uint8_t SEG_INI[] = {
  SEG_F | SEG_E,           
  SEG_C | SEG_E | SEG_G,   
  SEG_F | SEG_E,     
  SEG_SPACE,          
  };
  const uint8_t SEG_INIT[] = {
  SEG_F | SEG_E,           
  SEG_C | SEG_E | SEG_G,   
  SEG_F | SEG_E,     
  SEG_F | SEG_E | SEG_D | SEG_G,          
  };

  const uint8_t SEG_NOPE[] = {
  SEG_SPACE,   
  SEG_SPACE,                           
  SEG_SPACE,    
  SEG_SPACE,          
  };
  


  
    digitalWrite(2, HIGH);
    delay(50);
    digitalWrite(3, HIGH);
    delay(50);
    digitalWrite(4, HIGH);
    delay(50);
    digitalWrite(5, HIGH);
    delay(50);
    digitalWrite(6, HIGH);
    delay(50);
    digitalWrite(7, HIGH);
    delay(50);
    digitalWrite(8, HIGH);
    delay(50);
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(10, HIGH);
    delay(50);
    digitalWrite(12, HIGH);
    delay(50);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(A4, HIGH);
    delay(50);
    digitalWrite(A5, HIGH);
    delay(50);

    display.setSegments(SEG_NOPE);
    delay(50);
    display.setSegments(SEG_I);
    delay(50);
    display.setSegments(SEG_IN);
    delay(50);
    display.setSegments(SEG_INI);
    delay(50);
    display.setSegments(SEG_INIT);
    delay(50);
    display.setSegments(SEG_INI);
    delay(50);
    display.setSegments(SEG_IN);
    delay(50);
    display.setSegments(SEG_I);
    delay(50);
    display.setSegments(SEG_NOPE);
    delay(50);

    
    digitalWrite(A5, LOW);
    delay(50);
    digitalWrite(A4, LOW);
    delay(50);
    digitalWrite(13, LOW);
    delay(50);
    digitalWrite(12, LOW);
    delay(50);
    digitalWrite(10, LOW);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    digitalWrite(8, LOW);
    delay(50);
    digitalWrite(7, LOW);
    delay(50);
    digitalWrite(6, LOW);
    delay(50);
    digitalWrite(5, LOW);
    delay(50);
    digitalWrite(4, LOW);
    delay(50);
    digitalWrite(3, LOW);
    delay(50);
    digitalWrite(2, LOW);
    delay(50);
  
    tempServo.write(160);
    delay(400);  
    tempServo.write(20); 
    delay(400);
                                       
}

void setTempLight(){

  

int roundedTemp = temperature;
if (Blink == ""){
  digitalWrite(2, LOW);
}

digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
digitalWrite(6, LOW);
digitalWrite(7, LOW);
digitalWrite(8, LOW);
digitalWrite(9, LOW);
digitalWrite(10, LOW);
digitalWrite(12, LOW);


if (roundedTemp < 17 && roundedTemp != 0 && lightStatus != "OFF"){

  if (Blink == "")

 {
   Blink = "LL";
 }
 
}


if (roundedTemp == 17 && lightStatus != "OFF"){
  digitalWrite(2, HIGH);
  Blink = "";
}
if (roundedTemp == 18 && lightStatus != "OFF"){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  Blink = "";
}
if (roundedTemp == 19 && lightStatus != "OFF"){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  Blink = "";
}
if (roundedTemp == 20 && lightStatus != "OFF"){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  Blink = "";
}
if (roundedTemp == 21 && lightStatus != "OFF"){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  Blink = "";
}
if (roundedTemp == 22 && lightStatus != "OFF"){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  Blink = "";
}
if (roundedTemp == 23 && lightStatus != "OFF"){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  Blink = "";
}
if (roundedTemp == 24 && lightStatus != "OFF"){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  Blink = "";
}
if (roundedTemp == 25 && lightStatus != "OFF"){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  Blink = "";
}
if (roundedTemp == 26 && lightStatus != "OFF"){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(12, HIGH);
  Blink = "";
}
if (roundedTemp > 26 && lightStatus != "OFF"){
  if (Blink == ""){
    Blink = "HL";
  }
  
}
}



