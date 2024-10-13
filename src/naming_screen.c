#include "naming_screen.h"

#include "global.h"

#include "msgdata/msg.naix"
#include "msgdata/msg/msg_0197.h"
#include "msgdata/msg/msg_0249.h"
#include "msgdata/msg/msg_0254.h"

#include "bg_window.h"
#include "filesystem.h"
#include "font.h"
#include "gf_gfx_loader.h"
#include "gf_gfx_planes.h"
#include "launch_application.h"
#include "math_util.h"
#include "message_format.h"
#include "msgdata.h"
#include "obj_char_transfer.h"
#include "obj_pltt_transfer.h"
#include "pokemon_icon_idx.h"
#include "sound_02004A44.h"
#include "systask_environment.h"
#include "system.h"
#include "text.h"
#include "unk_02005D10.h"
#include "unk_0200ACF0.h"
#include "unk_0200B150.h"
#include "unk_0200FA24.h"
#include "unk_02013534.h"
#include "unk_020163E0.h"
#include "unk_020183F0.h"
#include "vram_transfer_manager.h"

typedef struct NamingScreenAppData {
    NameScreenType type;
    int unk_004;
    int unk_008;
    int maxLen;
    int unk_010;
    int unk_014;
    Options *unk_018;
    int cursorX;
    int cursorY;
    int unk_024;
    int unk_028;
    int unk_02C;
    int unk_030;
    int unk_034;
    u16 unk_038;
    u16 unk_03A[6][13];
    u8 filler_0D6[2];
    u16 unk_0D8[0x20];
    u16 unk_118[0x20];
    u16 unk_158;
    u16 unk_15A[3];
    BgConfig *bgConfig; // 0x160
    u8 filler_164[4];
    MessageFormat *msgFormat; // 0x168
    MsgData *msgData_249;     // 0x16C
    MsgData *msgData_254;     // 0x170
    MsgData *msgData_197;     // 0x174
    String *unk_178;
    String *unk_17C;
    String *unk_180;
    String *unk_184;
    SpriteList *unk_188;
    GF_G2dRenderer unk_18C;
    GF_2DGfxResMan *unk_2B4[4];
    GF_2DGfxResObj *unk_2C4[2][4];
    SpriteResourcesHeader unk_2E4;
    SpriteResourcesHeader unk_308;
    Sprite *unk_32C[14];
    Sprite *unk_364[12];
    Sprite *unk_394[2];
    SysTask *unk_39C[7];
    Window unk_3B8[10];
    int unk_458;
    int unk_45C;
    int unk_460;
    GFBgLayer unk_464;
    VecFx32 unk_468[2];
    u8 filler_480[4];
    int unk_484;
    int unk_488;
    int unk_48C;
    int unk_490[7];
    void *unk_4AC;
    NNSG2dCharacterData *unk_4B0;
    void *unk_4B4;
    NNSG2dCharacterData *unk_4B8;
    void *unk_4BC;
    NNSG2dPaletteData *unk_4C0;
    u8 unk_4C4[0x100];
    UnkStruct_020163E0 *unk_5C4;
    BOOL unk_5C8;
    int unk_5CC;
    BOOL *unk_5D0;
} NamingScreenAppData; // size: 0x5D4

typedef struct UnkStruct_02102278 {
    u8 x;
    u8 y;
    u16 unk_2_0 : 2;
    u8 unk_4_0  : 5;
    u8 unk_4_5  : 5;
} UnkStruct_02102278;

BOOL NamingScreenApp_Init(OVY_MANAGER *ovyMan, int *pState);
static void sub_02082AEC(NNSG2dCharacterData *pCharData, NNSG2dPaletteData *pPlttData, int species, int form);
BOOL NamingScreenApp_Main(OVY_MANAGER *ovyMan, int *pState);
static int sub_02082CF8(NamingScreenAppData *data, int a1);
static void sub_02082E28(NamingScreenAppData *data, NamingScreenArgs *args);
static BOOL sub_02082EC0(const u16 *s);
BOOL NamingScreenApp_Exit(OVY_MANAGER *ovyMan, int *pState);
static void sub_02083140(void *param);
static BOOL sub_02082EC0(const u16 *s);
static void sub_02083160(NamingScreenAppData *data, NamingScreenArgs *args);
static void sub_02083184(void);
static void sub_020831A4(BgConfig *bgConfig);
static void sub_020832E4(GFPlaneToggle enable);
static void sub_02083334(NamingScreenAppData *data, OVY_MANAGER *ovyMan);
static void sub_020834FC(NamingScreenAppData *data, OVY_MANAGER *ovyMan);
static void sub_02083614(BgConfig *bgConfig, Window *a1);
static void sub_02083654(NamingScreenAppData *data, NARC *narc);
static void sub_0208377C(void);
static void sub_020837AC(NamingScreenAppData *data, NARC *narc);
static void sub_020839B8(SysTask *task, void *taskData);
static void sub_020839EC(NamingScreenAppData *data);
static void sub_02083BB4(NamingScreenAppData *data, SpriteTemplate *tmplate);
static void sub_02083CAC(SysTask *task, void *taskData);
static void sub_02083D34(BgConfig *bgConfig, Window *windows, int *pState, int pageNum, GFBgLayer *pBgId, VecFx32 *posVecs, Sprite **pSprites, void *pRawData);
static void sub_02083F18(Window *window, NameScreenType unused, String *msg);
static void sub_02083F48(Window *window, NameScreenType unused, String *msg);
static void sub_02083F9C(NamingScreenAppData *data, OVY_MANAGER *ovyMan, NARC *narc);
static void sub_0208421C(BgConfig *bgConfig, GFBgLayer bgId, VecFx32 *pos);
static void sub_0208423C(VecFx32 *posVecs, GFBgLayer bgId);
static int sub_02084264(int val, int lo, int hi);
static void sub_02084274(NamingScreenAppData *data, int a1);
static void sub_0208432C(NamingScreenAppData *data);
static void sub_02084430(NamingScreenAppData *data, int a1);
static void sub_02084500(u16 *a0);
static void sub_02084540(Window *window, const u16 *rawChars, int x, int y, int spacing, int textSpeed, u32 color, u8 *buttonPixels);
static void *sub_02084640(Window *window, String *string, FontID fontId, u32 color);
static void sub_02084664(Window *windows, const u16 *a1, void *a2, String *a3);
static void sub_02084740(Window *a0, u16 *a1, u16 a2, u16 *a3, void *a4, String *a5);
static void sub_02084830(u16 (*a0)[13], const int a1);
static int sub_02084884(NamingScreenAppData *data, u16 key, BOOL a2);
static void sub_02084C58(NamingScreenAppData *data, BOOL a1);
static int sub_02084C78(const u16 *a0, int a1);
static BOOL sub_02084C98(int a0, int a1, u16 *a2, int a3);
static BOOL sub_02084D04(int a0, int a1, int a2, int a3, u16 *a4, int a5);
static void sub_02084E18(Sprite **sprites, int a1, int maxLen);
static void sub_02084E54(Window *window, u16 fillVal, int pageNum, u32 textColor, u8 *pRawData);
static void sub_02084F3C(int *a0, Sprite **a1, int a2);
static void sub_02084FCC(NamingScreenAppData *data);
static BOOL sub_0208503C(NamingScreenAppData *data);

static NamingScreenAppData *_021D43B0;

static const int _021021E8[][4] = {
    { 0x04, 0x44, 0x03, 0x01 },
    { 0x24, 0x44, 0x08, 0x01 },
    { 0x44, 0x44, 0x0D, 0x01 },
    { 0x00, 0xC8, 0x12, 0x01 },
    { 0x65, 0x44, 0x14, 0x01 },
    { 0x88, 0x44, 0x17, 0x01 },
    { 0xB0, 0x44, 0x19, 0x01 },
    { 0x16, 0x38, 0x25, 0x02 },
    { 0x1A, 0x5B, 0x27, 0x00 },
};

static const u16 _02101DBE[] = { 0xE002, 0xE002, 0xE003, 0xE003, 0xE004, 0xE004, 0xD004, 0xD004, 0xE007, 0xE007, 0xE007, 0xE008, 0xE008 };

static const u16 _02101DD8[] = { 0xD004, 0xD004, 0xD004, 0xD004, 0xD004, 0xD004, 0xD004, 0xD004, 0xE007, 0xE007, 0xE007, 0xE008, 0xE008 };

static const u16 *_021104E4[] = {
    _02101DBE,
    _02101DBE,
    _02101DBE,
    _02101DBE,
    _02101DD8,
};

static const u16 _02101D80[] = {
    0x0019,
    0x0039,
    0x0059,
    0x0061,
    0x007A,
    0x009E,
    0x00C6,
    0x0000,
};

static const u8 _02101D4C[] = {
    0x28,
    0x28,
    0x28,
    0x28,
    0x29,
    0x29,
    0x29,
};

static const u16 _02101E80[] = { 0x012B, 0x012C, 0x012D, 0x012E, 0x012F, 0x0130, 0x0131, 0x0132, 0x0133, 0x0134, 0x01DE, 0x01AD, 0x01AE, 0xFFFF };

static const u16 _02101E9C[] = { 0x0135, 0x0136, 0x0137, 0x0138, 0x0139, 0x013A, 0x013B, 0x013C, 0x013D, 0x013E, 0x01DE, 0x01B3, 0x01BE, 0xFFFF };

static const u16 _02101EB8[] = { 0x013F, 0x0140, 0x0141, 0x0142, 0x0143, 0x0144, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01BB, 0x01BC, 0xFFFF };

static const u16 _02101E2C[] = { 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0xFFFF };

static const u16 _02101E64[] = { 0x0121, 0x0122, 0x0123, 0x0124, 0x0125, 0x0126, 0x0127, 0x0128, 0x0129, 0x012A, 0x01DE, 0x01DE, 0x01DE, 0xFFFF };

static const u16 _02101EF0[] = { 0x0145, 0x0146, 0x0147, 0x0148, 0x0149, 0x014A, 0x014B, 0x014C, 0x014D, 0x014E, 0x01DE, 0x01AD, 0x01AE, 0xFFFF };

static const u16 _02101F0C[] = { 0x014F, 0x0150, 0x0151, 0x0152, 0x0153, 0x0154, 0x0155, 0x0156, 0x0157, 0x0158, 0x01DE, 0x01B3, 0x01BE, 0xFFFF };

static const u16 _0210205C[] = { 0x0159, 0x015A, 0x015B, 0x015C, 0x015D, 0x015E, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01BB, 0x01BC, 0xFFFF };

static const u16 _02101F60[] = { 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0xFFFF };

static const u16 _02102024[] = { 0x0121, 0x0122, 0x0123, 0x0124, 0x0125, 0x0126, 0x0127, 0x0128, 0x0129, 0x012A, 0x01DE, 0x01DE, 0x01DE, 0xFFFF };

static const u16 _02101F98[] = { 0x01AD, 0x01AE, 0x01C4, 0x01C5, 0x01AB, 0x01AC, 0x01DE, 0x01DE, 0x01DE, 0x01BB, 0x01BC, 0x01DE, 0x01DE, 0xFFFF };

static const u16 _02101FD0[] = { 0x01B4, 0x01B5, 0x01B2, 0x01B3, 0x01B9, 0x01BA, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0x01DE, 0xFFFF };

static const u16 _02101FEC[] = { 0x01AF, 0x01B0, 0x01C3, 0x01D0, 0x01C0, 0x01D2, 0x01BD, 0x01BE, 0x01BF, 0x01B1, 0x01C1, 0x01DE, 0x01DE, 0xFFFF };

static const u16 _02102008[] = { 0x01CB, 0x01CC, 0x01CD, 0x01CE, 0x01CF, 0x01C6, 0x01C8, 0x01C9, 0x01C7, 0x01CA, 0x01D1, 0x01DE, 0x01DE, 0xFFFF };

static const u16 _02102040[] = { 0x01D3, 0x01D4, 0x01D5, 0x01D6, 0x01D7, 0x01D8, 0x01D9, 0x01DA, 0x01DD, 0x01DB, 0x01DC, 0x01DE, 0x01DE, 0xFFFF };

