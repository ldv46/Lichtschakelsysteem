//Afstandbediening codes
unsigned long lamp1code = elroTransmitter.getTelegram(0,'A',true);
unsigned long lamp2code = elroTransmitter.getTelegram(0,'A',false);
unsigned long lamp3code = elroTransmitter.getTelegram(0,'B',true);
unsigned long lamp4code = elroTransmitter.getTelegram(0,'B',false);
//Lampcode huiscode 31
char lamp1 = 'A';
char lamp2 = 'D';
char lamp3 = 'B';
char lamp4 = 'C';

void Lampinit(){
  LED('O');
  elroTransmitter.sendSignal(31, lamp1,lamp1status);
  LED('B');
  elroTransmitter.sendSignal(31, lamp2,lamp2status);
  LED('O');
  elroTransmitter.sendSignal(31, lamp3,lamp3status);
  LED('G');
  elroTransmitter.sendSignal(31, lamp4,lamp4status);
  LED('B');
}


void translateCode(unsigned long receivedCode, unsigned int period) {
  // Signaal vergelijken
  if (RemoteTransmitter::isSameCode(lamp1code, receivedCode)) {
    elroTransmitter.sendSignal(31, lamp1,!lamp1status);
    lamp1status = !lamp1status;
    eepromwl.write(1, lamp1status);
  }	
  if (RemoteTransmitter::isSameCode(lamp2code, receivedCode)) {  
    elroTransmitter.sendSignal(31, lamp2,!lamp2status);
    lamp2status = !lamp2status;
    eepromwl.write(2, lamp2status);
  }  
  if (RemoteTransmitter::isSameCode(lamp3code, receivedCode)) {  
    elroTransmitter.sendSignal(31, lamp3,!lamp3status);
    lamp3status = !lamp3status;
    eepromwl.write(3, lamp3status);
  }
  if (RemoteTransmitter::isSameCode(lamp4code, receivedCode)) {  
    elroTransmitter.sendSignal(31, lamp4,!lamp4status);
    lamp4status = !lamp4status;
    eepromwl.write(4, lamp4status);
  }
}
