const int NTP_PACKET_SIZE= 48; 				// NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[NTP_PACKET_SIZE]; 			// buffer to hold incoming and outgoing packets 
const char* host = "0.nl.pool.ntp.org";			// Use random servers through DNS
IPAddress rem_add;
unsigned long epochDST;

unsigned long sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE); 
  // Initialize values needed to form NTP request
  packetBuffer[0] = 0b11100011;	  // LI, Version, Mode
  packetBuffer[1] = 0;	   // Stratum, or type of clock
  packetBuffer[2] = 6;	   // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]	= 49; 
  packetBuffer[13]	= 0x4E;
  packetBuffer[14]	= 49;
  packetBuffer[15]	= 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp: 
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer,NTP_PACKET_SIZE);
  udp.endPacket(); 
}


int adjustDstEurope(){  //Zomer/wintertijd correctie
  // last sunday of march
  int beginDSTDate=  (31 - (5* year() /4 + 4) % 7);
  int beginDSTMonth=3;
  //last sunday of october
  int endDSTDate= (31 - (5 * year() /4 + 1) % 7);
  int endDSTMonth=10;
  // DST is valid as:
  if (((month() > beginDSTMonth) && (month() < endDSTMonth))
      || ((month() == beginDSTMonth) && (day() >= beginDSTDate))
      || ((month() == endDSTMonth) && (day() <= endDSTDate)))
  return 7200;  // DST europe = utc +2 hour
  else return 3600; // nonDST europe = utc +1 hour
}

void NTPontvang(){
  if ( udp.parsePacket() && ntpcheck == 1) {  // We've received a packet, read the data from it
    udp.read(packetBuffer,NTP_PACKET_SIZE);	 // read the packet into the buffer
    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);  
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;	 		 	
    // now convert NTP time into everyday time:
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;	 
    unsigned long epoch = secsSince1900 - seventyYears;	
    if(tijdcheck == 0)setTime(epoch); //Wanneer geen RTC eerst tijd instellen met ntpsync, daarna corrigeren voor zomer/winter tijd 
    epochDST = epoch + adjustDstEurope();
    // print Unix time:
    Serial.print("Unix tijd (UTC + DST) = ");Serial.println(epochDST);
  }
}
  
void NTPsync(){
  wdt_reset();
    if(Dns.getHostByName(host, rem_add) == 1 ){
      Serial.println(F("DNS resolve..."));	 
      Serial.print(host); Serial.print(F("  = ")); Serial.println(rem_add);
      sendNTPpacket(rem_add);
      ntpcheck = 1;
      delay(1000);
      NTPontvang();
      setTime(epochDST);
      if(tijdcheck == 1){
       RTC.set(now());
      }
      Serial.println(F("Tijd aangepast naar:"));
      if(hour() < 10)Serial.print("0");Serial.print(hour()); Serial.print(":");if(minute() < 10)Serial.print("0");Serial.print(minute());
      Serial.print(" ");
      Serial.print(day());Serial.print("/");Serial.print(month());Serial.print("/");Serial.println(year());
     }else{
      Serial.print(F("DNS fail..."));
      ntpcheck = 0;
     }
}

TimedAction ntpsync = TimedAction(1800000, NTPsync);

