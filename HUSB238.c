#include "HUSB238.h"

#define I2C_READ_TIMEOUT_MS 5
#define I2C_WRITE_WAIT_MS 5

#define HUSB238_REG_PD_STATUS0 0x00
#define HUSB238_REG_PD_STATUS1 0x01
#define HUSB238_REG_SRC_PDO_5V 0x02
#define HUSB238_REG_SRC_PDO_9V 0x03
#define HUSB238_REG_SRC_PDO_12V 0x04
#define HUSB238_REG_SRC_PDO_15V 0x05
#define HUSB238_REG_SRC_PDO_18V 0x06
#define HUSB238_REG_SRC_PDO_20V 0x07
#define HUSB238_REG_SRC_PDO 0x08
#define HUSB238_REG_GO_COMMAND 0x09

static struct HUSB238_Platform platform = { 0 };

void HUSB238_Init(struct HUSB238_Platform *platformPtr) {
    platform = *platformPtr;
}

bool HUSB238_ReadStatus(struct HUSB238_Status *status) {
    int ret;

    // Read PD_STATUS0 register
    uint8_t pdStatus0Data;
    ret = platform.i2cReadReg(HUSB238_I2C_ADDR, HUSB238_REG_PD_STATUS0, &pdStatus0Data, 1, I2C_READ_TIMEOUT_MS);
    if (ret < 0) {
        platform.debugPrint("HUSB238: Failed to read PD_STATUS0 register: %d\r\n", -ret);
        return false;
    }

    status->pdSrcVoltage = (enum HUSB238_PDSrcVoltage)((pdStatus0Data >> 4) & 0x0f);
    status->pdSrcCurrent = (enum HUSB238_PDSrcCurrent)(pdStatus0Data & 0x0f);

    // Read PD_STATUS1 register
    uint8_t pdStatus1Data;
    ret = platform.i2cReadReg(HUSB238_I2C_ADDR, HUSB238_REG_PD_STATUS1, &pdStatus1Data, 1, I2C_READ_TIMEOUT_MS);
    if (ret < 0) {
        platform.debugPrint("HUSB238: Failed to read PD_STATUS1 register: %d\r\n", -ret);
        return false;
    }

    status->ccDir = (enum HUSB238_CCDir)((pdStatus1Data >> 7) & 0x01);
    status->attach = (bool)((pdStatus1Data >> 6) & 0x01);
    status->pdResponse = (enum HUSB238_PDResponse)((pdStatus1Data >> 3) & 0x07);
    status->v5VVoltage = (bool)((pdStatus1Data >> 2) & 0x01);
    status->v5VCurrent = (enum HUSB238_5VCurrent)(pdStatus1Data & 0x03);

    return true;
}

bool HUSB238_ReadSrcPDO_5V(struct HUSB238_SrcPDO *srcPDO) {
    int ret;

    // Read SRC_PDO_5V register
    uint8_t srcPDO5VData;
    ret = platform.i2cReadReg(HUSB238_I2C_ADDR, HUSB238_REG_SRC_PDO_5V, &srcPDO5VData, 1, I2C_READ_TIMEOUT_MS);
    if (ret < 0) {
        platform.debugPrint("HUSB238: Failed to read SRC_PDO_5V register: %d\r\n", -ret);
        return false;
    }

    srcPDO->srcDetect = (bool)((srcPDO5VData >> 7) & 0x01);
    srcPDO->pdSrcCurrent = (enum HUSB238_PDSrcCurrent)(srcPDO5VData & 0xf);

    return true;
}

bool HUSB238_ReadSrcPDO_9V(struct HUSB238_SrcPDO *srcPDO) {
    int ret;

    // Read SRC_PDO_9V register
    uint8_t srcPDO9VData;
    ret = platform.i2cReadReg(HUSB238_I2C_ADDR, HUSB238_REG_SRC_PDO_9V, &srcPDO9VData, 1, I2C_READ_TIMEOUT_MS);
    if (ret < 0) {
        platform.debugPrint("HUSB238: Failed to read SRC_PDO_9V register: %d\r\n", -ret);
        return false;
    }

    srcPDO->srcDetect = (bool)((srcPDO9VData >> 7) & 0x01);
    srcPDO->pdSrcCurrent = (enum HUSB238_PDSrcCurrent)(srcPDO9VData & 0xf);

    return true;
}

