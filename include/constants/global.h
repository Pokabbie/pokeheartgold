#ifndef POKEHEARTGOLD_CONSTANTS_GLOBAL_H
#define POKEHEARTGOLD_CONSTANTS_GLOBAL_H

#include "constants/rgb.h"
#include "constants/charcode.h"
#include "constants/global.fieldmap.h"

#define PLAYER_NAME_LENGTH      7
#define POKEMON_NAME_LENGTH     10

#define PLAYER_GENDER_MALE       0
#define PLAYER_GENDER_FEMALE     1

#define PARTY_SIZE 6

// alias
#ifndef PM_ASM
#define NNS_G2D_VRAM_TYPE_BOTH      ((NNS_G2D_VRAM_TYPE)(NNS_G2D_VRAM_TYPE_2DMAIN|NNS_G2D_VRAM_TYPE_2DSUB))
#endif //PM_ASM

#endif //POKEHEARTGOLD_CONSTANTS_GLOBAL_H