static const u16 _02101F7C[] = { 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x0001, 0x00E1, 0x00E2, 0xFFFF };

static const u16 _02101DF2[] = { 0x00E3, 0x00E4, 0x00F9, 0x00F8, 0x00E5, 0x00E6, 0x00F5, 0x00F6, 0x00F7, 0x00E7, 0x0001, 0x00EE, 0x00EF, 0xFFFF };

static const u16 _02101F44[] = { 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x0106, 0x0104, 0xFFFF };

static const u16 _02101F28[] = { 0x00FF, 0x0100, 0x0101, 0x0102, 0x0103, 0x00FC, 0x00FA, 0x00FD, 0x00FB, 0x00FE, 0x0105, 0x0001, 0x0001, 0xFFFF };

static const u16 _02101E48[] = { 0x0107, 0x0108, 0x0109, 0x010A, 0x010B, 0x010C, 0x010D, 0x010E, 0x0111, 0x010F, 0x0110, 0x0001, 0x0001, 0xFFFF };

static const u16 _021020D4[] = { 0x0121, 0x0122, 0x0123, 0x0124, 0x0125, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0xFFFF };

static const u16 _021020F8[] = { 0x0126, 0x0127, 0x0128, 0x0129, 0x012A, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0xFFFF };

static const u16 _0210211C[] = { 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0xFFFF };

static const u16 *_021104F8[][5] = {
    { _02101E80, _02101E9C, _02101EB8, _02101E2C, _02101E64 },
    { _02101EF0, _02101F0C, _0210205C, _02101F60, _02102024 },
    { _02101F98, _02101FD0, _02101FEC, _02102008, _02102040 },
    { _02101F7C, _02101DF2, _02101F44, _02101F28, _02101E48 },
    { _021020D4, _021020F8, _0210211C, _0210211C, _0210211C },
};

static const u16 _02102422[][3] = {
    { 0x0003, 0x0001, 0x0002 },
    { 0x0005, 0x0001, 0x0004 },
    { 0x0007, 0x0001, 0x0006 },
    { 0x0009, 0x0001, 0x0008 },
    { 0x000B, 0x0001, 0x000A },
    { 0x0053, 0x0001, 0x0052 },
    { 0x0055, 0x0001, 0x0054 },
    { 0x0057, 0x0001, 0x0056 },
    { 0x0059, 0x0001, 0x0058 },
    { 0x005B, 0x0001, 0x005A },
    { 0x0045, 0x0001, 0x0044 },
    { 0x0047, 0x0001, 0x0046 },
    { 0x0049, 0x0001, 0x0048 },
    { 0x0095, 0x0001, 0x0094 },
    { 0x0097, 0x0001, 0x0096 },
    { 0x0099, 0x0001, 0x0098 },
    { 0x00AC, 0x0001, 0x00C6 },
    { 0x00AD, 0x0001, 0x00C7 },
    { 0x00AE, 0x0001, 0x00C8 },
    { 0x00AF, 0x0001, 0x00C9 },
    { 0x00B0, 0x0001, 0x00CA },
    { 0x00B1, 0x0001, 0x00CB },
    { 0x00B2, 0x0001, 0x00CC },
    { 0x00B3, 0x0001, 0x00CD },
    { 0x00B4, 0x0001, 0x00CE },
    { 0x00B5, 0x0001, 0x00CF },
    { 0x00B6, 0x0001, 0x00D0 },
    { 0x00B7, 0x0001, 0x00D1 },
    { 0x00B8, 0x0001, 0x00D2 },
    { 0x00B9, 0x0001, 0x00D3 },
    { 0x00BA, 0x0001, 0x00D4 },
    { 0x00BB, 0x0001, 0x00D5 },
    { 0x00BC, 0x0001, 0x00D6 },
    { 0x00BD, 0x0001, 0x00D7 },
    { 0x00BE, 0x0001, 0x00D8 },
    { 0x00BF, 0x0001, 0x00D9 },
    { 0x00C0, 0x0001, 0x00DA },
    { 0x00C1, 0x0001, 0x00DB },
    { 0x00C2, 0x0001, 0x00DC },
    { 0x00C3, 0x0001, 0x00DD },
    { 0x00C4, 0x0001, 0x00DE },
    { 0x00C5, 0x0001, 0x00DF },
    { 0x0025, 0x0026, 0x0024 },
    { 0x0075, 0x0076, 0x0074 },
    { 0x000C, 0x000D, 0x0001 },
    { 0x000E, 0x000F, 0x0001 },
    { 0x0010, 0x0011, 0x0001 },
    { 0x0012, 0x0013, 0x0001 },
    { 0x0014, 0x0015, 0x0001 },
    { 0x0016, 0x0017, 0x0001 },
    { 0x0018, 0x0019, 0x0001 },
    { 0x001A, 0x001B, 0x0001 },
    { 0x001C, 0x001D, 0x0001 },
    { 0x001E, 0x001F, 0x0001 },
    { 0x0020, 0x0021, 0x0001 },
    { 0x0022, 0x0023, 0x0001 },
    { 0x0027, 0x0028, 0x0001 },
    { 0x0029, 0x002A, 0x0001 },
    { 0x005C, 0x005D, 0x0001 },
    { 0x005E, 0x005F, 0x0001 },
    { 0x0060, 0x0061, 0x0001 },
    { 0x0062, 0x0063, 0x0001 },
    { 0x0064, 0x0065, 0x0001 },
    { 0x0066, 0x0067, 0x0001 },
    { 0x0068, 0x0069, 0x0001 },
    { 0x006A, 0x006B, 0x0001 },
    { 0x006C, 0x006D, 0x0001 },
    { 0x006E, 0x006F, 0x0001 },
    { 0x0070, 0x0071, 0x0001 },
    { 0x0072, 0x0073, 0x0001 },
    { 0x0077, 0x0078, 0x0001 },
    { 0x0079, 0x007A, 0x0001 },
    { 0x0030, 0x0031, 0x0032 },
    { 0x0033, 0x0034, 0x0035 },
    { 0x0036, 0x0037, 0x0038 },
    { 0x0039, 0x003A, 0x003B },
    { 0x003C, 0x003D, 0x003E },
    { 0x0080, 0x0081, 0x0082 },
    { 0x0083, 0x0084, 0x0085 },
    { 0x0086, 0x0087, 0x0088 },
    { 0x0089, 0x008A, 0x008B },
    { 0x008C, 0x008D, 0x008E },
};

static const u16 _021021B8[][2] = {
    { 0x0024, 0x0026 },
    { 0x0074, 0x0076 },
    { 0x0032, 0x0031 },
    { 0x0035, 0x0034 },
    { 0x0038, 0x0037 },
    { 0x003B, 0x003A },
    { 0x003E, 0x003D },
    { 0x0082, 0x0081 },
    { 0x0085, 0x0084 },
    { 0x0088, 0x0087 },
    { 0x008B, 0x008A },
    { 0x008E, 0x008D },
};

static const u16 _02102190[][2] = {
    { 0x0031, 0x0032 },
    { 0x0034, 0x0035 },
    { 0x0037, 0x0038 },
    { 0x003A, 0x003B },
    { 0x003D, 0x003E },
    { 0x0081, 0x0082 },
    { 0x0084, 0x0085 },
    { 0x0087, 0x0088 },
    { 0x008A, 0x008B },
    { 0x008D, 0x008E },
};

static const int _02101D54[] = {
    0x00000070,
    0x0000004C,
    0x00000048,
};

static const u8 _02101D40[] = {
    0x04,
    0x07,
    0x0D,
    0x0A,
};

const u16 _02101D90[] = { 0x0003, 0x002B, 0x0020, 0x002F, 0x0001, 0x002B, 0x003F, 0x0009, 0x0030, 0x00E2, 0xFFFF };

// ポケモンの ニックネ－ムは？
const u16 _02102094[] = { 0x008E, 0x0062, 0x0093, 0x00A1, 0x002F, 0x0001, 0x007C, 0x0074, 0x0060, 0x007E, 0x00F1, 0x0091, 0x0030, 0x00E2, 0xFFFF };

const u16 _02101DA6[] = { 0x008D, 0x0074, 0x0060, 0x006A, 0x002F, 0x0001, 0x002B, 0x003F, 0x0009, 0x0030, 0x00E2, 0xFFFF };

static const u16 *sDeadstrippedPointersTable[] = {
    _02101D90,
    _02102094,
    _02101DA6,
};

static const int _021020B4[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    8,
};

const OVY_MGR_TEMPLATE gOverlayTemplate_NamingScreen = {
    NamingScreenApp_Init,
    NamingScreenApp_Main,
    NamingScreenApp_Exit,
    FS_OVERLAY_ID_NONE,
};

BOOL NamingScreenApp_Init(OVY_MANAGER *ovyMan, int *pState) {
    NamingScreenAppData *data;
    NARC *narc;
    switch (*pState) {
    case 0:
        Main_SetVBlankIntrCB(NULL, NULL);
        HBlankInterruptDisable();
        GfGfx_DisableEngineAPlanes();
        GfGfx_DisableEngineBPlanes();
        GX_SetVisiblePlane(0);
        GXS_SetVisiblePlane(0);
        CreateHeap(HEAP_ID_3, HEAP_ID_NAMING_SCREEN, 0x28000);

        data = OverlayManager_CreateAndGetData(ovyMan, sizeof(NamingScreenAppData), HEAP_ID_NAMING_SCREEN);
        memset(data, 0, sizeof(NamingScreenAppData));
        data->bgConfig    = BgConfig_Alloc(HEAP_ID_NAMING_SCREEN);
        narc              = NARC_New(NARC_a_0_3_1, HEAP_ID_NAMING_SCREEN);
        data->msgFormat   = MessageFormat_New(HEAP_ID_NAMING_SCREEN);
        data->msgData_249 = NewMsgDataFromNarc(MSGDATA_LOAD_DIRECT, NARC_msgdata_msg, NARC_msg_msg_0249_bin, HEAP_ID_NAMING_SCREEN);
        data->msgData_254 = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_msgdata_msg, NARC_msg_msg_0254_bin, HEAP_ID_NAMING_SCREEN);
        data->msgData_197 = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_msgdata_msg, NARC_msg_msg_0197_bin, HEAP_ID_NAMING_SCREEN);
        SetKeyRepeatTimers(4, 8);
        sub_02083184();
        sub_020831A4(data->bgConfig);
        sub_02083160(data, OverlayManager_GetArgs(ovyMan));
        sub_02083654(data, narc);
        FontID_Alloc(2, HEAP_ID_NAMING_SCREEN);
        Main_SetVBlankIntrCB(sub_02083140, NULL);
        sub_02083334(data, ovyMan);
        FontID_SetAccessDirect(0, HEAP_ID_NAMING_SCREEN);
        sub_0208377C();
        sub_020837AC(data, narc);
        sub_020839EC(data);
        sub_02083F9C(data, ovyMan, narc);
        sub_02084740(&data->unk_3B8[4], data->unk_0D8, data->unk_158, data->unk_15A, data->unk_4C4, data->unk_17C);
        sub_02004EC4(0x34, 0, 0);
        BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 16, 1, HEAP_ID_NAMING_SCREEN);
        sub_020832E4(GF_PLANE_TOGGLE_ON);
        GfGfx_SetMainDisplay(PM_LCD_BOTTOM);
        NARC_Delete(narc);
        ++(*pState);
        break;
    case 1:
        data = OverlayManager_GetData(ovyMan);
        if (data->type == NAME_SCREEN_POKEMON) {
            sub_02082AEC(data->unk_4B8, data->unk_4C0, data->unk_004, data->unk_008);
        }
        _021D43B0     = data;
        data->unk_5C4 = sub_020163E0(NULL, PM_LCD_BOTTOM, 12, HEAP_ID_NAMING_SCREEN);
        *pState       = 0;
        return TRUE;
    }

    return FALSE;
}

