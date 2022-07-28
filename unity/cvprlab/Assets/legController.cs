using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class legController : MonoBehaviour
{
    private LineRenderer lr;
    private Transform[] points;

    private void Awake() {
        lr = GetComponent<LineRenderer>();
    }

    public void SetUpLine(Transform[] points) {
        lr.positionCount = points.Length;
        this.points = points;
    }
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update() {
     for (int i = 0; i < points.Length; i++) {
        lr.SetPosition(i, points[i].position);
     }   
    }
}
