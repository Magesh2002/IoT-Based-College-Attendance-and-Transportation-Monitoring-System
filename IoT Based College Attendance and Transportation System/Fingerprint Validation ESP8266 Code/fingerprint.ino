#include <Adafruit_Fingerprint.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFiClient.h> 
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <TinyGPS++.h> 
float lat = 0,lon = 0; // create variable for latitude and longitude object  
//#include <Adafruit_GFX.h>          //https://github.com/adafruit/Adafruit-GFX-Library
//#include <Adafruit_SSD1306.h>      //https://github.com/adafruit/Adafruit_SSD1306

//************************************************************************
//Fingerprint scanner Pins
#define Finger_Rx 14 //D1
#define Finger_Tx 12 //D2
#define CMDBUFFER_SIZE 32
#define FORCE_SENSOR_PIN A0
const int buzzer = 02;
TinyGPSPlus gps;
// Declaration for SSD1306 display connected using software I2C
//#define SCREEN_WIDTH 128 // OLED display width, in pixels`
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//************************************************************************
SoftwareSerial mySerial(Finger_Rx, Finger_Tx);

SoftwareSerial gpsSerial(4,5);//rx,tx 

//#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
//// For UNO and others without hardware serial, we must use software serial...
//// pin #2 is IN from sensor (GREEN wire)
//// pin #3 is OUT from arduino  (WHITE wire)
//// Set up the serial port to use softwareserial..
//SoftwareSerial mySerial(2, 3);
//
//#else
//// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
//// #0 is green wire, #1 is white
//#define mySerial Serial1
//
//#endif


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
/* Set these to your desired credentials. */
const char *ssid = "VIVO V27";  //ENTER YOUR WIFI SETTINGS
const char *password = "Magesh@2002";

WiFiClient wifiClient;
//TinyGPS gps; // create gps object 

