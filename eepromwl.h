void EEPROMinit(){
  eepromwl.write(31, 223);
  if(eepromwl.read(31) == 223){
  }else{
    while(true){
      analogWrite(3, 100); //R
      analogWrite(5, 0); //G
      analogWrite(6, 0); //B
    }
  }
}
