#define BUFSIZ 50

void HTMLserver(){
  char clientline[BUFSIZ];
  char *filename;
  int index = 0;
  int image = 0;
  boolean homepage;
  EthernetClient client = server.available();
  if (client) {
    boolean current_line_is_blank = true;
    index = 0;
    while (client.connected()) {
      LED('W');
      if (client.available()) {
        char c = client.read();
        if (c != '\n' && c != '\r') {
          clientline[index] = c;
          index++;
          if (index >= BUFSIZ)
            index = BUFSIZ -1;
          continue;
        }
        clientline[index] = 0;
        filename = 0;
        if (strstr(clientline, "GET / ") != 0) {  //If you are going to the homepage, the filename is set to the rootFileName
          homepage = 1;
          filename = "deel1.html";
        }
        if (strstr(clientline, "GET /") != 0) {
          if (!filename) { 
            filename = clientline + 5;  //gets rid of the GET / in the filename
            homepage = 0; 
          }
          (strstr(clientline, " HTTP"))[0] = 0;  //gets rid of everything from HTTP to the end.
          if (!SD.open(filename)) {  //if the file doesn't exist a 404 is sent
            client.println("HTTP/1.1 404 Not Found");
            client.println("Content-Type: text/html");
            client.println();
            client.println("<h2>File Not Found!</h2>");
            break;
          }
          client.println("HTTP/1.1 200 OK");
          if (strstr(filename, ".htm") != 0)  //Sets content type.
            client.println("Content-Type: text/html");
          if (strstr(filename, ".html") != 0)  //Sets content type.
            client.println("Content-Type: text/html");
          else if (strstr(filename, ".css") != 0)
            client.println("Content-Type: text/css");
          else if (strstr(filename, ".png") != 0)
            client.println("Content-Type: image/png");
          else if (strstr(filename, ".jpg") != 0)
            client.println("Content-Type: image/jpeg");
          else if (strstr(filename, ".gif") != 0)
            client.println("Content-Type: image/gif");
          else if (strstr(filename, ".js") != 0)
            client.println("Content-Type: application/x-javascript");
          else if (strstr(filename, ".xml") != 0)
            client.println("Content-Type: application/xml");
          else
            client.println("Content-Type: text");
          client.println();
          int16_t c;
          if(homepage == 0){
            bestand = SD.open(filename);
            while ((c = bestand.read()) >= 0) {
              client.write((char)c);  //sends file to website client
            }
            bestand.close();
          }
          if(homepage == 1){
            bestand = SD.open("deel1.html");
            while ((c = bestand.read()) >= 0) {
              client.write((char)c);  //sends file to website client
            }
            bestand.close();
            client.print(day());client.print("/");client.print(month());client.print("/");client.print(year());
            client.println("<br />");
            client.print(hour());client.print(":");client.print(minute());client.print(":");client.print(second());
            client.println("<br />");
            client.print("Lamp 1 is ");
            client.print(lamp1status);
            client.println("<br />");
            client.print("Lamp 2 is ");
            client.print(lamp2status);
            client.println("<br />");
            client.print("Lamp 3 is ");
            client.print(lamp3status);
            bestand = SD.open("deel2.html");
            while ((c = bestand.read()) >= 0) {
              client.write((char)c);  //sends file to website client
            }
            bestand.close();
          }
        } 
        else {
          client.println("HTTP/1.1 404 Not Found");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<h2>File Not Found!</h2>");
        }
        break;
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    LED('G');
  }
}
