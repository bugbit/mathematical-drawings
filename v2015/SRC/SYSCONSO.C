#include <stdio.h>
#include <string.h>
#include <process.h>

#include "dibuixos.h"

int _cdecl main(int argc,char *argv[])
{
	return dw_main();
}

int choosevideo(VIDEO *videos,int num,VIDEO **vp)
{
	int i=1,k;
	VIDEO *v=videos;

	do
	{
		printf("Choose driver video:\n");
		for(;i<=num;v++)
			printf(" %02d) %s\n",i++,v->name);
		printf(" 00) Exit\n");
		printf("\n>  ");
		scanf("%d",&k);
		if (!k)
			return DWE_EXIT;
	} while(k<0 || k>=vi_num);
	*vp=videos+(k-1);

	return 0;
}

int choosegrmode(GRMODE *g,int num,GRMODE **gp)
{
	int i=1,k;

	do
	{
		printf("Choose video mode:\n");
		for(;i<=num;g++)
			printf(" %02d) %dx%dx%d\n",i++,g->w,g->h,g->maxcol);
		printf(" 00) Exit\n");
		printf("\n>  ");
		scanf("%d",&k);
		if (!k)
		{
			return DWE_EXIT;
		}
	} while(k<0 && k>=num);
	*gp=g+(k-1);

	return 0;
}

void showError(char *msg)
{
	printf(msg);
}