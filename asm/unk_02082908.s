#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/ribbon.h"
#include "constants/party_menu.h"
#include "msgdata/msg/msg_0300.h"
	.include "asm/macros.inc"
	.include "unk_02082908.inc"
	.include "global.inc"

	.public gOverlayTemplate_Battle
	.public gNatureStatMods
	.extern NamingScreenApp_Init
	.extern NamingScreenApp_Main
	.extern NamingScreenApp_Exit
	.extern sub_02084C78
	.extern sub_02084430
	.extern sub_02084540

	.text

	thumb_func_start sub_02084D04
sub_02084D04: ; 0x02084D04
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r0, r1, #0
	ldr r1, [sp, #0x1c]
	mov lr, r2
	mov ip, r3
	cmp r1, #0
	beq _02084D20
	sub r1, r1, #1
	ldr r6, [sp, #0x18]
	lsl r7, r1, #1
	ldrh r5, [r6, r7]
	cmp r5, #1
	bne _02084D24
_02084D20:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02084D24:
	add r2, r4, #0
	cmp r4, r0
	bge _02084D56
	mov r1, #6
	ldr r3, _02084DFC ; =_02102422
	mul r1, r4
	add r3, r3, r1
_02084D32:
	ldrh r1, [r3]
	cmp r5, r1
	bne _02084D4E
	add r3, r2, #0
	mov r0, #6
	mul r3, r0
	mov r0, lr
	ldr r2, _02084DFC ; =_02102422
	lsl r1, r0, #1
	add r0, r2, r3
	ldrh r0, [r1, r0]
	strh r0, [r6, r7]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02084D4E:
	add r2, r2, #1
	add r3, r3, #6
	cmp r2, r0
	blt _02084D32
_02084D56:
	cmp r4, r0
	bge _02084D86
	mov r2, lr
	ldr r1, _02084DFC ; =_02102422
	lsl r2, r2, #1
	add r1, r1, r2
	mov r2, #6
	mul r2, r4
	add r2, r1, r2
_02084D68:
	ldrh r1, [r2]
	cmp r5, r1
	bne _02084D7E
	mov r0, #6
	add r1, r4, #0
	mul r1, r0
	ldr r0, _02084DFC ; =_02102422
	ldrh r0, [r0, r1]
	strh r0, [r6, r7]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02084D7E:
	add r4, r4, #1
	add r2, r2, #6
	cmp r4, r0
	blt _02084D68
_02084D86:
	ldr r1, _02084E00 ; =0x0000D001
	mov r0, ip
	cmp r0, r1
	beq _02084DA0
	add r1, r1, #1
	mov r0, ip
	cmp r0, r1
	beq _02084DC0
	ldr r1, _02084E04 ; =0x0000E006
	mov r0, ip
	cmp r0, r1
	beq _02084DE0
	b _02084DF8
_02084DA0:
	ldr r1, _02084E08 ; =_021021B8
	mov r2, #0
_02084DA4:
	ldrh r0, [r1]
	cmp r5, r0
	bne _02084DB6
	ldr r0, _02084E0C ; =_021021B8 + 2
	lsl r1, r2, #2
	ldrh r0, [r0, r1]
	strh r0, [r6, r7]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02084DB6:
	add r2, r2, #1
	add r1, r1, #4
	cmp r2, #0xc
	blo _02084DA4
	b _02084DF8
_02084DC0:
	ldr r1, _02084E10 ; =_02102190
	mov r2, #0
_02084DC4:
	ldrh r0, [r1]
	cmp r5, r0
	bne _02084DD6
	ldr r0, _02084E14 ; =_02102190 + 2
	lsl r1, r2, #2
	ldrh r0, [r0, r1]
	strh r0, [r6, r7]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02084DD6:
	add r2, r2, #1
	add r1, r1, #4
	cmp r2, #0xa
	blo _02084DC4
	b _02084DF8
_02084DE0:
	cmp r5, #0x26
	bne _02084DEC
	mov r0, #0x24
	strh r0, [r6, r7]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02084DEC:
	cmp r5, #0x76
	bne _02084DF8
	mov r0, #0x74
	strh r0, [r6, r7]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02084DF8:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_02084DFC: .word _02102422
_02084E00: .word 0x0000D001
_02084E04: .word 0x0000E006
_02084E08: .word _021021B8
_02084E0C: .word _021021B8 + 2
_02084E10: .word _02102190
_02084E14: .word _02102190 + 2
	thumb_func_end sub_02084D04

	thumb_func_start sub_02084E18
sub_02084E18: ; 0x02084E18
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r2, #0
	mov r4, #0
	str r0, [sp]
	str r1, [sp, #4]
	cmp r6, #0
	ble _02084E3C
	add r5, r0, #0
	mov r7, #0x2b
_02084E2C:
	ldr r0, [r5]
	add r1, r7, #0
	bl Sprite_SetAnimCtrlSeq
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r6
	blt _02084E2C
_02084E3C:
	ldr r0, [sp, #4]
	cmp r0, r6
	beq _02084E4E
	lsl r1, r0, #2
	ldr r0, [sp]
	ldr r0, [r0, r1]
	mov r1, #0x2c
	bl Sprite_SetAnimCtrlSeq
_02084E4E:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
	thumb_func_end sub_02084E18

	thumb_func_start sub_02084E54
sub_02084E54: ; 0x02084E54
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r2, [sp, #0x10]
	ldr r2, [sp, #0x30]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r5, r0, #0
	str r3, [sp, #0x14]
	str r2, [sp, #0x30]
	bl FillWindowPixelBuffer
	ldr r1, _02084F34 ; =_02101D44
	ldr r0, [sp, #0x10]
	mov r7, #0
	ldrb r4, [r1, r0]
	mov r6, #0x10
_02084E74:
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0x13
	lsl r2, r6, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x10
	mov r3, #0
	bl FillWindowPixelRect
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0x13
	lsl r2, r6, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x10
	mov r3, #0x26
	bl FillWindowPixelRect
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0x13
	lsl r2, r6, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x10
	mov r3, #0x4c
	bl FillWindowPixelRect
	add r7, r7, #1
	add r6, #0x20
	cmp r7, #6
	blt _02084E74
	mov r7, #0
	add r6, r7, #0
_02084EC2:
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0x13
	lsl r2, r6, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x10
	mov r3, #0x13
	bl FillWindowPixelRect
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0x13
	lsl r2, r6, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x10
	mov r3, #0x39
	bl FillWindowPixelRect
	add r7, r7, #1
	add r6, #0x20
	cmp r7, #7
	blt _02084EC2
	ldr r0, [sp, #0x10]
	mov r1, #0x14
	ldr r2, _02084F38 ; =_021104F8
	mul r1, r0
	mov r7, #0
	mov r6, #4
	add r4, r2, r1
_02084F04:
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x14]
	mov r2, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x30]
	add r3, r6, #0
	str r0, [sp, #0xc]
	ldr r1, [r4]
	add r0, r5, #0
	bl sub_02084540
	add r7, r7, #1
	add r6, #0x13
	add r4, r4, #4
	cmp r7, #5
	blt _02084F04
	add r0, r5, #0
	bl CopyWindowToVram
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_02084F34: .word _02101D44
_02084F38: .word _021104F8
	thumb_func_end sub_02084E54

	thumb_func_start sub_02084F3C
sub_02084F3C: ; 0x02084F3C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	str r0, [sp]
	mov r7, #0
	add r1, r0, #0
_02084F48:
	ldr r0, [r1]
	cmp r0, #0
	beq _02084F7E
	mov r0, #0
	ldr r4, _02084FC0 ; =_021021E8
	str r0, [sp, #4]
	add r5, r6, #0
_02084F56:
	ldr r0, [r5]
	ldr r1, [r4, #8]
	bl Sprite_SetAnimCtrlSeq
	ldr r0, [sp, #4]
	add r4, #0x10
	add r0, r0, #1
	add r5, r5, #4
	str r0, [sp, #4]
	cmp r0, #3
	blt _02084F56
	ldr r1, _02084FC4 ; =_021021E8 + 8
	lsl r2, r7, #4
	lsl r0, r7, #2
	ldr r1, [r1, r2]
	ldr r0, [r6, r0]
	sub r1, r1, #3
	bl Sprite_SetAnimCtrlSeq
	b _02084F86
_02084F7E:
	add r7, r7, #1
	add r1, r1, #4
	cmp r7, #3
	blt _02084F48
_02084F86:
	ldr r4, [sp]
	ldr r5, _02084FC8 ; =_021021E8 + 0x50
	mov r7, #5
	add r4, #0x14
	add r6, #0x14
_02084F90:
	ldr r0, [r4]
	cmp r0, #0
	beq _02084FA0
	ldr r1, [r5, #8]
	ldr r0, [r6]
	add r1, r1, #1
	bl Sprite_SetAnimCtrlSeq
_02084FA0:
	add r7, r7, #1
	add r4, r4, #4
	add r5, #0x10
	add r6, r6, #4
	cmp r7, #7
	blt _02084F90
	mov r2, #0
	add r1, r2, #0
_02084FB0:
	ldr r0, [sp]
	add r2, r2, #1
	stmia r0!, {r1}
	str r0, [sp]
	cmp r2, #7
	blt _02084FB0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_02084FC0: .word _021021E8
_02084FC4: .word _021021E8 + 8
_02084FC8: .word _021021E8 + 0x50
	thumb_func_end sub_02084F3C

	thumb_func_start sub_02084FCC
sub_02084FCC: ; 0x02084FCC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xd3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl Sprite_IsCellAnimationRunning
	cmp r0, #0
	bne _02085038
	mov r0, #0x56
	lsl r0, r0, #2
	ldrh r1, [r4, r0]
	ldr r0, [r4, #0xc]
	cmp r1, r0
	bne _02085004
	mov r0, #0xc
	str r0, [r4, #0x1c]
	mov r0, #0
	str r0, [r4, #0x20]
	mov r0, #0xd3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x27
	bl Sprite_SetAnimCtrlSeq
	mov r0, #0
	str r0, [r4, #0x34]
	b _02085010
_02085004:
	mov r0, #0xd3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x27
	bl Sprite_SetAnimCtrlSeq
_02085010:
	ldr r0, [r4, #0x30]
	cmp r0, #0
	bne _02085024
	mov r0, #0xd3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl Sprite_SetVisibleFlag
	b _0208502C
_02085024:
	add r0, r4, #0
	mov r1, #0
	bl sub_02084430
_0208502C:
	mov r0, #0xd3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl Sprite_SetOamMode
_02085038:
	pop {r4, pc}
	.balign 4, 0
	thumb_func_end sub_02084FCC

	thumb_func_start sub_0208503C
sub_0208503C: ; 0x0208503C
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	mov r0, #0
	mov ip, r0
	ldr r0, [sp]
	ldr r0, [r0]
	cmp r0, #4
	bne _02085050
	mov r0, #4
	mov ip, r0
_02085050:
	ldr r2, _020850EC ; =gSystem + 0x40
	ldrh r0, [r2, #0x24]
	cmp r0, #0
	beq _020850E6
	ldrh r0, [r2, #0x20]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov lr, r0
	ldrh r0, [r2, #0x22]
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	mov r0, ip
	cmp r0, #0x47
	bhs _020850E6
	mov r0, #6
	mov r2, ip
	mul r0, r2
	ldr r2, _020850F0 ; =_02102278
	add r2, r2, r0
	add r3, r2, #0
_02085078:
	ldrh r4, [r3, #2]
	ldrb r0, [r2]
	ldrb r6, [r2, #1]
	lsl r4, r4, #0x1e
	lsr r4, r4, #0x1e
	beq _0208508E
	cmp r4, #1
	beq _02085094
	cmp r4, #2
	beq _0208509A
	b _0208509E
_0208508E:
	mov r5, #0x1f
	mov r1, #0x16
	b _0208509E
_02085094:
	mov r5, #0x20
	mov r1, #0x16
	b _0208509E
_0208509A:
	mov r5, #0x10
	mov r1, #0x13
_0208509E:
	mov r4, lr
	cmp r4, r0
	blo _020850D8
	cmp r7, r6
	blo _020850D8
	add r4, r0, r5
	mov r0, lr
	cmp r0, r4
	bgt _020850D8
	add r0, r6, r1
	cmp r7, r0
	bgt _020850D8
	ldr r2, _020850F0 ; =_02102278
	mov r1, #6
	mov r0, ip
	mul r1, r0
	add r2, r2, r1
	ldrb r0, [r2, #4]
	lsl r0, r0, #0x1b
	lsr r1, r0, #0x1b
	ldr r0, [sp]
	str r1, [r0, #0x1c]
	ldrb r0, [r2, #5]
	lsl r0, r0, #0x1b
	lsr r1, r0, #0x1b
	ldr r0, [sp]
	str r1, [r0, #0x20]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_020850D8:
	mov r0, ip
	add r0, r0, #1
	add r2, r2, #6
	add r3, r3, #6
	mov ip, r0
	cmp r0, #0x47
	blo _02085078
_020850E6:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_020850EC: .word gSystem + 0x40
_020850F0: .word _02102278
	thumb_func_end sub_0208503C

	.rodata

	.global _02101D3C
_02101D3C:
	.byte 0x60, 0x68, 0x50, 0x58

	.global _02101D40
_02101D40:
	.byte 0x04, 0x07, 0x0D, 0x0A
_02101D44:
	.byte 0x03, 0x06, 0x0C, 0x09, 0x09, 0x00, 0x00, 0x00

	.global _02101D4C
_02101D4C:
	.byte 0x28, 0x28, 0x28, 0x28
	.byte 0x29, 0x29, 0x29, 0x00

	.global _02101D54
_02101D54:
	.word 0x00000070
	.word 0x0000004C
	.word 0x00000048

	.global _02101D60
_02101D60: // GraphicsModes
	.word 0x00000001, 0x00000000, 0x00000000, 0x00000000

	.global _02101D70
_02101D70: // ObjCharTransferTemplate
	.word 0x00000014
	.word 0x00000800
	.word 0x00000800
	.word 0x00000012

	.global _02101D80
_02101D80:
	.short 0x0019, 0x0039, 0x0059, 0x0061, 0x007A, 0x009E, 0x00C6, 0x0000
	.short 0x0003, 0x002B, 0x0020, 0x002F, 0x0001, 0x002B, 0x003F, 0x0009
	.short 0x0030, 0x00E2, 0xFFFF, 0x008D, 0x0074, 0x0060, 0x006A, 0x002F
	.short 0x0001, 0x002B, 0x003F, 0x0009, 0x0030, 0x00E2, 0xFFFF

_02101DBE:
	.short 0xE002, 0xE002, 0xE003, 0xE003, 0xE004, 0xE004, 0xD004, 0xD004
	.short 0xE007, 0xE007, 0xE007, 0xE008, 0xE008

_02101DD8:
	.short 0xD004, 0xD004, 0xD004, 0xD004, 0xD004, 0xD004, 0xD004, 0xD004
	.short 0xE007, 0xE007, 0xE007, 0xE008, 0xE008

_02101DF2:
	.short 0x00E3, 0x00E4, 0x00F9, 0x00F8, 0x00E5, 0x00E6, 0x00F5
	.short 0x00F6, 0x00F7, 0x00E7, 0x0001, 0x00EE, 0x00EF, 0xFFFF, 0x0000

	.global _02101E10
_02101E10: // BgTemplate
	.word 0x00000000, 0x00000000, 0x00000800, 0x00000000
	.byte 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00
	.word 0x00000000
_02101E2C:
	.short 0x01DE, 0x01DE
	.short 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE
	.short 0x01DE, 0x01DE, 0x01DE, 0xFFFF
_02101E48:
	.short 0x0107, 0x0108, 0x0109, 0x010A
	.short 0x010B, 0x010C, 0x010D, 0x010E, 0x0111, 0x010F, 0x0110, 0x0001
	.short 0x0001, 0xFFFF
_02101E64:
	.short 0x0121, 0x0122, 0x0123, 0x0124, 0x0125, 0x0126
	.short 0x0127, 0x0128, 0x0129, 0x012A, 0x01DE, 0x01DE, 0x01DE, 0xFFFF
_02101E80:
	.short 0x012B, 0x012C, 0x012D, 0x012E, 0x012F, 0x0130, 0x0131, 0x0132
	.short 0x0133, 0x0134, 0x01DE, 0x01AD, 0x01AE, 0xFFFF
_02101E9C:
	.short 0x0135, 0x0136, 0x0137, 0x0138, 0x0139, 0x013A, 0x013B, 0x013C, 0x013D, 0x013E, 0x01DE, 0x01B3, 0x01BE, 0xFFFF
_02101EB8:
	.short 0x013F, 0x0140, 0x0141, 0x0142, 0x0143, 0x0144, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01BB, 0x01BC, 0xFFFF

	.global _02101ED4
_02101ED4: // BgTemplate
	.word 0x00000000, 0x00000000, 0x00001000, 0x00000000
	.byte 0x03, 0x00, 0x1E, 0x04, 0x00, 0x01, 0x00, 0x00
	.word 0x00000000
_02101EF0:
	.short 0x0145, 0x0146, 0x0147, 0x0148, 0x0149, 0x014A, 0x014B, 0x014C, 0x014D, 0x014E, 0x01DE, 0x01AD, 0x01AE, 0xFFFF
_02101F0C:
	.short 0x014F, 0x0150, 0x0151, 0x0152, 0x0153, 0x0154, 0x0155, 0x0156, 0x0157, 0x0158, 0x01DE, 0x01B3, 0x01BE, 0xFFFF
_02101F28:
	.short 0x00FF, 0x0100, 0x0101, 0x0102, 0x0103, 0x00FC, 0x00FA, 0x00FD, 0x00FB, 0x00FE, 0x0105, 0x0001, 0x0001, 0xFFFF
_02101F44:
	.short 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x0106, 0x0104, 0xFFFF
_02101F60:
	.short 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0xFFFF
_02101F7C:
	.short 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x0001, 0x00E1, 0x00E2, 0xFFFF
_02101F98:
	.short 0x01AD, 0x01AE, 0x01C4, 0x01C5, 0x01AB, 0x01AC, 0x01DE, 0x01DE, 0x01DE, 0x01BB, 0x01BC, 0x01DE, 0x01DE, 0xFFFF

	.global _02101FB4
_02101FB4: // BgTemplate
	.word 0x00000000, 0x00000000, 0x00001000, 0x00000000
	.byte 0x03, 0x00, 0x1C, 0x04, 0x00, 0x02, 0x00, 0x00
	.word 0x00000000
_02101FD0:
	.short 0x01B4, 0x01B5, 0x01B2, 0x01B3, 0x01B9, 0x01BA, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0xFFFF
_02101FEC:
	.short 0x01AF, 0x01B0, 0x01C3, 0x01D0, 0x01C0, 0x01D2, 0x01BD, 0x01BE, 0x01BF, 0x01B1, 0x01C1, 0x01DE, 0x01DE, 0xFFFF
_02102008:
	.short 0x01CB, 0x01CC, 0x01CD, 0x01CE, 0x01CF, 0x01C6, 0x01C8, 0x01C9, 0x01C7, 0x01CA, 0x01D1, 0x01DE, 0x01DE, 0xFFFF
_02102024:
	.short 0x0121, 0x0122, 0x0123, 0x0124, 0x0125, 0x0126, 0x0127, 0x0128, 0x0129, 0x012A, 0x01DE, 0x01DE, 0x01DE, 0xFFFF
_02102040:
	.short 0x01D3, 0x01D4, 0x01D5, 0x01D6, 0x01D7, 0x01D8, 0x01D9, 0x01DA, 0x01DD, 0x01DB, 0x01DC, 0x01DE, 0x01DE, 0xFFFF
_0210205C:
	.short 0x0159, 0x015A, 0x015B, 0x015C, 0x015D, 0x015E, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01BB, 0x01BC, 0xFFFF

	.global _02102078
_02102078:  // BgTemplate
	.word 0x00000000, 0x00000000, 0x00000800, 0x00000000
	.byte 0x01, 0x00, 0x1A, 0x00, 0x00, 0x03, 0x00, 0x00
	.word 0x00000000

_02102094:
	.short 0x008E, 0x0062, 0x0093, 0x00A1, 0x002F, 0x0001, 0x007C, 0x0074, 0x0060, 0x007E, 0x00F1, 0x0091, 0x0030, 0x00E2, 0xFFFF

	.balign 4, 0
	.global _021020B4
_021020B4:
	.word 0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000008
_021020D4:
	.short 0x0121, 0x0122, 0x0123, 0x0124, 0x0125, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0xFFFF
_021020F8:
	.short 0x0126, 0x0127, 0x0128, 0x0129, 0x012A, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0xFFFF
_0210211C:
	.short 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0xFFFF
	.global _02102140
_02102140: // GraphicsBanks
	.word 0x00000001, 0x00000000, 0x00000004, 0x00000000
	.word 0x00000002, 0x00000000, 0x00000100, 0x00000000
	.word 0x00000000, 0x00000000

	.global _02102168
_02102168:
	.word  0,  0
	.word  0, -1
	.word  0,  1
	.word -1,  0
	.word  1,  0
_02102190:
	.short 0x0031, 0x0032
	.short 0x0034, 0x0035
	.short 0x0037, 0x0038
	.short 0x003A, 0x003B
	.short 0x003D, 0x003E
	.short 0x0081, 0x0082
	.short 0x0084, 0x0085
	.short 0x0087, 0x0088
	.short 0x008A, 0x008B
	.short 0x008D, 0x008E
_021021B8:
	.short 0x0024, 0x0026
	.short 0x0074, 0x0076
	.short 0x0032, 0x0031
	.short 0x0035, 0x0034
	.short 0x0038, 0x0037
	.short 0x003B, 0x003A
	.short 0x003E, 0x003D
	.short 0x0082, 0x0081
	.short 0x0085, 0x0084
	.short 0x0088, 0x0087
	.short 0x008B, 0x008A
	.short 0x008E, 0x008D

	.global _021021E8
_021021E8:
	.word 0x00000004, 0x00000044, 0x00000003, 0x00000001
	.word 0x00000024, 0x00000044, 0x00000008, 0x00000001
	.word 0x00000044, 0x00000044, 0x0000000D, 0x00000001
	.word 0x00000000, 0x000000C8, 0x00000012, 0x00000001
	.word 0x00000065, 0x00000044, 0x00000014, 0x00000001
	.word 0x00000088, 0x00000044, 0x00000017, 0x00000001
	.word 0x000000B0, 0x00000044, 0x00000019, 0x00000001
	.word 0x00000016, 0x00000038, 0x00000025, 0x00000002
	.word 0x0000001A, 0x0000005B, 0x00000027, 0x00000000

_02102278:
	.byte 0x19, 0x3C
	.short 0x00
	.byte 0x00, 0x00
	.byte 0x39, 0x3C
	.short 0x00
	.byte 0x02, 0x00
	.byte 0x59, 0x3C
	.short 0x00
	.byte 0x04, 0x00
	.byte 0x00, 0xC0
	.short 0x00
	.byte 0x04, 0x00
	.byte 0x9D, 0x3C
	.short 0x01
	.byte 0x08, 0x00
	.byte 0xC5, 0x3C
	.short 0x01
	.byte 0x0B, 0x00
	.byte 0x1C, 0x58
	.short 0x02
	.byte 0x00, 0x01
	.byte 0x2C, 0x58
	.short 0x02
	.byte 0x01, 0x01
	.byte 0x3C, 0x58
	.short 0x0002
	.byte 0x02, 0x01
	.byte 0x4C, 0x58
	.short 0x0002
	.byte 0x03, 0x01
	.byte 0x5C, 0x58
	.short 0x0002
	.byte 0x04, 0x01
	.byte 0x6C, 0x58
	.short 0x0002
	.byte 0x05, 0x01
	.byte 0x7C, 0x58
	.short 0x0002
	.byte 0x06, 0x01
	.byte 0x8C, 0x58
	.short 0x0002
	.byte 0x07, 0x01
	.byte 0x9C, 0x58
	.short 0x0002
	.byte 0x08, 0x01
	.byte 0xAC, 0x58
	.short 0x0002
	.byte 0x09, 0x01
	.byte 0xBC, 0x58
	.short 0x0002
	.byte 0x0A, 0x01
	.byte 0xCC, 0x58
	.short 0x0002
	.byte 0x0B, 0x01
	.byte 0xDC, 0x58
	.short 0x0002
	.byte 0x0C, 0x01
	.byte 0x1C, 0x6B
	.short 0x0002
	.byte 0x00, 0x02
	.byte 0x2C, 0x6B
	.short 0x0002
	.byte 0x01, 0x02
	.byte 0x3C, 0x6B
	.short 0x0002
	.byte 0x02, 0x02
	.byte 0x4C, 0x6B
	.short 0x0002
	.byte 0x03, 0x02
	.byte 0x5C, 0x6B
	.short 0x0002
	.byte 0x04, 0x02
	.byte 0x6C, 0x6B
	.short 0x0002
	.byte 0x05, 0x02
	.byte 0x7C, 0x6B
	.short 0x0002
	.byte 0x06, 0x02
	.byte 0x8C, 0x6B
	.short 0x0002
	.byte 0x07, 0x02
	.byte 0x9C, 0x6B
	.short 0x0002
	.byte 0x08, 0x02
	.byte 0xAC, 0x6B
	.short 0x0002
	.byte 0x09, 0x02
	.byte 0xBC, 0x6B
	.short 0x0002
	.byte 0x0A, 0x02
	.byte 0xCC, 0x6B
	.short 0x0002
	.byte 0x0B, 0x02
	.byte 0xDC, 0x6B
	.short 0x0002
	.byte 0x0C, 0x02
	.byte 0x1C, 0x7E
	.short 0x0002
	.byte 0x00, 0x03
	.byte 0x2C, 0x7E
	.short 0x0002
	.byte 0x01, 0x03
	.byte 0x3C, 0x7E
	.short 0x0002
	.byte 0x02, 0x03
	.byte 0x4C, 0x7E
	.short 0x0002
	.byte 0x03, 0x03
	.byte 0x5C, 0x7E
	.short 0x0002
	.byte 0x04, 0x03
	.byte 0x6C, 0x7E
	.short 0x0002
	.byte 0x05, 0x03
	.byte 0x7C, 0x7E
	.short 0x0002
	.byte 0x06, 0x03
	.byte 0x8C, 0x7E
	.short 0x0002
	.byte 0x07, 0x03
	.byte 0x9C, 0x7E
	.short 0x0002
	.byte 0x08, 0x03
	.byte 0xAC, 0x7E
	.short 0x0002
	.byte 0x09, 0x03
	.byte 0xBC, 0x7E
	.short 0x0002
	.byte 0x0A, 0x03
	.byte 0xCC, 0x7E
	.short 0x0002
	.byte 0x0B, 0x03
	.byte 0xDC, 0x7E
	.short 0x0002
	.byte 0x0C, 0x03
	.byte 0x1C, 0x91
	.short 0x0002
	.byte 0x00, 0x04
	.byte 0x2C, 0x91
	.short 0x0002
	.byte 0x01, 0x04
	.byte 0x3C, 0x91
	.short 0x0002
	.byte 0x02, 0x04
	.byte 0x4C, 0x91
	.short 0x0002
	.byte 0x03, 0x04
	.byte 0x5C, 0x91
	.short 0x0002
	.byte 0x04, 0x04
	.byte 0x6C, 0x91
	.short 0x0002
	.byte 0x05, 0x04
	.byte 0x7C, 0x91
	.short 0x0002
	.byte 0x06, 0x04
	.byte 0x8C, 0x91
	.short 0x0002
	.byte 0x07, 0x04
	.byte 0x9C, 0x91
	.short 0x0002
	.byte 0x08, 0x04
	.byte 0xAC, 0x91
	.short 0x0002
	.byte 0x09, 0x04
	.byte 0xBC, 0x91
	.short 0x0002
	.byte 0x0A, 0x04
	.byte 0xCC, 0x91
	.short 0x0002
	.byte 0x0B, 0x04
	.byte 0xDC, 0x91
	.short 0x0002
	.byte 0x0C, 0x04
	.byte 0x1C, 0xA4
	.short 0x0002
	.byte 0x00, 0x05
	.byte 0x2C, 0xA4
	.short 0x0002
	.byte 0x01, 0x05
	.byte 0x3C, 0xA4
	.short 0x0002
	.byte 0x02, 0x05
	.byte 0x4C, 0xA4
	.short 0x0002
	.byte 0x03, 0x05
	.byte 0x5C, 0xA4
	.short 0x0002
	.byte 0x04, 0x05
	.byte 0x6C, 0xA4
	.short 0x0002
	.byte 0x05, 0x05
	.byte 0x7C, 0xA4
	.short 0x0002
	.byte 0x06, 0x05
	.byte 0x8C, 0xA4
	.short 0x0002
	.byte 0x07, 0x05
	.byte 0x9C, 0xA4
	.short 0x0002
	.byte 0x08, 0x05
	.byte 0xAC, 0xA4
	.short 0x0002
	.byte 0x09, 0x05
	.byte 0xBC, 0xA4
	.short 0x0002
	.byte 0x0A, 0x05
	.byte 0xCC, 0xA4
	.short 0x0002
	.byte 0x0B, 0x05
	.byte 0xDC, 0xA4
	.short 0x0002
	.byte 0x0C, 0x05

	.global _02102422
_02102422:
	.short 0x0003, 0x0001, 0x0002
	.short 0x0005, 0x0001, 0x0004
	.short 0x0007, 0x0001, 0x0006
	.short 0x0009, 0x0001, 0x0008
	.short 0x000B, 0x0001, 0x000A
	.short 0x0053, 0x0001, 0x0052
	.short 0x0055, 0x0001, 0x0054
	.short 0x0057, 0x0001, 0x0056
	.short 0x0059, 0x0001, 0x0058
	.short 0x005B, 0x0001, 0x005A
	.short 0x0045, 0x0001, 0x0044
	.short 0x0047, 0x0001, 0x0046
	.short 0x0049, 0x0001, 0x0048
	.short 0x0095, 0x0001, 0x0094
	.short 0x0097, 0x0001, 0x0096
	.short 0x0099, 0x0001, 0x0098
	.short 0x00AC, 0x0001, 0x00C6
	.short 0x00AD, 0x0001, 0x00C7
	.short 0x00AE, 0x0001, 0x00C8
	.short 0x00AF, 0x0001, 0x00C9
	.short 0x00B0, 0x0001, 0x00CA
	.short 0x00B1, 0x0001, 0x00CB
	.short 0x00B2, 0x0001, 0x00CC
	.short 0x00B3, 0x0001, 0x00CD
	.short 0x00B4, 0x0001, 0x00CE
	.short 0x00B5, 0x0001, 0x00CF
	.short 0x00B6, 0x0001, 0x00D0
	.short 0x00B7, 0x0001, 0x00D1
	.short 0x00B8, 0x0001, 0x00D2
	.short 0x00B9, 0x0001, 0x00D3
	.short 0x00BA, 0x0001, 0x00D4
	.short 0x00BB, 0x0001, 0x00D5
	.short 0x00BC, 0x0001, 0x00D6
	.short 0x00BD, 0x0001, 0x00D7
	.short 0x00BE, 0x0001, 0x00D8
	.short 0x00BF, 0x0001, 0x00D9
	.short 0x00C0, 0x0001, 0x00DA
	.short 0x00C1, 0x0001, 0x00DB
	.short 0x00C2, 0x0001, 0x00DC
	.short 0x00C3, 0x0001, 0x00DD
	.short 0x00C4, 0x0001, 0x00DE
	.short 0x00C5, 0x0001, 0x00DF
	.short 0x0025, 0x0026, 0x0024
	.short 0x0075, 0x0076, 0x0074
	.short 0x000C, 0x000D, 0x0001
	.short 0x000E, 0x000F, 0x0001
	.short 0x0010, 0x0011, 0x0001
	.short 0x0012, 0x0013, 0x0001
	.short 0x0014, 0x0015, 0x0001
	.short 0x0016, 0x0017, 0x0001
	.short 0x0018, 0x0019, 0x0001
	.short 0x001A, 0x001B, 0x0001
	.short 0x001C, 0x001D, 0x0001
	.short 0x001E, 0x001F, 0x0001
	.short 0x0020, 0x0021, 0x0001
	.short 0x0022, 0x0023, 0x0001
	.short 0x0027, 0x0028, 0x0001
	.short 0x0029, 0x002A, 0x0001
	.short 0x005C, 0x005D, 0x0001
	.short 0x005E, 0x005F, 0x0001
	.short 0x0060, 0x0061, 0x0001
	.short 0x0062, 0x0063, 0x0001
	.short 0x0064, 0x0065, 0x0001
	.short 0x0066, 0x0067, 0x0001
	.short 0x0068, 0x0069, 0x0001
	.short 0x006A, 0x006B, 0x0001
	.short 0x006C, 0x006D, 0x0001
	.short 0x006E, 0x006F, 0x0001
	.short 0x0070, 0x0071, 0x0001
	.short 0x0072, 0x0073, 0x0001
	.short 0x0077, 0x0078, 0x0001
	.short 0x0079, 0x007A, 0x0001
	.short 0x0030, 0x0031, 0x0032
	.short 0x0033, 0x0034, 0x0035
	.short 0x0036, 0x0037, 0x0038
	.short 0x0039, 0x003A, 0x003B
	.short 0x003C, 0x003D, 0x003E
	.short 0x0080, 0x0081, 0x0082
	.short 0x0083, 0x0084, 0x0085
	.short 0x0086, 0x0087, 0x0088
	.short 0x0089, 0x008A, 0x008B
	.short 0x008C, 0x008D, 0x008E

	.balign 4, 0
	.public gOverlayTemplate_NamingScreen
gOverlayTemplate_NamingScreen:
	.word NamingScreenApp_Init, NamingScreenApp_Main, NamingScreenApp_Exit, 0xFFFFFFFF

	.data

	.global _021104E4
_021104E4:
	.word _02101DBE
	.word _02101DBE
	.word _02101DBE
	.word _02101DBE
	.word _02101DD8

	.global _021104F8
_021104F8:
	.word _02101E80, _02101E9C, _02101EB8, _02101E2C, _02101E64
	.word _02101EF0, _02101F0C, _0210205C, _02101F60, _02102024
	.word _02101F98, _02101FD0, _02101FEC, _02102008, _02102040
	.word _02101F7C, _02101DF2, _02101F44, _02101F28, _02101E48
	.word _021020D4, _021020F8, _0210211C, _0210211C, _0210211C
