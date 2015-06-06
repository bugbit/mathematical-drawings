#include "test1\vesa.h"
#include "test1\dpmi32.h"

unsigned char *screen;

static void initvideo_nolfb();
static void initvideo_lfb();

void waitb()
{
	asm
	{
		mov	dx,3dah
	}
wb1:
	asm
	{
		in	al,dx
		test	al,8
		jnz	wb1
	}
wb2:
	asm
	{
		in	al,dx
		test	al,8
		jz	wb2
	}
}

void initvideo()
{
	initvideo_lfb();
}

static void initvideo_nolfb()
{
	struct regs regs;
	unsigned long sel;

	regs.EAX=0x13;
	interrupcion_real(0x10, &regs);
	/*
	waitb();
	//clear palette
	asm
	{
		mov	dx,3c8h
		xor	al,al
		out	dx,al
		inc	dx
		mov	cx,768
	}
vi1:
	asm
	{
		out	dx,al
		loop	vi1
		//400 rows
		mov	dx,3d4h
		mov	ax,00009h
		out	dx,ax
		//tweak
		mov	ax,00014h
		out	dx,ax
		mov	ax,0e317h
		out	dx,ax
		mov	dx,3c4h
		mov	ax,0604h
		out	dx,ax
		mov	dx,3c4h
		mov	ax,0f02h
		out	dx,ax
		mov	ax,0a000h
		mov	es,ax
		xor	di,di
		mov	cx,32768
		xor	ax,ax
		rep	stosw
		//640 wide
		mov	dx,3d4h
		mov	ax,05013h
		out	dx,ax
	}
   */
	// screen = 0xA000

	dpmiSegToDescriptor(0xA000,&sel);
   screen=(unsigned char *) (sel << 4);
}

static void initvideo_lfb()
{
	struct regs regs;
	unsigned long RealSeg;
	unsigned long DosSel;

	// Allocate some DOS memory

	dpmiAllocateDOSMemory (256, &RealSeg, &DosSel);

	// Preload rmcall register structure

	regs.SS = 0;
	regs.SP = 0;
	regs.ES = (unsigned short) RealSeg;
	regs.EDI = 0;
	regs.EAX = 0x4F01;
	regs.ECX = 0x0101;

	// Call the VESA BIOS

	//dpmiSimulateInterrupt(0x10, &rmcall);
	interrupcion_real(0x10, &regs);

	// Get the pointer to the LFB

	dpmiMapPhysicalRegion ( * (unsigned long *) ((RealSeg << 4) + 40), \
								  640 * 480, (unsigned long *) &screen);

	// Free the DOS memory block as we don't need it any more

	dpmiFreeDOSMemory(DosSel);

	// Set the video mode. This could be done with 3 lines of

	regs.EBX = 0x4101;
	regs.EAX = 0x4F02;
	interrupcion_real(0x10, &regs);
}

void deinitvideo()
{
	struct regs regs;

	// Set video mode back to text mode. Again, this could be done

	regs.EAX = 0x0003;
	interrupcion_real(0x10, &regs);

}
