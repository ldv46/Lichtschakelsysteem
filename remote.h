unsigned long lamp1 = elroTransmitter.getTelegram(0,'A',true);
unsigned long lamp2 = elroTransmitter.getTelegram(0,'A',false);
unsigned long lamp3 = elroTransmitter.getTelegram(0,'B',true);
unsigned long lamp4 = elroTransmitter.getTelegram(0,'B',false);

void Lampinit(){
  LED('O');
  elroTransmitter.sendSignal(31,'A',lamp1status);
  LED('B');
  elroTransmitter.sendSignal(31,'B',lamp2status);
  LED('O');
  elroTransmitter.sendSignal(31,'C',lamp3status);
  LED('G');
  elroTransmitter.sendSignal(31,'D',lamp4status);
  LED('B');
}


void translateCode(unsigned long receivedCode, unsigned int period) {
  // Signaal vergelijken
  if (RemoteTransmitter::isSameCode(lamp1, receivedCode)) {
    elroTransmitter.sendSignal(31,'A',!lamp1status);
    lamp1status = !lamp1status;
    eepromwl.write(1, lamp1status);
  }	
  if (RemoteTransmitter::isSameCode(lamp2, receivedCode)) {  
    elroTransmitter.sendSignal(31,'D',!lamp2status);
    lamp2status = !lamp2status;
    eepromwl.write(2, lamp2status);
  }  
  if (RemoteTransmitter::isSameCode(lamp3, receivedCode)) {  
    elroTransmitter.sendSignal(31,'C',!lamp3status);
    lamp3status = !lamp3status;
    eepromwl.write(3, lamp3status);
  }
  if (RemoteTransmitter::isSameCode(lamp4, receivedCode)) {  
    elroTransmitter.sendSignal(31,'B',!lamp4status);
    lamp4status = !lamp4status;
    eepromwl.write(4, lamp4status);
  }
}
