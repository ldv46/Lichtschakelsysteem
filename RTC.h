void RTCopstart(){
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet){
      LED('Y');
      tijdcheck = 0;
      Serial.println("RTC niet gevonden");
  } else {
  tijdcheck = 1;
  Serial.println("RTC geinitialiseerd");
  if(hour() < 10)Serial.print("0");Serial.print(hour()); Serial.print(":");if(minute() < 10)Serial.print("0");Serial.print(minute());
  Serial.print(" ");
  Serial.print(day());Serial.print("/");Serial.print(month());Serial.print("/");Serial.println(year());
  }
}
