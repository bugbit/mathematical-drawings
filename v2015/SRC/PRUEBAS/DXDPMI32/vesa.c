#include "dpmi32.h"

int initvideo()
{
    DPMI_DosPtr ptr;
    int ret;
    RMCallStruc rmcall;

    // Allocate some DOS memory

    ret=dpmiAllocateDOSMemory(256, &ptr);
    
    if (ret==0)
    {
      rmcall.ss = 0;
      rmcall.sp = 0;
      rmcall.es = (unsigned short) ptr.segment;
      rmcall.edi = 0;
      rmcall.eax = 0x4F01;
      rmcall.ecx = 0x0101;

      // Call the VESA BIOS modo 640x480 256 Colores

      ret=dpmiSimulateInterrupt(0x10, &rmcall);
      if (ret==0)
      {
	// Get the pointer to the LFB

    dpmiMapPhysicalRegion ( * (unsigned long *) ((RealSeg << 4) + 40), \
                       640 * 480, (unsigned long *) &screen);

// Free the DOS memory block as we don't need it any more

dpmiFreeDOSMemory(DosSel);

// Set the video mode. This could be done with 3 lines of
// inline assembly but we don't want to use any assembly here

rmcall.ebx = 0x4101;
rmcall.eax = 0x4F02;
dpmiSimulateInterrupt(0x10, &rmcall);

      }

    }
  
    return ret;
}

void deinitvideo()
{
}
