void SDinit(){
  if(!SD.begin(4)){
    while(true)LED('R');
  }
}
