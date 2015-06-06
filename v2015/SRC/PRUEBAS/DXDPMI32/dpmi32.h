#ifndef DPMI32_H

#define DPMI32_H

typedef struct
{
    unsigned int segment;
    unsigned int selector;
} DPMI_DosPtr;

typedef struct { unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
                 unsigned short flags, es, ds, fs, gs, ip, cs, sp, ss;
               } RMCallStruc;

int dpmiAllocateDOSMemory ( unsigned long sizeinbytes, DPMI_DosPtr *dp);

int dpmiSimulateInterrupt ( int intnum, RMCallStruc *rcregs );

int dpmiMapPhysicalRegion ( unsigned long mapStart,unsigned long mapSize, unsigned long *mapLinear);

#endif
