void EEPROMinit(){
  eepromwl.write(31, 223);
  if(eepromwl.read(31) == 223){
  }else{
    while(true)LED('R');
  }
}
