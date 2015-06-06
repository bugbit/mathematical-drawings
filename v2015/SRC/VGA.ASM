	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "VGA.C"
	?debug	C E9A0EDAF46055647412E43
	?debug	C E990EDAF460A4449425549584F532E48
_TEXT	segment byte public use16 'CODE'
_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
_TEXT	segment byte public use16 'CODE'
	?debug	C E801055647412E43A0EDAF46
   ;	
   ;	 waitb()
   ;	
	?debug	L 4
	assume	cs:_TEXT
@waitb	proc	near
	?debug	B
	?debug	B
   ;	
   ;	{
   ;		asm {
   ;			mov	dx,3dah
   ;	
	?debug	L 7
	mov		dx,3dah
@1@30:
   ;	
   ;		}
   ;	l1:
   ;		asm {
   ;			in	al,dx
   ;	
	?debug	L 11
	in		al,dx
   ;	
   ;			test	al,8
   ;	
	?debug	L 12
	test		al,8
   ;	
   ;			jnz	l1
   ;	
	?debug	L 13
	jne	short @1@30
@1@114:
   ;	
   ;		}
   ;	l2:
   ;		asm {
   ;			in	al,dx
   ;	
	?debug	L 17
	in		al,dx
   ;	
   ;			test	al,8
   ;	
	?debug	L 18
	test		al,8
   ;	
   ;			jz	l2
   ;	
	?debug	L 19
	je	short @1@114
   ;	
   ;		}
   ;	}
   ;	
	?debug	L 21
	ret	
	?debug	E
	?debug	E
@waitb	endp
   ;	
   ;	void initvideo()
   ;	
	?debug	L 23
	assume	cs:_TEXT
@initvideo	proc	near
	?debug	B
	push	di
	?debug	B
   ;	
   ;	{
   ;		asm {
   ;			mov	ax,13h
   ;	
	?debug	L 26
	mov		ax,13h
   ;	
   ;			int	10h
   ;	
	?debug	L 27
	int		10h
   ;	
   ;		}
   ;		waitb();
   ;	
	?debug	L 29
	call	near ptr @waitb
   ;	
   ;		asm {
   ;			//clear palette
   ;			mov	dx,3c8h
   ;	
	?debug	L 32
	mov		dx,3c8h
   ;	
   ;			xor	al,al
   ;	
	?debug	L 33
	xor		al,al
   ;	
   ;			out	dx,al
   ;	
	?debug	L 34
	out		dx,al
   ;	
   ;			inc	dx
   ;	
	?debug	L 35
	inc		dx
   ;	
   ;			mov	cx,768
   ;	
	?debug	L 36
	mov		cx,768
@2@254:
   ;	
   ;		}
   ;	ll1:
   ;		asm {
   ;			out	dx,al
   ;	
	?debug	L 40
	out		dx,al
   ;	
   ;			loop	ll1
   ;	
	?debug	L 41
	loop	short @2@254
   ;	
   ;			//400 rows
   ;			mov	dx,3d4h
   ;	
	?debug	L 43
	mov		dx,3d4h
   ;	
   ;			mov	ax,00009h
   ;	
	?debug	L 44
	mov		ax,00009h
   ;	
   ;			out	dx,ax
   ;	
	?debug	L 45
	out		dx,ax
   ;	
   ;			//tweak
   ;			mov	ax,00014h
   ;	
	?debug	L 47
	mov		ax,00014h
   ;	
   ;			out	dx,ax
   ;	
	?debug	L 48
	out		dx,ax
   ;	
   ;			mov	ax,0e317h
   ;	
	?debug	L 49
	mov		ax,0e317h
   ;	
   ;			out	dx,ax
   ;	
	?debug	L 50
	out		dx,ax
   ;	
   ;			mov	dx,3c4h
   ;	
	?debug	L 51
	mov		dx,3c4h
   ;	
   ;			mov	ax,0604h
   ;	
	?debug	L 52
	mov		ax,0604h
   ;	
   ;			out	dx,ax
   ;	
	?debug	L 53
	out		dx,ax
   ;	
   ;			;
   ;	
	?debug	L 54
	;	
   ;	
   ;			mov	dx,3c4h
   ;	
	?debug	L 55
	mov		dx,3c4h
   ;	
   ;			mov	ax,0f02h
   ;	
	?debug	L 56
	mov		ax,0f02h
   ;	
   ;			out	dx,ax
   ;	
	?debug	L 57
	out		dx,ax
   ;	
   ;			mov	ax,0a000h
   ;	
	?debug	L 58
	mov		ax,0a000h
   ;	
   ;			mov	es,ax
   ;	
	?debug	L 59
	mov		es,ax
   ;	
   ;			xor	di,di
   ;	
	?debug	L 60
	xor		di,di
   ;	
   ;			mov	cx,32768
   ;	
	?debug	L 61
	mov		cx,32768
   ;	
   ;			xor	ax,ax
   ;	
	?debug	L 62
	xor		ax,ax
   ;	
   ;			rep	stosw
   ;	
	?debug	L 63
	rep	stosw	
   ;	
   ;			;
   ;	
	?debug	L 64
	;	
   ;	
   ;			//640 wide
   ;			mov	dx,3d4h
   ;	
	?debug	L 66
	mov		dx,3d4h
   ;	
   ;			mov	ax,05013h
   ;	
	?debug	L 67
	mov		ax,05013h
   ;	
   ;			out	dx,ax
   ;	
	?debug	L 68
	out		dx,ax
   ;	
   ;		}
   ;	}
   ;	
	?debug	L 70
	pop	di
	ret	
	?debug	E
	?debug	E