static void sub_02082AEC(NNSG2dCharacterData *pCharData, NNSG2dPaletteData *pPlttData, int species, int form) {
    GX_LoadOBJ(pCharData->pRawData, 0x57E0, 0x200);
    const u16 *rawPltt = pPlttData->pRawData;
    u32 plttNo         = GetMonIconPaletteEx(species, form, FALSE);
    GX_LoadOBJPltt(rawPltt + 16 * plttNo, 0xC0, 0x20);
}

BOOL NamingScreenApp_Main(OVY_MANAGER *ovyMan, int *pState) {
    NamingScreenAppData *data = OverlayManager_GetData(ovyMan);

    switch (*pState) {
    case 0:
        if (IsPaletteFadeFinished()) {
            *pState       = 1;
            data->unk_5CC = 0;
        }
        break;
    case 1:
        ++data->unk_5CC;
        sub_02084FCC(data);
        sub_02084F3C(data->unk_490, data->unk_32C, data->unk_460);
        if (data->unk_5CC > 5) {
            *pState       = 2;
            data->unk_5CC = 0;
        }
        break;
    case 2:
        switch (data->unk_45C) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            if (data->unk_034 == 0) {
                *pState = sub_02082CF8(data, *pState);
            }
            sub_02084FCC(data);
            break;
        case 5:
            sub_020834FC(data, ovyMan);
            FillWindowPixelBuffer(&data->unk_3B8[9], 15);
            DrawFrameAndWindow2(&data->unk_3B8[9], FALSE, 256, 10);
            data->unk_458 = AddTextPrinterParameterized(&data->unk_3B8[9], 1, data->unk_180, 0, 0, 1, NULL);
            CopyWindowToVram(&data->unk_3B8[9]);
            data->unk_45C = 6;
            break;
        case 6:
            if (!TextPrinterCheckActive(data->unk_458)) {
                PlaySE(SEQ_SE_DP_PIRORIRO);
                ++data->unk_490[6];
                data->unk_5CC = 0;
                data->unk_45C = 7;
            }
            break;
        case 7:
            ++data->unk_5CC;
            if (data->unk_5CC > 30) {
                BeginNormalPaletteFade(2, 0, 0, RGB_BLACK, 16, 1, HEAP_ID_NAMING_SCREEN);
                *pState = 3;
            }
            break;
        }
        sub_02083D34(data->bgConfig, data->unk_3B8, &data->unk_45C, data->unk_460, &data->unk_464, data->unk_468, data->unk_32C, data->unk_4B0->pRawData);
        sub_02084F3C(data->unk_490, data->unk_32C, data->unk_460);
        sub_02084500(&data->unk_038);
        break;
    case 3:
        if (IsPaletteFadeFinished()) {
            return TRUE;
        }
        break;
    }

    SpriteList_RenderAndAnimateSprites(data->unk_188);
    return FALSE;
}

static int sub_02082CF8(NamingScreenAppData *data, int a1) {
    int ret = a1;

    sub_0208432C(data);
    if (gSystem.newKeys & PAD_BUTTON_SELECT) {
        if (!Sprite_GetVisibleFlag(data->unk_32C[8])) {
            Sprite_SetVisibleFlag(data->unk_32C[8], TRUE);
            return ret;
        }
        if (data->type != 4) {
            data->unk_45C = 0;
            ++data->unk_460;
            if (data->unk_460 >= 3) {
                data->unk_460 = 0;
            }
            ++data->unk_490[data->unk_460];
            sub_02084830(data->unk_03A, data->unk_460);
            PlaySE(SEQ_SE_DP_SYU03);
            data->unk_030 = 1;
        }
        ++data->unk_490[data->unk_460];
        sub_02084830(data->unk_03A, data->unk_460);
        PlaySE(SEQ_SE_DP_SYU03);
    } else if (gSystem.newKeys & PAD_BUTTON_A) {
        ret           = sub_02084884(data, data->unk_03A[data->cursorY][data->cursorX], TRUE);
        data->unk_030 = 1;
    } else if (data->unk_5C8 == TRUE) {
        ret = sub_02084884(data, data->unk_03A[data->cursorY][data->cursorX], FALSE);
    } else if (gSystem.newKeys & PAD_BUTTON_B) {
        ret = sub_02084884(data, 0xE007, TRUE);
    } else if (gSystem.newKeys & PAD_BUTTON_R) {
        ret = sub_02084884(data, 0xE006, TRUE);
    }
    return ret;
}

#ifdef HEARTGOLD
#define FIRST_DEFAULT_NAME_MALE   msg_0254_00000
#define FIRST_DEFAULT_NAME_FEMALE msg_0254_00018
#define FIRST_DEFAULT_NAME_RIVAL  msg_0254_00084
#else
#define FIRST_DEFAULT_NAME_MALE   msg_0254_00042
#define FIRST_DEFAULT_NAME_FEMALE msg_0254_00060
#define FIRST_DEFAULT_NAME_RIVAL  msg_0254_00085
#endif // HEARTGOLD

static void sub_02082E28(NamingScreenAppData *data, NamingScreenArgs *args) {
    String *string;

    if (data->type == NAME_SCREEN_PLAYER) {
        if (data->unk_004 == PLAYER_GENDER_MALE) {
            string = NewString_ReadMsgData(data->msgData_254, FIRST_DEFAULT_NAME_MALE + (LCRandom() % 18));
        } else if (data->unk_004 == PLAYER_GENDER_FEMALE) {
            string = NewString_ReadMsgData(data->msgData_254, FIRST_DEFAULT_NAME_FEMALE + (LCRandom() % 18));
        }
        // UB: Nonbinary players will not initialize string.
        String_Copy(args->nameInputString, string);
        String_Delete(string);
        CopyStringToU16Array(args->nameInputString, args->unk1C, 10);
    } else if (data->type == NAME_SCREEN_RIVAL) {
        string = NewString_ReadMsgData(data->msgData_254, FIRST_DEFAULT_NAME_RIVAL);
        String_Copy(args->nameInputString, string);
        String_Delete(string);
        CopyStringToU16Array(args->nameInputString, args->unk1C, 10);
    } else {
        args->unk14 = 1;
    }
}

static BOOL sub_02082EC0(const u16 *s) {
    BOOL ret = TRUE;
    int i;

    for (i = 0;; ++i) {
        if (s[i] == EOS) {
            break;
        }
        if (s[i] != CHAR_SPACE) {
            ret = FALSE;
        }
    }
    return ret;
}

BOOL NamingScreenApp_Exit(OVY_MANAGER *ovyMan, int *pState) {
    NamingScreenAppData *data = OverlayManager_GetData(ovyMan);
    NamingScreenArgs *args    = OverlayManager_GetArgs(ovyMan);

    data->unk_0D8[data->unk_158] = EOS;
    if (data->type == NAME_SCREEN_POKEMON) {
        Pokemon *mon = AllocMonZeroed(HEAP_ID_NAMING_SCREEN);
        CreateMon(mon, data->unk_004, 5, 10, 10, 10, 10, 10);
        // wtf
        FreeToHeap(mon);
    }
    if (data->unk_158 == 0 || !StringNotEqual(data->unk_0D8, data->unk_118) || sub_02082EC0(data->unk_0D8)) {
        sub_02082E28(data, args);
    } else {
        CopyU16StringArray(data->unk_118, data->unk_0D8);
        CopyU16StringArray(args->unk1C, data->unk_0D8);
        CopyU16ArrayToString(args->nameInputString, data->unk_0D8);
    }
    String_Delete(data->unk_184);
    for (int i = 0; i < 7; ++i) {
        DestroySysTaskAndEnvironment(data->unk_39C[i]);
    }
    sub_0200AEB0(data->unk_2C4[PM_LCD_TOP][GF_GFX_RES_TYPE_CHAR]);
    sub_0200AEB0(data->unk_2C4[PM_LCD_BOTTOM][GF_GFX_RES_TYPE_CHAR]);
    sub_0200B0A8(data->unk_2C4[PM_LCD_TOP][GF_GFX_RES_TYPE_PLTT]);
    sub_0200B0A8(data->unk_2C4[PM_LCD_BOTTOM][GF_GFX_RES_TYPE_PLTT]);
    for (int i = 0; i < 4; ++i) {
        Destroy2DGfxResObjMan(data->unk_2B4[i]);
    }
    SpriteList_Delete(data->unk_188);
    OamManager_Free();
    FreeToHeapExplicit(HEAP_ID_NAMING_SCREEN, data->unk_4AC);
    if (data->type == NAME_SCREEN_POKEMON) {
        FreeToHeapExplicit(HEAP_ID_NAMING_SCREEN, data->unk_4B4);
        FreeToHeapExplicit(HEAP_ID_NAMING_SCREEN, data->unk_4BC);
    }
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_SUB_3);
    ObjCharTransfer_Destroy();
    ObjPlttTransfer_Destroy();
    sub_02083614(data->bgConfig, data->unk_3B8);
    FontID_SetAccessLazy(0);
    GX_SetVisibleWnd(GX_WNDMASK_NONE);
    FontID_Release(2);
    if (data->unk_180 != NULL) {
        String_Delete(data->unk_180);
    }
    String_Delete(data->unk_178);
    String_Delete(data->unk_17C);
    DestroyMsgData(data->msgData_197);
    DestroyMsgData(data->msgData_254);
    DestroyMsgData(data->msgData_249);
    MessageFormat_Delete(data->msgFormat);
    OverlayManager_FreeData(ovyMan);
    Main_SetVBlankIntrCB(NULL, NULL);
    DestroyHeap(HEAP_ID_NAMING_SCREEN);
    GfGfx_SetMainDisplay(PM_LCD_TOP);
    return TRUE;
}

// -------------------------------
// Public functions
// -------------------------------

NamingScreenArgs *NamingScreen_CreateArgs(HeapID heapId, NameScreenType kind, int param, int maxLen, Options *options, int *a5) {
    NamingScreenArgs *ret = AllocFromHeap(heapId, sizeof(NamingScreenArgs));
    ret->kind             = kind;
    ret->playerGender     = param;
    ret->maxLen           = maxLen;
    ret->unk14            = 0;
    ret->unk1C[0]         = EOS;
    ret->nameInputString  = String_New(32, heapId);
    ret->unk44            = 0;
    ret->unk48            = 0;
    ret->monGender        = 0;
    ret->options          = options;
    ret->monForm          = 0;
    ret->unk50            = a5;
    return ret;
}

void NamingScreen_DeleteArgs(NamingScreenArgs *namingScreenArgs) {
    GF_ASSERT(namingScreenArgs->nameInputString != NULL);
    GF_ASSERT(namingScreenArgs != NULL); // UB: should check this first
    String_Delete(namingScreenArgs->nameInputString);
    FreeToHeap(namingScreenArgs);
}

// -------------------------------
// Back to private scope
// -------------------------------

