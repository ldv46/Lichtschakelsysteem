/*
Lichtschakelsysteem LdV46
Schakelaars op huiscode 18 (01001)
Afstandsbediening op 9 (10010)
*/

#include "Wire.h"
#include "EEPROM.h"
#include "Time.h"
#include "DS3232RTC.h"
#include "EEPROMWearLeveler.h"
EEPROMWearLeveler eepromwl(1024, 32);
#include "RemoteTransmitter.h"
#include "RemoteReceiver.h"
#include "TimedAction.h"
#include <avr/wdt.h>
ActionTransmitter actionTransmitter(7);
#include "variabelen.h"
#include "eepromwl.h"
#include "RTC.h"
#include <SPI.h>      
#include <SD.h>
#include <Ethernet.h>
EthernetServer server(80);
#include <Dns.h>
EthernetUDP udp; //Initialiseer UDP als udp
DNSClient Dns;
#include "netwerk.h"
#include "NTP.h"
#include "remote.h"
#include "server.h"

void setup()
{
  Netwerkinit();
  wdt_reset();
  wdt_enable(WDTO_8S); 
  pinMode(3, OUTPUT);pinMode(5, OUTPUT);pinMode(6, OUTPUT); //(R/G/B)
  pinMode(7, OUTPUT); //433Mhz zender
  pinMode(2, INPUT); //433Mhz ontvanger
  pinMode(4, OUTPUT); //SS SDkaart
  pinMode(10, OUTPUT); //SS Ethernet
  EEPROMinit();
  RTCopstart();
  NTPsync();
  RemoteReceiver::init(0, 1, translateCode);
  digitalClockDisplay();
  analogWrite(3, 100); //R
  analogWrite(5, 100); //G
  analogWrite(6, 100); //B
}

void loop()
{
  wdt_reset();
  HTMLserver();
  ntpsync.check();
}
