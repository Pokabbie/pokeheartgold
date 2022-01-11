#include "math_util.h"
#include "heap.h"

#define FX16_TO_FX32(x)   FX32_CONST(FX_FX16_TO_F32(x))

u32 sMTRNG_State[624];
u32 sLCRNG_State;
int sMTRNG_Cycles = 625;
u32 sMTRNG_XOR[2] = {0, 0x9908B0DF};
MATHCRC16Table *_021D15A4 = NULL;

u16 sub_0201FCD4(u16 deg);

fx32 sub_0201FBB8(u16 deg) {
    fx16 sinval;
    if (deg >= 360) {
        return 0;
    }
    sinval = FX_SinIdx(sub_0201FCD4(deg));
    return FX16_TO_FX32(sinval);
}

fx32 sub_0201FC30(u16 deg) {
    fx16 cosval;
    if (deg >= 360) {
        return 0;
    }
    cosval = FX_CosIdx(sub_0201FCD4(deg));
    return FX16_TO_FX32(cosval);
}

fx32 sub_0201FCAC(u16 deg) {
    deg %= 360;
    return sub_0201FBB8(deg);
}

fx32 sub_0201FCC0(u16 deg) {
    deg %= 360;
    return sub_0201FC30(deg);
}

u16 sub_0201FCD4(u16 deg) {
    if (deg >= 360) {
        return 0;
    }
    return FX_DEG_TO_IDX(deg << FX32_SHIFT);
}

u16 sub_0201FD00(u16 deg) {
    return sub_0201FCD4(deg % 360);
}

fx32 sub_0201FD14(fx32 deg) {
    return sub_0201FCAC(deg >> FX32_SHIFT);
}

fx32 sub_0201FD20(fx32 deg) {
    return sub_0201FCC0(deg >> FX32_SHIFT);
}

u32 GetLCRNGSeed(void) {
    return sLCRNG_State;
}

void SetLCRNGSeed(u32 seed) {
    sLCRNG_State = seed;
}

u16 LCRandom(void) {
    sLCRNG_State *= 1103515245;
    sLCRNG_State += 24691;
    return sLCRNG_State / 65536;
}

u32 PRandom(u32 seed) {
    return seed * 1812433253 + 1;
}

void SetMTRNGSeed(u32 seed) {
    sMTRNG_State[0] = seed;
    for (sMTRNG_Cycles = 1; sMTRNG_Cycles < 624; sMTRNG_Cycles++) {
        sMTRNG_State[sMTRNG_Cycles] = 1812433253 * (sMTRNG_State[sMTRNG_Cycles - 1] ^ (sMTRNG_State[sMTRNG_Cycles - 1] >> 30)) + sMTRNG_Cycles;
    }
}

u32 MTRandom(void)
{
    u32 val;
    s32 i;

    if (sMTRNG_Cycles >= 624) {
        if (sMTRNG_Cycles == 625) {
            SetMTRNGSeed(5489);
        }

        for (i = 0; i < 227; i++) {
            val = (sMTRNG_State[i] & 0x80000000) | (sMTRNG_State[i + 1] & 0x7fffffff);
            sMTRNG_State[i] = sMTRNG_State[i + 397] ^ (val >> 1) ^ sMTRNG_XOR[val & 0x1];
        }
        for (; i < 623; i++) {
            val = (sMTRNG_State[i] & 0x80000000) | (sMTRNG_State[i + 1] & 0x7fffffff);
            sMTRNG_State[i] = sMTRNG_State[i + -227] ^ (val >> 1) ^ sMTRNG_XOR[val & 0x1];
        }

        val = (sMTRNG_State[623] & 0x80000000) | (sMTRNG_State[0] & 0x7fffffff);
        sMTRNG_State[623] = sMTRNG_State[396] ^ (val >> 1) ^ sMTRNG_XOR[val & 0x1];

        sMTRNG_Cycles = 0;
    }

    val = sMTRNG_State[sMTRNG_Cycles++]; // has to be this way in order to match

    val ^= val >> 11;
    val ^= (val << 7) & 0x9d2c5680;
    val ^= (val << 15) & 0xefc60000;
    val ^= val >> 18;

    return val;
}

void MTX22_2DAffine(MtxFx22 * mtx, u16 radians, fx32 x, fx32 y, u8 type) {
    if (type == 1) {
        radians = (u16)((u32)(radians * 65535) >> 8);
    } else if (type == 2) {
        radians = (u16)((u32)(radians * 65535) / 360);
    }
    MTX_Rot22_(mtx, FX_SinIdx(radians), FX_CosIdx(radians));
    MTX_ScaleApply22(mtx, mtx, x, y);
}

u32 Math_CalcArraySum(const void *data, u32 size) {
    const u8 *data8 = (const u8 *)data;
    u32 sum = 0;
    int i;
    for (i = 0; i < size; i++) {
        sum += *data8++;
    }
    return sum;
}

u16 MonEncryptionLCRNG(u32 *seed_p);

void _MonEncryptSegment(u16 * data, u32 size, u32 seed) {
    int i;
    for (i = 0; i < size / 2; i++) {
        data[i] ^= MonEncryptionLCRNG(&seed);
    }
}

void _MonDecryptSegment(u16 * data, u32 size, u32 seed) {
    _MonEncryptSegment(data, size, seed);
}

u16 MonEncryptionLCRNG(u32 * seed) {
    *seed = *seed * 1103515245 + 24691;
    return (u16)(*seed >> 16);
}

u16 GF_CalcCRC16(const void *data, u32 size) {
    return MATH_CalcCRC16CCITT(_021D15A4, data, size);
}

void GF_CRC16Init(HeapID heapId) {
    GF_ASSERT(_021D15A4 == NULL);
    _021D15A4 = AllocFromHeap(heapId, sizeof(MATHCRC16Table));
    MATH_CRC16InitTable(_021D15A4);
}
