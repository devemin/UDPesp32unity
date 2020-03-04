# UDPesp32unity
UDP test, ESP32 x Unity

# ESP32 x Unity で UDP通信をテストする

こんにちは。このリポジトリでは、簡単に UDP通信のテストを行います。

ESP32(送信) と PC側(受信)にて行います。

買ってきて30分で出来て感動しました・・・！ ESP32 便利すぎ？

# 動作

https://twitter.com/devemin/status/1234733593882005504



# 使い方

1. Arduinoで、udptest.ino を開きます。（Arduino IDE環境構築は下記URL参照）

　（私は秋月WROOM32D開発キット win10 で、シリアルのドライバインストールが必要でした。）

2. Arduino IDE 上で、コード内最初のSSID, pass, 送り先IPアドレス　の３か所を各環境に合わせ入力し、書き込んでください。wifi接続されます。

　（SSID はアクセスポイントの名前、送り先IPアドレスは、win 10 ならスタート→ 入力「cmd」 → 「Enter」 → 入力「ipconfig /all」 → 使ってるネットワークのアドレスを調べる（イーサネットやワイヤレスネットワークの IP v4 アドレス。192.168.0.10 等）　virtualネットワーク等色々ありますので間違えないよう）　）

3. Unity でこのリポジトリをダウンロードし開きます。Scenes/SampleScene シーンを開きます。

　（UDPcontrolオブジェクトに、udptest.cs スクリプトをアタッチしております。）

4. 再生ボタンを押すと、画面に変化はありませんが、待ち受け状態になります。データ受信するとDebugコンソールに受信したバイトの数字が表示されます。

5. 接続されました！　適宜その送受信のコードをご変更ください。

　(つながらない場合は、Arduino, Unity が同じwifi ネットワークにあること、ポートを揃えてるかどうか等、ご自身でご確認下さいね☆　)


# 参考にしたURL。

ほぼこちらのqiita のコードを参考にさせてもらっています。　ありがとうございます。

参考１   Qiita UnityでUDPを受信してみる

https://qiita.com/Tsukkey/items/247285c703fbbc6c6cd2

参考２   Qiita ESP32でUDP通信やってみた（ESP32インストール手順解説あり）

https://qiita.com/nenjiru/items/8fa8dfb27f55c0205651


# その他

当環境　Unity 2019.1.10f1　　　Arduino IDE 1.8.9

MIT Liscence

@devemin   https://twitter.com/devemin

もし良かったらスターやコメントお願い致します♪

