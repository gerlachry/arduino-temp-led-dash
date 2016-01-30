  // Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

//#include "DHT.h"

//#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
//DHT dht(DHTPIN, DHTTYPE);

int baselineTempF = 65;
int maxTempF = 75;
int ledCount = 10;
int ledPins[] = {4,5,6,7,8,9,10,11,12,13};
int alarmPin = 2;

void setup() {
  Serial.begin(9600);
  Serial.println("DHT22 Temperature LED bars!");

  //dht.begin();
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
  pinMode(alarmPin, OUTPUT);
  //initialize();
}

void loop() {
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);
 float temperature = getVoltage(0);  //getting the voltage reading from the temperature sensor
 temperature = (((temperature - .5) * 100)*1.8)+32;          //converting from 10 mv per degree wit 500 mV offset
                                                  //to degrees ((volatge - 500mV) times 100)
 Serial.println(temperature);                     //printing the result
 delay(5000);  

  //map temp to bargraph LED level
  int ledLevel = map(temperature, baselineTempF, maxTempF, 0, ledCount);
  Serial.print("ledLevel : ");
  Serial.println(ledLevel);
  //output LEDs
  for (int thisLed = 0; thisLed < ledCount; thisLed++){
    if (thisLed < ledLevel){
      digitalWrite(ledPins[thisLed], HIGH);
    } else {
      digitalWrite(ledPins[thisLed], LOW);
    }
  }
  //If temperature value is out of range, sound an alarm
  if(temperature > maxTempF)
  {
    Serial.println("temp too hot!");
    tone(alarmPin,1760,1000);
  }
  if(temperature < baselineTempF)
  {
    Serial.println("temp too low!");
    tone(alarmPin,440,1000);
  }
  delay(5000);
  
}

float getVoltage(int pin){
 return (analogRead(pin) * .004882814); //converting from a 0 to 1023 digital range
                                        // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}

void initialize()
{
  int delay_val=50;
  int i=0,n=0; 
  
  while(i < 14 && n==0)
  {
    digitalWrite(ledPins[i], HIGH);   // set the LED on
    delay(delay_val);              // wait for a second
    i=i+1;
    if(i==14)
    {
      n=1;
    }

  }

  i=0;
  
  while(i<14 && n==1)
  {
    digitalWrite(ledPins[i], LOW);   // set the LED off
    delay(delay_val); 
    i=i+1; 
    if(i==14)
    {
      n=0;
    }
  }
  

}

