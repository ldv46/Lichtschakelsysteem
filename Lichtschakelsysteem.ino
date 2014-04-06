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
#include "RemoteTransmitter.h"
#include "RemoteReceiver.h"
#include "TimedAction.h"
#include <avr/wdt.h>
ActionTransmitter actionTransmitter(7);
#include "variabelen.h"
#include "RTC.h"
#include <SPI.h>      
#include <SD.h>
#include <Ethernet.h>
EthernetServer server(80);
#include <Dns.h>
EthernetUDP udp; //Initialiseer UDP als udp, standaard in library op pin 53
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
  Serial.begin(9600);
  pinMode(3, OUTPUT);pinMode(5, OUTPUT);pinMode(6, OUTPUT); //(R/G/B)
  pinMode(7, OUTPUT);
  pinMode(2, INPUT);
  RTCopstart();
  NTPsync();
  RemoteReceiver::init(0, 1, translateCode);
  digitalClockDisplay();
  analogWrite(5, 100);
}

void loop()
{
  wdt_reset();
  HTMLserver();
}
