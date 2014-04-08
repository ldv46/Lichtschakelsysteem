unsigned long lamp1 = actionTransmitter.getTelegram(9,'A',true);
unsigned long lamp2 = actionTransmitter.getTelegram(9,'A',false);
unsigned long lamp3 = actionTransmitter.getTelegram(9,'B',true);
unsigned long lamp4 = actionTransmitter.getTelegram(9,'B',false);

void Lampinit(){
  LED('O');
  actionTransmitter.sendSignal(18,'A',lamp1status);
  actionTransmitter.sendSignal(18,'A',lamp1status);
  LED('B');
  actionTransmitter.sendSignal(18,'B',lamp2status);
  actionTransmitter.sendSignal(18,'B',lamp2status);
  LED('O');
  actionTransmitter.sendSignal(18,'C',lamp3status);
  actionTransmitter.sendSignal(18,'C',lamp3status);
  LED('G');
  actionTransmitter.sendSignal(18,'D',lamp4status);
  actionTransmitter.sendSignal(18,'D',lamp4status);
  LED('B');
}


void translateCode(unsigned long receivedCode, unsigned int period) {
  // Enabled interrupts, so RemoteReceiver::isReceiving() can be used.
  interrupts(); 
  // Compare the signals
  if (RemoteTransmitter::isSameCode(lamp1, receivedCode)) {
    while(RemoteReceiver::isReceiving()); // Wait for a free ether
    actionTransmitter.sendSignal(18,'A',!lamp1status);
    actionTransmitter.sendSignal(18,'A',!lamp1status);
    lamp1status = !lamp1status;
  }	
  if (RemoteTransmitter::isSameCode(lamp2, receivedCode)) {  
    while(RemoteReceiver::isReceiving()); // Wait for a free ether
    actionTransmitter.sendSignal(18,'B',!lamp2status);
    actionTransmitter.sendSignal(18,'B',!lamp2status);
    lamp2status = !lamp2status;
  }  
  if (RemoteTransmitter::isSameCode(lamp3, receivedCode)) {  
    while(RemoteReceiver::isReceiving()); // Wait for a free ether
    actionTransmitter.sendSignal(18,'C',!lamp3status);
    actionTransmitter.sendSignal(18,'C',!lamp3status);
    lamp3status = !lamp3status;
  }
  if (RemoteTransmitter::isSameCode(lamp4, receivedCode)) {  
    while(RemoteReceiver::isReceiving()); // Wait for a free ether
    actionTransmitter.sendSignal(18,'D',!lamp4status);
    actionTransmitter.sendSignal(18,'D',!lamp4status);
    lamp3status = !lamp3status;
  }
}
