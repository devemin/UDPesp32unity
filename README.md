# UDPesp32unity
UDP test, ESP32 x Unity

# ESP32 x Unity で UDP通信をテストする

こんにちは。このリポジトリでは、簡単に WiFiを使った UDP通信のテストを行います。

ESP32 と PCにて、それぞれ送受信を行います。　ESP32 便利すぎ？

# 動作

https://twitter.com/devemin/status/1234733593882005504

最初の１方向通信の動作、今は送受信に更新しました。
加えて、Float と Int の両方の送信例を書きました。（2020/11/8）

ESP32 → Unity：　float のデータを９バイト送ってます。 Arduino IDE, Unity それぞれシリアルモニタ or コンソールでデータが表示されます。

Unity → ESP32：　Unity 画面上のボタンを押すと、４バイトのInt 整数データを送信。　ESP32 で受信し、シリアルモニタにそれが表示されます
（ESP32 受信部では、パケットのバイト数で処理分けしています。）

# コード

Arduino: udptest.ino

Unity: udptest.cs

# 使い方

1. Arduino IDEで、udptest.ino を開きます。（Arduino IDE環境構築は下記URL参照）

　（私は秋月WROOM32D開発キット win10 で、シリアルのドライバインストールが必要でした。）
　（M5StickC でも出来ると思います。その場合は、udptest.ino 冒頭の #include <M5StickC.h> と、setup() 内の M5.begin() を有効にしてください。）

2. Arduino IDE 上で、コード内最初のWiFIアクセスポイントの SSID, pass、そして送り先PCのIPアドレス　の３か所を各環境に合わせ入力し、書き込んでください。wifi接続されます。

　（SSID はアクセスポイントの名前、送り先IPアドレスは、win 10 ならスタート→ 入力「cmd」 → 「Enter」 → 入力「ipconfig /all」 → 使ってるネットワークのアドレスを調べる（イーサネットやワイヤレスネットワークの IP v4 アドレス。192.168.0.10 等）　virtualネットワーク等色々ありますので間違えないよう）　）

3. Unity でこのリポジトリをダウンロードし開きます。SampleScene シーンを開きます。
　udptest.cs 最初の方の相手IPアドレス(ESP32)を入力します。（ESP32が正しくWiFI につながれば、Arduino IDE シリアルモニタ上で最初に表示されるはずです。見逃したらリセットボタンでも押してみてください。）

　（UDPcontrolオブジェクトに、udptest.cs スクリプトをアタッチしております。）

4. 再生ボタンを押すと、画面に変化はありませんが、待ち受け状態になります。コンソールに受信したデータが表示されます。（されない場合はIPアドレスやポート番号等チェック）

5. 画面内の「send」ボタンを押すと、ESP32 へデータを送信します。

6. これで送受信できました！　float または Int32 で送受信するサンプルとなりますので、適宜コードをご変更ください。

　(つながらない場合は、Arduino, Unity が同じwifi ネットワークにあること、ポートを揃えてるかどうか等、ご確認下さい。)

 （ＰＣ再インストールして試したところ、Windows 10 のネットワークプロファイルが「パブリック」だとPCでUDP受信できず、「プライベート」にしたら受信できました。受信できないときは、ファイヤーウォール設定のポートの設定もご確認下さい。）


# 参考にしたURL。

ほぼこちらの方々のコードを参考にさせてもらっています。　ありがとうございます。

参考１   Qiita UnityでUDPを受信してみる

https://qiita.com/Tsukkey/items/247285c703fbbc6c6cd2

参考２   Qiita ESP32でUDP通信やってみた（ESP32インストール手順解説あり）

https://qiita.com/nenjiru/items/8fa8dfb27f55c0205651

参考３　 M5Stack同士でWiFi, UDPによる双方向リアルタイム同時通信する実験

https://www.mgo-tec.com/blog-entry-udp-wifi-m5stack.html/3#title09

# その他

当環境　Unity 2019.1.10f1　　　Arduino IDE 1.8.9

MIT Licence

@devemin   https://twitter.com/devemin

もし良かったらスターやコメントお願い致します♪

