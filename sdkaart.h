boolean has_filesystem = true;
Sd2Card card;
SdVolume volume;
SdFile root;
SdFile file;

void SDinit(){
  // initialize the SD card
  Serial << F("Setting up SD card...");
  if (!card.init(SPI_FULL_SPEED, 4)) {
    Serial << F("Card failed\n");
    LED('R');
    delay(1000);
  } 
  // initialize a FAT volume
  if (!volume.init(&card)) {
    Serial << F("Vol.init failed!\n");
    LED('R');
    delay(1000);
  } else {
    Serial.print("\nVolume type is FAT");
    Serial.println(volume.fatType(), DEC);
  }
  if (!root.openRoot(&volume)) {
    Serial << F("openRoot failed!\n");
    LED('R');
    delay(1000);
  } else {
    root.ls(LS_R | LS_DATE | LS_SIZE); //debug inhoud SDkaart
  }
}
