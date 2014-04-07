void HTMLserver(){
// listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    analogWrite(3, 100);
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
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
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    analogWrite(3, 0);
  }
}
