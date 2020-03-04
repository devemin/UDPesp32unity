#include <WiFi.h>
#include <WiFiUdp.h>


//UDP通信について
//https://qiita.com/Tsukkey/items/247285c703fbbc6c6cd2


const char* ssid = "apssid";
const char* password = "passpass";

static WiFiUDP wifiUdp; 
static const char *kRemoteIpadr = "192.168.x.x";
static const int kRmoteUdpPort = 22222; //送信先のポート
static const int kLocalPort = 7000;  //自身のポート


byte x = 0;


void setup() {
  
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }


  while( WiFi.status() != WL_CONNECTED) {
    delay(500);  
  }  
  wifiUdp.begin(kLocalPort);
  

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  
}

void loop() {

  wifiUdp.beginPacket(kRemoteIpadr, kRmoteUdpPort);
  wifiUdp.write(x);
  wifiUdp.endPacket();  

  //float 等送る時は共用体を利用するとのこと
  //https://hawksnowlog.blogspot.com/2016/11/sending-multibytes-with-serialwrite.html#float-4byte-%E3%81%AE%E6%83%85%E5%A0%B1%E3%82%92%E9%80%81%E4%BF%A1%E3%81%99%E3%82%8B%E6%96%B9%E6%B3%95

  delay(300);

  x++;
  if (x >= 255) {
    x = 0;
  }
}
