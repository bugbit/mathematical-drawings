#include <dos.h>
#include <memory.h>

#include "dibuixos.h"

static int check386();

int checkSystem()
{
	if (check386())
	{
		dw_errorcode=DWE_NO386;
		return -1;
	}
	if (_8087!=3)
	{
		dw_errorcode=DWE_NO387;
		return -1;
   }

	return 0;
}

int check386()
{
	asm {
								//	8086 CPU check
								//	Bits 12-15 are always set on the 8086 processor.
		pushf					// save EFLAGS
		pop	bx				// store EFLAGS in BX
		mov	ax,0FFFh		// clear bits 12-15 in EFLAGS
		and	ax,bx
		push	ax				// store new EFLAGS value on stack
		popf					// replace current EFLAGS value
		pushf					// set new EFLAGS
		pop	ax				// store new EFLAGS in AX
		and	ax,0F000h	// if bits 12-15 are set, then 8086/8088
		cmp	ax,0F000h
		je	no386				// je => 8086
								//	80286 CPU check
								//	Bits 12-15 are always clear on the 80286 processor.
		or	bx,0F000h		// try to set bits 12-15
		push	bx
		popf
		pushf
		pop	ax
		and	ax,0F000h	// if bits 12-15 are cleared, then 80286
		jnz	is386			// jz => 80286

	}
no386:
	asm {
		mov	dw_errorcode,DWE_NO386
		mov	ax,-1
		jmp	chksysok
	}
is386:
	asm {
		xor	ax,ax
	}
chksysok:
}