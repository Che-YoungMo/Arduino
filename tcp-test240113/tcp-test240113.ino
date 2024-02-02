#include <EtherCard.h>
#include <enc28j60.h>
#include <net.h>

#include <Ethernet.h>

// Define the MAC address of your ENC28J60 module
byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

// IP address of the Arduino
byte myip[] = { 192, 168, 1, 177 };

// TCP port to listen on
unsigned int myport = 80;

// Pin to control the LED
const int ledPin = 13;

void setup() {
  Serial.begin(9600);
  
  // Initialize the Ethernet module
  if (ether.begin(sizeof Ethernet::buffer, mymac, 53) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
  
  ether.staticSetup(myip);
  ether.printIp("IP: ", ether.myip);
  ether.printIp("GW: ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);
  
  // Start listening for incoming connections on the specified port
  ether.tcpServerOpen(myport);
}

void loop() {
  // Check for incoming TCP connections
  word len = ether.packetLoop(ether.packetReceive());
  
  // Handle incoming TCP data
  if (len > 0 && ether.packetLoopIcmpCheckReply(ether.header, myip)) {
    // Check if the received data is a command to toggle the LED
    if (strncmp("TOGGLE", (char *)Ethernet::buffer + TCP_DATA_P, 6) == 0) {
      toggleLED();
    }
    
    // Send a response back to the client
    ether.tcpServerReply(len);
  }
}

void toggleLED() {
  // Toggle the state of the LED
  digitalWrite(ledPin, !digitalRead(ledPin));
  
  // Print the current state of the LED to the Serial monitor
  Serial.print("LED is ");
  Serial.println(digitalRead(ledPin) ? "ON" : "OFF");
}
이 코드를 Arduino에 업로드