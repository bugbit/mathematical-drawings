#include "pch.h"

#include "dibuixos.h"

int fastpi(char *str,int at,int numdec)
{
	int digits=at+numdec-1,ret=RET_SUCESS;
	int len,j,i;
	unsigned int *x,*r,*pi,carry,num,dem,c,q;
	
	digits++;
	len=digits*10/3+2;
	if ((x=calloc(len,sizeof(*x)))!=NULL)
	{
		if ((r=calloc(len,sizeof(*r)))!=NULL)
		{
			if ((pi=calloc(digits,sizeof(*pi)))!=NULL)
			{
				for (j = 0; j < len; j++)
					x[j] = 20;
				for (i = 0; i < digits; i++)
				{
					carry = 0;
					for (j = 0; j < len; j++)
					{
						num = (unsigned int)(len - j - 1);
						dem = num * 2 + 1;

						x[j] += carry;

						q = x[j] / dem;
						r[j] = x[j] % dem;

						carry = q * num;
					}
					
					pi[i] = (x[len-1] / 10);

					r[len - 1] = x[len - 1] % 10;

					for (j = 0; j < len; j++)
						x[j] = r[j] * 10;
				}
				
				c=0;
				
				for(i = digits - 1,j=0; i >=0; i--,j++)
				{
					pi[i] += c;
					c = pi[i] / 10;

					if (j>=at)
						*str++='0'+(pi[i] % 10);
				}
				*str++='\x0';
				
				free(pi);
			}
			else
				ret=seterror("fastpi: %s",strerror(errno));
			free(r);
		}
		else
			ret=seterror("fastpi: %s",strerror(errno));
		free(x);
	}
	else
		ret=seterror("fastpi: %s",strerror(errno));
		
	return ret;
}