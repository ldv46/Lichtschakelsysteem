void Netwerkinit(){ //Netwerk initialisatie
    Serial.println(F("Verbinding maken met netwerk..."));
    Ethernet.begin(MAC, IP); //Alleen MAC voor DHCP
    server.begin();
    Dns.begin(Ethernet.dnsServerIP()); //DNS
    udp.begin(5678); //zet UDP poort 5678
}
