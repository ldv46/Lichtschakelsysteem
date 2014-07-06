//Afstandbediening codes
unsigned long lamp1code = actionTransmitter.getTelegram(9,'A',true);
unsigned long lamp2code = actionTransmitter.getTelegram(9,'A',false);
unsigned long lamp3code = actionTransmitter.getTelegram(9,'B',true);
unsigned long lamp4code = actionTransmitter.getTelegram(9,'B',false);
unsigned long lamp5code = actionTransmitter.getTelegram(9,'C',true);
unsigned long lamp6code = actionTransmitter.getTelegram(9,'C',false);
//Lampcode huiscode 18
char lamp1 = 'A';
char lamp2 = 'B';
char lamp3 = 'C';
char lamp4 = 'D';
//Lampcode huiscode 19
char lamp5 = 'A';
char lamp6 = 'B';

void Lampinit(){
  LED('B');
  actionTransmitter.sendSignal(18, lamp1,lamp1status);
  actionTransmitter.sendSignal(18, lamp2,lamp2status);
  actionTransmitter.sendSignal(18, lamp3,lamp3status);
  actionTransmitter.sendSignal(18, lamp4,lamp4status);
  actionTransmitter.sendSignal(19, lamp5,lamp5status);
  actionTransmitter.sendSignal(19, lamp6,lamp6status);
}

void Schakel(char* schakelaar){
  if(strcasecmp(schakelaar, "SCHAKELAAR1") == 0){
    actionTransmitter.sendSignal(18, lamp1,!lamp1status);
    lamp1status = !lamp1status;
    eepromwl.write(1, lamp1status);
  }
  if(strcasecmp(schakelaar, "SCHAKELAAR2") == 0){
    actionTransmitter.sendSignal(18, lamp2,!lamp2status);
    lamp2status = !lamp2status;
    eepromwl.write(2, lamp2status);
  }
  if(strcasecmp(schakelaar, "SCHAKELAAR3") == 0){
    actionTransmitter.sendSignal(18, lamp3,!lamp3status);
    lamp3status = !lamp3status;
    eepromwl.write(3, lamp3status);
  }
  if(strcasecmp(schakelaar, "SCHAKELAAR4") == 0){
    actionTransmitter.sendSignal(18, lamp4,!lamp4status);
    lamp4status = !lamp4status;
    eepromwl.write(4, lamp4status);
  }
  if(strcasecmp(schakelaar, "SCHAKELAAR5") == 0){
    actionTransmitter.sendSignal(19, lamp5,!lamp5status);
    lamp5status = !lamp5status;
    eepromwl.write(5, lamp5status);
  }
  if(strcasecmp(schakelaar, "SCHAKELAAR6") == 0){
    actionTransmitter.sendSignal(19, lamp6,!lamp6status);
    lamp6status = !lamp6status;
    eepromwl.write(6, lamp6status);
  }
}

void translateCode(unsigned long receivedCode, unsigned int period) {
  LED('B');
  // Signaal vergelijken
  if (RemoteTransmitter::isSameCode(lamp1code, receivedCode)) {
    Schakel("schakelaar1");
  }	
  if (RemoteTransmitter::isSameCode(lamp2code, receivedCode)) {  
    Schakel("schakelaar2");
  }  
  if (RemoteTransmitter::isSameCode(lamp3code, receivedCode)) {  
    Schakel("schakelaar3");
  }
  if (RemoteTransmitter::isSameCode(lamp4code, receivedCode)) {  
    Schakel("schakelaar4");
  }
  if (RemoteTransmitter::isSameCode(lamp5code, receivedCode)) {  
    Schakel("schakelaar5");
  }
  if (RemoteTransmitter::isSameCode(lamp6code, receivedCode)) {  
    Schakel("schakelaar6");
  }
}


