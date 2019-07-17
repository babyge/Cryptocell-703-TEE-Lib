/*******************************************************************************
* The confidential and proprietary information contained in this file may      *
* only be used by a person authorised under and to the extent permitted        *
* by a subsisting licensing agreement from ARM Limited or its affiliates.      *
*   (C) COPYRIGHT [2001-2017] ARM Limited or its affiliates.                   *
*       ALL RIGHTS RESERVED                                                    *
* This entire notice must be reproduced on all copies of this file             *
* and copies of this file may only be made by a person if such person is       *
* permitted to do so under the terms of a subsisting license agreement         *
* from ARM Limited or its affiliates.                                          *
*******************************************************************************/

#ifndef TEST_PAL_CLI_H_
#define TEST_PAL_CLI_H_

/*!
 @file
 @brief This file contains CLI APIs used by tests. Supported only for FreeRTOS.
 */

/*!
 @addtogroup pal_cli_test
 @{
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*COMMAND_CALLBACK)(char *pcWriteBuffer, size_t xWriteBufferLen,
    const char *pcCommandString);

struct Test_PalCliCommand {
    /*!< The command that causes pxCommandInterpreter to be executed.
     * For example "help".  Must be all lower case. */
    const char            *const pcCommand;
    /*!< String that describes how to use the command. Should start
     * with the command itself, and end with "\r\n".
     * For example "help: Returns a list of all the commands\r\n". */
    const char            *const pcHelpString;
    /*!< A pointer to the callback function that will return the output
     * generated by the command. */
    const COMMAND_CALLBACK        pxCommandInterpreter;
    int8_t                cExpectedNumberOfParameters;
};

/******************************************************************************/
/*!
 * @brief This function registers a new CLI command.
 *
 *
 * @return 0 on success.
 * @return 1 on failure.
 */
uint32_t Test_PalCLIRegisterCommand(
 struct Test_PalCliCommand *commandToRegister /*!< Command structure.*/
);

/******************************************************************************/
/*!
 * @brief This function obtains a parameter string by its index and stores the
 * parameter string length.
 *
 *
 * @return Parameter string on success.
 * @return NULL on failure.
 */
const char *Test_PalCLIGetParameter(
 const char *commandString, /*!< The command string itself.*/
 uint32_t wantedParamIndx, /*!< Parameter index.*/
 uint32_t *paramStringLength /*!< Parameter string length.*/
);

#ifdef __cplusplus
}
#endif
/*!
 @}
 */
#endif /* TEST_PAL_CLI_H_ */