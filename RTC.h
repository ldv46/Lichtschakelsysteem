void RTCopstart(){
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet){
      LED('Y');
      delay(1000);
      tijdcheck = 0;
      Serial.println("RTC niet gevonden");
  } else {
  tijdcheck = 1;
  Serial.println("RTC geinitialiseerd");
  Serial.println("RTC tijd:");
  if(hour() < 10)Serial.print("0");Serial.print(hour()); Serial.print(":");if(minute() < 10)Serial.print("0");Serial.print(minute());Serial.print(":");if(second() < 10)Serial.print("0");Serial.print(second());
  Serial.print(" ");
  Serial.print(day());Serial.print("/");Serial.print(month());Serial.print("/");Serial.println(year());
  }
}
