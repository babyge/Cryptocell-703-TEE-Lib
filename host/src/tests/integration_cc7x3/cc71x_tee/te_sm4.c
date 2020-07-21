/*
 * Copyright (c) 2001-2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause OR Arm's non-OSI source license
 *
 */

#include <stdio.h>
#include <stdint.h>

#include "test_engine.h"

#include "cc_sm4.h"

/******************************************************************
 * Defines
 ******************************************************************/
#define SM4_TV_MAX_DATA_SIZE    64

/******************************************************************
 * Types
 ******************************************************************/
typedef struct Sm4Vector_t{
    CCSm4OperationMode_t operationMode;
    CCSm4EncryptMode_t encryptDecryptFlag;
    CCSm4Key_t pKey;
    CCSm4Iv_t pIV;
    size_t dataSize;
    uint8_t dataIn[SM4_TV_MAX_DATA_SIZE];
    uint8_t dataRef[SM4_TV_MAX_DATA_SIZE];
    uint8_t dataOut[SM4_TV_MAX_DATA_SIZE];
} Sm4Vector_t;


/******************************************************************
 * Externs
 ******************************************************************/

/******************************************************************
 * Globals
 ******************************************************************/

static Sm4Vector_t sm4_ecb_decrypt_vector = {
    .operationMode = CC_SM4_MODE_ECB,
    .encryptDecryptFlag = CC_SM4_DECRYPT,
    /* CCSm4Key_t */
    .pKey = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF},
    /* CCSm4Iv_t */
    .pIV = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .dataSize = 16,
    /* Input */
    .dataIn = {0xF7, 0x66, 0x67, 0x8F, 0x13, 0xF0, 0x1A, 0xDE, 0xAC, 0x1B, 0x3E, 0xA9, 0x55, 0xAD, 0xB5, 0x94},
    /* Expected results */
    .dataRef = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
    /* Output */
    .dataOut = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
};

static Sm4Vector_t sm4_cbc_encrypt_vector = {
    .operationMode = CC_SM4_MODE_CBC,
    .encryptDecryptFlag = CC_SM4_ENCRYPT,
    /* CCSm4Key_t */
    .pKey = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10},
    /* CCSm4Iv_t */
    .pIV = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
    .dataSize = 32,
    /* Input */
    .dataIn = {0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xCC, 0xCC, 0xCC, 0xCC, 0xDD, 0xDD, 0xDD, 0xDD,
               0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB},
    /* Expected results */
    .dataRef = {0x78, 0xEB, 0xB1, 0x1C, 0xC4, 0x0B, 0x0A, 0x48, 0x31, 0x2A, 0xAE, 0xB2, 0x04, 0x02, 0x44, 0xCB,
                0x4C, 0xB7, 0x01, 0x69, 0x51, 0x90, 0x92, 0x26, 0x97, 0x9B, 0x0D, 0x15, 0xDC, 0x6A, 0x8F, 0x6D},
    /* Output */
    .dataOut = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
};

static Sm4Vector_t sm4_ctr_encrypt_vector = {
    .operationMode = CC_SM4_MODE_CTR,
    .encryptDecryptFlag = CC_SM4_ENCRYPT,
    /* CCSm4Key_t */
    .pKey = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF},
    /* CCSm4Iv_t */
    .pIV = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
    .dataSize = 64,
    /* Input */
    .dataIn = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
               0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD,
               0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
               0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB},
    /* Expected results */
    .dataRef = {0x5D, 0xCC, 0xCD, 0x25, 0xB9, 0x5A, 0xB0, 0x74, 0x17, 0xA0, 0x85, 0x12, 0xEE, 0x16, 0x0E, 0x2F,
                0x8F, 0x66, 0x15, 0x21, 0xCB, 0xBA, 0xB4, 0x4C, 0xC8, 0x71, 0x38, 0x44, 0x5B, 0xC2, 0x9E, 0x5C,
                0x0A, 0xE0, 0x29, 0x72, 0x05, 0xD6, 0x27, 0x04, 0x17, 0x3B, 0x21, 0x23, 0x9B, 0x88, 0x7F, 0x6C,
                0x8C, 0xB5, 0xB8, 0x00, 0x91, 0x7A, 0x24, 0x88, 0x28, 0x4B, 0xDE, 0x9E, 0x16, 0xEA, 0x29, 0x06},
    /* Output */
    .dataOut = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
};

