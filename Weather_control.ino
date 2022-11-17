//include libraries for sensor
#include<DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
//include libraries for LCD display
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


//soil moisture pins
int soil_moist_pin= A1;
int output_value;

//LED Sensor pins
int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor
int THRES = 450; // Condition for light to turn on

// LED PIN 
int lightPin = 12;

// Constants for the motor
const int IN1 = 7;
const int IN2 = 8;
const int ENA = 5;
const int SPEED = 200;
// const int ON = 100; // This will be replaced by the water moisture value

//Liquid Crystal display info
LiquidCrystal_I2C lcd(0x27,2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // set the LCD address to 0x27 for a 16 chars and 2 line display
DHT mydht (DHTPIN,DHTTYPE);


void setup() {
  //start ld screen
  Serial.begin(9600);

  //Light pin set-up
  pinMode(lightPin, OUTPUT);

  //Pin mode set-up for motor
  pinMode (IN1, OUTPUT); 
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);
  
  // The LCD screen
  lcd.begin(20,4);                   

  lcd.backlight();

  mydht.begin();
}

void loop() {

  //Light sensor pin info
  sensorValue = analogRead(sensorPin); // read the value from the sensor
   Serial.println(sensorValue); //prints the values coming from the sensor on the screen
  if(sensorValue < THRES){
    digitalWrite(lightPin, HIGH);
  } else {
    digitalWrite(lightPin, LOW);
  }
  // Maybe remove and include only at the end
  //delay(100);
  
  //soil moisture data
   output_value = analogRead(soil_moist_pin);
   output_value = map(output_value,550,0,0,100);

   //control speed for motor
  analogWrite(ENA, SPEED);
  //control direction 
  if(output_value < 0){
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
   } else {
    digitalWrite(IN1, LOW);
   }
   
// put your main code here, to run repeatedly:
int hum = mydht.readHumidity();
int temp = mydht.readTemperature();
lcd.clear();
lcd.setCursor(8,0);
lcd.print("DATA");
lcd.setCursor(4,1);
lcd.print("TEMPERATURE:");
lcd.print(temp);
lcd.print("C");
lcd.setCursor(4,2);
lcd.print("HUMIDITY:");
lcd.print(hum);
lcd.print("%");
lcd.setCursor(2,3);
lcd.print("SOIL MOISTURE:");
lcd.print(output_value);
lcd.print("%");

delay(100);
}
