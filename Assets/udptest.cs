using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine.UI;

//Unity でUDP通信受信
//https://qiita.com/nenjiru/items/8fa8dfb27f55c0205651

//パケット構造作ってる
//https://younaship.com/2018/12/31/unity%E4%B8%8A%E3%81%A7websocket%E3%82%92%E7%94%A8%E3%81%84%E3%81%9F%E9%80%9A%E4%BF%A1%E6%A9%9F%E8%83%BD%E3%83%9E%E3%83%AB%E3%83%81%E3%83%97%E3%83%AC%E3%82%A4%E3%82%92%E5%AE%9F%E8%A3%85%E3%81%99/

//タイムアウトについて
//https://teratail.com/questions/56000

public class udptest : MonoBehaviour
{
    int LOCA_LPORT = 22222;
    static UdpClient udp;
    Thread thread;


    void Start()
    {
        udp = new UdpClient(LOCA_LPORT);
        udp.Client.ReceiveTimeout = 0;
        thread = new Thread(new ThreadStart(ThreadMethod));
        thread.Start();



    }

    void Update()
    {

    }
    void OnApplicationQuit()
    {
        thread.Abort();
    }

    private static void ThreadMethod()
    {
        while (true)
        {
            IPEndPoint remoteEP = null;
            byte[] data = udp.Receive(ref remoteEP);
            Debug.Log(data[0].ToString());

            //連続したバイトを2byte や4byte のデータタイプ(int や float など)に変換するときは、ビットシフトなど利用
            //送られてくるバイトをシフトしてAND演算など
            // float newdata = (data[0] << 8) & (data[1]);

        }
    }
}
