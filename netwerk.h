boolean file_handler(TinyWebServer& web_server);
boolean index_handler(TinyWebServer& web_server);

void send_file_name(TinyWebServer& web_server, const char* filename) {
  if (!filename) {
    web_server.send_error_code(404);
    web_server << F("Could not parse URL");
  } else {
    TinyWebServer::MimeType mime_type = TinyWebServer::get_mime_type_from_filename(filename);
    web_server.send_error_code(200);
    if (file.open(&root, filename, O_READ)) {
      web_server.send_content_type(mime_type);
      web_server.end_headers();
      Serial << F("Read file "); Serial.println(filename);
      web_server.send_file(file);
      file.close();
  } else {
      web_server.send_content_type("text/plain");
      web_server.end_headers();
      Serial << F("Could not find file: "); Serial.println(filename);
      web_server << F("Could not find file: ") << filename << "\n";
    }
  }
}

boolean file_handler(TinyWebServer& web_server) {
  char* filename = TinyWebServer::get_file_from_path(web_server.get_path());
  Serial << filename;
  send_file_name(web_server, filename);
  free(filename);
  return true;
}

boolean index_handler(TinyWebServer& web_server) {
  send_file_name(web_server, "INDEX.HTML");
  return true;
}

TinyWebServer::PathHandler handlers[] = {
  {"/", TinyWebServer::GET, &index_handler },
  {"/" "*", TinyWebServer::GET, &file_handler },
  {NULL},
};

TinyWebServer web = TinyWebServer(handlers, NULL);

void Netwerkinit(){ //Netwerk initialisatie
    Ethernet.begin(MAC, IP); //Alleen MAC voor DHCP
    web.begin();
    Dns.begin(Ethernet.dnsServerIP()); //DNS
    udp.begin(5678); //zet UDP poort 5678
}
