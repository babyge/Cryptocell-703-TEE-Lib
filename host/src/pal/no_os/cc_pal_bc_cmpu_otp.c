/*
 * Copyright (c) 2001-2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause OR Arm's non-OSI source license
 *
 */

#ifdef CC_CMPU_BC_MODE
#include "cc_pal_types.h"
#include "cc_otp_defs.h"
#include "cc_prod_error.h"

uint32_t rtlOtpMaskTable[CC_OTP_USER_DEFINED_OFFSET] = {
        0x04030201,    // 0x0
        0x08070605,    // 0x1
        0x0c0b0a09,    // 0x2
        0x100f0e0d,    // 0x3
        0x14131211,    // 0x4
        0x18171615,    // 0x5
        0x1c1b1a19,    // 0x6
        0x201f1e1d,    // 0x7
        0x24232221,    // 0x8
        0x28272625,    // 0x9
        0x2c2b2a29,    // 0xa
        0x302f2e2d,    // 0xb
        0x34333231,    // 0xc
        0x38373635,    // 0xd
        0x3c3b3a39,    // 0xe
        0x403f3e3d,    // 0xf
        0x00000000,    // 0x10
        0x00000000,    // 0x11
        0x00000000,    // 0x12
        0x00000000,    // 0x13
        0x00000000,    // 0x14
        0x00000000,    // 0x15
        0x00000000,    // 0x16
        0x00000000,    // 0x17
        0x00000000,    // 0x18
        0x00000000,    // 0x19
        0x00000000,    // 0x1A
        0x44434241,    // 0x1B
        0x48474645,    // 0x1C
        0x4c4b4a49,    // 0x1D
        0x504f4e4d,    // 0x1E
        0x54535251,    // 0x1F
        0x58575655,    // 0x20
        0x5c5b5a59,    // 0x21
        0x605f5e5d,    // 0x22
        0x00000000,    // 0x23
        0x00000000,    // 0x24
        0x00000000,    // 0x25
        0x00000000,    // 0x26
        0x00000000,    // 0x27
        0x00000000,    // 0x28
        0x00000000,    // 0x29
        0x00000000,    // 0x2A
        0x00000000,    // 0x2B
        0x00000000,    // 0x2C
        0x00000000,    // 0x2D
        0x00000000,    // 0x2E
        0x00000000,    // 0x2F
        0x00000000,    // 0x30
        0x00000000,    // 0x31
        0x00000000,    // 0x32
        0x00000000,    // 0x33
};

/**
 * @brief   Writes a word to a specific offset in the OTP.
 *          It is a user specific implementation.
 *
 * @param[in] otpData       - Word value to write
 * @param[in] otpWordOffset - Offset in the OTP
 *
 * @return CC_OK
 */

uint32_t CC_PalOtpWordWrite(uint32_t otpData, uint32_t otpWordOffset)
{
    CC_UNUSED_PARAM(otpData);
    CC_UNUSED_PARAM(otpWordOffset);

    return CC_OK;
}

/**
 * @brief   Reads a word from a specific offset in the OTP.
 *          It is a user specific implementation.
 *
 * @param[in] otpWordOffset - Offset in the OTP
 *
 * @return OTP Word
 */

uint32_t CC_PalOtpWordRead(uint32_t otpWordOffset)
{
    CC_UNUSED_PARAM(otpWordOffset);

    return CC_OK;
}

/**
 * @brief   Writes a word to a specific offset in the OTP.
 *          It is a user specific implementation.
 *
 * @param[in]     wordOffsetInTable - Offset in the mask table
 * @param[in/out] rtlOtpMask        - RTL OTP mask word
 *
 * @return error
 */

uint32_t CC_PalGetRtlOtpMask(uint32_t wordOffsetInTable, unsigned long* rtlOtpMask)
{
    uint32_t error = CC_OK;

    *rtlOtpMask = 0;
    if (wordOffsetInTable < CC_OTP_USER_DEFINED_OFFSET) {
        *rtlOtpMask = rtlOtpMaskTable[wordOffsetInTable];
    } else {
        error = CC_PROD_INVALID_OTP_RANGE_ERR;
    }

    return error;
}

#endif


