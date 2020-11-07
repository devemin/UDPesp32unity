//↓M5StickC ならこれを有効にし、Setup() でM5.begin() を行う
//#include <M5StickC.h>
#include <WiFi.h>
#include <WiFiUdp.h>


//ESP32 x Unity x UDP
//WiFi UDPにて送受信するサンプルです。

//参考：
//ESP32でUDP通信やってみた（ESP32インストール手順解説あり）
//https://qiita.com/Tsukkey/items/247285c703fbbc6c6cd2
//M5Stack同士でWiFi, UDPによる双方向リアルタイム同時通信する実験
//https://www.mgo-tec.com/blog-entry-udp-wifi-m5stack.html/3#title09
//２バイト以上のデータタイプはビットシフトしてバイト分割して送る、float は共用体を利用して送る
//https://hawksnowlog.blogspot.com/2016/11/sending-multibytes-with-serialwrite.html#float-4byte-%E3%81%AE%E6%83%85%E5%A0%B1%E3%82%92%E9%80%81%E4%BF%A1%E3%81%99%E3%82%8B%E6%96%B9%E6%B3%95

const char* ssid = "apname";
const char* password = "appassword";

const char* client_address = "192.168.0.33";  //送り先
const int client_port = 22222;  //送り先
const int server_port = 22224;  //このESP32 のポート番号


#define RECVDATANUM 9
#define SENDDATANUM 9

WiFiUDP udp;

//データ送受信のfloat のやり取りの為に、共用体を用いる。
//共用体は、下記宣言で4byte のバイナリデータなのに、.ival や .fval 等とアクセスすることで中身を int や float に読み替えられる機能
typedef union {
  int32_t ival;
  float fval;
  byte binary[4];
} uf;


uf r_ufdata[RECVDATANUM];
uf s_ufdata[SENDDATANUM];




void setup() {
  Serial.begin(115200);

  //M5StickC の時は実行
  //M5.begin();

  //WiFi 初期化
  Serial.println("[ESP32] Connecting to WiFi network: " + String(ssid));
  WiFi.disconnect(true, true);
  delay(500);
  WiFi.begin(ssid, password);
  while( WiFi.status() != WL_CONNECTED) {
    delay(500);  
  }  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  //UDP 開始
  udp.begin(server_port);
  delay(500);  

}


//受信
//パケットが来ていれば、RECVDATANUM 分だけr_ufdata配列に保存する
void receiveUDP(){
    int packetSize = udp.parsePacket();
    byte tmpbuf[128];

    //今回はUnity にここに来る処理は入れてないが、RECVDATANUM 分のfloatが来た場合の処理　の想定
    if(packetSize == RECVDATANUM){
      //Serial.println("recv");
      for (int a=0; a<RECVDATANUM; a++) 
      {
        udp.read(tmpbuf, sizeof(uf));
        for (int b=0; b<sizeof(uf); b++) 
        {
          r_ufdata[a].binary[b] = tmpbuf[a*sizeof(uf) + b];
        }
        //Serial.println("recv: " + String(r_ufdata[a].ival) );
        Serial.println("recv: " + String(r_ufdata[a].fval) );
      }
    }
    //Unity のテストボタンで４バイトのデータが送られてきた時の処理    
    else if(packetSize == 4)
    {
      //Serial.println("recv");
      udp.read(tmpbuf, sizeof(uf));
      for (int a=0; a<sizeof(uf); a++) 
      {
        r_ufdata[0].binary[a] = tmpbuf[a];
      }
      Serial.println("recv: " + String(r_ufdata[0].ival) );
    }
}


//送信
//SENDDATANUM 分送る
void sendUDP(){
  String test = "";
  
  //Serial.println("send");    
  udp.beginPacket(client_address, client_port);

  for (int a=0; a<SENDDATANUM; a++) {
    udp.write(s_ufdata[a].binary, sizeof(uf) );
    //test += String(s_ufdata[a].ival) + ", ";
    test += String(s_ufdata[a].fval) + ", ";
  }
  Serial.println("send: " + test );
  
  udp.endPacket();
}

 
void loop() {

  //もしデータパケットが来ていれば受信する
  receiveUDP();


  //テストデータとして、0.0 ～ 0.5 のデータ値を作って送る
  //たとえばジャイロやセンサのデータを少数のまま送信できます。
  for (int c=0; c<SENDDATANUM; c++) {
    s_ufdata[c].fval = ( 0.1 * (float)c );
  }

  //こちらはint データの送信例
  /*
  for (int c=0; c<SENDDATANUM; c++) {
    s_ufdata[c].ival = c;
  }
  */
    
  sendUDP();


  delay(500);
  
}
