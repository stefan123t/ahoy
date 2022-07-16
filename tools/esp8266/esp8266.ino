//-----------------------------------------------------------------------------
// 2022 Ahoy, https://www.mikrocontroller.net/topic/525778
// Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//-----------------------------------------------------------------------------

#include "Arduino.h"

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>

#include <ESP8266HTTPUpdateServer.h>
#include "app.h"
#include "config.h"

//SD_logger
#include <SPI.h>
#include <SD.h>
const int chipSelect = 16; //SD-CS pin GPIO16 = D0

app myApp;

//-----------------------------------------------------------------------------
void setup() {
  myApp.setup(WIFI_TRY_CONNECT_TIME);

  // TODO: move to HmRadio
  attachInterrupt(digitalPinToInterrupt(myApp.getIrqPin()), handleIntr, FALLING);

  if (!SD.begin(chipSelect)) {
    Serial.println("SD card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("SD card initialized.");

}


//-----------------------------------------------------------------------------
void loop() {
  myApp.loop();

  
}


//-----------------------------------------------------------------------------
ICACHE_RAM_ATTR void handleIntr(void) {
  myApp.handleIntr();
}
