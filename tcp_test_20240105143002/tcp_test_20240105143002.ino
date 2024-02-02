#include <EtherCard.h>
#include <IPAddress.h>

#define STATIC 0  // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,100,51 };
// gateway ip address
static byte gwip[] = { 192,168,100,1 };
#endif


// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x35 };

byte Ethernet::buffer[500]; // tcp/ip send and receive buffer
//const char *data;
//byte tcpOpcode = 0x00;

//int tcpIndex = 0;

//- TCP 로 받는 패킷의 데이터를 받기 위한 변수들

//#define STX 0x02

//#define ETX 0x03

//#define OPCODE_1 0x11

//#define OPCODE_2 0x12

//#define OPCODE_3 0x13

//#define OPCODE_4 0x14

int i=0;
char* data;
long time=0;

void setup(){
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(57600);
  Serial.println(F("\n[backSoon]"));

  if (ether.begin(sizeof Ethernet::buffer, mymac,53) == 0)
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
}


void loop(){

  uint16_t payloadPos = ether.packetLoop(ether.packetReceive());

  if (payloadPos)
  {
     char* incomingData = (char *) Ethernet::buffer + payloadPos;
     data = incomingData + i;


/*
    for(int i=payloadPos;Ethernet::buffer[i];i++){
     Serial.print((char)Ethernet::buffer[i]);
     data=(char *)Ethernet::buffer[i];
    }
   Serial.println(data);
*/
//
//    Serial.println(ether.packetReceive());
//    Serial.println(payloadPos,DEC);

//data = incomingData;
    Serial.println("INCOMING TCP PACKET"); //PORT 80
    Serial.println("-------------------");
    Serial.println(incomingData); 
//    Serial.println(incomingData[0]); 
    Serial.println("-------------------");
    cmpCmd(data);
/*
    cmpCmd(incomingData);

    if(strcmp("1on",incomingData) == 0) {
      digitalWrite(10, HIGH);
    }
    else if(strcmp("1off",incomingData) == 0) {
      digitalWrite(10, LOW);
    }
    else if(strcmp("2on",incomingData) == 0) {
      digitalWrite(13, HIGH);
    }
    else if(strcmp("2off",incomingData) == 0) {
      digitalWrite(13, LOW);
    }     
*/ 
    // I want to send or write incomingData via TCP 
    

  }

   delay(1000);
}
  
void cmpCmd(char* data){


    if(strncmp("1on",data,3) == 0) {
      digitalWrite(10, HIGH);
      i=i+3;
    }
    else if(strncmp("1off",data,4) == 0) {
      digitalWrite(10, LOW);
      i=i+4;
    }
    else if(strncmp("2on",data,3) == 0) {
      digitalWrite(13, HIGH);
      i=i+3;
    }
    else if(strncmp("2off",data,4) == 0) {
      digitalWrite(13, LOW);
      i=i+4;
    } 

    Serial.println(i);
    delay(1000);
     // I want to send or write incomingData via TCP 

/*
    if(strstr(incomingData,"1on") != 0){
      digitalWrite(10, HIGH);
    }
    else if(strstr(incomingData,"1off") != 0){
      digitalWrite(10, LOW);
    }
*/
}