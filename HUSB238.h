#ifndef HUSB238_H
#define HUSB238_H

#include <stdint.h>
#include <stdbool.h>

#define HUSB238_I2C_ADDR 0x08

enum HUSB238_PDSrcVoltage {
    HUSB238_UNATTACHED = 00,
    HUSB238_PD_5V = 01,
    HUSB238_PD_9V = 02,
    HUSB238_PD_12V = 03,
    HUSB238_PD_15V = 04,
    HUSB238_PD_18V = 05,
    HUSB238_PD_20V = 06,
};

enum HUSB238_PDSrcCurrent {
    HUSB238_0_5A = 000,
    HUSB238_0_7A = 001,
    HUSB238_1_0A = 002,
    HUSB238_1_25A = 003,
    HUSB238_1_5A = 004,
    HUSB238_1_75A = 005,
    HUSB238_2_0A = 006,
    HUSB238_2_25A = 007,
    HUSB238_2_5A = 010,
    HUSB238_2_75A = 011,
    HUSB238_3_0A = 012,
    HUSB238_3_25A = 013,
    HUSB238_3_5A = 014,
    HUSB238_4_0A = 015,
    HUSB238_4_5A = 016,
    HUSB238_5_0A = 017,
};

enum HUSB238_CCDir {
    HUSB238_CCDir_CC1_OR_UNATTACHED = 0,
    HUSB238_CCDir_CC2 = 1,
};

enum HUSB238_PDResponse {
    HUSB238_PDResponse_NO_RESPONSE = 00,
    HUSB238_PDResponse_SUCCESS = 01,
    HUSB238_PDResponse_INVALID_CMD = 03,
    HUSB238_PDResponse_CMD_NOT_SUPP = 04,
    HUSB238_PDResponse_TRX_FAIL = 05,
};

enum HUSB238_5VCurrent {
    HUSB238_5VCurrent_DEFAULT = 0,
    HUSB238_5VCurrent_1_5A = 1,
    HUSB238_5VCurrent_2_4A = 2,
    HUSB238_5VCurrent_3A = 3,
};

enum HUSB238_SrcPDOSelect {
    HUSB238_SrcPDOSelect_NOT_SELECTED = 000,
    HUSB238_SrcPDOSelect_5V = 001,
    HUSB238_SrcPDOSelect_9V = 002,
    HUSB238_SrcPDOSelect_12V = 003,
    HUSB238_SrcPDOSelect_15V = 010,
    HUSB238_SrcPDOSelect_18V = 011,
    HUSB238_SrcPDOSelect_20V = 012,
};

enum HUSB238_CommandFunc {
    HUSB238_CommandFunc_REQUEST_SELECTED_PDO = 001,
    HUSB238_CommandFunc_SEND_GET_SRC_CAP = 004,
    HUSB238_CommandFunc_SEND_HARD_RESET = 020,
};

struct HUSB238_Status {
    enum HUSB238_PDSrcVoltage pdSrcVoltage;
    enum HUSB238_PDSrcCurrent pdSrcCurrent;
    enum HUSB238_CCDir ccDir;
    bool attach;
    enum HUSB238_PDResponse pdResponse;
    bool v5VVoltage;
    enum HUSB238_5VCurrent v5VCurrent;
};

struct HUSB238_SrcPDO {
    bool srcDetect;
    enum HUSB238_PDSrcCurrent pdSrcCurrent;
};

struct HUSB238_Platform {
    int (*i2cWriteReg)(uint8_t addr7bit, uint8_t regNum, const uint8_t *data, uint8_t length, uint8_t wait);
    int (*i2cReadReg)(uint8_t addr7bit, uint8_t regNum, uint8_t *data, uint8_t length, int timeout);

    void (*debugPrint)(const char *fmt, ...);
};

void HUSB238_Init(struct HUSB238_Platform *platform);

bool HUSB238_ReadStatus(struct HUSB238_Status *status);
bool HUSB238_ReadSrcPDO_5V(struct HUSB238_SrcPDO *srcPDO);
bool HUSB238_ReadSrcPDO_9V(struct HUSB238_SrcPDO *srcPDO);
bool HUSB238_ReadSrcPDO_12V(struct HUSB238_SrcPDO *srcPDO);
bool HUSB238_ReadSrcPDO_15V(struct HUSB238_SrcPDO *srcPDO);
bool HUSB238_ReadSrcPDO_18V(struct HUSB238_SrcPDO *srcPDO);
bool HUSB238_ReadSrcPDO_20V(struct HUSB238_SrcPDO *srcPDO);

bool HUSB238_GetSrcPDOSelect(enum HUSB238_SrcPDOSelect *srcPDOSelect);
bool HUSB238_SetSrcPDOSelect(enum HUSB238_SrcPDOSelect srcPDOSelect);

bool HUSB238_SendCommand(enum HUSB238_CommandFunc commandFunc);

int HUSB238_DecodePDSrcVoltage_V(enum HUSB238_PDSrcVoltage pdSrcVoltage);
int HUSB238_DecodePDSrcCurrent_mA(enum HUSB238_PDSrcCurrent pdSrcCurrent);
int HUSB238_Decode5VCurrent_mA(enum HUSB238_5VCurrent v5VCurrent);
int HUSB238_DecodeSrcPDOSelect_V(enum HUSB238_SrcPDOSelect srcPDOSelect);

#endif // HUSB238_H