@initvideo	endp
   ;	
   ;	void closevideo()
   ;	
	?debug	L 72
	assume	cs:_TEXT
@closevideo	proc	near
	?debug	B
	?debug	B
   ;	
   ;	{
   ;		asm {
   ;			mov	ax,3h
   ;	
	?debug	L 75
	mov		ax,3h
   ;	
   ;			int	10h
   ;	
	?debug	L 76
	int		10h
   ;	
   ;		}
   ;	}
   ;	
	?debug	L 78
	ret	
	?debug	E
	?debug	E
@closevideo	endp
   ;	
   ;	void _fastcall  gprintlinexy(int x,int y,int color,char *str)
   ;	
	?debug	L 80
	assume	cs:_TEXT
@gprintlinexy	proc	near
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,6
	push	si
	push	di
	?debug	C E318000400160200
	?debug	C E603737472180A04000005636F6C6F72040AFAFF+
	?debug	C 000179040AFCFF000178040AFEFF00
	mov	word ptr [bp-2],ax
	mov	word ptr [bp-4],dx
	mov	word ptr [bp-6],bx
	?debug	B
   ;	
   ;	{
   ;		asm {
   ;			push	ds
   ;	
	?debug	L 83
	push		ds
   ;	
   ;			lds	si,str
   ;	
	?debug	L 84
	lds		si,[bp+4]
   ;	
   ;			mov	ax,0xf000
   ;	
	?debug	L 85
	mov		ax,0f000H
   ;	
   ;			mov	fs,ax
   ;	
	?debug	L 86
	mov		fs,ax
   ;	
   ;			mov	cx,size
   ;	
	?debug	L 87
	mov		cx,size
   ;	
   ;			mov	ax,0a000h
   ;	
	?debug	L 88
	mov		ax,0a000h
   ;	
   ;			mov	es,ax
   ;	
	?debug	L 89
	mov		es,ax
   ;	
   ;			mov	bx,y
   ;	
	?debug	L 90
	mov		bx,[bp-4]
   ;	
   ;			mov	ax,160
   ;	
	?debug	L 91
	mov		ax,160
   ;	
   ;			mul	bx
   ;	
	?debug	L 92
	mul		bx
   ;	
   ;			mov	di,ax
   ;	
	?debug	L 93
	mov		di,ax
   ;	
   ;			mov	dx,x
   ;	
	?debug	L 94
	mov		dx,[bp-2]
   ;	
   ;			cld
   ;	
	?debug	L 95
	cld	
@4@394:
   ;	
   ;		}
   ;		buletra:
   ;		asm {
   ;			lodsb
   ;	
	?debug	L 99
	lodsb	
   ;	
   ;			and	al,al
   ;	
	?debug	L 100
	and		al,al
   ;	
   ;			jz		fin
   ;	
	?debug	L 101
	je	short @4@926
   ;	
   ;			push	cx
   ;	
	?debug	L 102
	push		cx
   ;	
   ;			mov	cx,dx
   ;	
	?debug	L 103
	mov		cx,dx
   ;	
   ;			mov	ax,cx
   ;	
	?debug	L 104
	mov		ax,cx
   ;	
   ;			shr	ax,2
   ;	
	?debug	L 105
	shr		ax,2
   ;	
   ;			add	di,ax
   ;	
	?debug	L 106
	add		di,ax
   ;	
   ;			mov	ax,0102h
   ;	
	?debug	L 107
	mov		ax,0102h
   ;	
   ;			and	cl,3
   ;	
	?debug	L 108
	and		cl,3
   ;	
   ;			shl	ah,cl
   ;	
	?debug	L 109
	shl		ah,cl
   ;	
   ;			mov	dx,3c4h
   ;	
	?debug	L 110
	mov		dx,3c4h
   ;	
   ;			out	dx,ax
   ;	
	?debug	L 111
	out		dx,ax
   ;	
   ;			pop	cx
   ;	
	?debug	L 112
	pop		cx
   ;	
   ;		mov	ax,0a000h
   ;	
	?debug	L 113
	mov		ax,0a000h
   ;	
   ;		mov	es,ax
   ;	
	?debug	L 114
	mov		es,ax
   ;	
   ;		mov	ax,color
   ;	
	?debug	L 115
	mov		ax,[bp-6]
   ;	
   ;		mov	es:[di],al
   ;	
	?debug	L 116
	mov		es:[di],al
   ;	
   ;	
   ;	
   ;			loop	buletra
   ;	
	?debug	L 119
	loop	short @4@394
@4@926:
   ;	
   ;		}
   ;		fin:
   ;		asm {
   ;			pop	ds
   ;	
	?debug	L 123
	pop		ds
   ;	
   ;		}
   ;	}
   ;	
	?debug	L 125
	pop	di
	pop	si
	leave	
	ret	4
	?debug	C E60178040AFEFF000179040AFCFF0005636F6C6F+
	?debug	C 72040AFAFF0003737472180A040000
	?debug	E
	?debug	E
@gprintlinexy	endp
	?debug	C E9
	?debug	C FA00000000
_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
_DATA	ends
_TEXT	segment byte public use16 'CODE'
_TEXT	ends
	public	@gprintlinexy
	public	@closevideo
	public	@initvideo
	public	@waitb
_s@	equ	s@
	?debug	C EA010B
	?debug	C E31900000023010200
	?debug	C EC0D40677072696E746C696E657879191800
	?debug	C E31A00000023010200
	?debug	C EC0B40636C6F7365766964656F1A1800
	?debug	C E31B00000023010200
	?debug	C EC0A40696E6974766964656F1B1800
	?debug	C E31C00000023010200
	?debug	C EC064077616974621C1800
	end
