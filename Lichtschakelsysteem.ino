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
EEPROMWearLeveler eepromwl(4096, 128);
#include "RemoteTransmitter.h"
#include "RemoteReceiver.h"
#include "TimedAction.h"
#include <avr/wdt.h>
ElroTransmitter elroTransmitter(7);
#include "variabelen.h"
#include "eepromwl.h"
#include "RTC.h"
#include <SPI.h>      
#include <SD.h>
#include <Ethernet.h>
#include <utility/w5100.h>
#include <Dns.h>
EthernetUDP udp; //Initialiseer UDP als udp
DNSClient Dns;
#include <Flash.h>
#include "sdkaart.h"
#include <TinyWebServer.h>
#include "remote.h"
#include "xml.h"
#include "netwerk.h"
#include "NTP.h"



void setup()
{
  wdt_reset();
  wdt_enable(WDTO_8S);
  Serial.begin(115200);
  pinMode(3, OUTPUT);pinMode(5, OUTPUT);pinMode(6, OUTPUT); //(R/G/B)
  pinMode(7, OUTPUT); //433Mhz zender
  pinMode(2, INPUT); //433Mhz ontvanger
  pinMode(SS_PIN, OUTPUT); //SS Ethernet
  digitalWrite(SS_PIN, HIGH);
  pinMode(10, OUTPUT); //SS Ethernet
  pinMode(4, OUTPUT); //SS SDkaart
  digitalWrite(10, HIGH);
  digitalWrite(4, HIGH);
  SDinit();
  Netwerkinit();
  EEPROMinit();
  RTCopstart();
  NTPsync();
  Lampinit();
  RemoteReceiver::init(0, 1, translateCode);
}

void loop()
{
  LED('G');
  wdt_reset();
  web.process();
  ntpsync.check();
}

void LED(char kleur){
  switch (kleur){
    case 'R': //Rood (netwerkfout)
      analogWrite(3, 60); //R
      analogWrite(5, 0); //G
      analogWrite(6, 0); //B
      break;
    case 'G': //Groen (alles OK)
      analogWrite(3, 0); //R
      analogWrite(5, 60); //G
      analogWrite(6, 0); //B
      break;
    case 'B': //Blauw (lamp aan)
      analogWrite(3, 0); //R
      analogWrite(5, 0); //G
      analogWrite(6, 60); //B
      break;
    case 'Y': //Geel (RTC of NTP fout)
      analogWrite(3, 40); //R
      analogWrite(5, 20); //G
      analogWrite(6, 0); //B
      break;
    case 'C': //Cyaan (EEPROM fout)
      analogWrite(3, 0); //R
      analogWrite(5, 30); //G
      analogWrite(6, 30); //B
      break;
    case 'M': //Magenta (SD fout)
      analogWrite(3, 30); //R
      analogWrite(5, 0); //G
      analogWrite(6, 30); //B
      break;
    case 'W': //Wit (netwerk in gebruik)
      analogWrite(3, 20); //R
      analogWrite(5, 20); //G
      analogWrite(6, 20); //B
      break;
    case 'O': //Off (Uit)
      analogWrite(3, 0); //R
      analogWrite(5, 0); //G
      analogWrite(6, 0); //B
      break;
  }
}