static void sub_02083140(void *param) {
    GF_RunVramTransferTasks();
    OamManager_ApplyAndResetBuffers();
    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void sub_02083160(NamingScreenAppData *data, NamingScreenArgs *args) {
    data->type    = args->kind;
    data->unk_004 = args->playerGender;
    data->unk_008 = args->monForm;
    data->maxLen  = args->maxLen;
    data->unk_010 = args->monGender;
    data->unk_018 = args->options;
    data->unk_5D0 = args->unk50;
}

static void sub_02083184(void) {
    static const GraphicsBanks _02102140 = {
        GX_VRAM_BG_128_A,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_128_B,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_NONE,
        GX_VRAM_TEXPLTT_NONE,
    };
    GraphicsBanks graphicsBanks = _02102140;
    GfGfx_SetBanks(&graphicsBanks);
}

static void sub_020831A4(BgConfig *bgConfig) {
    {
        static const GraphicsModes _02101D60 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D,
        };
        GraphicsModes graphicsModes = _02101D60;
        SetBothScreensModesAndDisable(&graphicsModes);
    }

    {
        static const BgTemplate _02101ED4 = {
            .x          = 0x00000000,
            .y          = 0x00000000,
            .bufferSize = GF_BG_BUF_SIZE_512x256_4BPP,
            .baseTile   = 0x00000000,
            .size       = GF_BG_SCR_SIZE_512x256,
            .colorMode  = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase   = GX_BG_CHARBASE_0x10000,
            .bgExtPltt  = GX_BG_EXTPLTT_01,
            .priority   = 1,
            .areaOver   = GX_BG_AREAOVER_XLU,
            .mosaic     = 0x00000000,
        };
        BgTemplate bgTemplate = _02101ED4;
        InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_0, &bgTemplate, GF_BG_TYPE_TEXT);
        BgClearTilemapBufferAndCommit(bgConfig, GF_BG_LYR_MAIN_0);
    }

    {
        static const BgTemplate _02101FB4 = {
            .x          = 0x00000000,
            .y          = 0x00000000,
            .bufferSize = GF_BG_BUF_SIZE_512x256_4BPP,
            .baseTile   = 0x00000000,
            .size       = GF_BG_SCR_SIZE_512x256,
            .colorMode  = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe000,
            .charBase   = GX_BG_CHARBASE_0x10000,
            .bgExtPltt  = GX_BG_EXTPLTT_01,
            .priority   = 2,
            .areaOver   = GX_BG_AREAOVER_XLU,
            .mosaic     = 0x00000000,
        };
        BgTemplate bgTemplate = _02101FB4;
        InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_1, &bgTemplate, GF_BG_TYPE_TEXT);
        BgClearTilemapBufferAndCommit(bgConfig, GF_BG_LYR_MAIN_1);
    }

    {
        static const BgTemplate _02102078 = {
            .x          = 0x00000000,
            .y          = 0x00000000,
            .bufferSize = GF_BG_BUF_SIZE_256x256_4BPP,
            .baseTile   = 0x00000000,
            .size       = GF_BG_SCR_SIZE_256x256,
            .colorMode  = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xd000,
            .charBase   = GX_BG_CHARBASE_0x00000,
            .bgExtPltt  = GX_BG_EXTPLTT_01,
            .priority   = 3,
            .areaOver   = GX_BG_AREAOVER_XLU,
            .mosaic     = 0x00000000,
        };
        BgTemplate bgTemplate = _02102078;
        InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_2, &bgTemplate, GF_BG_TYPE_TEXT);
        BgClearTilemapBufferAndCommit(bgConfig, GF_BG_LYR_MAIN_2);
    }

    {
        static const BgTemplate _02101E10 = {
            .x          = 0x00000000,
            .y          = 0x00000000,
            .bufferSize = GF_BG_BUF_SIZE_256x256_4BPP,
            .baseTile   = 0x00000000,
            .size       = GF_BG_SCR_SIZE_256x256,
            .colorMode  = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase   = GX_BG_CHARBASE_0x10000,
            .bgExtPltt  = GX_BG_EXTPLTT_01,
            .priority   = 0,
            .areaOver   = GX_BG_AREAOVER_XLU,
            .mosaic     = 0x00000000,
        };
        BgTemplate bgTemplate = _02101E10;
        InitBgFromTemplate(bgConfig, GF_BG_LYR_SUB_0, &bgTemplate, GF_BG_TYPE_TEXT);
        BgClearTilemapBufferAndCommit(bgConfig, GF_BG_LYR_SUB_0);
    }

    sub_020832E4(GF_PLANE_TOGGLE_OFF);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 0x20, 0, HEAP_ID_NAMING_SCREEN);
    BG_ClearCharDataRange(GF_BG_LYR_SUB_0, 0x20, 0, HEAP_ID_NAMING_SCREEN);
    GX_SetVisibleWnd(GX_WNDMASK_W0);
    G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_OBJ, 1);
    G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ,
        1);
    G2_SetWnd0Position(0, 0, 255, 64);
    G2S_BlendNone();
}

static void sub_020832E4(GFPlaneToggle enable) {
    GfGfx_EngineATogglePlanes(GX_PLANEMASK_BG0, enable);
    GfGfx_EngineATogglePlanes(GX_PLANEMASK_BG1, enable);
    GfGfx_EngineATogglePlanes(GX_PLANEMASK_BG2, enable);
    GfGfx_EngineATogglePlanes(GX_PLANEMASK_BG3, GF_PLANE_TOGGLE_OFF);
    GfGfx_EngineATogglePlanes(GX_PLANEMASK_OBJ, enable);
    GfGfx_EngineBTogglePlanes(GX_PLANEMASK_BG0, enable);
    GfGfx_EngineBTogglePlanes(GX_PLANEMASK_BG1, GF_PLANE_TOGGLE_OFF);
    GfGfx_EngineBTogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_OFF);
}

static void sub_02083334(NamingScreenAppData *data, OVY_MANAGER *ovyMan) {
    NamingScreenArgs *args = OverlayManager_GetArgs(ovyMan);

    data->unk_45C = 4;
    sub_0208423C(data->unk_468, GF_BG_LYR_MAIN_0);
    BgSetPosTextAndCommit(data->bgConfig, data->unk_464, BG_POS_OP_SET_X, data->unk_468[data->unk_464].x);
    BgSetPosTextAndCommit(data->bgConfig, data->unk_464, BG_POS_OP_SET_Y, data->unk_468[data->unk_464].y);
    BgSetPosTextAndCommit(data->bgConfig, data->unk_464 ^ 1, BG_POS_OP_SET_X, data->unk_468[data->unk_464 ^ 1].x);
    BgSetPosTextAndCommit(data->bgConfig, data->unk_464 ^ 1, BG_POS_OP_SET_Y, data->unk_468[data->unk_464 ^ 1].y);
    data->unk_118[0] = EOS;
    if (args->nameInputString != NULL) {
        CopyStringToU16Array(args->nameInputString, data->unk_118, 32);
    }
    MI_CpuFill16(data->unk_0D8, 1, sizeof(data->unk_0D8));
    if (data->type == NAME_SCREEN_POKEMON) {
        Pokemon *mon = AllocMonZeroed(HEAP_ID_NAMING_SCREEN);
        CreateMon(mon, data->unk_004, 5, 10, 10, 10, 10, 10);
        BufferBoxMonSpeciesName(data->msgFormat, 0, Mon_GetBoxMon(mon));
        FreeToHeap(mon);
    }
    if (args->unk44) {
        data->unk_014 = 1;
    }
    data->unk_178               = ReadMsgData_ExpandPlaceholders(data->msgFormat, data->msgData_249, _021020B4[data->type], HEAP_ID_NAMING_SCREEN);
    data->unk_17C               = ReadMsgData_ExpandPlaceholders(data->msgFormat, data->msgData_249, msg_0249_00009, HEAP_ID_NAMING_SCREEN);
    data->unk_184               = NewString_ReadMsgData(data->msgData_249, msg_0249_00007);
    data->unk_158               = StringLength(data->unk_118);
    data->cursorX               = 0;
    data->cursorY               = 1;
    data->unk_024               = -1;
    data->unk_028               = -1;
    data->unk_030               = 1;
    data->unk_034               = 0;
    data->unk_484               = -1;
    data->unk_488               = 0;
    data->unk_48C               = 0;
    data->unk_0D8[data->maxLen] = EOS;
    for (int i = 0; i < 7; ++i) {
        data->unk_490[i] = 0;
    }
    if (data->type == NAME_SCREEN_UNK4) {
        data->unk_490[3] = 1;
    } else {
        data->unk_490[0] = 1;
    }
}

static void sub_020834FC(NamingScreenAppData *data, OVY_MANAGER *ovyMan) {
    NamingScreenArgs *args = OverlayManager_GetArgs(ovyMan);
    if (args->unk44 != 0) {
        String *string    = String_New(200, HEAP_ID_NAMING_SCREEN);
        data->unk_180     = NULL;
        int boxno         = PCStorage_GetActiveBox(args->unk48);
        int nextOpenBoxNo = PCStorage_FindFirstBoxWithEmptySlot(args->unk48);
        BufferPCBoxName(data->msgFormat, 1, args->unk48, boxno);
        if (boxno != nextOpenBoxNo) {
            BufferPCBoxName(data->msgFormat, 2, args->unk48, nextOpenBoxNo);
            args->unk44 += 2;
        } else {
            BufferPCBoxName(data->msgFormat, 2, args->unk48, boxno);
        }
        if (data->unk_158 == 0 || sub_02082EC0(data->unk_0D8)) {
            Pokemon *mon = AllocMonZeroed(HEAP_ID_NAMING_SCREEN);
            CreateMon(mon, data->unk_004, 1, 0, 0, 0, 0, 0);
            BufferBoxMonSpeciesName(data->msgFormat, 0, Mon_GetBoxMon(mon));
            FreeToHeap(mon);
        } else {
            data->unk_0D8[data->unk_158] = EOS;
            CopyU16ArrayToString(string, data->unk_0D8);
            BufferString(data->msgFormat, 0, string, 0, 0, 0);
        }
        data->unk_180 = ReadMsgData_ExpandPlaceholders(data->msgFormat, data->msgData_197, args->unk44, HEAP_ID_NAMING_SCREEN);
        data->unk_014 = 1;
        String_Delete(string);
    }
}

static void sub_02083614(BgConfig *bgConfig, Window *a1) {
    for (int i = 0; i < 10; ++i) {
        RemoveWindow(&a1[i]);
    }
    FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_SUB_0);
    FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_MAIN_2);
    FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_MAIN_1);
    FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_MAIN_0);
    FreeToHeapExplicit(HEAP_ID_NAMING_SCREEN, bgConfig);
}

static void sub_02083654(NamingScreenAppData *data, NARC *narc) {
    BgConfig *bgConfig = data->bgConfig;

    GfGfxLoader_GXLoadPalFromOpenNarc(narc, 0, GF_PAL_LOCATION_MAIN_BG, (enum GFPalSlotOffset)0, 0x60, HEAP_ID_NAMING_SCREEN);
    GfGfxLoader_GXLoadPal(NARC_a_0_1_4, 71, GF_PAL_LOCATION_SUB_BG, (enum GFPalSlotOffset)0, 0x20, HEAP_ID_NAMING_SCREEN);
    BG_SetMaskColor(GF_BG_LYR_SUB_0, RGB_BLACK);

    GfGfxLoader_LoadCharDataFromOpenNarc(narc, 2, bgConfig, GF_BG_LYR_MAIN_2, 0, 0x2000, TRUE, HEAP_ID_NAMING_SCREEN);
    GfGfxLoader_LoadScrnDataFromOpenNarc(narc, 4, bgConfig, GF_BG_LYR_MAIN_2, 0, 0x600, TRUE, HEAP_ID_NAMING_SCREEN);

    GfGfxLoader_LoadCharDataFromOpenNarc(narc, 2, bgConfig, GF_BG_LYR_MAIN_1, 0, 0x2000, TRUE, HEAP_ID_NAMING_SCREEN);
    GfGfxLoader_LoadScrnDataFromOpenNarc(narc, 6, bgConfig, GF_BG_LYR_MAIN_1, 0, 0x380, TRUE, HEAP_ID_NAMING_SCREEN);

    GfGfxLoader_LoadScrnDataFromOpenNarc(narc, 7, bgConfig, GF_BG_LYR_MAIN_0, 0, 0x380, TRUE, HEAP_ID_NAMING_SCREEN);

    LoadFontPal1(GF_PAL_LOCATION_MAIN_BG, (enum GFPalSlotOffset)0x180, HEAP_ID_NAMING_SCREEN);
    LoadUserFrameGfx2(data->bgConfig, GF_BG_LYR_SUB_0, 0x100, 10, Options_GetFrame(data->unk_018), HEAP_ID_NAMING_SCREEN);
    LoadFontPal1(GF_PAL_LOCATION_SUB_BG, (enum GFPalSlotOffset)0x180, HEAP_ID_NAMING_SCREEN);

    data->unk_4AC = GfGfxLoader_GetCharDataFromOpenNarc(narc, 16, TRUE, &data->unk_4B0, HEAP_ID_NAMING_SCREEN);
}

static void sub_0208377C(void) {
    static const ObjCharTransferTemplate _02101D70 = {
        .maxTasks = 20,
        .sizeMain = 0x800,
        .sizeSub  = 0x800,
        .heapId   = HEAP_ID_NAMING_SCREEN,
    };
    ObjCharTransferTemplate tmplate = _02101D70;
    ObjCharTransfer_Init(&tmplate);
    ObjPlttTransfer_Init(20, HEAP_ID_NAMING_SCREEN);
    ObjCharTransfer_ClearBuffers();
    ObjPlttTransfer_Reset();
}