//************************************************************************
String postData ; // post array that will be send to the website
String link = "http://projectoutput.co.in/smartbus/ajax.php"; //computer IP or the server domain
String link2 = "http://projectoutput.co.in/smartbus/ajax2.php"; //computer IP or the server domain
String link3 = "http://projectoutput.co.in/smartbus/ajax3.php"; //computer IP or the server domain
String link4 = "http://projectoutput.co.in/smartbus/ajax4.php"; //computer IP or the server domain
//*************************Biometric Icons*********************************
#define Wifi_start_width 54
#define Wifi_start_height 49
const uint8_t PROGMEM Wifi_start_bits[] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x1f,0xf0,0x00,0x00,0x00
,0x00,0x03,0xff,0xff,0x80,0x00,0x00
,0x00,0x1f,0xf0,0x1f,0xf0,0x00,0x00
,0x00,0x7e,0x00,0x00,0xfc,0x00,0x00
,0x01,0xf0,0x00,0x00,0x1f,0x00,0x00
,0x03,0xc0,0x00,0x00,0x07,0xc0,0x00
,0x0f,0x00,0x00,0x00,0x01,0xe0,0x00
,0x1c,0x00,0x00,0x00,0x00,0x70,0x00
,0x38,0x00,0x07,0xc0,0x00,0x38,0x00
,0x70,0x00,0xff,0xfe,0x00,0x1e,0x00
,0xe0,0x03,0xfc,0x7f,0xc0,0x0e,0x00
,0x00,0x1f,0x80,0x03,0xf0,0x00,0x00
,0x00,0x3c,0x00,0x00,0x78,0x00,0x00
,0x00,0xf0,0x00,0x00,0x1c,0x00,0x00
,0x01,0xe0,0x00,0x00,0x0c,0x00,0x00
,0x03,0x80,0x00,0x00,0x00,0x00,0x00
,0x03,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x3f,0xf8,0x07,0x1e,0x00
,0x00,0x00,0xff,0xfe,0x1f,0xbf,0x80
,0x00,0x03,0xe0,0x04,0x7f,0xff,0xc0
,0x00,0x07,0x80,0x00,0xff,0xff,0xe0
,0x00,0x0e,0x00,0x00,0xff,0xff,0xe0
,0x00,0x0c,0x00,0x00,0x7f,0xff,0xc0
,0x00,0x00,0x00,0x00,0xfe,0x07,0xe0
,0x00,0x00,0x00,0x03,0xf8,0x03,0xf8
,0x00,0x00,0x07,0xe7,0xf9,0xf1,0xfc
,0x00,0x00,0x1f,0xe7,0xf1,0xf9,0xfc
,0x00,0x00,0x1f,0xe7,0xf3,0xf9,0xfc
,0x00,0x00,0x3f,0xe7,0xf3,0xf9,0xfc
,0x00,0x00,0x3f,0xe7,0xf1,0xf1,0xfc
,0x00,0x00,0x3f,0xe3,0xf8,0xe3,0xfc
,0x00,0x00,0x3f,0xf3,0xfc,0x07,0xf8
,0x00,0x00,0x1f,0xf0,0x7f,0x0f,0xc0
,0x00,0x00,0x0f,0xe0,0x7f,0xff,0xe0
,0x00,0x00,0x07,0xc0,0xff,0xff,0xe0
,0x00,0x00,0x00,0x00,0x7f,0xff,0xe0
,0x00,0x00,0x00,0x00,0x3f,0xff,0x80
,0x00,0x00,0x00,0x00,0x1f,0xbf,0x00
,0x00,0x00,0x00,0x00,0x03,0x18,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
#define Wifi_connected_width 63
#define Wifi_connected_height 49
const uint8_t PROGMEM Wifi_connected_bits[] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x03,0xff,0xff,0x80,0x00,0x00
,0x00,0x00,0x3f,0xff,0xff,0xf8,0x00,0x00
,0x00,0x01,0xff,0xff,0xff,0xff,0x00,0x00
,0x00,0x0f,0xff,0xff,0xff,0xff,0xe0,0x00
,0x00,0x3f,0xff,0xc0,0x07,0xff,0xf8,0x00
,0x00,0xff,0xf8,0x00,0x00,0x3f,0xfe,0x00
,0x03,0xff,0x80,0x00,0x00,0x03,0xff,0x80
,0x07,0xfe,0x00,0x00,0x00,0x00,0xff,0xc0
,0x1f,0xf8,0x00,0x00,0x00,0x00,0x3f,0xf0
,0x3f,0xe0,0x01,0xff,0xff,0x00,0x0f,0xf8
,0x7f,0x80,0x0f,0xff,0xff,0xe0,0x03,0xfc
,0xff,0x00,0x7f,0xff,0xff,0xfc,0x01,0xfe
,0xfc,0x01,0xff,0xff,0xff,0xff,0x00,0x7e
,0x78,0x07,0xff,0xc0,0x07,0xff,0xc0,0x3c
,0x00,0x0f,0xfc,0x00,0x00,0x7f,0xe0,0x00
,0x00,0x1f,0xf0,0x00,0x00,0x1f,0xf0,0x00
,0x00,0x3f,0xc0,0x00,0x00,0x07,0xf8,0x00
,0x00,0x7f,0x00,0x01,0x00,0x01,0xfc,0x00
,0x00,0x7e,0x00,0x7f,0xfc,0x00,0xfc,0x00
,0x00,0x3c,0x03,0xff,0xff,0x80,0x78,0x00
,0x00,0x00,0x07,0xff,0xff,0xc0,0x00,0x00
,0x00,0x00,0x1f,0xff,0xff,0xf0,0x00,0x00
,0x00,0x00,0x3f,0xf0,0x1f,0xf8,0x00,0x00
,0x00,0x00,0x3f,0x80,0x03,0xf8,0x00,0x00
,0x00,0x00,0x3f,0x00,0x01,0xf8,0x00,0x00
,0x00,0x00,0x1c,0x00,0x00,0x70,0x00,0x00
,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0xe0,0x00,0x00,0x00
,0x00,0x00,0x00,0x1f,0xf0,0x00,0x00,0x00
,0x00,0x00,0x00,0x3f,0xf8,0x00,0x00,0x00
,0x00,0x00,0x00,0x3f,0xf8,0x00,0x00,0x00
,0x00,0x00,0x00,0x3f,0xf8,0x00,0x00,0x00
,0x00,0x00,0x00,0x3f,0xf8,0x00,0x00,0x00
,0x00,0x00,0x00,0x1f,0xf0,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0xe0,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
#define FinPr_start_width 64
#define FinPr_start_height 64
const uint8_t PROGMEM FinPr_start_bits[] = {
  0x00,0x00,0x00,0x1f,0xe0,0x00,0x00,0x00
,0x00,0x00,0x01,0xff,0xfe,0x00,0x00,0x00
,0x00,0x00,0x03,0xff,0xff,0x80,0x00,0x00
,0x00,0x00,0x0f,0xc0,0x0f,0xe0,0x00,0x00
,0x00,0x00,0x1f,0x00,0x01,0xf8,0x00,0x00
,0x00,0x00,0x3c,0x00,0x00,0x7c,0x00,0x00
,0x00,0x00,0x78,0x00,0x00,0x3e,0x00,0x00
,0x00,0x00,0xf0,0x3f,0xf8,0x0f,0x00,0x00
,0x00,0x01,0xe0,0xff,0xfe,0x07,0x80,0x00
,0x00,0x03,0xc3,0xff,0xff,0x03,0x80,0x00
,0x00,0x03,0x87,0xc0,0x07,0xc3,0xc0,0x00
,0x00,0x07,0x0f,0x00,0x03,0xe1,0xc0,0x00
,0x00,0x0f,0x0e,0x00,0x00,0xe0,0xe0,0x00
,0x00,0x0e,0x1c,0x00,0x00,0xf0,0xe0,0x00
,0x00,0x0c,0x3c,0x1f,0xe0,0x70,0xe0,0x00
,0x00,0x00,0x38,0x3f,0xf0,0x38,0x70,0x00
,0x00,0x00,0x78,0x78,0xf8,0x38,0x70,0x00
,0x00,0x00,0x70,0x70,0x3c,0x18,0x70,0x00
,0x00,0x00,0xe0,0xe0,0x1e,0x1c,0x70,0x00
,0x00,0x03,0xe1,0xe0,0x0e,0x1c,0x70,0x00
,0x00,0x0f,0xc1,0xc3,0x0e,0x1c,0x70,0x00
,0x00,0x3f,0x03,0xc3,0x8e,0x1c,0x70,0x00
,0x00,0x3e,0x03,0x87,0x0e,0x1c,0x70,0x00
,0x00,0x30,0x07,0x07,0x0e,0x18,0xe0,0x00
,0x00,0x00,0x0e,0x0e,0x0e,0x38,0xe0,0x00
,0x00,0x00,0x3e,0x1e,0x1e,0x38,0xe0,0x00
,0x00,0x00,0xf8,0x1c,0x1c,0x38,0xe0,0x00
,0x00,0x03,0xf0,0x38,0x3c,0x38,0xe0,0x00
,0x00,0x3f,0xc0,0xf8,0x78,0x38,0xe0,0x00
,0x00,0x7f,0x01,0xf0,0x70,0x38,0xf0,0x00
,0x00,0x78,0x03,0xe0,0xe0,0x38,0x70,0x00
,0x00,0x00,0x0f,0x81,0xe0,0x38,0x7c,0x00
,0x00,0x00,0x3f,0x03,0xc0,0x38,0x3e,0x00
,0x00,0x00,0xfc,0x0f,0x80,0x38,0x1e,0x00
,0x00,0x07,0xf0,0x1f,0x1c,0x1c,0x04,0x00
,0x00,0x3f,0xc0,0x3e,0x3f,0x1e,0x00,0x00
,0x00,0x7f,0x00,0xf8,0x7f,0x0f,0x00,0x00
,0x00,0x38,0x01,0xf0,0xf7,0x07,0xc0,0x00
,0x00,0x00,0x07,0xe1,0xe3,0x83,0xf8,0x00
,0x00,0x00,0x3f,0x87,0xc3,0xc0,0xfc,0x00
,0x00,0x01,0xfe,0x0f,0x81,0xe0,0x3c,0x00
,0x00,0x0f,0xf8,0x1f,0x00,0xf0,0x00,0x00
,0x00,0x1f,0xc0,0x7c,0x00,0x7c,0x00,0x00
,0x00,0x1e,0x01,0xf8,0x00,0x3f,0x00,0x00
,0x00,0x00,0x07,0xe0,0x78,0x0f,0xc0,0x00
,0x00,0x00,0x3f,0x81,0xfe,0x07,0xf0,0x00
,0x00,0x01,0xfe,0x07,0xff,0x01,0xf0,0x00
,0x00,0x07,0xf8,0x0f,0x87,0x80,0x30,0x00
,0x00,0x07,0xc0,0x3f,0x03,0xe0,0x00,0x00
,0x00,0x06,0x00,0xfc,0x01,0xf8,0x00,0x00
,0x00,0x00,0x03,0xf0,0x00,0x7e,0x00,0x00
,0x00,0x00,0x0f,0xc0,0x00,0x3f,0x80,0x00
,0x00,0x00,0x7f,0x00,0xf8,0x0f,0x80,0x00
,0x00,0x00,0xfc,0x03,0xfe,0x01,0x80,0x00
,0x00,0x00,0xf0,0x1f,0xff,0x80,0x00,0x00
,0x00,0x00,0x00,0x7f,0x07,0xe0,0x00,0x00
,0x00,0x00,0x00,0xfc,0x03,0xf8,0x00,0x00
,0x00,0x00,0x03,0xf0,0x00,0x78,0x00,0x00
,0x00,0x00,0x0f,0xc0,0x00,0x18,0x00,0x00
,0x00,0x00,0x0f,0x01,0xf8,0x00,0x00,0x00
,0x00,0x00,0x00,0x07,0xfe,0x00,0x00,0x00
,0x00,0x00,0x00,0x1f,0xfe,0x00,0x00,0x00
,0x00,0x00,0x00,0x1e,0x0e,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00
};
//---------------------------------------------------------------
#define FinPr_valid_width 64
#define FinPr_valid_height 64
const uint8_t PROGMEM FinPr_valid_bits[] = {
  0x00,0x00,0x03,0xfe,0x00,0x00,0x00,0x00
,0x00,0x00,0x1f,0xff,0xe0,0x00,0x00,0x00
,0x00,0x00,0x7f,0xff,0xf8,0x00,0x00,0x00
,0x00,0x00,0xfc,0x00,0xfe,0x00,0x00,0x00
,0x00,0x03,0xe0,0x00,0x1f,0x00,0x00,0x00
,0x00,0x07,0xc0,0x00,0x07,0x80,0x00,0x00
,0x00,0x0f,0x80,0x00,0x03,0xe0,0x00,0x00
,0x00,0x0e,0x03,0xff,0x01,0xe0,0x00,0x00
,0x00,0x1c,0x1f,0xff,0xe0,0xf0,0x00,0x00
,0x00,0x3c,0x3f,0xff,0xf0,0x78,0x00,0x00
,0x00,0x78,0x7c,0x00,0xf8,0x3c,0x00,0x00
,0x00,0x70,0xf0,0x00,0x3c,0x1c,0x00,0x00
,0x00,0xe1,0xe0,0x00,0x1e,0x1c,0x00,0x00
,0x00,0xe1,0xc0,0x00,0x0f,0x0e,0x00,0x00
,0x00,0xc3,0x81,0xfc,0x07,0x0e,0x00,0x00
,0x00,0x03,0x83,0xff,0x07,0x8e,0x00,0x00
,0x00,0x07,0x07,0x8f,0x83,0x87,0x00,0x00
,0x00,0x0f,0x0f,0x03,0xc3,0x87,0x00,0x00
,0x00,0x1e,0x0e,0x01,0xc3,0x87,0x00,0x00
,0x00,0x3c,0x1c,0x00,0xe1,0x87,0x00,0x00
,0x00,0xf8,0x1c,0x30,0xe1,0x87,0x00,0x00
,0x07,0xf0,0x38,0x70,0xe1,0x86,0x00,0x00
,0x07,0xc0,0x78,0x70,0xe3,0x8e,0x00,0x00
,0x02,0x00,0xf0,0xf0,0xe3,0x8e,0x00,0x00
,0x00,0x01,0xe0,0xe0,0xe3,0x8e,0x00,0x00
,0x00,0x03,0xc1,0xe1,0xc3,0x8e,0x00,0x00
,0x00,0x0f,0x83,0xc3,0xc3,0x8e,0x00,0x00
,0x00,0x7f,0x07,0x83,0x83,0x0e,0x00,0x00
,0x07,0xfc,0x0f,0x07,0x83,0x0e,0x00,0x00
,0x07,0xf0,0x1e,0x0f,0x03,0x0e,0x00,0x00
,0x07,0x80,0x7c,0x1e,0x03,0x07,0x00,0x00
,0x00,0x00,0xf8,0x3c,0x03,0x87,0x80,0x00
,0x00,0x03,0xf0,0x78,0x03,0x83,0xc0,0x00
,0x00,0x1f,0xc0,0xf0,0x02,0x00,0x00,0x00
,0x00,0xff,0x01,0xe1,0xc0,0x0c,0x00,0x00
,0x07,0xfc,0x03,0xc3,0xe1,0xff,0xc0,0x00
,0x07,0xe0,0x0f,0x87,0xc7,0xff,0xf0,0x00
,0x07,0x00,0x3f,0x0f,0x0f,0xff,0xfc,0x00
,0x00,0x00,0x7c,0x3e,0x3f,0xff,0xfe,0x00
,0x00,0x03,0xf8,0x7c,0x3f,0xff,0xff,0x00
,0x00,0x1f,0xe0,0xf0,0x7f,0xff,0xff,0x80
,0x00,0xff,0x83,0xe0,0xff,0xff,0xff,0x80
,0x01,0xfc,0x07,0xc1,0xff,0xff,0xe3,0xc0
,0x01,0xe0,0x1f,0x01,0xff,0xff,0xc3,0xc0
,0x00,0x00,0xfe,0x01,0xff,0xff,0x87,0xe0
,0x00,0x03,0xf8,0x13,0xff,0xff,0x0f,0xe0
,0x00,0x1f,0xe0,0x73,0xff,0xfe,0x1f,0xe0
,0x00,0x7f,0x81,0xf3,0xff,0xfc,0x1f,0xe0
,0x00,0xfc,0x03,0xe3,0xef,0xf8,0x3f,0xe0
,0x00,0x60,0x0f,0xc3,0xc7,0xf0,0x7f,0xe0
,0x00,0x00,0x3f,0x03,0xc3,0xe0,0xff,0xe0
,0x00,0x00,0xfc,0x03,0xc1,0xc1,0xff,0xe0
,0x00,0x07,0xf0,0x13,0xe0,0x83,0xff,0xe0
,0x00,0x0f,0xc0,0x7b,0xf8,0x07,0xff,0xe0
,0x00,0x0f,0x01,0xf9,0xfc,0x0f,0xff,0xc0
,0x00,0x00,0x07,0xf1,0xfe,0x1f,0xff,0xc0
,0x00,0x00,0x1f,0xc0,0xff,0x3f,0xff,0x80
,0x00,0x00,0x7e,0x00,0xff,0xff,0xff,0x80
,0x00,0x00,0xfc,0x00,0x7f,0xff,0xff,0x00
,0x00,0x00,0xf0,0x1f,0x3f,0xff,0xfe,0x00
,0x00,0x00,0x00,0x7f,0x1f,0xff,0xfc,0x00
,0x00,0x00,0x01,0xff,0x8f,0xff,0xf8,0x00
,0x00,0x00,0x03,0xe0,0xe3,0xff,0xe0,0x00
,0x00,0x00,0x01,0x80,0x00,0x7f,0x00,0x00
};
//---------------------------------------------------------------
#define FinPr_invalid_width 64
#define FinPr_invalid_height 64
const uint8_t PROGMEM FinPr_invalid_bits[] = {
  0x00,0x00,0x03,0xfe,0x00,0x00,0x00,0x00
,0x00,0x00,0x1f,0xff,0xe0,0x00,0x00,0x00
,0x00,0x00,0x7f,0xff,0xf8,0x00,0x00,0x00
,0x00,0x00,0xfc,0x00,0xfe,0x00,0x00,0x00
,0x00,0x03,0xe0,0x00,0x1f,0x00,0x00,0x00
,0x00,0x07,0xc0,0x00,0x07,0x80,0x00,0x00
,0x00,0x0f,0x80,0x00,0x03,0xe0,0x00,0x00
,0x00,0x0e,0x03,0xff,0x01,0xe0,0x00,0x00
,0x00,0x1c,0x1f,0xff,0xe0,0xf0,0x00,0x00
,0x00,0x3c,0x3f,0xff,0xf0,0x78,0x00,0x00
,0x00,0x78,0x7c,0x00,0xf8,0x3c,0x00,0x00
,0x00,0x70,0xf0,0x00,0x3c,0x1c,0x00,0x00
,0x00,0xe1,0xe0,0x00,0x1e,0x1c,0x00,0x00
,0x00,0xe1,0xc0,0x00,0x0f,0x0e,0x00,0x00
,0x00,0xc3,0x81,0xfc,0x07,0x0e,0x00,0x00
,0x00,0x03,0x83,0xff,0x07,0x8e,0x00,0x00
,0x00,0x07,0x07,0x8f,0x83,0x87,0x00,0x00
,0x00,0x0f,0x0f,0x03,0xc3,0x87,0x00,0x00
,0x00,0x1e,0x0e,0x01,0xc3,0x87,0x00,0x00
,0x00,0x3c,0x1c,0x00,0xe1,0x87,0x00,0x00
,0x00,0xf8,0x1c,0x30,0xe1,0x87,0x00,0x00
,0x07,0xf0,0x38,0x70,0xe1,0x86,0x00,0x00
,0x07,0xc0,0x78,0x70,0xe3,0x8e,0x00,0x00
,0x02,0x00,0xf0,0xf0,0xe3,0x8e,0x00,0x00
,0x00,0x01,0xe0,0xe0,0xe3,0x8e,0x00,0x00
,0x00,0x03,0xc1,0xe1,0xc3,0x8e,0x00,0x00
,0x00,0x0f,0x83,0xc3,0xc3,0x8e,0x00,0x00
,0x00,0x7f,0x07,0x83,0x83,0x0e,0x00,0x00
,0x07,0xfc,0x0f,0x07,0x83,0x0e,0x00,0x00
,0x07,0xf0,0x1e,0x0f,0x03,0x0e,0x00,0x00
,0x07,0x80,0x7c,0x1e,0x03,0x07,0x00,0x00
,0x00,0x00,0xf8,0x3c,0x03,0x87,0x80,0x00
,0x00,0x03,0xf0,0x78,0x03,0x83,0xc0,0x00
,0x00,0x1f,0xc0,0xf0,0x02,0x00,0x00,0x00
,0x00,0xff,0x01,0xe1,0xc0,0x00,0x00,0x00
,0x07,0xfc,0x03,0xc3,0xe1,0xff,0xc0,0x00
,0x07,0xe0,0x0f,0x87,0xc7,0xff,0xf0,0x00
,0x07,0x00,0x3f,0x0f,0x0f,0xff,0xf8,0x00
,0x00,0x00,0x7c,0x3e,0x1f,0xff,0xfe,0x00
,0x00,0x03,0xf8,0x7c,0x3f,0xff,0xff,0x00
,0x00,0x1f,0xe0,0xf0,0x7f,0xff,0xff,0x00
,0x00,0xff,0x83,0xe0,0xfe,0xff,0xbf,0x80
,0x01,0xfc,0x07,0xc0,0xfc,0x7f,0x1f,0xc0
,0x01,0xe0,0x1f,0x01,0xf8,0x3e,0x0f,0xc0
,0x00,0x00,0xfe,0x01,0xf8,0x1c,0x07,0xe0
,0x00,0x03,0xf8,0x13,0xf8,0x00,0x0f,0xe0
,0x00,0x1f,0xe0,0x73,0xfc,0x00,0x1f,0xe0
,0x00,0x7f,0x81,0xf3,0xfe,0x00,0x3f,0xe0
,0x00,0xfc,0x03,0xe3,0xff,0x00,0x7f,0xe0
,0x00,0x60,0x0f,0xc3,0xff,0x80,0xff,0xe0
,0x00,0x00,0x3f,0x03,0xff,0x00,0x7f,0xe0
,0x00,0x00,0xfc,0x03,0xfe,0x00,0x3f,0xe0
,0x00,0x07,0xf0,0x13,0xfc,0x00,0x1f,0xe0
,0x00,0x0f,0xc0,0x79,0xf8,0x08,0x0f,0xe0
,0x00,0x0f,0x01,0xf9,0xf8,0x1c,0x0f,0xc0
,0x00,0x00,0x07,0xf1,0xfc,0x3e,0x1f,0xc0
,0x00,0x00,0x1f,0xc0,0xfe,0x7f,0x3f,0x80
,0x00,0x00,0x7e,0x00,0xff,0xff,0xff,0x80
,0x00,0x00,0xfc,0x00,0x7f,0xff,0xff,0x00
,0x00,0x00,0xf0,0x1f,0x3f,0xff,0xfe,0x00
,0x00,0x00,0x00,0x7f,0x1f,0xff,0xfc,0x00
,0x00,0x00,0x01,0xff,0x8f,0xff,0xf8,0x00
,0x00,0x00,0x03,0xe0,0xe3,0xff,0xe0,0x00
,0x00,0x00,0x01,0x80,0x00,0x7f,0x00,0x00
};
//---------------------------------------------------------------
#define FinPr_failed_width 64
#define FinPr_failed_height 64
const uint8_t PROGMEM FinPr_failed_bits[] = {
0x00,0x00,0x3f,0xe0,0x00,0x00,0x00,0x00
,0x00,0x01,0xff,0xfe,0x00,0x00,0x00,0x00
,0x00,0x0f,0xc0,0x1f,0x80,0x00,0x00,0x00
,0x00,0x1e,0x00,0x03,0xc0,0x00,0x00,0x00
,0x00,0x78,0x00,0x00,0xf0,0x00,0x00,0x00
,0x00,0xe0,0x00,0x00,0x38,0x00,0x00,0x00
,0x01,0xc0,0x00,0x00,0x1c,0x00,0x00,0x00
,0x03,0x80,0x00,0x00,0x0e,0x00,0x00,0x00
,0x07,0x00,0x7f,0xe0,0x07,0x00,0x00,0x00
,0x06,0x01,0xff,0xf8,0x03,0x00,0x00,0x00
,0x0c,0x03,0xc0,0x3c,0x03,0x80,0x00,0x00
,0x1c,0x0f,0x00,0x0e,0x01,0x80,0x00,0x00
,0x18,0x0c,0x00,0x03,0x00,0xc0,0x00,0x00
,0x18,0x18,0x00,0x01,0x80,0xc0,0x00,0x00
,0x30,0x38,0x00,0x01,0xc0,0xe0,0x00,0x00
,0x30,0x30,0x0f,0x00,0xc0,0x60,0x00,0x00
,0x30,0x30,0x3f,0xc0,0xe0,0x60,0x00,0x00
,0x70,0x60,0x78,0xe0,0x60,0x60,0x00,0x00
,0x60,0x60,0x60,0x60,0x60,0x70,0x00,0x00
,0x60,0x60,0x60,0x60,0x60,0x30,0x00,0x00
,0x60,0x60,0x60,0x60,0x30,0x30,0x00,0x00
,0x60,0x60,0x60,0x30,0x30,0x20,0x00,0x00
,0x60,0x60,0x60,0x30,0x30,0x01,0xe0,0x00
,0x60,0x60,0x60,0x30,0x30,0x0f,0xfc,0x00
,0x60,0x60,0x60,0x30,0x30,0x3f,0xff,0x00
,0x60,0x60,0x60,0x30,0x18,0x78,0x03,0x80
,0x60,0x60,0x60,0x30,0x1c,0x60,0x01,0x80
,0x60,0x60,0x30,0x38,0x0c,0xc0,0x00,0xc0
,0x00,0x60,0x30,0x18,0x00,0xc0,0x00,0xc0
,0x00,0x60,0x30,0x18,0x00,0xc0,0x00,0xc0
,0x00,0xe0,0x30,0x0c,0x01,0xc0,0x00,0xe0
,0x00,0xc0,0x18,0x0e,0x01,0xc0,0x00,0xe0
,0x60,0xc0,0x18,0x07,0x01,0xc0,0x00,0xe0
,0x01,0xc0,0x1c,0x03,0x81,0xc0,0x00,0xe0
,0x01,0x80,0x0c,0x01,0xc1,0xc0,0x00,0xe0
,0x03,0x80,0x0e,0x00,0xf1,0xc0,0x00,0xe0
,0x0f,0x00,0x06,0x00,0x01,0xc0,0x00,0xe0
,0x3e,0x01,0x03,0x00,0x01,0xc0,0x00,0xe0
,0x30,0x03,0x83,0x80,0x1f,0xff,0xff,0xfe
,0x00,0x03,0x81,0xc0,0x3f,0xff,0xff,0xff
,0x00,0x07,0xc0,0xe0,0x30,0x00,0x00,0x03
,0x00,0x0e,0xc0,0x78,0x30,0x00,0x00,0x03
,0x00,0x3c,0x60,0x1e,0x30,0x00,0x00,0x03
,0x00,0x78,0x70,0x0f,0x30,0x00,0x00,0x03
,0x03,0xe0,0x38,0x03,0x30,0x00,0x00,0x03
,0x07,0x80,0x1c,0x00,0x30,0x00,0x00,0x03
,0xc0,0x00,0x0f,0x00,0x30,0x00,0x00,0x03
,0xc0,0x00,0x03,0x80,0x30,0x01,0xe0,0x03
,0x00,0x18,0x01,0xe0,0x30,0x03,0xf0,0x03
,0x00,0x18,0x00,0x7c,0x30,0x07,0x38,0x03
,0x00,0x0c,0x00,0x1f,0x30,0x06,0x18,0x03
,0x18,0x0e,0x00,0x07,0x30,0x06,0x18,0x03
,0x0c,0x07,0x80,0x00,0x30,0x07,0x38,0x03
,0x0e,0x03,0xc0,0x00,0x30,0x03,0x30,0x03
,0x07,0x00,0xf0,0x00,0x30,0x03,0x30,0x03
,0x03,0x00,0x7e,0x00,0x30,0x03,0x30,0x03
,0x01,0x80,0x1f,0xc0,0x30,0x03,0x30,0x03
,0x01,0xc0,0x03,0xe1,0x30,0x07,0xf8,0x03
,0x00,0xf0,0x00,0x01,0x30,0x03,0xf0,0x03
,0x00,0x38,0x00,0x00,0x30,0x00,0x00,0x03
,0x00,0x1e,0x00,0x00,0x30,0x00,0x00,0x03
,0x00,0x07,0xc0,0x00,0x30,0x00,0x00,0x03
,0x00,0x01,0xff,0x80,0x3f,0xff,0xff,0xff
,0x00,0x00,0x3f,0x80,0x1f,0xff,0xff,0xfe
};
//---------------------------------------------------------------
#define FinPr_scan_width 64
#define FinPr_scan_height 64
const uint8_t PROGMEM FinPr_scan_bits[] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x1f,0xf8,0x00,0x00,0x00
,0x00,0x00,0x00,0x7f,0xff,0x00,0x00,0x00
,0x00,0x00,0x01,0xfc,0x7f,0xc0,0x00,0x00
,0x00,0x00,0x03,0xc0,0x03,0xe0,0x00,0x00
,0x00,0x00,0x07,0x80,0x00,0xf0,0x00,0x00
,0x00,0x00,0x0e,0x00,0x00,0x3c,0x00,0x00
,0x00,0x00,0x1c,0x1f,0xfc,0x1c,0x00,0x00
,0x00,0x00,0x38,0x7f,0xfe,0x0e,0x00,0x00
,0x00,0x00,0x78,0xf8,0x0f,0x87,0x00,0x00
,0x00,0x00,0x71,0xe0,0x03,0xc7,0x00,0x00
,0x00,0x00,0xe3,0x80,0x01,0xc3,0x80,0x00
,0x00,0x00,0xc3,0x83,0xc0,0xe3,0x80,0x00
,0x00,0x00,0xc7,0x0f,0xf0,0x71,0x80,0x00
,0x00,0x00,0x06,0x1f,0xf8,0x71,0xc0,0x00
,0x00,0x00,0x0e,0x1c,0x3c,0x31,0xc0,0x00
,0x00,0x00,0x1c,0x38,0x1c,0x31,0xc0,0x00
,0x00,0x00,0x38,0x70,0x0e,0x39,0xc0,0x00
,0x00,0x01,0xf0,0x71,0x8e,0x39,0xc0,0x00
,0x00,0x03,0xe0,0xe1,0x86,0x31,0xc0,0x00
,0x00,0x03,0x81,0xe3,0x8e,0x31,0x80,0x00
,0x00,0x00,0x03,0xc3,0x8e,0x33,0x80,0x00
,0x00,0x00,0x07,0x87,0x0c,0x73,0x80,0x00
,0x00,0x00,0x1f,0x0e,0x1c,0x73,0x80,0x00
,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xfe
,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xfe
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x03,0xf0,0x1e,0x3e,0x1c,0x00,0x00
,0x00,0x03,0x80,0x7c,0x77,0x0f,0x00,0x00
,0x00,0x00,0x01,0xf0,0xe3,0x07,0xc0,0x00
,0x00,0x00,0x07,0xe3,0xc3,0x81,0xf0,0x00
,0x00,0x00,0x3f,0x87,0x81,0xc0,0x60,0x00
,0x00,0x01,0xfc,0x1f,0x00,0xf0,0x00,0x00
,0x00,0x01,0xe0,0x3c,0x00,0x7c,0x00,0x00
,0x00,0x00,0x00,0xf8,0x78,0x1f,0x00,0x00
,0x00,0x00,0x07,0xe0,0xfc,0x0f,0xc0,0x00
,0x00,0x00,0x3f,0x83,0xef,0x03,0xc0,0x00
,0x00,0x00,0xfc,0x0f,0x87,0x80,0x00,0x00
,0x00,0x00,0x70,0x1f,0x03,0xe0,0x00,0x00
,0x00,0x00,0x00,0x7c,0x00,0xf8,0x00,0x00
,0x00,0x00,0x01,0xf0,0x00,0x3e,0x00,0x00
,0x00,0x00,0x0f,0xc0,0xf8,0x0f,0x00,0x00
,0x00,0x00,0x1f,0x03,0xfe,0x02,0x00,0x00
,0x00,0x00,0x0c,0x0f,0x8f,0x80,0x00,0x00
,0x00,0x00,0x00,0x3f,0x03,0xe0,0x00,0x00
,0x00,0x00,0x00,0xf8,0x00,0xf0,0x00,0x00
,0x00,0x00,0x01,0xe0,0x00,0x30,0x00,0x00
,0x00,0x00,0x01,0xc0,0xf8,0x00,0x00,0x00
,0x00,0x00,0x00,0x07,0xfe,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0x8e,0x00,0x00,0x00
,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
void setup()
{
  Serial.begin(115200);
  while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}

   pinMode(buzzer, OUTPUT);
  connectToWiFi();
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("Adafruit finger detect test\n");
  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor\n");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' ");
  }
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
  
}

