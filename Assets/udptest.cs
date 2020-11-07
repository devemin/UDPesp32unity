using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System;
using UnityEngine.Experimental.GlobalIllumination;

//Unity でUDP通信受信
//https://qiita.com/nenjiru/items/8fa8dfb27f55c0205651

//パケット構造作ってる
//https://younaship.com/2018/12/31/unity%E4%B8%8A%E3%81%A7websocket%E3%82%92%E7%94%A8%E3%81%84%E3%81%9F%E9%80%9A%E4%BF%A1%E6%A9%9F%E8%83%BD%E3%83%9E%E3%83%AB%E3%83%81%E3%83%97%E3%83%AC%E3%82%A4%E3%82%92%E5%AE%9F%E8%A3%85%E3%81%99/

//タイムアウトについて
//https://teratail.com/questions/56000

public class udptest : MonoBehaviour
{
    int LOCAL_PORT = 22222;
    static UdpClient udp;
    static UdpClient udp_send;

    Thread thread;

    const int datanum = 9;
    static float[] f_buf = new float[datanum];
    static Int32[] i_buf = new Int32[datanum];


    string host = "192.168.0.62";
    int port = 22224;

    // Start is called before the first frame update
    void Start()
    {
        udp = new UdpClient(LOCAL_PORT);
        udp_send = new UdpClient();
        udp.Client.ReceiveTimeout = 0;          //0にしてみたら通信できたけど、タイムアウト０＝
        udp_send.Connect(host, port);
        thread = new Thread(new ThreadStart(ThreadMethod));
        thread.Start();
    }

    // Update is called once per frame
    void Update()
    {
        //アクセス例
        //Debug.Log(i_buf[1].ToString());
        //Debug.Log(f_buf[2].ToString());
    }
    void OnApplicationQuit()
    {
        udp_send.Close();
        thread.Abort();
    }

    private static void ThreadMethod()
    {
        String test;

        while (true)
        {
            IPEndPoint remoteEP = null;
            byte[] data = udp.Receive(ref remoteEP);
            //Debug.Log(data.Length.ToString());

            //パケットサイズが正しければ処理開始
            if (data.Length == datanum * 4 ) // float または Int32 のサイズとして 4
            {
                test = "";

                for (int a = 0; a<datanum; a++)
                {
                    //i_buf[a] = BitConverter.ToInt32(data, a * sizeof(Int32) );
                    //test += i_buf[a].ToString() + ", ";

                    f_buf[a] = BitConverter.ToSingle(data, a * sizeof(float) );
                    test += f_buf[a].ToString() + ", ";
                }
                Debug.Log(test);
            }
        }
    }


    public void senddataUDP()
    {
        //4byte だけテストで送る
        //0x36353433 = 909456435
        //送るバイト順の、処理順に注意
        //送信成功したら、ESP32 のシリアルモニタで、909456435と表示されます。
        byte[] data = { 0x33, 0x34, 0x35, 0x36};
        udp_send.Send(data, 4);

        Debug.Log("Data send! check your ESP32 serial monitor.");
    }

}