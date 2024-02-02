#include <UIPEthernet.h>

#define LED1 10
#define LED2 13
#define	CR	13
#define	LF	10
char	TermStr[5] = { CR, LF, 0 };

EthernetServer server = EthernetServer(1000);

void setup()
{
  Serial.begin(115200);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);

  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
  IPAddress myIP(192,168,100,6);

  Ethernet.begin(mac,myIP);

  server.begin();
}

void loop()
{
  size_t size;

  if (EthernetClient client = server.available())
    {
      while((size = client.available()) > 0)
        {
          uint8_t* msg = (uint8_t*)malloc(size);
          size = client.read(msg,size);
          Serial.write(msg,size);
          
          if(strncmp("1on",msg,3) == 0) {
            digitalWrite(LED1, HIGH);
//            client.println("1on");
          }
          else if(strncmp("1off",msg,4) == 0) {
            digitalWrite(LED1, LOW);
//            client.println("1off");
          }
          else if(strncmp("2on",msg,3) == 0) {
            digitalWrite(LED2, HIGH);
//            client.println("2on");
          }
          else if(strncmp("2off",msg,4) == 0) {
            digitalWrite(LED2, LOW);
//            client.println("2off");
          }
          else if(strncmp("1r",msg,2) == 0) {
            int st = digitalRead(LED1);
            if(st == 1) {
                client.println("1on");
//              client.write("1on",3);
//              client.write(13);
//              client.write(10);
            }
            else if(st == 0) {
                client.println("1off");
//              client.write("1off",4);
//              client.write(TermStr,sizeof(TermStr));
//              client.write(13);
//              client.write(10);
            }
          }
          else if(strncmp("2r",msg,2) == 0) {
            int st = digitalRead(LED2);
            if(st == 1) {
                client.println("2on");
//              client.write("2on",3);
//              client.write(TermStr,sizeof(TermStr));
//              client.write(13);
//              client.write(10);
            }
            else if(st == 0) {
                client.println("2off");
//              client.write("2off",4);
//              client.write(TermStr,sizeof(TermStr));
//              client.write(13);
//              client.write(10);
            }
          }

//          client.write(TermStr,sizeof(TermStr));
          free(msg);
        }
//        client.println("OK!");
//      client.stop();
    }
}