bool HUSB238_ReadSrcPDO_12V(struct HUSB238_SrcPDO *srcPDO) {
    int ret;

    // Read SRC_PDO_12V register
    uint8_t srcPDO12VData;
    ret = platform.i2cReadReg(HUSB238_I2C_ADDR, HUSB238_REG_SRC_PDO_12V, &srcPDO12VData, 1, I2C_READ_TIMEOUT_MS);
    if (ret < 0) {
        platform.debugPrint("HUSB238: Failed to read SRC_PDO_12V register: %d\r\n", -ret);
        return false;
    }

    srcPDO->srcDetect = (bool)((srcPDO12VData >> 7) & 0x01);
    srcPDO->pdSrcCurrent = (enum HUSB238_PDSrcCurrent)(srcPDO12VData & 0xf);

    return true;
}

bool HUSB238_ReadSrcPDO_15V(struct HUSB238_SrcPDO *srcPDO) {
    int ret;

    // Read SRC_PDO_15V register
    uint8_t srcPDO15VData;
    ret = platform.i2cReadReg(HUSB238_I2C_ADDR, HUSB238_REG_SRC_PDO_15V, &srcPDO15VData, 1, I2C_READ_TIMEOUT_MS);
    if (ret < 0) {
        platform.debugPrint("HUSB238: Failed to read SRC_PDO_15V register: %d\r\n", -ret);
        return false;
    }

    srcPDO->srcDetect = (bool)((srcPDO15VData >> 7) & 0x01);
    srcPDO->pdSrcCurrent = (enum HUSB238_PDSrcCurrent)(srcPDO15VData & 0xf);

    return true;
}

bool HUSB238_ReadSrcPDO_18V(struct HUSB238_SrcPDO *srcPDO) {
    int ret;

    // Read SRC_PDO_18V register
    uint8_t srcPDO18VData;
    ret = platform.i2cReadReg(HUSB238_I2C_ADDR, HUSB238_REG_SRC_PDO_18V, &srcPDO18VData, 1, I2C_READ_TIMEOUT_MS);
    if (ret < 0) {
        platform.debugPrint("HUSB238: Failed to read SRC_PDO_18V register: %d\r\n", -ret);
        return false;
    }

    srcPDO->srcDetect = (bool)((srcPDO18VData >> 7) & 0x01);
    srcPDO->pdSrcCurrent = (enum HUSB238_PDSrcCurrent)(srcPDO18VData & 0xf);

    return true;
}

bool HUSB238_ReadSrcPDO_20V(struct HUSB238_SrcPDO *srcPDO) {
    int ret;

    // Read SRC_PDO_20V register
    uint8_t srcPDO20VData;
    ret = platform.i2cReadReg(HUSB238_I2C_ADDR, HUSB238_REG_SRC_PDO_20V, &srcPDO20VData, 1, I2C_READ_TIMEOUT_MS);
    if (ret < 0) {
        platform.debugPrint("HUSB238: Failed to read SRC_PDO_20V register: %d\r\n", -ret);
        return false;
    }

    srcPDO->srcDetect = (bool)((srcPDO20VData >> 7) & 0x01);
    srcPDO->pdSrcCurrent = (enum HUSB238_PDSrcCurrent)(srcPDO20VData & 0xf);

    return true;
}

bool HUSB238_GetSrcPDOSelect(enum HUSB238_SrcPDOSelect *srcPDOSelect) {
    int ret;

    // Read SRC_PDO register
    uint8_t srcPDOData;
    ret = platform.i2cReadReg(HUSB238_I2C_ADDR, HUSB238_REG_SRC_PDO, &srcPDOData, 1, I2C_READ_TIMEOUT_MS);
    if (ret < 0) {
        platform.debugPrint("HUSB238: Failed to read SRC_PDO register: %d\r\n", -ret);
        return false;
    }

    *srcPDOSelect = (enum HUSB238_SrcPDOSelect)((srcPDOData >> 4) & 0xf);

    return true;
}

