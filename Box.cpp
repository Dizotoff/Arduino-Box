#include <dht.h>
#define SENSOR_PIN A1
#include <RTC.h>
RTC    time;
 
 
// Create sensor object
DHT sensor = DHT();
int Relay1 = 4;
int Relay2 = 2;
 
void setup()
{
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  delay(300);
    Serial.begin(9600);
         time.begin(RTC_DS3231);
          pinMode(Relay1, OUTPUT);    
pinMode(Relay2, OUTPUT);
 
    Serial.begin(9600);
 
    
    sensor.attach(A0);
    
    delay(4000);
   
}
 
void loop()
{
 
// Set working time of vents and lights from 00 to 6 pm
  if (time.Hours>=00  && time.Hours<18 )
  {
// Check if relays is working
if (digitalRead(Relay1) == HIGH && digitalRead(Relay2) == HIGH)
     {
   digitalWrite(Relay1, LOW);
  digitalWrite(Relay2, LOW);
     }
}
    else
  {
     if (digitalRead(Relay1) == LOW && digitalRead(Relay2) == LOW)
     {
   digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
     }
}
 
             
 
      Serial.println(time.gettime("d-m-Y, H:i:s, D")); // выводим время
     
   
  delay(1000);
    int val = analogRead(SENSOR_PIN);
    Serial.println(val);
 
    // method update gives current changes
    sensor.update();
 
    switch (sensor.getLastError())
    {
        case DHT_ERROR_OK:
            char msg[128];
            sprintf(msg, "Temperature = %dC Humidity = %d%%",
                    sensor.getTemperatureInt(), sensor.getHumidityInt());
            Serial.println(msg);
            break;
        case DHT_ERROR_START_FAILED_1:
            Serial.println("Error: start failed (stage 1)");
            break;
        case DHT_ERROR_START_FAILED_2:
            Serial.println("Error: start failed (stage 2)");
            break;
        case DHT_ERROR_READ_TIMEOUT:
            Serial.println("Error: read timeout");
            break;
        case DHT_ERROR_CHECKSUM_FAILURE:
            Serial.println("Error: checksum error");
            break;
    }
 
   
}