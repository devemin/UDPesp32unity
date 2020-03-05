#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "SSID";
const char* password = "passpass";

const char* client_address = "192.168.0.13";  //送り先
const int client_port = 22222;  //送り先
const int server_port = 22224;  //このESP32 のポート番号


//ESP32 x Unity x UDP
//3byte UDPにて送受信するサンプルです。

//参考：
//ESP32でUDP通信やってみた（ESP32インストール手順解説あり）
//https://qiita.com/Tsukkey/items/247285c703fbbc6c6cd2

//M5Stack同士でWiFi, UDPによる双方向リアルタイム同時通信する実験
//https://www.mgo-tec.com/blog-entry-udp-wifi-m5stack.html/3#title09


WiFiUDP udp;
boolean sendflag = false;

byte recvbuf[1024];
byte sendbuf[1024];
int recvbuf_size = 3;
int sendbuf_size = 3;

int c=0;


void connectToWiFi(){
}

void setup() {
  Serial.begin(115200);

  Serial.println("[ESP32] Connecting to WiFi network: " + String(ssid));
  WiFi.disconnect(true, true);
  delay(500);
  
  WiFi.begin(ssid, password);
  while( WiFi.status() != WL_CONNECTED) {
    delay(500);  
  }  
  udp.begin(server_port);
  delay(500);  

  randomSeed(1);
}


void receiveUDP(){
    int packetSize = udp.parsePacket();
    
    if(packetSize > 0){
      //Serial.println("recv");
      int getsize = udp.read(recvbuf, recvbuf_size);
      Serial.print(recvbuf[0], HEX);
      Serial.print(recvbuf[1], HEX);
      Serial.print(recvbuf[2], HEX);
      Serial.print("\n");
    }
}

void sendUDP(){
  if(sendflag){
    //Serial.println("send");    
    udp.beginPacket(client_address, client_port);
    udp.write(sendbuf, sendbuf_size);
    udp.endPacket();
    sendflag = false;
  }
}

 
void loop() {
  receiveUDP();


  if (c>= 10) {
    sendflag = true;
    sendbuf[0] = random(0,255);
    sendbuf[1] = random(0,255);
    sendbuf[2] = random(0,255);

    sendUDP();
    c = 0;
  }
  delay(100);
  c++;
  
}
