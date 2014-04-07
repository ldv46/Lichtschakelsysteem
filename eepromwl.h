void EEPROMinit(){
  eepromwl.write(32, 223);
  if(eepromwl.read(32) == 223){
  }else{
    while(true);
  }
}
