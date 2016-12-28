#include "pch.h"

#include "dibuixos.h"

typedef struct
{
	LISTDECIMALPI listpi;
} Pi;

static int pi_readargs(Pi *data,int argc, char **argv);
static int pi_init(Pi *data);
static int pi_initgl(Pi *data);
static void pi_run(Pi *data);
static void pi_deinit(Pi *data);

DIBUIXODEF dib_pi=
{
	"pi",sizeof(Pi),pi_readargs,pi_init,pi_initgl,pi_run,pi_deinit,
	{
		"show all decimals pi"
	}
};

int lpi_make(LISTDECIMALPI *lpi)
{
	int w=width/8,h=height/9;
	char *cars=glexBitmapMakeCars(w,h);
	
	if (cars==NULL)
		return RET_ERROR;
	
	lpi->cars=lpi->cars_act=cars;
	lpi->width=w;
	lpi->height=h;
	lpi->at=-1;
		
	return RET_SUCESS;
}

void lpi_next(LISTDECIMALPI *lpi,int ndec)
{
	int n,n1,n2;
	
	while(ndec>0)
	{
		if (lpi->at<0)
		{
			sprintf(&lpi->ninedig,"3.%09i",ninedigitsofpi(1));
			lpi->at=9-1;
			lpi->position=0;
		}
		else if(lpi->position>8)
		{
			sprintf(&lpi->ninedig,"%09i",ninedigitsofpi(lpi->at));
			lpi->at += 9;
			lpi->position=0;
		}
		n=9-lpi->position;
		n1=min(ndec,n);
		for(;n1>0;)
		{
			switch(*(lpi->cars_act))
			{
				case 0:
					lpi->cars_act=glexBitmapCarsScrollUp(lpi->cars);
					break;
				case '\n':
					lpi->cars_act++;
					break;
				default:
					*(lpi->cars_act++)=lpi->ninedig[lpi->position++];
					ndec--;
					n1--;
			}
		}
	}
}

void lpi_next_slow(LISTDECIMALPI *lpi)
{
	lpi_next(lpi,1);
}

void lpi_render(LISTDECIMALPI *lpi)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(0.0, 0.0, 1.0);
	glRasterPos2f(0, 13);
	glutBitmapString(GLUT_BITMAP_8_BY_13,lpi->cars);
	glxswap();	
}

static int pi_readargs(Pi *data,int argc, char **argv)
{
	return RET_SUCESS;
}

static int pi_init(Pi *data)
{
	return lpi_make(&data->listpi);
}

static int pi_initgl(Pi *data)
{
	return RET_SUCESS;
}

static void pi_run(Pi *data)
{
	int rate=40;
	
	while(timestuff(0,1,&data->listpi,lpi_next_slow,lpi_render,2*1000000)!=RET_CANCEL)
	{
		if (rate>10)
			rate -= 10;
		else if (rate>1)
			rate--;
	}
}

static void pi_deinit(Pi *data)
{
	FREE(data->listpi.cars);
}