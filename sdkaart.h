boolean has_filesystem = true;
Sd2Card card;
SdVolume volume;
SdFile root;
SdFile file;
const int sdChipSelect = 4;            // SD card chipSelect

void SDinit(){
 digitalWrite(10, HIGH); // but turn off the W5100 chip!
  // initialize the SD card
  Serial << F("Setting up SD card...\n");
  if (!card.init(SPI_FULL_SPEED, 4)) {
    Serial << F("card failed\n");
    has_filesystem = false;
    LED('R');
    delay(1000);
  }
  // initialize a FAT volume
  if (!volume.init(&card)) {
    Serial << F("vol.init failed!\n");
    has_filesystem = false;
    LED('R');
    delay(1000);
  }
  if (!root.openRoot(&volume)) {
    Serial << F("openRoot failed");
    has_filesystem = false;
    LED('R');
    delay(1000);
  }
}
