/*
Adressen in EEPROM:
lamp1status = 1 
lamp2status = 2
lamp3status = 3
lamp4status = 4
*/

void EEPROMinit(){
  eepromwl.write(31, 223);
  if(eepromwl.read(31) == 223){
    lamp1status = eepromwl.read(1);
    lamp2status = eepromwl.read(2);
    lamp3status = eepromwl.read(3);
    lamp4status = eepromwl.read(4);
  }else{
    while(true)LED('R');
  }
}
