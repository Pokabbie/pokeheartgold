    .include "macros/btlcmd.inc"

    .data

_000:
    CompareMonDataToValue OPCODE_FLAG_NOT, BATTLER_CATEGORY_FAINTED_MON, BMON_DATA_STATUS2, STATUS2_DESTINY_BOND, _TRY_GRUDGE
    IfSameSide BATTLER_CATEGORY_ATTACKER, BATTLER_CATEGORY_FAINTED_MON, _TRY_GRUDGE
    CompareMonDataToValue OPCODE_EQU, BATTLER_CATEGORY_ATTACKER, BMON_DATA_HP, 0, _TRY_GRUDGE
    // {0} took {1} down with it!
    PrintMessage msg_0197_00391, TAG_NICKNAME_NICKNAME, BATTLER_CATEGORY_FAINTED_MON, BATTLER_CATEGORY_ATTACKER
    UpdateVarFromVar OPCODE_GET, BSCRIPT_VAR_BATTLER_FAINTED, BSCRIPT_VAR_LAST_BATTLER_ID
    UpdateMonDataFromVar OPCODE_GET, BATTLER_CATEGORY_ATTACKER, BMON_DATA_HP, BSCRIPT_VAR_HP_CALC
    UpdateVar OPCODE_MUL, BSCRIPT_VAR_HP_CALC, -1
    UpdateVarFromVar OPCODE_SET, BSCRIPT_VAR_MSG_BATTLER_TEMP, BSCRIPT_VAR_BATTLER_ATTACKER
    UpdateVar OPCODE_FLAG_ON, BSCRIPT_VAR_BATTLE_STATUS, BATTLE_STATUS_NO_BLINK
    Call BATTLE_SUBSCRIPT_UPDATE_HP
    PlayFaintAnimation 
    Wait 
    HealthbarSlideOut BATTLER_CATEGORY_FAINTED_MON
    // {0} fainted!
    PrintMessage msg_0197_00030, TAG_NICKNAME, BATTLER_CATEGORY_FAINTED_MON
    Wait 
    WaitButtonABTime 30
    IncrementGameStat BATTLER_CATEGORY_FAINTED_MON, BATTLER_TYPE_SOLO_ENEMY, GAME_STAT_UNK42
    IncrementGameStat BATTLER_CATEGORY_FAINTED_MON, BATTLER_TYPE_SOLO_PLAYER, GAME_STAT_UNK97
    UpdateVarFromVar OPCODE_GET, BSCRIPT_VAR_LAST_BATTLER_ID, BSCRIPT_VAR_BATTLER_FAINTED

_TRY_GRUDGE:
    TryGrudge _FAINT_MON
    // {0}’s {1} lost all its PP due to the grudge!
    PrintMessage msg_0197_00568, TAG_NICKNAME_MOVE, BATTLER_CATEGORY_ATTACKER, BATTLER_CATEGORY_MSG_TEMP
    Wait 
    WaitButtonABTime 30

_FAINT_MON:
    UpdateVar OPCODE_FLAG_ON, BSCRIPT_VAR_BATTLE_STATUS_2, BATTLE_STATUS2_NO_EXP_GAINED
    Call BATTLE_SUBSCRIPT_FAINT_MON
    UpdateVar OPCODE_FLAG_OFF, BSCRIPT_VAR_BATTLE_STATUS_2, BATTLE_STATUS2_NO_EXP_GAINED
    End 