static void sub_020837AC(NamingScreenAppData *data, NARC *narc) {
    NNS_G2dInitOamManagerModule();
    GX_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);
    GXS_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);
    OamManager_Create(0, 128, 0, 32, 0, 128, 0, 32, HEAP_ID_NAMING_SCREEN);
    data->unk_188 = G2dRenderer_Init(44, &data->unk_18C, HEAP_ID_NAMING_SCREEN);
    G2dRenderer_SetSubSurfaceCoords(&data->unk_18C, 0, FX32_CONST(256));

    for (int i = 0; i < 4; ++i) {
        data->unk_2B4[i] = Create2DGfxResObjMan(2, (GfGfxResType)i, HEAP_ID_NAMING_SCREEN);
    }

    data->unk_2C4[PM_LCD_TOP][GF_GFX_RES_TYPE_CHAR] = AddCharResObjFromOpenNarc(data->unk_2B4[GF_GFX_RES_TYPE_CHAR], narc, 10, TRUE, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAP_ID_NAMING_SCREEN);
    data->unk_2C4[PM_LCD_TOP][GF_GFX_RES_TYPE_PLTT] = AddPlttResObjFromOpenNarc(data->unk_2B4[GF_GFX_RES_TYPE_PLTT], narc, 1, FALSE, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 9, HEAP_ID_NAMING_SCREEN);
    data->unk_2C4[PM_LCD_TOP][GF_GFX_RES_TYPE_CELL] = AddCellOrAnimResObjFromOpenNarc(data->unk_2B4[GF_GFX_RES_TYPE_CELL], narc, 12, TRUE, 0, GF_GFX_RES_TYPE_CELL, HEAP_ID_NAMING_SCREEN);
    data->unk_2C4[PM_LCD_TOP][GF_GFX_RES_TYPE_ANIM] = AddCellOrAnimResObjFromOpenNarc(data->unk_2B4[GF_GFX_RES_TYPE_ANIM], narc, 14, TRUE, 0, GF_GFX_RES_TYPE_ANIM, HEAP_ID_NAMING_SCREEN);
    if (data->type == NAME_SCREEN_POKEMON) {
        data->unk_4B4 = GfGfxLoader_GetCharData(NARC_poketool_icongra_poke_icon, GetMonIconNaixEx(data->unk_004, FALSE, data->unk_008), FALSE, &data->unk_4B8, HEAP_ID_NAMING_SCREEN);
        DC_FlushRange(data->unk_4B8, 0x200);
        data->unk_4BC = GfGfxLoader_GetPlttData(NARC_poketool_icongra_poke_icon, sub_02074490(), &data->unk_4C0, HEAP_ID_NAMING_SCREEN);
        DC_FlushRange(data->unk_4C0, 0x80);
    }

    data->unk_2C4[PM_LCD_BOTTOM][GF_GFX_RES_TYPE_CHAR] = AddCharResObjFromOpenNarc(data->unk_2B4[GF_GFX_RES_TYPE_CHAR], narc, 11, TRUE, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAP_ID_NAMING_SCREEN);
    data->unk_2C4[PM_LCD_BOTTOM][GF_GFX_RES_TYPE_PLTT] = AddPlttResObjFromOpenNarc(data->unk_2B4[GF_GFX_RES_TYPE_PLTT], narc, 1, FALSE, 1, NNS_G2D_VRAM_TYPE_2DSUB, 3, HEAP_ID_NAMING_SCREEN);
    data->unk_2C4[PM_LCD_BOTTOM][GF_GFX_RES_TYPE_CELL] = AddCellOrAnimResObjFromOpenNarc(data->unk_2B4[GF_GFX_RES_TYPE_CELL], narc, 13, TRUE, 1, GF_GFX_RES_TYPE_CELL, HEAP_ID_NAMING_SCREEN);
    data->unk_2C4[PM_LCD_BOTTOM][GF_GFX_RES_TYPE_ANIM] = AddCellOrAnimResObjFromOpenNarc(data->unk_2B4[GF_GFX_RES_TYPE_ANIM], narc, 15, TRUE, 1, GF_GFX_RES_TYPE_ANIM, HEAP_ID_NAMING_SCREEN);

    sub_0200ACF0(data->unk_2C4[PM_LCD_TOP][GF_GFX_RES_TYPE_CHAR]);
    sub_0200ACF0(data->unk_2C4[PM_LCD_BOTTOM][GF_GFX_RES_TYPE_CHAR]);
    sub_0200AF94(data->unk_2C4[PM_LCD_TOP][GF_GFX_RES_TYPE_PLTT]);
    sub_0200AF94(data->unk_2C4[PM_LCD_BOTTOM][GF_GFX_RES_TYPE_PLTT]);
}

typedef struct SysTaskData_020839B8 {
    Sprite *sprite;
    Sprite *sprite2;
    fx32 dx;
    int i;
} SysTaskData_020839B8;

static void sub_020839B8(SysTask *task, void *taskData) {
    SysTaskData_020839B8 *data = taskData;
    VecFx32 *pMatrix           = Sprite_GetMatrixPtr(data->sprite);
    VecFx32 matrix;
    matrix.x = pMatrix->x + data->dx;
    matrix.y = FX32_ONE * _021021E8[data->i][1];
    matrix.z = 0;
    Sprite_SetMatrix(data->sprite2, &matrix);
}

static void sub_020839EC(NamingScreenAppData *data) {
    int i;
    CreateSpriteResourcesHeader(&data->unk_2E4, 0, 0, 0, 0, -1, -1, 0, 1, data->unk_2B4[GF_GFX_RES_TYPE_CHAR], data->unk_2B4[GF_GFX_RES_TYPE_PLTT], data->unk_2B4[GF_GFX_RES_TYPE_CELL], data->unk_2B4[GF_GFX_RES_TYPE_ANIM], NULL, NULL);
    CreateSpriteResourcesHeader(&data->unk_308, 1, 1, 1, 1, -1, -1, 0, 0, data->unk_2B4[GF_GFX_RES_TYPE_CHAR], data->unk_2B4[GF_GFX_RES_TYPE_PLTT], data->unk_2B4[GF_GFX_RES_TYPE_CELL], data->unk_2B4[GF_GFX_RES_TYPE_ANIM], NULL, NULL);
    {
        SpriteTemplate spriteTemplate;
        spriteTemplate.spriteList  = data->unk_188;
        spriteTemplate.header      = &data->unk_2E4;
        spriteTemplate.position.x  = FX32_CONST(32);
        spriteTemplate.position.y  = FX32_CONST(96);
        spriteTemplate.position.z  = 0;
        spriteTemplate.scale.x     = FX32_ONE;
        spriteTemplate.scale.y     = FX32_ONE;
        spriteTemplate.scale.z     = FX32_ONE;
        spriteTemplate.rotation    = 0;
        spriteTemplate.priority    = 1;
        spriteTemplate.whichScreen = NNS_G2D_VRAM_TYPE_2DMAIN;
        spriteTemplate.heapId      = HEAP_ID_NAMING_SCREEN;

        for (i = 0; i < 9; ++i) {
            spriteTemplate.position.x = _021021E8[i][0] * FX32_ONE;
            spriteTemplate.position.y = _021021E8[i][1] * FX32_ONE;
            data->unk_32C[i]          = Sprite_CreateAffine(&spriteTemplate);
            Sprite_SetAnimActiveFlag(data->unk_32C[i], TRUE);
            Sprite_SetAnimCtrlSeq(data->unk_32C[i], _021021E8[i][2]);
            Sprite_SetDrawPriority(data->unk_32C[i], _021021E8[i][3]);
        }
        Sprite_SetVisibleFlag(data->unk_32C[4], FALSE);
        for (i = 0; i < 7; ++i) {
            data->unk_39C[i]               = CreateSysTaskAndEnvironment(sub_020839B8, sizeof(SysTaskData_020839B8), 5, HEAP_ID_NAMING_SCREEN);
            SysTaskData_020839B8 *taskData = SysTask_GetData(data->unk_39C[i]);
            taskData->sprite               = data->unk_32C[7];
            taskData->sprite2              = data->unk_32C[i];
            taskData->dx                   = _021021E8[i][0] * FX32_ONE;
            taskData->i                    = i;
        }
        // regswap: data->maxLen should be r2, instead r0
        for (i = 0; i < data->maxLen; ++i) {
            spriteTemplate.position.x = FX32_ONE * (80 + i * 12);
            spriteTemplate.position.y = FX32_ONE * 39;
            data->unk_364[i]          = Sprite_CreateAffine(&spriteTemplate);
            Sprite_SetAnimActiveFlag(data->unk_364[i], TRUE);
            Sprite_SetAnimCtrlSeq(data->unk_364[i], 43);
        }
        sub_02084E18(data->unk_364, data->unk_158, data->maxLen);
        sub_02083BB4(data, &spriteTemplate);
    }
    GfGfx_EngineATogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_ON);
    GfGfx_EngineBTogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_ON);
}

static void sub_02083BB4(NamingScreenAppData *data, SpriteTemplate *tmplate) {
    tmplate->position.x = FX32_CONST(24);
    tmplate->position.y = FX32_CONST(8);
    data->unk_394[0]    = Sprite_CreateAffine(tmplate);
    Sprite_SetAnimActiveFlag(data->unk_394[0], TRUE);

    switch (data->type) {
    case NAME_SCREEN_PLAYER:
        if (data->unk_004 == PLAYER_GENDER_MALE) {
            Sprite_SetAnimCtrlSeq(data->unk_394[0], 48);
        } else {
            Sprite_SetAnimCtrlSeq(data->unk_394[0], 49);
        }
        break;
    case NAME_SCREEN_RIVAL:
        Sprite_SetAnimCtrlSeq(data->unk_394[0], 51);
        break;
    case NAME_SCREEN_UNK6:
        Sprite_SetAnimCtrlSeq(data->unk_394[0], 55);
        break;
    case NAME_SCREEN_GROUP:
        Sprite_SetAnimCtrlSeq(data->unk_394[0], 54);
        break;
    case NAME_SCREEN_UNK4:
    case NAME_SCREEN_UNK7:
        Sprite_SetAnimCtrlSeq(data->unk_394[0], 53);
        break;
    case NAME_SCREEN_BOX:
        Sprite_SetAnimCtrlSeq(data->unk_394[0], 47);
        break;
    case NAME_SCREEN_POKEMON:
        Sprite_SetAnimCtrlSeq(data->unk_394[0], 50);
        if (data->unk_010 != 2) {
            tmplate->position.x = (13 * data->maxLen + 80) * FX32_ONE;
            tmplate->position.y = FX32_CONST(27);
            data->unk_394[1]    = Sprite_CreateAffine(tmplate);
            if (data->unk_010 == 0) {
                Sprite_SetAnimCtrlSeq(data->unk_394[1], 45);
            } else {
                Sprite_SetAnimCtrlSeq(data->unk_394[1], 46);
            }
        }
        break;
    }
}

typedef struct SysTaskData_02083CAC {
    Sprite *sprite;
    int state;
    fx32 x;
    int y;
} SysTaskData_02083CAC;

static void sub_02083CAC(SysTask *task, void *taskData) {
    SysTaskData_02083CAC *data = taskData;

    VecFx32 matrix;

    matrix.y = data->y;
    matrix.z = 0;
    switch (data->state) {
    case 0:
        matrix.x = data->x + FX32_CONST(4);
        Sprite_SetMatrix(data->sprite, &matrix);
        break;
    case 2:
        matrix.x = data->x - FX32_CONST(3);
        Sprite_SetMatrix(data->sprite, &matrix);
        break;
    case 4:
        matrix.x = data->x + FX32_CONST(2);
        Sprite_SetMatrix(data->sprite, &matrix);
        break;
    case 6:
        matrix.x = data->x;
        Sprite_SetMatrix(data->sprite, &matrix);
        DestroySysTaskAndEnvironment(task); // invalidates data
        break;
    }
    ++data->state; // UB: potential use after free
}

