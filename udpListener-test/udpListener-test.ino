// Demonstrates usage of the new udpServer feature.
// You can register the same function to multiple ports,
// and multiple functions to the same port.
//
// 2013-4-7 Brian Lee <cybexsoft@hotmail.com>
//
// License: GPLv2

#include <EtherCard.h>
#include <IPAddress.h>

#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// Ethernet interface IP address
static byte myip[] = { 192,168,100,100 };
// Gateway IP address
static byte gwip[] = { 192,168,100,1 };
#endif

// Ethernet MAC address - must be unique on your network
static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[500]; // TCP/IP send and receive buffer
char ReplyBuffer[] = "ack";
static uint32_t timer;

// Callback that prints received packets to the serial port
void udpSerialPrint(uint16_t dest_port, uint8_t src_ip[IP_LEN], uint16_t src_port, const char *data, uint16_t len){
  IPAddress src(src_ip[0],src_ip[1],src_ip[2],src_ip[3]);

  Serial.print("dest_port: ");
  Serial.println(dest_port);
  Serial.print("src_port: ");
  Serial.println(src_port);


  Serial.print("src_ip: ");
  ether.printIp(src_ip);
  Serial.print("\ndata: ");
  Serial.println(data);

  if(strcmp("1on",data) == 0) {
    digitalWrite(10, HIGH);
  }
  else if(strcmp("1off",data) == 0) {
    digitalWrite(10, LOW);
  }
  else if(strcmp("2on",data) == 0) {
    digitalWrite(13, HIGH);
  }
  else if(strcmp("2off",data) == 0) {
    digitalWrite(13, LOW);
  }

  ether.sendUdp(ReplyBuffer,sizeof(ReplyBuffer),dest_port, src_ip, src_port);

}

void setup(){
  Serial.begin(57600);
//  Serial.println(F("\n[backSoon]"));
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  // Change 'SS' to your Slave Select pin if you aren't using the default pin
  if (ether.begin(sizeof Ethernet::buffer, mymac, 53) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
#if STATIC
  ether.staticSetup(myip, gwip);
#else
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));
#endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);

  // Register udpSerialPrint() to port 1337
  ether.udpServerListenOnPort(&udpSerialPrint, 5000);

  // Register udpSerialPrint() to port 42.
  ether.udpServerListenOnPort(&udpSerialPrint, 42);
}

void loop(){
  // This must be called for ethercard functions to work.
  ether.packetLoop(ether.packetReceive());
}


/*
//Processing sketch to send test UDP packets.

import hypermedia.net.*;

 UDP udp;  // define the UDP object


 void setup() {
 udp = new UDP( this, 6000 );  // create a new datagram connection on port 6000
 //udp.log( true );     // <-- printout the connection activity
 udp.listen( true );           // and wait for incoming message
 }

 void draw()
 {
 }

 void keyPressed() {
 String ip       = "192.168.0.200";  // the remote IP address
 int port        = 1337;    // the destination port

 udp.send("Greetings via UDP!", ip, port );   // the message to send

 }

 void receive( byte[] data ) {       // <-- default handler
 //void receive( byte[] data, String ip, int port ) {  // <-- extended handler

 for(int i=0; i < data.length; i++)
 print(char(data[i]));
 println();
 }
*/
