/*
 * Copyright (c) 2001-2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause OR Arm's non-OSI source license
 *
 */

/*!
 @file
 @brief This file contains the error definitions of the platform-dependent PAL APIs.
 */

 /*!
  @addtogroup cc_pal_error
  @{
  */

#ifndef _CC_PAL_ERROR_H
#define _CC_PAL_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif

/*! The PAL error base.*/
#define CC_PAL_BASE_ERROR                0x0F000000

/* Memory error returns */
/*! Buffer 1 is greater than buffer 2 error.*/
#define CC_PAL_MEM_BUF1_GREATER          CC_PAL_BASE_ERROR + 0x01UL
/*! Buffer 2 is greater than buffer 1 error.*/
#define CC_PAL_MEM_BUF2_GREATER          CC_PAL_BASE_ERROR + 0x02UL

/* Semaphore error returns */
/*! Semaphore creation failed.*/
#define CC_PAL_SEM_CREATE_FAILED         CC_PAL_BASE_ERROR + 0x03UL
/*! Semaphore deletion failed.*/
#define CC_PAL_SEM_DELETE_FAILED         CC_PAL_BASE_ERROR + 0x04UL
/*! Semaphore reached timeout.*/
#define CC_PAL_SEM_WAIT_TIMEOUT          CC_PAL_BASE_ERROR + 0x05UL
/*! Semaphore wait failed.*/
#define CC_PAL_SEM_WAIT_FAILED           CC_PAL_BASE_ERROR + 0x06UL
/*! Semaphore release failed.*/
#define CC_PAL_SEM_RELEASE_FAILED        CC_PAL_BASE_ERROR + 0x07UL
/*! Illegal PAL address.*/
#define CC_PAL_ILLEGAL_ADDRESS       CC_PAL_BASE_ERROR + 0x08UL

#ifdef __cplusplus
}
#endif
/*!
 @}
 */

#endif