static void sub_02083D34(BgConfig *bgConfig, Window *windows, int *pState, int pageNum, GFBgLayer *pBgId, VecFx32 *posVecs, Sprite **pSprites, void *pRawData) {
    GFBgLayer bgId_prev = *pBgId;
    GFBgLayer bgId_curr = (GFBgLayer)(bgId_prev ^ 1);

    switch (*pState) {
    case 0: {
        u16 fillVal = _02101D40[pageNum] | (_02101D40[pageNum] << 4);
        GfGfxLoader_LoadScrnData(NARC_a_0_3_1, pageNum + 6, bgConfig, bgId_prev, 0, 0x380, TRUE, HEAP_ID_NAMING_SCREEN);
        sub_0208423C(posVecs, bgId_prev);
        sub_02084E54(&windows[bgId_prev], fillVal, pageNum, MAKE_TEXT_COLOR(14, 15, 0), pRawData);
        ++(*pState);
        break;
    }
    case 1:
        BgSetPosTextAndCommit(bgConfig, bgId_prev, BG_POS_OP_SET_X, 238);
        BgSetPosTextAndCommit(bgConfig, bgId_prev, BG_POS_OP_SET_Y, -80);
        ++*(pState);
        break;
    case 2:
        posVecs[bgId_prev].x -= 24;
        if (posVecs[bgId_prev].x < -1) {
            SysTaskData_02083CAC *data;
            SysTask *task;

            task                 = CreateSysTaskAndEnvironment(sub_02083CAC, sizeof(SysTaskData_02083CAC), 0, HEAP_ID_NAMING_SCREEN);
            data                 = SysTask_GetData(task);
            data->sprite         = pSprites[7];
            data->state          = 0;
            data->x              = Sprite_GetMatrixPtr(pSprites[7])->x;
            data->y              = Sprite_GetMatrixPtr(pSprites[7])->y;
            posVecs[bgId_prev].x = -11;
            ++(*pState);
        }
        posVecs[bgId_curr].y -= 10;
        if (posVecs[bgId_curr].y < -196) {
            posVecs[bgId_curr].y = -196;
        }
        BgSetPosTextAndCommit(bgConfig, bgId_prev, BG_POS_OP_SET_X, posVecs[bgId_prev].x);
        BgSetPosTextAndCommit(bgConfig, bgId_curr, BG_POS_OP_SET_Y, posVecs[bgId_curr].y);
        break;
    case 3:
        posVecs[bgId_curr].y -= 10;
        if (posVecs[bgId_curr].y < -196) {
            posVecs[bgId_curr].y = -196;
        }
        BgSetPosTextAndCommit(bgConfig, bgId_prev, BG_POS_OP_SET_X, posVecs[bgId_prev].x);
        BgSetPosTextAndCommit(bgConfig, bgId_curr, BG_POS_OP_SET_Y, posVecs[bgId_curr].y);
        if (posVecs[bgId_prev].x == -11 && posVecs[bgId_curr].y == -196) {
            ++(*pState);
            (*pBgId) ^= 1;
            sub_0208421C(bgConfig, *pBgId, posVecs);
            PlaySE(SEQ_SE_DP_NAMEIN_01);
        }
        break;
    case 4:
        break;
    }
}

static void sub_02083F18(Window *window, NameScreenType unused, String *msg) {
    DrawFrameAndWindow2(window, FALSE, 0x100, 10);
    AddTextPrinterParameterized(window, 1, msg, 0, 0, TEXT_SPEED_INSTANT, NULL);
    CopyWindowToVram(window);
}

static void sub_02083F48(Window *window, NameScreenType unused, String *msg) {
    int x           = 16;
    int width       = FontID_String_GetWidth(0, msg, 0);
    int windowWidth = GetWindowWidth(window) * 8;
    if (width + 16 > windowWidth) {
        x = windowWidth - width;
    }
    FillWindowPixelBuffer(window, 1);
    AddTextPrinterParameterizedWithColor(window, 0, msg, x, 0, TEXT_SPEED_INSTANT, MAKE_TEXT_COLOR(14, 15, 1), NULL);
    CopyWindowToVram(window);
}

static void sub_02083F9C(NamingScreenAppData *data, OVY_MANAGER *ovyMan, NARC *narc) {
    AddWindowParameterized(data->bgConfig, &data->unk_3B8[0], GF_BG_LYR_MAIN_0, 2, 1, 26, 12, 1, 0x100);
    AddWindowParameterized(data->bgConfig, &data->unk_3B8[1], GF_BG_LYR_MAIN_1, 2, 1, 26, 12, 1, 0x238);

    if (data->type == NAME_SCREEN_UNK4) {
        GfGfxLoader_LoadScrnDataFromOpenNarc(narc, 9, data->bgConfig, GF_BG_LYR_MAIN_1, 0, 0x380, TRUE, HEAP_ID_NAMING_SCREEN);
        data->unk_460 = 4;
        sub_02084830(data->unk_03A, 4);
        sub_02084E54(&data->unk_3B8[1], 0x0A0A, 4, MAKE_TEXT_COLOR(14, 15, 0), data->unk_4B0->pRawData);
    } else {
        data->unk_460 = 0;
        sub_02084830(data->unk_03A, 0);
        sub_02084E54(&data->unk_3B8[1], 0x0404, 0, MAKE_TEXT_COLOR(14, 15, 0), data->unk_4B0->pRawData);
    }

    AddWindowParameterized(data->bgConfig, &data->unk_3B8[2], GF_BG_LYR_MAIN_2, 7, 2, 22, 2, 0, 0x370);

    int win3Width = (data->maxLen * 12) / 8 + 1;
    AddWindowParameterized(data->bgConfig, &data->unk_3B8[3], GF_BG_LYR_MAIN_2, 10, 3, win3Width, 2, 0, 0x39C);
    FillWindowPixelBuffer(&data->unk_3B8[3], 1);

    AddWindowParameterized(data->bgConfig, &data->unk_3B8[8], GF_BG_LYR_MAIN_2, win3Width + 9, 3, 7, 2, 0, 0x3C0);
    FillWindowPixelBuffer(&data->unk_3B8[8], 1);

    if (data->type == NAME_SCREEN_GROUP) {
        sub_02083F48(&data->unk_3B8[8], data->type, data->unk_184);
        CopyWindowToVram(&data->unk_3B8[8]);
    }

    AddWindowParameterized(data->bgConfig, &data->unk_3B8[9], GF_BG_LYR_SUB_0, 2, 19, 27, 4, 12, 0x084);
    FillWindowPixelBuffer(&data->unk_3B8[9], 15);
    sub_02083F18(&data->unk_3B8[9], data->type, data->unk_178);

    OverlayManager_GetArgs(ovyMan);

    if (data->unk_118[0] != EOS) {
        CopyU16StringArray(data->unk_0D8, data->unk_118);
        sub_02084540(&data->unk_3B8[3], data->unk_0D8, 0, 0, 12, TEXT_SPEED_INSTANT, MAKE_TEXT_COLOR(14, 15, 1), NULL);
    }

    for (int i = 0; i < 3; ++i) {
        AddWindowParameterized(data->bgConfig, &data->unk_3B8[i + 4], GF_BG_LYR_MAIN_2, 0, 0, 2, 2, 0, 0x078);
        FillWindowPixelBuffer(&data->unk_3B8[i + 4], 0);
    }

    AddWindowParameterized(data->bgConfig, &data->unk_3B8[7], GF_BG_LYR_MAIN_2, 0, 0, 16, 2, 0, 0x084);
    FillWindowPixelBuffer(&data->unk_3B8[7], 0);
}

static void sub_0208421C(BgConfig *bgConfig, GFBgLayer bgId, VecFx32 *pos) {
    SetBgPriority(bgId, 1);
    SetBgPriority(bgId ^ 1, 2);
}

static void sub_0208423C(VecFx32 *posVecs, GFBgLayer bgId) {
    posVecs[bgId].x     = 238;
    posVecs[bgId].y     = -80;
    posVecs[bgId ^ 1].x = -11;
    posVecs[bgId ^ 1].y = -80;
}

static const int _02102168[][2] = {
    { 0,  0  },
    { 0,  -1 },
    { 0,  1  },
    { -1, 0  },
    { 1,  0  },
};

static int sub_02084264(int val, int lo, int hi) {
    if (val >= hi) {
        val = lo;
    }
    if (val < lo) {
        val = hi - 1;
    }
    return val;
}

static void sub_02084274(NamingScreenAppData *data, int a1) {
    if (a1 == 0) {
        return;
    }

    u16 sp0  = data->unk_03A[data->cursorY][data->cursorX];
    int newX = sub_02084264(data->cursorX + _02102168[a1][0], 0, 13);
    int newY = sub_02084264(data->cursorY + _02102168[a1][1], 0, 6);
    while (data->unk_03A[newY][newX] == 0xD004 || (data->unk_03A[newY][newX] == sp0 && data->unk_03A[newY][newX] > 0xE001)) {
        if (data->unk_028 == 0 && data->unk_03A[newY][newX] == 0xD004 && _02102168[a1][1] != 0) {
            newX = sub_02084264(newX + data->unk_02C, 0, 13);
        } else {
            newX = sub_02084264(newX + _02102168[a1][0], 0, 13);
            newY = sub_02084264(newY + _02102168[a1][1], 0, 6);
        }
    }
    data->cursorX = newX;
    data->cursorY = newY;
}

static void sub_0208432C(NamingScreenAppData *data) {
    int r4  = 0;
    int r6  = 0;
    BOOL r7 = FALSE;
    if (!Sprite_GetVisibleFlag(data->unk_32C[8])) {
        r7 = TRUE;
    }

    if (gSystem.newAndRepeatedKeys & PAD_KEY_UP) {
        PlaySE(SEQ_SE_DP_SELECT);
        Sprite_SetVisibleFlag(data->unk_32C[8], TRUE);
        r6 = 1;
        ++r4;
    }
    if (gSystem.newAndRepeatedKeys & PAD_KEY_DOWN) {
        PlaySE(SEQ_SE_DP_SELECT);
        Sprite_SetVisibleFlag(data->unk_32C[8], TRUE);
        r6 = 2;
        ++r4;
    }
    if (gSystem.newAndRepeatedKeys & PAD_KEY_LEFT) {
        PlaySE(SEQ_SE_DP_SELECT);
        Sprite_SetVisibleFlag(data->unk_32C[8], TRUE);
        r6 = 3;
        ++r4;
    }
    if (gSystem.newAndRepeatedKeys & PAD_KEY_RIGHT) {
        PlaySE(SEQ_SE_DP_SELECT);
        Sprite_SetVisibleFlag(data->unk_32C[8], TRUE);
        r6 = 4;
        ++r4;
    }
    if (gSystem.newKeys & PAD_BUTTON_START) {
        PlaySE(SEQ_SE_DP_SELECT);
        Sprite_SetVisibleFlag(data->unk_32C[8], TRUE);
        data->cursorX = 12;
        data->cursorY = 0;
        ++r4;
    }
    data->unk_5C8 = sub_0208503C(data);
    if (data->unk_5C8 == TRUE) {
        r6 = 0;
        ++r4;
    }
    if (r7 == TRUE) {
        r4 = 0;
        sub_02084430(data, r6);
    }
    if (r4) {
        sub_02084274(data, r6);
        sub_02084430(data, r6);
    }
}

