	.include "asm/macros.inc"
	.include "unk_020215A0.inc"
	.include "global.inc"

	.extern _021D21F4
	.extern sub_02021C08
	.extern sub_02021DA8

	.text

	thumb_func_start sub_02021FB0
sub_02021FB0: ; 0x02021FB0
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x10
	bl NNS_G2dInitImageProxy
	ldr r1, [r4, #4]
	cmp r1, #3
	beq _02021FC8
	add r0, r4, #0
	bl sub_02021FDC
	pop {r4, pc}
_02021FC8:
	add r0, r4, #0
	mov r1, #1
	bl sub_02021FDC
	add r0, r4, #0
	mov r1, #2
	bl sub_02021FDC
	pop {r4, pc}
	.balign 4, 0
	thumb_func_end sub_02021FB0

	thumb_func_start sub_02021FDC
sub_02021FDC: ; 0x02021FDC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r2, [r5, #0x40]
	add r4, r1, #0
	cmp r2, #0
	beq _02021FEC
	bl sub_02021DA8
_02021FEC:
	cmp r4, #1
	bne _02021FFA
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r1, [r5, #0x34]
	ldr r0, [r0]
	b _02022000
_02021FFA:
	ldr r0, _02022020 ; =0x04001000
	ldr r1, [r5, #0x38]
	ldr r0, [r0]
_02022000:
	ldr r0, [r5]
	add r5, #0x10
	add r2, r4, #0
	add r3, r5, #0
	bl NNS_G2dLoadImageVramTransfer
	cmp r4, #1
	bne _02022018
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r0, [r0]
	pop {r3, r4, r5, pc}
_02022018:
	ldr r0, _02022020 ; =0x04001000
	ldr r0, [r0]
	pop {r3, r4, r5, pc}
	nop
_02022020: .word 0x04001000
	thumb_func_end sub_02021FDC

	thumb_func_start sub_02022024
sub_02022024: ; 0x02022024
	push {r3, r4}
	ldr r1, _0202205C ; =_021D21F4
	mov r0, #0
	ldr r4, [r1]
	ldr r1, [r4, #4]
	cmp r1, #0
	ble _02022054
	ldr r1, [r4]
	add r3, r1, #0
_02022036:
	add r2, r3, #0
	add r2, #0x3c
	ldrb r2, [r2]
	cmp r2, #0
	bne _0202204A
	mov r2, #0x54
	mul r2, r0
	add r0, r1, r2
	pop {r3, r4}
	bx lr
_0202204A:
	ldr r2, [r4, #4]
	add r0, r0, #1
	add r3, #0x54
	cmp r0, r2
	blt _02022036
_02022054:
	mov r0, #0
	pop {r3, r4}
	bx lr
	nop
_0202205C: .word _021D21F4
	thumb_func_end sub_02022024

	thumb_func_start sub_02022060
sub_02022060: ; 0x02022060
	push {r3, lr}
	bl GX_GetBankForOBJ
	cmp r0, #0x30
	bgt _02022090
	bge _020220D8
	cmp r0, #0x10
	bgt _0202208A
	bge _020220CC
	cmp r0, #3
	bhi _02022108
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02022082: ; jump table
	.short _020220AA - _02022082 - 2 ; case 0
	.short _020220F0 - _02022082 - 2 ; case 1
	.short _020220F0 - _02022082 - 2 ; case 2
	.short _020220FC - _02022082 - 2 ; case 3
_0202208A:
	cmp r0, #0x20
	beq _020220B4
	b _02022108
_02022090:
	cmp r0, #0x50
	bgt _0202209C
	bge _020220D8
	cmp r0, #0x40
	beq _020220B4
	b _02022108
_0202209C:
	cmp r0, #0x60
	bgt _020220A4
	beq _020220C0
	b _02022108
_020220A4:
	cmp r0, #0x70
	beq _020220E4
	b _02022108
_020220AA:
	ldr r0, _020221B0 ; =_021D21F4
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x14]
	b _02022110
_020220B4:
	ldr r0, _020221B0 ; =_021D21F4
	mov r1, #1
	ldr r0, [r0]
	lsl r1, r1, #0xe
	str r1, [r0, #0x14]
	b _02022110
_020220C0:
	ldr r0, _020221B0 ; =_021D21F4
	mov r1, #2
	ldr r0, [r0]
	lsl r1, r1, #0xe
	str r1, [r0, #0x14]
	b _02022110
_020220CC:
	ldr r0, _020221B0 ; =_021D21F4
	mov r1, #1
	ldr r0, [r0]
	lsl r1, r1, #0x10
	str r1, [r0, #0x14]
	b _02022110
_020220D8:
	ldr r0, _020221B0 ; =_021D21F4
	mov r1, #5
	ldr r0, [r0]
	lsl r1, r1, #0xe
	str r1, [r0, #0x14]
	b _02022110
_020220E4:
	ldr r0, _020221B0 ; =_021D21F4
	mov r1, #6
	ldr r0, [r0]
	lsl r1, r1, #0xe
	str r1, [r0, #0x14]
	b _02022110
_020220F0:
	ldr r0, _020221B0 ; =_021D21F4
	mov r1, #2
	ldr r0, [r0]
	lsl r1, r1, #0x10
	str r1, [r0, #0x14]
	b _02022110
_020220FC:
	ldr r0, _020221B0 ; =_021D21F4
	mov r1, #1
	ldr r0, [r0]
	lsl r1, r1, #0x12
	str r1, [r0, #0x14]
	b _02022110
_02022108:
	ldr r0, _020221B0 ; =_021D21F4
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x14]
_02022110:
	bl GX_GetBankForSubOBJ
	cmp r0, #0
	beq _02022126
	cmp r0, #8
	beq _0202213A
	mov r1, #1
	lsl r1, r1, #8
	cmp r0, r1
	beq _02022130
	b _02022146
_02022126:
	ldr r0, _020221B0 ; =_021D21F4
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x18]
	b _0202214E
_02022130:
	ldr r0, _020221B0 ; =_021D21F4
	lsl r1, r1, #6
	ldr r0, [r0]
	str r1, [r0, #0x18]
	b _0202214E
_0202213A:
	ldr r0, _020221B0 ; =_021D21F4
	mov r1, #2
	ldr r0, [r0]
	lsl r1, r1, #0x10
	str r1, [r0, #0x18]
	b _0202214E
_02022146:
	ldr r0, _020221B0 ; =_021D21F4
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x18]
_0202214E:
	ldr r0, _020221B0 ; =_021D21F4
	ldr r1, [r0]
	ldr r0, [r1, #0x24]
	ldr r1, [r1, #0x2c]
	bl sub_020224B8
	ldr r1, _020221B0 ; =_021D21F4
	ldr r3, [r1]
	ldr r2, [r3, #0x14]
	sub r0, r2, r0
	str r0, [r3, #0x1c]
	ldr r1, [r1]
	ldr r0, [r1, #0x28]
	ldr r1, [r1, #0x30]
	bl sub_020224B8
	ldr r1, _020221B0 ; =_021D21F4
	ldr r3, [r1]
	ldr r2, [r3, #0x18]
	sub r0, r2, r0
	str r0, [r3, #0x20]
	ldr r1, [r1]
	mov r2, #0
	ldr r0, [r1, #0x1c]
	cmp r0, #0
	blt _0202218A
	ldr r0, [r1, #0x20]
	cmp r0, #0
	blt _0202218A
	mov r2, #1
_0202218A:
	cmp r2, #0
	bne _02022192
	bl GF_AssertFail
_02022192:
	ldr r0, _020221B0 ; =_021D21F4
	mov r2, #0
	ldr r1, [r0]
	ldr r0, [r1, #0x1c]
	cmp r0, #0
	blt _020221A6
	ldr r0, [r1, #0x20]
	cmp r0, #0
	blt _020221A6
	mov r2, #1
_020221A6:
	cmp r2, #0
	bne _020221AE
	bl GF_AssertFail
_020221AE:
	pop {r3, pc}
	.balign 4, 0
_020221B0: .word _021D21F4
	thumb_func_end sub_02022060

	thumb_func_start sub_020221B4
sub_020221B4: ; 0x020221B4
	push {r3, lr}
	ldr r0, _020221CC ; =_021D21F4
	ldr r0, [r0]
	ldr r0, [r0, #0x34]
	bl sub_02022278
	ldr r0, _020221CC ; =_021D21F4
	ldr r0, [r0]
	ldr r0, [r0, #0x38]
	bl sub_02022278
	pop {r3, pc}
	.balign 4, 0
_020221CC: .word _021D21F4
	thumb_func_end sub_020221B4

	thumb_func_start sub_020221D0
sub_020221D0: ; 0x020221D0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _02022234 ; =_021D21F4
	add r4, r1, #0
	ldr r1, [r0]
	add r6, r2, #0
	str r5, [r1, #0x24]
	ldr r1, [r0]
	str r4, [r1, #0x28]
	ldr r0, [r0]
	ldr r0, [r0, #0x34]
	cmp r0, #0
	beq _020221EE
	bl FreeToHeap
_020221EE:
	ldr r0, _02022234 ; =_021D21F4
	ldr r0, [r0]
	ldr r0, [r0, #0x38]
	cmp r0, #0
	beq _020221FC
	bl FreeToHeap
_020221FC:
	ldr r0, _02022234 ; =_021D21F4
	ldr r0, [r0]
	ldr r0, [r0, #0x24]
	cmp r0, #0
	beq _02022214
	add r0, r6, #0
	lsr r1, r5, #3
	bl AllocFromHeap
	ldr r1, _02022234 ; =_021D21F4
	ldr r1, [r1]
	str r0, [r1, #0x34]
_02022214:
	ldr r0, _02022234 ; =_021D21F4
	ldr r0, [r0]
	ldr r0, [r0, #0x28]
	cmp r0, #0
	beq _0202222C
	add r0, r6, #0
	lsr r1, r4, #3
	bl AllocFromHeap
	ldr r1, _02022234 ; =_021D21F4
	ldr r1, [r1]
	str r0, [r1, #0x38]
_0202222C:
	bl sub_020221B4
	pop {r4, r5, r6, pc}
	nop
_02022234: .word _021D21F4
	thumb_func_end sub_020221D0

	thumb_func_start sub_02022238
sub_02022238: ; 0x02022238
	push {r3, lr}
	cmp r0, #0
	beq _0202225A
	ldr r1, _0202225C ; =_021D21F4
	ldr r2, [r1]
	ldr r1, [r2, #0x34]
	cmp r0, r1
	bne _02022252
	mov r1, #0
	str r1, [r2, #0x24]
	bl FreeToHeap
	pop {r3, pc}
_02022252:
	mov r1, #0
	str r1, [r2, #0x28]
	bl FreeToHeap
_0202225A:
	pop {r3, pc}
	.balign 4, 0
_0202225C: .word _021D21F4
	thumb_func_end sub_02022238

	thumb_func_start sub_02022260
sub_02022260: ; 0x02022260
	ldr r1, _02022274 ; =_021D21F4
	ldr r2, [r1]
	ldr r1, [r2, #0x34]
	cmp r0, r1
	bne _0202226E
	ldr r0, [r2, #0x24]
	bx lr
_0202226E:
	ldr r0, [r2, #0x28]
	bx lr
	nop
_02022274: .word _021D21F4
	thumb_func_end sub_02022260

	thumb_func_start sub_02022278
sub_02022278: ; 0x02022278
	push {r4, lr}
	add r4, r0, #0
	beq _0202228E
	bl sub_02022260
	add r2, r0, #0
	add r0, r4, #0
	mov r1, #0
	lsr r2, r2, #3
	bl memset
_0202228E:
	pop {r4, pc}
	thumb_func_end sub_02022278

	thumb_func_start sub_02022290
sub_02022290: ; 0x02022290
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	beq _020222E6
	add r0, r4, #0
	bl sub_02022260
	add r6, r5, r6
	add r7, r0, #0
	cmp r5, r6
	bhs _020222E6
_020222AA:
	cmp r5, r7
	bhs _020222E6
	add r0, r5, #0
	add r1, sp, #4
	add r2, sp, #0
	bl sub_02022560
	add r0, sp, #0
	ldrb r1, [r0]
	mov r0, #1
	lsl r0, r1
	ldr r1, [sp, #4]
	ldrb r1, [r4, r1]
	tst r0, r1
	beq _020222CC
	bl GF_AssertFail
_020222CC:
	add r2, sp, #0
	ldrb r3, [r2]
	ldr r1, [sp, #4]
	mov r2, #1
	lsl r2, r3
	lsl r2, r2, #0x18
	ldrb r0, [r4, r1]
	lsr r2, r2, #0x18
	add r5, r5, #1
	orr r0, r2
	strb r0, [r4, r1]
	cmp r5, r6
	blo _020222AA
_020222E6:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
	thumb_func_end sub_02022290

	thumb_func_start sub_020222EC
sub_020222EC: ; 0x020222EC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	str r1, [sp]
	cmp r1, #0
	beq _0202236A
	add r0, r1, #0
	bl sub_02022260
	mov r6, #0
	str r0, [sp, #4]
	cmp r0, #0
	bls _0202236A
_02022306:
	add r0, r6, #0
	add r1, sp, #0xc
	add r2, sp, #8
	bl sub_02022560
	add r0, sp, #8
	ldrb r1, [r0]
	mov r0, #1
	mov r4, #0
	lsl r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	b _02022348
_02022320:
	add r5, r6, r4
	add r0, r5, #0
	add r1, sp, #0xc
	add r2, sp, #8
	bl sub_02022560
	add r0, sp, #8
	ldrb r1, [r0]
	mov r0, #1
	lsl r0, r1
	lsl r0, r0, #0x18
	ldr r1, [sp, #4]
	lsr r0, r0, #0x18
	cmp r5, r1
	blo _02022346
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_02022346:
	add r4, r4, #1
_02022348:
	ldr r2, [sp, #0xc]
	ldr r1, [sp]
	ldrb r1, [r1, r2]
	tst r0, r1
	bne _02022356
	cmp r4, r7
	bls _02022320
_02022356:
	cmp r4, r7
	bls _02022360
	add sp, #0x10
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
_02022360:
	add r0, r6, r4
	add r6, r0, #1
	ldr r0, [sp, #4]
	cmp r6, r0
	blo _02022306
_0202236A:
	mov r0, #0
	mvn r0, r0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
	thumb_func_end sub_020222EC

	thumb_func_start sub_02022374
sub_02022374: ; 0x02022374
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r4, r2, #0
	beq _020223BE
	add r6, r5, r1
	cmp r5, r6
	bhs _020223BE
	add r7, sp, #0
_02022386:
	add r0, r5, #0
	add r1, sp, #4
	add r2, sp, #0
	bl sub_02022560
	ldrb r1, [r7]
	mov r0, #1
	lsl r0, r1
	ldr r1, [sp, #4]
	ldrb r1, [r4, r1]
	tst r0, r1
	bne _020223A2
	bl GF_AssertFail
_020223A2:
	ldrb r0, [r7]
	mov r1, #1
	ldr r3, [sp, #4]
	lsl r1, r0
	mov r0, #0xff
	eor r0, r1
	lsl r0, r0, #0x18
	ldrb r2, [r4, r3]
	lsr r0, r0, #0x18
	add r5, r5, #1
	and r0, r2
	strb r0, [r4, r3]
	cmp r5, r6
	blo _02022386
_020223BE:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
	thumb_func_end sub_02022374

	thumb_func_start sub_020223C4
sub_020223C4: ; 0x020223C4
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #1
	tst r0, r1
	beq _02022402
	add r0, r4, #0
	add r0, #0x10
	bl NNS_G2dGetImageLocation
	ldr r1, _02022444 ; =_021D21F4
	ldr r2, [r1]
	ldr r1, [r2, #0x1c]
	sub r0, r0, r1
	ldr r1, [r2, #0x2c]
	bl sub_020224A8
	ldr r1, _02022444 ; =_021D21F4
	add r5, r0, #0
	ldr r1, [r1]
	ldr r0, [r4, #0x4c]
	ldr r1, [r1, #0x2c]
	bl sub_020224A8
	ldr r2, _02022444 ; =_021D21F4
	add r1, r0, #0
	ldr r2, [r2]
	add r0, r5, #0
	ldr r2, [r2, #0x34]
	bl sub_02022374
_02022402:
	ldr r0, [r4, #4]
	mov r1, #2
	tst r0, r1
	beq _0202243C
	add r0, r4, #0
	add r0, #0x10
	bl NNS_G2dGetImageLocation
	ldr r1, _02022444 ; =_021D21F4
	ldr r2, [r1]
	ldr r1, [r2, #0x20]
	sub r0, r0, r1
	ldr r1, [r2, #0x30]
	bl sub_020224A8
	ldr r1, _02022444 ; =_021D21F4
	add r5, r0, #0
	ldr r1, [r1]
	ldr r0, [r4, #0x50]
	ldr r1, [r1, #0x30]
	bl sub_020224A8
	ldr r2, _02022444 ; =_021D21F4
	add r1, r0, #0
	ldr r2, [r2]
	add r0, r5, #0
	ldr r2, [r2, #0x38]
	bl sub_02022374
_0202243C:
	mov r0, #0
	str r0, [r4, #0x48]
	pop {r3, r4, r5, pc}
	nop
_02022444: .word _021D21F4
	thumb_func_end sub_020223C4

	thumb_func_start sub_02022448
sub_02022448: ; 0x02022448
	ldr r1, _0202247C ; =0x00100010
	cmp r0, r1
	bgt _02022456
	bge _0202246C
	cmp r0, #0x10
	beq _02022468
	b _02022478
_02022456:
	ldr r1, _02022480 ; =0x00200010
	cmp r0, r1
	bgt _02022460
	beq _02022470
	b _02022478
_02022460:
	ldr r1, _02022484 ; =0x00300010
	cmp r0, r1
	beq _02022474
	b _02022478
_02022468:
	mov r0, #1
	bx lr
_0202246C:
	mov r0, #2
	bx lr
_02022470:
	mov r0, #4
	bx lr
_02022474:
	mov r0, #8
	bx lr
_02022478:
	mov r0, #1
	bx lr
	.balign 4, 0
_0202247C: .word 0x00100010
_02022480: .word 0x00200010
_02022484: .word 0x00300010
	thumb_func_end sub_02022448

	thumb_func_start sub_02022488
sub_02022488: ; 0x02022488
	push {r4, r5, r6, lr}
	add r4, r1, #0
	lsl r4, r4, #5
	add r1, r4, #0
	add r5, r0, #0
	add r6, r2, #0
	bl _s32_div_f
	cmp r1, #0
	beq _020224A4
	sub r5, r5, r1
	cmp r6, #1
	bne _020224A4
	add r5, r5, r4
_020224A4:
	add r0, r5, #0
	pop {r4, r5, r6, pc}
	thumb_func_end sub_02022488

	thumb_func_start sub_020224A8
sub_020224A8: ; 0x020224A8
	asr r2, r0, #4
	lsr r2, r2, #0x1b
	add r2, r0, r2
	ldr r3, _020224B4 ; =_s32_div_f
	asr r0, r2, #5
	bx r3
	.balign 4, 0
_020224B4: .word _s32_div_f
	thumb_func_end sub_020224A8

	thumb_func_start sub_020224B8
sub_020224B8: ; 0x020224B8
	mul r1, r0
	lsl r0, r1, #5
	bx lr
	.balign 4, 0
	thumb_func_end sub_020224B8

	thumb_func_start sub_020224C0
sub_020224C0: ; 0x020224C0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r1, r2, #0
	mov r0, #1
	add r2, r4, #0
	add r7, r3, #0
	tst r2, r0
	beq _020224EA
	ldr r2, _0202250C ; =_021D21F4
	ldr r2, [r2]
	ldr r6, [r2, #0xc]
	ldr r2, [r2, #0x1c]
	add r3, r6, r5
	cmp r3, r2
	bls _020224E8
	bl GF_AssertFail
	mov r0, #0
	b _020224EA
_020224E8:
	str r6, [r1]
_020224EA:
	mov r1, #2
	tst r1, r4
	beq _02022508
	ldr r1, _0202250C ; =_021D21F4
	ldr r1, [r1]
	ldr r3, [r1, #0x10]
	ldr r1, [r1, #0x20]
	add r2, r3, r5
	cmp r2, r1
	bls _02022506
	bl GF_AssertFail
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02022506:
	str r3, [r7]
_02022508:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0202250C: .word _021D21F4
	thumb_func_end sub_020224C0

	thumb_func_start sub_02022510
sub_02022510: ; 0x02022510
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r2, #1
	add r0, r4, #0
	tst r0, r2
	beq _02022538
	ldr r0, _0202255C ; =_021D21F4
	ldr r3, [r0]
	ldr r1, [r3, #0xc]
	add r1, r1, r5
	str r1, [r3, #0xc]
	ldr r1, [r0]
	ldr r0, [r1, #0xc]
	ldr r1, [r1, #0x2c]
	bl sub_02022488
	ldr r1, _0202255C ; =_021D21F4
	ldr r1, [r1]
	str r0, [r1, #0xc]
_02022538:
	mov r0, #2
	tst r0, r4
	beq _0202255A
	ldr r0, _0202255C ; =_021D21F4
	ldr r2, [r0]
	ldr r1, [r2, #0x10]
	add r1, r1, r5
	str r1, [r2, #0x10]
	ldr r1, [r0]
	mov r2, #1
	ldr r0, [r1, #0x10]
	ldr r1, [r1, #0x30]
	bl sub_02022488
	ldr r1, _0202255C ; =_021D21F4
	ldr r1, [r1]
	str r0, [r1, #0x10]
_0202255A:
	pop {r3, r4, r5, pc}
	.balign 4, 0
_0202255C: .word _021D21F4
	thumb_func_end sub_02022510

	thumb_func_start sub_02022560
sub_02022560: ; 0x02022560
	asr r3, r0, #3
	str r3, [r1]
	mov r1, #7
	and r0, r1
	strb r0, [r2]
	bx lr
	thumb_func_end sub_02022560

	thumb_func_start sub_0202256C
sub_0202256C: ; 0x0202256C
	push {r3, r4}
	sub r0, r1, r0
	ldr r4, [sp, #8]
	str r0, [r3]
	bpl _02022582
	add r0, r2, r0
	str r0, [r4]
	mov r0, #0
	str r0, [r3]
	pop {r3, r4}
	bx lr
_02022582:
	str r2, [r4]
	pop {r3, r4}
	bx lr
	thumb_func_end sub_0202256C
