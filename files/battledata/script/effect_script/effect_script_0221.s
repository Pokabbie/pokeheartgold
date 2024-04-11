    .include "macros/btlcmd.inc"

    .data

_000:
    UpdateMonDataFromVar OPCODE_GET, BATTLER_CATEGORY_DEFENDER, BMON_DATA_MAXHP, BSCRIPT_VAR_CALC_TEMP
    UpdateVar OPCODE_DIV, BSCRIPT_VAR_CALC_TEMP, 0x00000002
    CompareMonDataToVar OPCODE_GT, BATTLER_CATEGORY_DEFENDER, BMON_DATA_HP, BSCRIPT_VAR_CALC_TEMP, _020
    UpdateVar OPCODE_SET, BSCRIPT_VAR_POWER_MULTI, 20
    GoTo _024

_020:
    UpdateVar OPCODE_SET, BSCRIPT_VAR_POWER_MULTI, 10

_024:
    CalcCrit 
    CalcDamage 
    End 
