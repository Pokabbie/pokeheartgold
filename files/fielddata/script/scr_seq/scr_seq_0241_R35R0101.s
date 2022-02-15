#include "constants/scrcmd.h"
#include "fielddata/script/scr_seq/event_R35R0101.h"
#include "msgdata/msg/msg_0388_R35R0101.h"
	.include "asm/macros/script.inc"

	.rodata

	scrdef scr_seq_R35R0101_000
	scrdef scr_seq_R35R0101_001
	scrdef_end

scr_seq_R35R0101_001:
	play_se SEQ_SE_DP_SELECT
	lockall
	faceplayer
	goto_if_set FLAG_GOT_RADIO_CARD, _0028
	npc_msg msg_0388_R35R0101_00013
	waitbutton
	closemsg
	releaseall
	end

_0028:
	npc_msg msg_0388_R35R0101_00014
	touchscreen_menu_hide
	getmenuchoice VAR_SPECIAL_RESULT
	touchscreen_menu_show
	compare VAR_SPECIAL_RESULT, 1
	goto_if_eq _004B
	npc_msg msg_0388_R35R0101_00015
	waitbutton
	closemsg
	releaseall
	end

_004B:
	npc_msg msg_0388_R35R0101_00016
	waitbutton
	closemsg
	releaseall
	end

scr_seq_R35R0101_000:
	play_se SEQ_SE_DP_SELECT
	lockall
	faceplayer
	compare VAR_UNK_4114, 1
	goto_if_eq _00BC
	compare VAR_UNK_4114, 2
	goto_if_ge _0104
	npc_msg msg_0388_R35R0101_00000
	touchscreen_menu_hide
	getmenuchoice VAR_SPECIAL_RESULT
	touchscreen_menu_show
	compare VAR_SPECIAL_RESULT, 1
	goto_if_eq _00EE
	get_party_count VAR_SPECIAL_RESULT
	compare VAR_SPECIAL_RESULT, 6
	goto_if_eq _00F9
	npc_msg msg_0388_R35R0101_00003
	give_loan_mon 7, 20, 101
	setvar VAR_UNK_4114, 1
	buffer_players_name 0
	npc_msg msg_0388_R35R0101_00004
	play_fanfare SEQ_ME_PT_SPECIAL
	wait_fanfare
_00BC:
	scrcmd_781 VAR_SPECIAL_RESULT
	compare VAR_SPECIAL_RESULT, 0
	goto_if_eq _0178
	goto_if_set FLAG_UNK_0B5, _00E3
	npc_msg msg_0388_R35R0101_00006
	waitbutton
	closemsg
	releaseall
	end

_00E3:
	npc_msg msg_0388_R35R0101_00005
	waitbutton
	closemsg
	releaseall
	end

_00EE:
	npc_msg msg_0388_R35R0101_00001
	waitbutton
	closemsg
	releaseall
	end

_00F9:
	npc_msg msg_0388_R35R0101_00002
	waitbutton
	closemsg
	releaseall
	end

_0104:
	compare VAR_UNK_4114, 4
	goto_if_ge _016D
	npc_msg msg_0388_R35R0101_00007
	goto_if_no_item_space ITEM_HP_UP, 1, _0163
	callstd std_give_item_verbose
	compare VAR_UNK_4114, 3
	goto_if_ne _0152
	setvar VAR_UNK_4114, 5
	goto _0158

_0152:
	setvar VAR_UNK_4114, 4
_0158:
	npc_msg msg_0388_R35R0101_00008
	waitbutton
	closemsg
	releaseall
	end

_0163:
	callstd std_bag_is_full
	closemsg
	releaseall
	end

_016D:
	npc_msg msg_0388_R35R0101_00010
	waitbutton
	closemsg
	releaseall
	end

_0178:
	setvar VAR_UNK_4114, 6
	npc_msg msg_0388_R35R0101_00009
	waitbutton
	closemsg
	releaseall
	end
	.balign 4, 0