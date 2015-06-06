#include "dpmi32.h"

int dpmiAllocateDOSMemory ( unsigned long SizeInBytes, DPMI_DosPtr *dp)
{
    /*
        si da error devuelve en ax el codigo de error,si no devuelve 0:
        07h (7)   memory control block destroyed
        08h (8)   insufficient memory
        si no devuelve 0 en ax
        si no error =>
            eax => Segment
            edx => Selector
    */
    __asm
    {
        mov     ebx,SizeInBytes
        add     ebx,15
        shr     ebx,4
        mov     eax,100h
        int     31h
        jc      @@error
        mov     ecx,dp
        mov     [ecx],eax
        mov     [ecx+4],edx
        xor     eax,eax
     @@error:
    }
    //ptr->segment=1;
    //ptr->selector=2;
}                                   

int dpmiSimulateInterrupt ( int intnum, RMCallStruc *rcregs )
{
  /*
   * es = segmento rcregs+2
   * edi = offset rcregs
   * bx = intnum
   * si no hay error devuelve 0
if failed:
  AX     = error code:
			  8012h - linear memory unavailable (stack)
			  8013h - physical memory unavailable (stack) (DPMI 1.0 only)
			  8014h - backing store unavailable (stack) (DPMI 1.0 only)
			  8021h - invalid value (CX too large) (DPMI 1.0 only)*/

   */
  __asm
  {  
    mov ax, rcregs+2
    mov es, ea
    mov	edi,rcregs
    mov	ebx,intnum    
    sub	ecx,ecx
    mov	eax,300h
    sbb	eax,eax
    inc	eax
  }
}

int dpmiMapPhysicalRegion ( unsigned long mapStart,unsigned long mapSize, unsigned long *mapLinear)
{
  /*
   * Algunos dispositivos con memoria mapeada como adaptadores de red y
tarjetas de video a veces tienen memoria mapeada en direcciones fisicas
que estan mas allá del primer mega de memoria que es accesible en modo real.
Bajo algunas implementaciones de DPMI , todas las direcciones son direcciones
lineales desde que ellas usan el mecanismo de paginado del 80386. Este
servicio puede ser usado por drivers de dispositivos para convertir de
direcciones fisicas a direcciones lineales.
Las direcciones lineales pueden ser usadas para acceder a la memoria del
dispositivo.
Algunas implementaciones de DPMI pueden no soportar esta llamada porque
puede ser usada para engañar la protección del sistema.
Esta llamada debe ser usada solamente por programa que requieran el acceso
directo a la memoria mapeada del dispositivo.

LLamada:
					  AX = 0800h
					  BX:CX = direccion fisica de memoria
					  SI:DI = longitud de la region a mapear en bytes

Devuelve:

					  Si funcion va bien:
					  Bandera de Carry bajada.
					  BX:CX =  Direccion lineal que puede ser usada para acceder
					  a la memoria fisica

					  Si funcion no va bien:
					  Carry flag alzado.

				Notas para el programador

					  o    Bajo implementaciones de  DPMI que no usan el mecanismo
							 de paginamiento del 80386, la funcion siempre ira
							 bien devolviendo la direccion lineal igual a la direccion
							 fisica.
					  o    Despues de la llamada el programador ha de construir un
							 selector apropiado(con la dirección lineal devuelta)
							 para acceder.
					  o    No usar esta funcion para acceder a direcciones de
							 memoria que esten por debajo del primer mega de memoria.
							 (direccionamiento de modo real)
!

_phyaddrmapp	proc	C
COMMENT !
si no hay error devuelve 0
y si hay error devuelve
	CF set on error
		 AX = error code (DPMI 1.0+) (8003h,8021h) (see #03143)
Notes:	implementations may refuse this call because it can circumvent protects
	the caller must build an appropriate selector for the memory
	do not use for memory mapped in the first megabyte
   */
  
  __asm
  {
      lea eax,mapStart
      mov bx,ss:[eax+2]
      mov cx,ss:[eax]
      lea eax,mapSize
      mov si,ss:[eax+2]
      mov di,ss:[eax]
      xor eax,eax
      mov ax,0800h
      int 31h
      jc error
      mov eax,mapLinear
      mov [eax+2],bx
      mov [eax],cx
      xor ax,ax
error:         sti
  }
}