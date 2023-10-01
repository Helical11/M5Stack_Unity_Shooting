using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class BulletManager : MonoBehaviour
{
    private float speed = 0.1f;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        transform.position += transform.forward * speed;
        Destroy(this.gameObject, 3.0f);
    }
}
