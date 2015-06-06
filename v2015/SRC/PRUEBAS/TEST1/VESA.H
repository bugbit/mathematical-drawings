#ifndef	VESA_H

#define	VESA_H

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char *screen;

void waitb();
void initvideo();
void deinitvideo();

#ifdef __cplusplus
}
#endif

#endif