static Sm4Vector_t sm4_ofb_encrypt_vector = {
    .operationMode = CC_SM4_MODE_OFB,
    .encryptDecryptFlag = CC_SM4_ENCRYPT,
    /* CCSm4Key_t */
    .pKey = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10},
    /* CCSm4Iv_t */
    .pIV = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
    .dataSize = 32,
    /* Input */
    .dataIn = {0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xCC, 0xCC, 0xCC, 0xCC, 0xDD, 0xDD, 0xDD, 0xDD,
               0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB},
    /* Expected results */
    .dataRef = {0xAC, 0x32, 0x36, 0xCB, 0x86, 0x1D, 0xD3, 0x16, 0xE6, 0x41, 0x3B, 0x4E, 0x3C, 0x75, 0x24, 0xB7, \
                0x1D, 0x01, 0xAC, 0xA2, 0x48, 0x7C, 0xA5, 0x82, 0xCB, 0xF5, 0x46, 0x3E, 0x66, 0x98, 0x53, 0x9B},
    /* Output */
    .dataOut = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
};

/******************************************************************
 * Static Prototypes
 ******************************************************************/
static TE_rc_t sm4_prepare(void *pContext);
static TE_rc_t sm4_execute(void *pContext);
static TE_rc_t sm4_verify(void *pContext);
static TE_rc_t sm4_clean(void *pContext);

/******************************************************************
 * Static functions
 ******************************************************************/
static TE_rc_t sm4_prepare(void *pContext)
{
    TE_rc_t res = TE_RC_SUCCESS;
    TE_UNUSED(pContext);

    goto bail;
bail:
    return res;
}

static TE_rc_t sm4_execute(void *pContext)
{
    TE_rc_t res = TE_RC_SUCCESS;
    TE_perfIndex_t cookie;
    Sm4Vector_t *sm4_vec = (Sm4Vector_t *)pContext;

    if(sm4_vec->encryptDecryptFlag == CC_SM4_ENCRYPT) {
            cookie = TE_perfOpenNewEntry("sm4", "encrpyt");
    } else {
            cookie = TE_perfOpenNewEntry("sm4", "decrypt");
    }

    /* test SM4 integrated API */
    TE_ASSERT( CC_Sm4(sm4_vec->pIV,
                 sm4_vec->pKey,
                 sm4_vec->encryptDecryptFlag,
                 sm4_vec->operationMode,
                 (uint8_t *)&(sm4_vec->dataIn),
                 sm4_vec->dataSize,
                 (uint8_t *)&(sm4_vec->dataOut)) == CC_OK);

    TE_perfCloseEntry(cookie);

    goto bail;

bail:
    return res;
}

static TE_rc_t sm4_verify(void *pContext)
{
    TE_rc_t res = TE_RC_SUCCESS;
    Sm4Vector_t *sm4_vec = (Sm4Vector_t *)pContext;

    TE_ASSERT( memcmp((uint8_t *)&(sm4_vec->dataOut), (uint8_t *)&(sm4_vec->dataRef), sm4_vec->dataSize) == 0);

    goto bail;
bail:
    return res;
}

static TE_rc_t sm4_clean(void *pContext)
{
    TE_rc_t res = TE_RC_SUCCESS;
    TE_UNUSED(pContext);

    goto bail;
bail:
    return res;
}

/******************************************************************
 * Public
 ******************************************************************/
int TE_init_sm4_test(void)
{
    TE_rc_t res = TE_RC_SUCCESS;

    TE_perfEntryInit("sm4", "encrpyt");
    TE_perfEntryInit("sm4", "decrypt");

    TE_ASSERT(TE_registerFlow("sm4",
                               "ecb",
                               "encrypt",
                               sm4_prepare,
                               sm4_execute,
                               sm4_verify,
                               sm4_clean,
                               &sm4_ecb_decrypt_vector) == TE_RC_SUCCESS);

    TE_ASSERT(TE_registerFlow("sm4",
                               "cbc",
                               "encrypt",
                               sm4_prepare,
                               sm4_execute,
                               sm4_verify,
                               sm4_clean,
                               &sm4_cbc_encrypt_vector) == TE_RC_SUCCESS);

    TE_ASSERT(TE_registerFlow("sm4",
                               "ctr",
                               "decrypt",
                               sm4_prepare,
                               sm4_execute,
                               sm4_verify,
                               sm4_clean,
                               &sm4_ctr_encrypt_vector) == TE_RC_SUCCESS);

    TE_ASSERT(TE_registerFlow("sm4",
                               "ofb",
                               "encrypt",
                               sm4_prepare,
                               sm4_execute,
                               sm4_verify,
                               sm4_clean,
                               &sm4_ofb_encrypt_vector) == TE_RC_SUCCESS);

    goto bail;

bail:
	return res;
}

