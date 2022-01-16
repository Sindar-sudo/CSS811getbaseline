#include "20font.h"
#include "icons.h"

// The font names are arrays references, thus must NOT be in quotes ""
#define AA_FONT_SMALL Bold20

#include <SPI.h>
#include <Wire.h>
#include <TFT_eSPI.h>       // Hardware-specific library
#include "Adafruit_CCS811.h"

#include <DHT.h>
#define DHTPIN 25     // what pin DHT22 is connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor

Adafruit_CCS811 ccs; //co2&voc sensor

float hum;
float temp;
uint16_t ccs811Baseline;

TFT_eSPI tft = TFT_eSPI();


void setup(void) {
  dht.begin();
  Serial.begin(9600); 
  tft.begin();
  tft.invertDisplay(1);
  tft.setRotation(1); //screen rotation
  if(!ccs.begin()){
    while(1);
  }
  // Wait for the sensor to be ready
  while(!ccs.available()); 
  tft.loadFont(AA_FONT_SMALL); //loads the custom font
}
  void loop() {
    tft.fillScreen(0x0000);
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    ccs.setEnvironmentalData(temp, hum); //temperature and humidity info for co2&voc compensation
    ccs811Baseline = ccs.getBaseline();
    Serial.println(ccs811Baseline, HEX);
    tft.setCursor(10, 10); //sets cursor to write new value
    tft.print("Baseline: ");
    tft.print(ccs811Baseline, HEX); // ccs811Baseline
    delay(5000);
  }