static void sub_02084430(NamingScreenAppData *data, int a1) {
    if (data->cursorY != 0) {
        if (data->unk_028 == 0 && data->unk_028 != data->cursorY) {
            Sprite_SetAnimCtrlSeq(data->unk_32C[8], 39);
        }
        if (a1 != 0) {
            Sprite_SetAnimCtrlSeq(data->unk_32C[8], 39);
        }

        VecFx32 vec;
        vec.x = (data->cursorX * 16 + 26) * FX32_ONE;
        vec.y = ((data->cursorY - 1) * 19 + 91) * FX32_ONE;
        // vec.z = 0;
        Sprite_SetMatrix(data->unk_32C[8], &vec);
    } else {
        int buttonId = data->unk_03A[data->cursorY][data->cursorX] - 0xE002;
        VecFx32 vec;

        vec.x = _02101D80[buttonId] * FX32_ONE;
        vec.y = FX32_CONST(68);
        // vec.z = 0;
        Sprite_SetAnimCtrlSeq(data->unk_32C[8], _02101D4C[buttonId]);
        Sprite_SetMatrix(data->unk_32C[8], &vec);
    }

    data->unk_038 = 180;
    Sprite_SetAnimCtrlCurrentFrame(data->unk_32C[8], 0);
    data->unk_024 = data->cursorX;
    data->unk_028 = data->cursorY;
    if (_02102168[a1][0] != 0) {
        data->unk_02C = _02102168[a1][0];
    }
}

static void sub_02084500(u16 *a0) {
    *a0 += 20;
    if (*a0 > 360) {
        *a0 = 0;
    }
    int val = ((GF_SinDeg(*a0) * 10) / FX32_ONE) + 15;
    u16 col = RGB(29, val, 0);
    GX_LoadOBJPltt(&col, 0x3A, sizeof(col));
}

static void sub_02084540(Window *window, const u16 *rawChars, int x, int y, int spacing, int textSpeed, u32 color, u8 *buttonPixels) {
    int i = 0;
    int width;
    int centerX;
    u16 sp38[2];
    String *string = String_New(2, HEAP_ID_NAMING_SCREEN);
    while (rawChars[i] != EOS) {
        if (rawChars[i] == 0xD001 || rawChars[i] == 0xD002 || rawChars[i] == 0xD003) {
            u16 buttonId = rawChars[i] - 0xD001;
            BlitBitmapRectToWindow(window, buttonPixels + (buttonId * 256) / 2, 0, 0, 12, 12, x + i * spacing, y + 2, 12, 12);
        } else if (rawChars[i] == 0xD004) {
            ++i;
            continue;
        } else {
            sp38[0] = rawChars[i];
            sp38[1] = EOS;
            width   = FontID_FlatArray_GetWidth(0, sp38, 0);
            CopyU16ArrayToString(string, sp38);
            centerX = x + i * spacing + ((spacing - width) / 2);
            AddTextPrinterParameterizedWithColor(window, 0, string, centerX, y, textSpeed, color, NULL);
        }
        ++i;
    }
    String_Delete(string);
}

static const u8 _02101D3C[] = { 0x60, 0x68, 0x50, 0x58 };

static void *sub_02084640(Window *window, String *string, FontID fontId, u32 color) {
    AddTextPrinterParameterizedWithColor(window, fontId, string, 0, 0, TEXT_SPEED_NOTRANSFER, color, NULL);
    return window->pixelBuffer;
}

static void sub_02084664(Window *windows, const u16 *a1, void *a2, String *a3) {
    u16 spC[21];
    u16 i;
    void *ptr;
    String *string;

    FillWindowPixelBuffer(&windows[3], 0);
    ptr = sub_02084640(&windows[3], a3, 2, MAKE_TEXT_COLOR(13, 14, 15));
    DC_FlushRange(ptr, 0x800);

    for (i = 0; i < 4; ++i) {
        sub_02013A50(&windows[3], 4, 2, i * 4, 0, a2);
        DC_FlushRange(a2, 0x100);
        GXS_LoadOBJ(a2, _02101D3C[i] * 32, 0x100);
    }

    string = String_New(21, HEAP_ID_NAMING_SCREEN);
    for (i = 0; i < 3; ++i) {
        spC[0] = a1[i];
        spC[1] = EOS;

        FillWindowPixelBuffer(&windows[i], 0);
        CopyU16ArrayToString(string, spC);
        ptr = sub_02084640(&windows[i], string, 2, MAKE_TEXT_COLOR(13, 14, 15));
        DC_FlushRange(ptr, 0x80);
        GXS_LoadOBJ(ptr, _02101D54[i] * 32, 0x80);
    }

    String_Delete(string);
}

static void sub_02084740(Window *a0, u16 *a1, u16 a2, u16 *a3, void *a4, String *a5) {
    int i;
    int j;
    u16 character;

    if (a2 == 0) {
        character = 0xD003;
    } else {
        character = a1[a2 - 1];
    }

    switch (character) {
    case 0xD001:
    case 0xD002:
    case 0xD003:
    case 0xD004:
    case 0xE002:
    case 0xE003:
    case 0xE004:
    case 0xE005:
    case 0xE006:
    case 0xE007:
    case 0xE008:
        character = 1;
        break;
    }

    for (i = 0; i < 3; ++i) {
        a3[i] = 1;
    }

    a3[0] = character;
    if (character != 1) {
        for (i = 0; i < 82u; ++i) {
            if (character == _02102422[i][0]) {
                for (j = 0; j < 3; ++j) {
                    a3[j] = _02102422[i][j];
                }
                break;
            }
            if (character == _02102422[i][2]) {
                for (j = 0; j < 3; ++j) {
                    a3[j] = _02102422[i][j];
                }
                break;
            }
        }
    }

    sub_02084664(a0, a3, a4, a5);
}

