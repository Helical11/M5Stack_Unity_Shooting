using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;
using System.IO.Ports;
using System.Threading;

public class Player : MonoBehaviour
{
    [SerializeField] GameObject bulletPrefab;
    private SerialPort serialPort;
    private float speed = 0.1f;
    public SerialHandler serialhandler;

        // 受信したデータを取得する
//        string data = serialPort.ReadLine();
//        Debug.Log(data);

        //弾を生成する
//        Instantiate(bulletPrefab, transform.position, transform.rotation);

    // Start is called before the first frame update
    void Start()
    {
        // シリアルポートのアップデートをトリガーにするイベントを登録する
        serialhandler.OnDataReceived += OnDataReceived;
    }

    void OnDataReceived(string message)
    {
        var data = message.Split(
                new string[] { "\n" }, System.StringSplitOptions.None);
        try
        {
            Debug.Log(data[0]);//Unityのコンソールに受信データを表示
        //弾を生成する
        Instantiate(bulletPrefab, transform.position, transform.rotation);

        }
        catch (System.Exception e)
        {
            Debug.LogWarning(e.Message);//エラーを表示
        }
    }

    // Update is called once per frame
    void Update()
    {

        //マウスの位置を取得する
        Vector3 mousePos = Input.mousePosition;

        //画面の真ん中を(0,0)にする
        mousePos.x = mousePos.x - (Screen.width / 2);
        mousePos.y = mousePos.y - (Screen.width / 2);

        //マウスの方向に回転させる
        Vector3 angle = transform.eulerAngles;

        angle.x = -mousePos.y * speed;
        angle.y = mousePos.x * speed;
        angle.z = 0;

        transform.eulerAngles = angle;

        }

    }
