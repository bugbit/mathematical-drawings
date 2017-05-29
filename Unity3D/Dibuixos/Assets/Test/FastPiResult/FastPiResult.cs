using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FastPiResult : MonoBehaviour {
    int digits = 200;
    // Use this for initialization
    void Start () {
        var pWatch = new System.Diagnostics.Stopwatch();

        pWatch.Start();

        digits++;

        uint[] x = new uint[digits * 10 / 3 + 2];
        uint[] r = new uint[digits * 10 / 3 + 2];

        uint[] pi = new uint[digits];

        for (int j = 0; j < x.Length; j++)
            x[j] = 20;

        for (int i = 0; i < digits; i++)
        {
            uint carry = 0;
            for (int j = 0; j < x.Length; j++)
            {
                uint num = (uint)(x.Length - j - 1);
                uint dem = num * 2 + 1;

                x[j] += carry;

                uint q = x[j] / dem;
                r[j] = x[j] % dem;

                carry = q * num;
            }


            pi[i] = (x[x.Length - 1] / 10);


            r[x.Length - 1] = x[x.Length - 1] % 10; ;

            for (int j = 0; j < x.Length; j++)
                x[j] = r[j] * 10;
        }

        var result = "";

        uint c = 0;

        for (int i = pi.Length - 1; i >= 0; i--)
        {
            pi[i] += c;
            c = pi[i] / 10;

            result = (pi[i] % 10).ToString() + result;
        }

        pWatch.Stop();
        Debug.Log(string.Format("Calculate pi: {0}", pWatch.ElapsedMilliseconds));
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