void loop()                     // run over and over again
{

  getFingerprintID();
  delay(50);  
  int analogReading = analogRead(FORCE_SENSOR_PIN);
  SendForceSensorReading(analogReading);
  delay(1000);
  gpsData();

}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected\n");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!\n");
    digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200); 
    SendFingerprintID();
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  SendFingerprintID();
  return finger.fingerID;
}
//********************connect to the WiFi******************
void connectToWiFi(){
    WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
    delay(1000);
    WiFi.mode(WIFI_STA);
    Serial.println("Connecting\n");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("Connected\n");

    digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200); 
    
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
}
//************send the fingerprint ID to the website*************
void SendFingerprintID(){
  
  HTTPClient http;    //Declare object of class HTTPClient
  //Post Data
  postData = "data=" + String(finger.fingerID); // Add the Fingerprint ID to the Post array in order to send it
  // Post methode
 
  http.begin(wifiClient, link); //initiate HTTP request, put your Website URL or Your Computer IP 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
  
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  Serial.println(postData);   //Post Data
  delay(1000);
  
  postData = "";
  http.end();  //Close connection
}
//************send the force sensor reading to the website*************
void SendForceSensorReading(int analogReading){
 
  Serial.print("Force sensor reading = ");
  Serial.print(analogReading); // print the raw analog reading

  if (analogReading < 10)       // from 0 to 9
    Serial.println(" -> no pressure");
  else if (analogReading < 30) // from 10 to 199
    Serial.println(" -> light touch");
  else { // from 200 to 499
    Serial.println(" -> Crashed");
    digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200); }
  
  HTTPClient http;    //Declare object of class HTTPClient
  //Post Data
  postData = "data=" + String(analogReading); // Add the Fingerprint ID to the Post array in order to send it
  // Post methode
 
  http.begin(wifiClient, link3); //initiate HTTP request, put your Website URL or Your Computer IP 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
  
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  Serial.println(postData);   //Post Data
  delay(1000);
  
  postData = "";
  http.end();  //Close connection
}
//************send GPS data to the website*************
void SendGPSData(String gpsData){
  
  HTTPClient http;    //Declare object of class HTTPClient
  //Post Data
  postData = "data=" + gpsData; 

 
  http.begin(wifiClient, link2); //initiate HTTP request, put your Website URL or Your Computer IP 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
  
//  Serial.println(httpCode);   //Print HTTP return code
//  Serial.println(payload);    //Print request response payload
//  Serial.println(postData);   //Post Data
  delay(1000);
  postData = "";
  http.end();  //Close connection
}
 void gpsData(){
    
//  static char cmdBuffer[CMDBUFFER_SIZE] = "";
//  char c;
int count = 0;
  while(Serial.available() && count < 3) 
  {
//    c = processCharInput(cmdBuffer, Serial.read());
//    if (c == '!') 
//    {
      
    String gpsData = Serial.readString();
    Serial.print(gpsData);
    SendGPSData(String(gpsData));
    count++;
    break;
//    }
    
    
  

 }
 }
 
