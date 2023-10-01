using System.Collections;
using System.Collections.Generic;
//using System.Numerics;
using Unity.VisualScripting;
using UnityEngine;

public class Shot : MonoBehaviour
{
    [SerializeField] GameObject bulletPrefab;
//    float power = 300f;
    float speed = 0.1f;
    // Start is called before the first frame update
    void Start()
    {

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

        //左クリックで弾を撃つ
        if (Input.GetMouseButtonDown(0))
        {
            //クリック時の処理
            Debug.Log("クリック");

            //弾を生成する
            Instantiate(bulletPrefab, transform.position, transform.rotation);

        }
    }
}
