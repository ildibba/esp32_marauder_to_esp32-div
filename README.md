
Edit esp32_marauder.ino ,modify the file like this 

/* FLASH SETTINGS
Board: LOLIN D32
Flash Frequency: 80MHz
Partition Scheme: Minimal SPIFFS
https://www.online-utility.org/image/convert/to/XBM
*/

#include "configs.h"

#ifndef HAS_SCREEN
  #define MenuFunctions_h
  #define Display_h
#endif

#include <WiFi.h>
#include "EvilPortal.h"
#include <Wire.h>
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include <Arduino.h>



///////////////////////////////////////////////////////////////

//#include <Wire.h>
#include <PCF8574.h>
#include "Switches.h"

// Indirizzo I2C del PCF8574
#define PCF_ADDRESS 0x20
PCF8574 pcf(PCF_ADDRESS);

// Pin PCF8574
#define BTN_UP     6
#define BTN_DOWN   3
#define BTN_LEFT   4
#define BTN_RIGHT  5
#define BTN_SELECT 7

// Pin virtuali fisici
#define U_BTN 36
#define D_BTN 35
#define L_BTN 13
#define R_BTN 39
#define C_BTN 34

// Variabile temporanea per leggere lo stato dei pin
uint8_t pcf_state = 0;
static inline uint8_t pcf_read_port() { Wire.requestFrom(PCF_ADDRESS, 1); return Wire.read(); }

// Funzioni di lettura usando read8()
bool readUBtn() { pcf_state = pcf_read_port(); return !(pcf_state & (1 << BTN_UP)); }
bool readDBtn() { pcf_state = pcf_read_port(); return !(pcf_state & (1 << BTN_DOWN)); }
bool readLBtn() { pcf_state = pcf_read_port(); return !(pcf_state & (1 << BTN_LEFT)); }
bool readRBtn() { pcf_state = pcf_read_port(); return !(pcf_state & (1 << BTN_RIGHT)); }
bool readCBtn() { pcf_state = pcf_read_port(); return !(pcf_state & (1 << BTN_SELECT)); }



// Creazione bottoni virtuali
Switches u_btn(readUBtn, 1500);  // 1500 tempo di pressione pulsanti
Switches d_btn(readDBtn, 1500);
Switches l_btn(readLBtn, 1500);
Switches r_btn(readRBtn, 1500);
Switches c_btn(readCBtn, 3000);



/////////////////////////////////////////////////////////////////
.
.
.
.
. 

void setup()
{

//////////////////////////////////////////////////////////

 Wire.begin(21, 22); // SDA=21, SCL=22
 pcf.begin();


///////////////////////////////////////////////////////////
.
.
.
in congig.h

change 


#ifdef MARAUDER_V7
      #define SD_CS 5
      #define SD_SCK  18
      #define SD_MISO 19
      #define SD_MOSI 23
    #endif
    
replace Switches.cpp and Switches.h
add library pcf8574

compile good luck
