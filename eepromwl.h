/*
Adressen in EEPROM:
lamp1status = 1 
lamp2status = 2
lamp3status = 3
lamp4status = 4
*/

void EEPROMinit(){
  eepromwl.write(127, 223);
  if(eepromwl.read(127) == 223){
    lamp1status = eepromwl.read(1);
    lamp2status = eepromwl.read(2);
    lamp3status = eepromwl.read(3);
    lamp4status = eepromwl.read(4);
    lamp5status = eepromwl.read(5);
    lamp6status = eepromwl.read(6);
  }else{
    while(true)LED('C');
  }
}
