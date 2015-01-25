#include <dht.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
Ein Pixel hat 8 x 6 bei Schriftgröße 1
Ein Pixel hat 16 x 12 bei Schriftgröße 2
*/

dht DHT;
#define DHT22_PIN 5

#define OLED_RESET 4 // not used / nicht genutzt bei diesem Display
Adafruit_SSD1306 display(OLED_RESET);

float temperature;
float humidity;


void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop()
{
  read_DHT();
  display_data();
  delay(5000);  
}

void read_DHT()
{
  int chk = DHT.read22(DHT22_PIN);
  temperature = DHT.temperature;
  humidity = DHT.humidity;
}

void display_data()
{
  /*
Ein Pixel hat 8 x 6 bei Schriftgröße 1
Ein Pixel hat 16 x 12 bei Schriftgröße 2
*/
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(34,0);
  display.println("Wohnzimmer");
  display.setTextSize(1);
  display.setCursor(0,30);
  display.print("TEMP(");
  display.write(247);
  display.print("C):");
  display.setTextSize(2);
  int posT = 80; 
    if (temperature < 0.0) { 
      if (temperature <= -10.0)  { 
        posT -= 12; 
      }
    }  else if (temperature < 10.0) { 
        posT += 12; 
      }
  display.setCursor(posT,30);
  display.print(temperature,1);
  display.setTextSize(1);
  display.setCursor(0,50);
  display.print("HUM(%):");
  display.setTextSize(2);
  int posH = 92; 
      if (humidity >= 99.5){
      }
      else if (humidity >= 9.5 && humidity < 99.5) { 
          posH += 12; 
      } 
      else { 
          posH += 24;
        }      
  display.setCursor(posH,50);
  display.print(humidity,0);
  display.setTextSize(1);
  display.setCursor(0,16);
  display.print("CLIMA:");
  display.setCursor(1,22);
  display.print("---------------------");
  if (humidity >= 40.0 && humidity <= 60.0 && temperature >= 17.0 && temperature <= 23.0) {
    display.setCursor(43,16);
    display.print("Optimal");
  }
  else if (humidity < 40.0) {
    display.setCursor(68,16);
    display.print("Zu trocken");
  }
  else if (humidity > 60.0) {
    display.setCursor(74,16);
    display.print("Zu feucht");
  }
  else if (temperature > 23.0) {
    display.setCursor(86,16);
    display.print("Zu warm");
  }
  else if (temperature < 17.0) {
  display.setCursor(86,16);
  display.print("Zu kalt");
  }
  display.display();
}