#ifdef NONMATCHING
static void sub_02084830(u16 (*a0)[13], const int a1) {
    int i;
    int j;

    for (i = 0; i < 13; ++i) {
        a0[0][i] = _021104E4[a1][i];
    }
    for (j = 0; j < 5; ++j) {
        for (i = 0; i < 13; ++i) {
            a0[j + 1][i] = _021104F8[a1][j][i];
        }
    }
}
#else
// clang-format off
static asm void sub_02084830(u16 (*a0)[13], const int a1) {
	push {r4, r5, r6, r7}
	mov r4, #0
	ldr r3, =_021104E4
	add r5, r4, #0
	add r6, r0, #0
	lsl r2, r1, #2
_0208483C:
	ldr r7, [r3, r2]
	add r4, r4, #1
	ldrh r7, [r7, r5]
	add r5, r5, #2
	strh r7, [r6, #0]
	add r6, r6, #2
	cmp r4, #0xd
	blt _0208483C
	mov r3, #0x14
	ldr r4, =_021104F8
	mul r3, r1
	mov r2, #0
	add r3, r4, r3
	add r1, r2, #0
_02084858:
	add r6, r1, #0
	add r4, r1, #0
	add r5, r0, #0
_0208485E:
	ldr r7, [r3, #0]
	add r6, r6, #1
	ldrh r7, [r7, r4]
	add r4, r4, #2
	strh r7, [r5, #0x1a]
	add r5, r5, #2
	cmp r6, #0xd
	blt _0208485E
	add r2, r2, #1
	add r3, r3, #4
	add r0, #0x1a
	cmp r2, #5
	blt _02084858
	pop {r4, r5, r6, r7}
	bx lr
}
// clang-format on
#endif // NONMATCHING

static int sub_02084884(NamingScreenAppData *data, u16 key, BOOL a2) {
    if (key == 0xD003 || key == 0xD004) {
        key = 1;
    }
    if (data->type == NAME_SCREEN_UNK4) {
        if (key == 0xE002 || key == 0xE003 || key == 0xE004 || key == 0xE005) {
            key = 1;
        }
    }
    if (!Sprite_GetVisibleFlag(data->unk_32C[8]) && gSystem.touchNew == 0) {
        Sprite_SetVisibleFlag(data->unk_32C[8], TRUE);
        return 2;
    }

    switch (key) {
    case 0xD001:
        if (sub_02084D04(0x2A, 0x52, 1, 0xD001, data->unk_0D8, data->unk_158)) {
            FillWindowPixelBuffer(&data->unk_3B8[3], 1);
            sub_02084540(&data->unk_3B8[3], data->unk_0D8, 0, 0, 12, TEXT_SPEED_INSTANT, MAKE_TEXT_COLOR(14, 15, 1), NULL);
            PlaySE(SEQ_SE_DP_BOX02);
        }
        break;
    case 0xD002:
        if (sub_02084D04(0x48, 0x52, 2, 0xD002, data->unk_0D8, data->unk_158)) {
            FillWindowPixelBuffer(&data->unk_3B8[3], 1);
            sub_02084540(&data->unk_3B8[3], data->unk_0D8, 0, 0, 12, TEXT_SPEED_INSTANT, MAKE_TEXT_COLOR(14, 15, 1), NULL);
            PlaySE(SEQ_SE_DP_BOX02);
        }
        break;
    case 0xE006:
        if (sub_02084C98(0, 0x52, data->unk_0D8, data->unk_158)) {
            FillWindowPixelBuffer(&data->unk_3B8[3], 1);
            sub_02084540(&data->unk_3B8[3], data->unk_0D8, 0, 0, 12, TEXT_SPEED_INSTANT, MAKE_TEXT_COLOR(14, 15, 1), NULL);
            ++data->unk_490[4];
            PlaySE(SEQ_SE_DP_BOX02);
        }
        break;
    case 0xE002:
    case 0xE003:
    case 0xE004:
    case 0xE005:
        if (data->unk_460 != key - 0xE002) {
            data->unk_45C = 0;
            data->unk_460 = key - 0xE002;
            sub_02084830(data->unk_03A, data->unk_460);
            ++data->unk_490[key - 0xE002];
            PlaySE(SEQ_SE_DP_SYU03);
        }
        break;
    case 0xE007:
        if (data->unk_158 != 0) {
            data->unk_0D8[data->unk_158 - 1] = EOS;
            --data->unk_158;
            FillWindowPixelBuffer(&data->unk_3B8[3], 1);
            if (data->unk_158 == 0) {
                CopyWindowToVram(&data->unk_3B8[3]);
            } else {
                sub_02084540(&data->unk_3B8[3], data->unk_0D8, 0, 0, 12, TEXT_SPEED_INSTANT, MAKE_TEXT_COLOR(14, 15, 1), NULL);
            }
            sub_02084740(&data->unk_3B8[4], data->unk_0D8, data->unk_158, data->unk_15A, data->unk_4C4, data->unk_17C);
            sub_02084E18(data->unk_364, data->unk_158, data->maxLen);
            ++data->unk_490[5];
            PlaySE(SEQ_SE_DP_SELECT);
        }
        break;
    case 0xE008:
        sub_020164C4(data->unk_5C4);
        if (data->unk_014 == 0) {
            PlaySE(SEQ_SE_DP_PIRORIRO);
            ++data->unk_490[6];
            BeginNormalPaletteFade(2, 0, 0, RGB_BLACK, 16, 1, HEAP_ID_NAMING_SCREEN);
            sub_02084C58(data, a2);
            return 3;
        } else {
            data->unk_45C = 5;
        }
        break;
    default:
        if (data->unk_460 == 4 && key == 1) {
            return 2;
        }
        if (data->unk_158 != data->maxLen) {
            data->unk_0D8[data->unk_158] = key;
            FillWindowPixelBuffer(&data->unk_3B8[3], 1);
            sub_02084540(&data->unk_3B8[3], data->unk_0D8, 0, 0, 12, TEXT_SPEED_INSTANT, MAKE_TEXT_COLOR(14, 15, 1), NULL);
            ++data->unk_158;
            sub_02084E18(data->unk_364, data->unk_158, data->maxLen);
            PlaySE(SEQ_SE_DP_BOX02);
            Sprite_SetVisibleFlag(data->unk_32C[8], TRUE);
            Sprite_SetOamMode(data->unk_32C[8], GX_OAM_MODE_XLU);
            G2_SetBlendAlpha(0, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2, 8, 8);
            Sprite_SetAnimCtrlSeq(data->unk_32C[8], 60);
            if (data->unk_158 == data->maxLen) {
                data->unk_034 = 1;
            }
            sub_02084740(&data->unk_3B8[4], data->unk_0D8, data->unk_158, data->unk_15A, data->unk_4C4, data->unk_17C);
        }
        break;
    }

    return 2;
}

static void sub_02084C58(NamingScreenAppData *data, BOOL a1) {
    if (data->unk_5D0 != NULL) {
        if (a1 == TRUE) {
            sub_02018410(data->unk_5D0, FALSE);
        } else {
            sub_02018410(data->unk_5D0, TRUE);
        }
    }
}

// DANGER: Can spin infinitely here
static int sub_02084C78(const u16 *a0, int a1) {
    do {
        a1 = sub_02084264(a1 + 1, 0, 3);
    } while (a0[a1] == 1);
    return a0[a1];
}

static BOOL sub_02084C98(int a0, int a1, u16 *a2, int a3) {
    int i;
    int j;
    u16 key;

    if (a3 == 0) {
        return FALSE;
    }
    key = a2[a3 - 1];
    for (i = a0; i < a1; ++i) {
        for (j = 0; j < 3; ++j) {
            if (key == _02102422[i][j] && key != 1) {
                a2[a3 - 1] = sub_02084C78(_02102422[i], j);
                return TRUE;
            }
        }
    }

    return FALSE;
}

static BOOL sub_02084D04(int a0, int a1, int a2, int a3, u16 *a4, int a5) {
    int i;
    u16 key;

    if (a5 == 0 || a4[a5 - 1] == 1) {
        return FALSE;
    }
    key = a4[a5 - 1];
    for (i = a0; i < a1; ++i) {
        if (key == _02102422[i][0]) {
            a4[a5 - 1] = _02102422[i][a2];
            return TRUE;
        }
    }
    for (i = a0; i < a1; ++i) {
        if (key == _02102422[i][a2]) {
            a4[a5 - 1] = _02102422[i][0];
            return TRUE;
        }
    }
    switch (a3) {
    case 0xD001:
        for (i = 0; i < 12u; ++i) {
            if (key == _021021B8[i][0]) {
                a4[a5 - 1] = _021021B8[i][1];
                return TRUE;
            }
        }
        break;
    case 0xD002:
        for (i = 0; i < 10u; ++i) {
            if (key == _02102190[i][0]) {
                a4[a5 - 1] = _02102190[i][1];
                return TRUE;
            }
        }
        break;
    case 0xE006:
        if (key == 0x26) {
            a4[a5 - 1] = 0x24;
            return TRUE;
        }
        if (key == 0x76) {
            a4[a5 - 1] = 0x74;
            return TRUE;
        }
        break;
    }

    return FALSE;
}

static void sub_02084E18(Sprite **sprites, int a1, int maxLen) {
    for (int i = 0; i < maxLen; ++i) {
        Sprite_SetAnimCtrlSeq(sprites[i], 43);
    }
    if (a1 != maxLen) {
        Sprite_SetAnimCtrlSeq(sprites[a1], 44);
    }
}

static const u8 _02101D44[] = { 0x03, 0x06, 0x0C, 0x09, 0x09 };

static void sub_02084E54(Window *window, u16 fillVal, int pageNum, u32 textColor, u8 *pRawData) {
    FillWindowPixelBuffer(window, fillVal);

    for (int i = 0; i < 6; ++i) {
        FillWindowPixelRect(window, _02101D44[pageNum], 32 * i + 16, 0, 16, 19);
        FillWindowPixelRect(window, _02101D44[pageNum], 32 * i + 16, 38, 16, 19);
        FillWindowPixelRect(window, _02101D44[pageNum], 32 * i + 16, 76, 16, 19);
    }

    for (int i = 0; i < 7; ++i) {
        FillWindowPixelRect(window, _02101D44[pageNum], 32 * i, 19, 16, 19);
        FillWindowPixelRect(window, _02101D44[pageNum], 32 * i, 57, 16, 19);
    }

    for (int i = 0; i < 5; ++i) {
        sub_02084540(window, _021104F8[pageNum][i], 0, 19 * i + 4, 16, TEXT_SPEED_NOTRANSFER, textColor, pRawData);
    }

    CopyWindowToVram(window);
}

static void sub_02084F3C(int *a0, Sprite **a1, int a2) {
    for (int i = 0; i < 3; ++i) {
        if (a0[i] != 0) {
            for (int j = 0; j < 3; ++j) {
                Sprite_SetAnimCtrlSeq(a1[j], _021021E8[j][2]);
            }
            Sprite_SetAnimCtrlSeq(a1[i], _021021E8[i][2] - 3);
            break;
        }
    }
    for (int i = 5; i < 7; ++i) {
        if (a0[i] != 0) {
            Sprite_SetAnimCtrlSeq(a1[i], _021021E8[i][2] + 1);
        }
    }
    for (int i = 0; i < 7; ++i) {
        a0[i] = 0;
    }
}

static void sub_02084FCC(NamingScreenAppData *data) {
    if (Sprite_IsCellAnimationRunning(data->unk_32C[8])) {
        return;
    }

    if (data->unk_158 == data->maxLen) {
        data->cursorX = 12;
        data->cursorY = 0;
        Sprite_SetAnimCtrlSeq(data->unk_32C[8], 39);
        data->unk_034 = 0;
    } else {
        Sprite_SetAnimCtrlSeq(data->unk_32C[8], 39);
    }
    if (!data->unk_030) {
        Sprite_SetVisibleFlag(data->unk_32C[8], FALSE);
    } else {
        sub_02084430(data, 0);
    }
    Sprite_SetOamMode(data->unk_32C[8], GX_OAM_MODE_NORMAL);
}

static const UnkStruct_02102278 _02102278[] = {
    { .x = 0x19, .y = 0x3C, .unk_2_0 = 0, .unk_4_0 = 0,  .unk_4_5 = 0 },
    { .x = 0x39, .y = 0x3C, .unk_2_0 = 0, .unk_4_0 = 2,  .unk_4_5 = 0 },
    { .x = 0x59, .y = 0x3C, .unk_2_0 = 0, .unk_4_0 = 4,  .unk_4_5 = 0 },
    { .x = 0x00, .y = 0xC0, .unk_2_0 = 0, .unk_4_0 = 4,  .unk_4_5 = 0 },
    { .x = 0x9D, .y = 0x3C, .unk_2_0 = 1, .unk_4_0 = 8,  .unk_4_5 = 0 },
    { .x = 0xC5, .y = 0x3C, .unk_2_0 = 1, .unk_4_0 = 11, .unk_4_5 = 0 },
    { .x = 0x1C, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 0,  .unk_4_5 = 1 },
    { .x = 0x2C, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 1,  .unk_4_5 = 1 },
    { .x = 0x3C, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 2,  .unk_4_5 = 1 },
    { .x = 0x4C, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 3,  .unk_4_5 = 1 },
    { .x = 0x5C, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 4,  .unk_4_5 = 1 },
    { .x = 0x6C, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 5,  .unk_4_5 = 1 },
    { .x = 0x7C, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 6,  .unk_4_5 = 1 },
    { .x = 0x8C, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 7,  .unk_4_5 = 1 },
    { .x = 0x9C, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 8,  .unk_4_5 = 1 },
    { .x = 0xAC, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 9,  .unk_4_5 = 1 },
    { .x = 0xBC, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 10, .unk_4_5 = 1 },
    { .x = 0xCC, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 11, .unk_4_5 = 1 },
    { .x = 0xDC, .y = 0x58, .unk_2_0 = 2, .unk_4_0 = 12, .unk_4_5 = 1 },
    { .x = 0x1C, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 0,  .unk_4_5 = 2 },
    { .x = 0x2C, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 1,  .unk_4_5 = 2 },
    { .x = 0x3C, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 2,  .unk_4_5 = 2 },
    { .x = 0x4C, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 3,  .unk_4_5 = 2 },
    { .x = 0x5C, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 4,  .unk_4_5 = 2 },
    { .x = 0x6C, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 5,  .unk_4_5 = 2 },
    { .x = 0x7C, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 6,  .unk_4_5 = 2 },
    { .x = 0x8C, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 7,  .unk_4_5 = 2 },
    { .x = 0x9C, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 8,  .unk_4_5 = 2 },
    { .x = 0xAC, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 9,  .unk_4_5 = 2 },
    { .x = 0xBC, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 10, .unk_4_5 = 2 },
    { .x = 0xCC, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 11, .unk_4_5 = 2 },
    { .x = 0xDC, .y = 0x6B, .unk_2_0 = 2, .unk_4_0 = 12, .unk_4_5 = 2 },
    { .x = 0x1C, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 0,  .unk_4_5 = 3 },
    { .x = 0x2C, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 1,  .unk_4_5 = 3 },
    { .x = 0x3C, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 2,  .unk_4_5 = 3 },
    { .x = 0x4C, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 3,  .unk_4_5 = 3 },
    { .x = 0x5C, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 4,  .unk_4_5 = 3 },
    { .x = 0x6C, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 5,  .unk_4_5 = 3 },
    { .x = 0x7C, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 6,  .unk_4_5 = 3 },
    { .x = 0x8C, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 7,  .unk_4_5 = 3 },
    { .x = 0x9C, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 8,  .unk_4_5 = 3 },
    { .x = 0xAC, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 9,  .unk_4_5 = 3 },
    { .x = 0xBC, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 10, .unk_4_5 = 3 },
    { .x = 0xCC, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 11, .unk_4_5 = 3 },
    { .x = 0xDC, .y = 0x7E, .unk_2_0 = 2, .unk_4_0 = 12, .unk_4_5 = 3 },
    { .x = 0x1C, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 0,  .unk_4_5 = 4 },
    { .x = 0x2C, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 1,  .unk_4_5 = 4 },
    { .x = 0x3C, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 2,  .unk_4_5 = 4 },
    { .x = 0x4C, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 3,  .unk_4_5 = 4 },
    { .x = 0x5C, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 4,  .unk_4_5 = 4 },
    { .x = 0x6C, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 5,  .unk_4_5 = 4 },
    { .x = 0x7C, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 6,  .unk_4_5 = 4 },
    { .x = 0x8C, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 7,  .unk_4_5 = 4 },
    { .x = 0x9C, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 8,  .unk_4_5 = 4 },
    { .x = 0xAC, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 9,  .unk_4_5 = 4 },
    { .x = 0xBC, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 10, .unk_4_5 = 4 },
    { .x = 0xCC, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 11, .unk_4_5 = 4 },
    { .x = 0xDC, .y = 0x91, .unk_2_0 = 2, .unk_4_0 = 12, .unk_4_5 = 4 },
    { .x = 0x1C, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 0,  .unk_4_5 = 5 },
    { .x = 0x2C, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 1,  .unk_4_5 = 5 },
    { .x = 0x3C, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 2,  .unk_4_5 = 5 },
    { .x = 0x4C, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 3,  .unk_4_5 = 5 },
    { .x = 0x5C, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 4,  .unk_4_5 = 5 },
    { .x = 0x6C, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 5,  .unk_4_5 = 5 },
    { .x = 0x7C, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 6,  .unk_4_5 = 5 },
    { .x = 0x8C, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 7,  .unk_4_5 = 5 },
    { .x = 0x9C, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 8,  .unk_4_5 = 5 },
    { .x = 0xAC, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 9,  .unk_4_5 = 5 },
    { .x = 0xBC, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 10, .unk_4_5 = 5 },
    { .x = 0xCC, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 11, .unk_4_5 = 5 },
    { .x = 0xDC, .y = 0xA4, .unk_2_0 = 2, .unk_4_0 = 12, .unk_4_5 = 5 },
};

static BOOL sub_0208503C(NamingScreenAppData *data) {
    int i;
    int ip = 0;
    u8 x;
    u8 y;
    u8 x0;
    u8 y0;
    u8 dx;
    u8 dy;
    if (data->type == NAME_SCREEN_UNK4) {
        ip = 4;
    }
    if (gSystem.touchNew) {
        x = gSystem.touchX;
        y = gSystem.touchY;

        for (i = ip; i < 71u; ++i) {
            x0 = _02102278[i].x;
            y0 = _02102278[i].y;
            switch (_02102278[i].unk_2_0) {
            case 0:
                dx = 31;
                dy = 22;
                break;
            case 1:
                dx = 32;
                dy = 22;
                break;
            case 2:
                dx = 16;
                dy = 19;
                break;
            }
            if (x >= x0 && y >= y0 && x <= x0 + dx && y <= y0 + dy) {
                data->cursorX = _02102278[i].unk_4_0;
                data->cursorY = _02102278[i].unk_4_5;
                return TRUE;
            }
        }
    }

    return FALSE;
}
