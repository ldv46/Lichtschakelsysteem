void RTCopstart(){
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet){
      LED('Y');
      tijdcheck = 0;
      Serial.println("RTC niet gevonden");
  } else {
  tijdcheck = 1;
  Serial.println("RTC geinitialiseerd");
  }
}