bool HUSB238_SetSrcPDOSelect(enum HUSB238_SrcPDOSelect srcPDOSelect) {
    int ret;

    // Write SRC_PDO register
    uint8_t srcPDOData = ((uint8_t)srcPDOSelect << 4);
    ret = platform.i2cWriteReg(HUSB238_I2C_ADDR, HUSB238_REG_SRC_PDO, &srcPDOData, 1, I2C_WRITE_WAIT_MS);
    if (ret < 0) {
        platform.debugPrint("HUSB238: Failed to write SRC_PDO register: %d\r\n", -ret);
        return false;
    }

    return true;
}

bool HUSB238_SendCommand(enum HUSB238_CommandFunc commandFunc) {
    int ret;

    // Write GO_COMMAND register
    uint8_t goCommandData = ((uint8_t)commandFunc);
    ret = platform.i2cWriteReg(HUSB238_I2C_ADDR, HUSB238_REG_GO_COMMAND, &goCommandData, 1, I2C_WRITE_WAIT_MS);
    if (ret < 0) {
        platform.debugPrint("HUSB238: Failed to write GO_COMMAND register: %d\r\n", -ret);
        return false;
    }

    return true;
}

int HUSB238_DecodePDSrcVoltage_V(enum HUSB238_PDSrcVoltage pdSrcVoltage) {
    switch (pdSrcVoltage) {
    case HUSB238_UNATTACHED:
        return 0;
    case HUSB238_PD_5V:
        return 5;
    case HUSB238_PD_9V:
        return 9;
    case HUSB238_PD_12V:
        return 12;
    case HUSB238_PD_15V:
        return 15;
    case HUSB238_PD_18V:
        return 18;
    case HUSB238_PD_20V:
        return 20;
    default:
        return -1;
    }
}

int HUSB238_DecodePDSrcCurrent_mA(enum HUSB238_PDSrcCurrent pdSrcCurrent) {
    switch (pdSrcCurrent) {
    case HUSB238_0_5A:
        return 500;
    case HUSB238_0_7A:
        return 700;
    case HUSB238_1_0A:
        return 1000;
    case HUSB238_1_25A:
        return 1250;
    case HUSB238_1_5A:
        return 1500;
    case HUSB238_1_75A:
        return 1750;
    case HUSB238_2_0A:
        return 2000;
    case HUSB238_2_25A:
        return 2250;
    case HUSB238_2_5A:
        return 2500;
    case HUSB238_2_75A:
        return 2750;
    case HUSB238_3_0A:
        return 3000;
    case HUSB238_3_25A:
        return 3250;
    case HUSB238_3_5A:
        return 3500;
    case HUSB238_4_0A:
        return 4000;
    case HUSB238_4_5A:
        return 4500;
    case HUSB238_5_0A:
        return 5000;
    default:
        return -1;
    }
}
int HUSB238_Decode5VCurrent_mA(enum HUSB238_5VCurrent v5VCurrent) {
    switch (v5VCurrent) {
    case HUSB238_5VCurrent_DEFAULT:
        return 1;
    case HUSB238_5VCurrent_1_5A:
        return 1500;
    case HUSB238_5VCurrent_2_4A:
        return 2400;
    case HUSB238_5VCurrent_3A:
        return 3000;
    default:
        return -1;
    }
}

int HUSB238_DecodeSrcPDOSelect_V(enum HUSB238_SrcPDOSelect srcPDOSelect) {
    switch (srcPDOSelect) {
    case HUSB238_SrcPDOSelect_NOT_SELECTED:
        return 0;
    case HUSB238_SrcPDOSelect_5V:
        return 5;
    case HUSB238_SrcPDOSelect_9V:
        return 9;
    case HUSB238_SrcPDOSelect_12V:
        return 12;
    case HUSB238_SrcPDOSelect_15V:
        return 15;
    case HUSB238_SrcPDOSelect_18V:
        return 18;
    case HUSB238_SrcPDOSelect_20V:
        return 20;
    default:
        return -1;
    }
}
