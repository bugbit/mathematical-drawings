#include "StdAfx.h"
#include "DIBUIXOS.H"

void calcpi(char *str,int n)
{
    int extra = 3;

    int len = 10 * (n + extra) / 3;
    int *a;
    int count = -2;
    int predigit = 0;
    int nines = 0;
	int aint=2;
	char *str2=str;
	int i,j,q,x,k;

	a=calloc(len,sizeof(int));
    for (j = 0; j < len; j++)
    {
        a[j] = 2;
    }
    for (j = 0; (j < len) && (count < n); j++)
    {
        q = 0;
        for (i = len - 1; i >= 0; i--)
        {
            x = 10 * a[i] + q * (i + 1);
            a[i] = (x % (2 * i + 1));
            q = x / (2 * i + 1);
        }
        a[0] = (q % 10);
        q /= 10;
        switch (q)
        {
            case 10:
                count++;
				*str2++='0'+predigit + 1;
                for (k = 0; k < nines; k++)
                {
                    count++;
                    *str2++='0';
                }
                predigit = 0;
                nines = 0;
                break;
            case 9:
                nines++;
                break;
            default:
                count++;
                *str2++='0'+predigit;
                predigit = q;
                if (nines == 0)
                {
                    continue;
                }
                for (k = 0; k < nines; k++)
                {
                    count++;
                    *str2++='9';
                }
                nines = 0;
        }
    }
	*str2='\x0';
	free(a);
	*str=*str++;
	*str='.';
}