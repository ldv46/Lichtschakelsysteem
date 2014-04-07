void RTCopstart(){
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet){
      analogWrite(3, 200);
      tijdcheck = 0;
  }
  tijdcheck = 1;
}
