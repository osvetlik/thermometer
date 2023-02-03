#include <WiFi.h>
#include <DHT.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeSans24pt7b.h>

#include "cfg.h"

#define DHTPIN 15

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=5*/ 5, /*DC=*/ 2, /*RST=*/ -1, /*BUSY=*/ 22));
GxEPD2_BW<GxEPD2_290_BS, GxEPD2_290_BS::HEIGHT> display(GxEPD2_290_BS(/*CS=5*/ SS, /*DC=*/ 22, /*RST=*/ 21, /*BUSY=*/ 4));

const char* TEMPERATURE_FORMAT = "%.1f C";
const char* HUMIDITY_FORMAT = "%.0f%%";
uint16_t TEMPERATURE_DISPLAY_CENTER_X;
uint16_t TEMPERATURE_DISPLAY_CENTER_Y;
uint16_t HUMIDITY_DISPLAY_CENTER_X;
uint16_t HUMIDITY_DISPLAY_CENTER_Y;

void setup() {
  Serial.begin(115200);
  // connectToWiFi();

  dht.begin();
  display.init();
  display.setRotation(1);
  display.setFont(&FreeSans24pt7b);
  display.setTextColor(0, 1);
  display.setFullWindow();
  display.fillScreen(1);
  display.display();

  TEMPERATURE_DISPLAY_CENTER_X = display.width() / 4;
  TEMPERATURE_DISPLAY_CENTER_Y = display.height() / 2;

  HUMIDITY_DISPLAY_CENTER_X = display.width() * 3 / 4;
  HUMIDITY_DISPLAY_CENTER_Y = display.height() / 2;
}

void loop() {
  char humidityStr[20];
  char temperatureStr[20];
  char heatIndexStr[20];

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();
  // Compute heat index in Celsius (isFahreheit = false)
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);

  sprintf(humidityStr, HUMIDITY_FORMAT, humidity);
  sprintf(temperatureStr, TEMPERATURE_FORMAT, temperature);
  sprintf(heatIndexStr, TEMPERATURE_FORMAT, heatIndex);

  display.fillRect(0, 0, display.width(), display.height(), 1);

  displayValue(TEMPERATURE_DISPLAY_CENTER_X, TEMPERATURE_DISPLAY_CENTER_Y, temperatureStr);
  displayValue(HUMIDITY_DISPLAY_CENTER_X, HUMIDITY_DISPLAY_CENTER_Y, humidityStr);

  display.displayWindow(0, 0, display.width(), display.height());

  delay(2000);
}

void displayValue(uint16_t centerX, uint16_t centerY, char* text) {
  Serial.printf("displayValue(%d, %d, '%s')\n", centerX, centerY, text);
  int16_t textBoundX, textBoundY;
  uint16_t textBoundWidth, textBoundHeight;

  display.getTextBounds(text, 0, 0, &textBoundX, &textBoundY, &textBoundWidth, &textBoundHeight);
  uint16_t x = centerX - (textBoundWidth - textBoundX) / 2;
  uint16_t y = centerY + textBoundHeight / 2;

  Serial.printf("x: %d, y: %d\n", x, y);

  // display.fillRect(x, y - textBoundHeight, textBoundWidth - textBoundX, textBoundHeight - textBoundY, 1);
  display.setCursor(x, y);
  display.print(text);
}

void connectToWiFi() {
  Serial.print(F("Connecting to WiFi .."));
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

// void helloWorldNotPaged() {
//   Serial.println(F("Trying the display."));
  // center the bounding box by transposition of the origin:
  // uint16_t x = ((display.width() - tbw) / 2) - tbx;
  // uint16_t y = ((display.height() - tbh) / 2) - tby;
  // display.setFullWindow();
  // display.fillScreen(GxEPD_WHITE);
  // display.fillRect(0, y - tbh, display.width(), tbh, GxEPD_WHITE);
  // display.setCursor(x, y);
  // display.print(HelloWorld);
  // display.displayWindow(0, y - tbh, display.width(), tbh);
  // display.display(true);
//   Serial.println(F("Display end."));
// }

// void helloWorld()
// {
//   Serial.println(F("Trying the display."));
  // center the bounding box by transposition of the origin:
//   uint16_t x = ((display.width() - tbw) / 2) - tbx;
//   uint16_t y = ((display.height() - tbh) / 2) - tby;
//   display.setFullWindow();
//   display.firstPage();
//   int i = 0;
//   do
//   {
//     display.fillScreen(GxEPD_WHITE);
//     display.setCursor(x, y);
//     display.print(HelloWorld);
//     Serial.printf("Display loop %d\n", i++);
//   }
//   while (display.nextPage());
//   Serial.println(F("Display end."));
//   display.hibernate();
// }
