void RTCopstart(){
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet){
      LED('Y');
      tijdcheck = 0;
  }
  tijdcheck = 1;
}
