/*
 * Copyright (c) 2001-2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause OR Arm’s non-OSI source license
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "board_configs.h"

#include "test_pal_mem.h"
#include "test_pal_map_addrs.h"
#include "test_pal_log.h"

#define TEST_HAL_MEM_DMA_BASE_ADDR		0x30100000
#define TEST_HAL_MEM_UNMANAGED_BASE_ADDR	0x30000000
#define TEST_HAL_MEM_DMA_AREA_LEN		0x0F000000	/* 240MB */
#define TEST_HAL_MEM_UNMANAGED_AREA_LEN		0x00100000	/* 1MB */

/******************************************************************************/
uint32_t Test_HalBoardInit(void)
{
	unsigned long DMABaseAddr;
	unsigned long unmanagedBaseAddr;

	/* maps the DMA base address */
	DMABaseAddr = (unsigned long)Test_PalMapAddr(
				 (void *)TEST_HAL_MEM_DMA_BASE_ADDR,
				 (void *)TEST_HAL_MEM_DMA_BASE_ADDR,
				 "/dev/mem",
				 TEST_HAL_MEM_DMA_AREA_LEN,
				 BM_READ|BM_WRITE|BM_EXEC|BM_SHARED|BM_FIXED);

	if (!VALID_MAPPED_ADDR(DMABaseAddr)) {
		TEST_PRINTF_ERROR("Error: mmap failed for DMABaseAddr\n");
		goto end_with_error;
	}

	TEST_PRINTF("DMABaseAddr = 0x%lx\n", DMABaseAddr);

	/* maps the unmanaged memory base address */
	unmanagedBaseAddr = (unsigned long)Test_PalMapAddr(
				 (void *)TEST_HAL_MEM_UNMANAGED_BASE_ADDR,
				 (void *)TEST_HAL_MEM_UNMANAGED_BASE_ADDR,
				 "/dev/mem",
				 TEST_HAL_MEM_UNMANAGED_AREA_LEN,
				 BM_READ|BM_WRITE|BM_EXEC|BM_SHARED|BM_FIXED);

	if (!VALID_MAPPED_ADDR(unmanagedBaseAddr)) {
		TEST_PRINTF_ERROR("Error: mmap failed for unmanagedBaseAddr\n");
		goto end_with_error;
	}
	TEST_PRINTF("unmanagedBaseAddr = 0x%lx\n", unmanagedBaseAddr);

	if (Test_PalMemInit(DMABaseAddr, unmanagedBaseAddr,
				TEST_HAL_MEM_DMA_AREA_LEN)) {
		TEST_PRINTF_ERROR("Error: MemInit failed\n");
		goto end_with_error;
	}

	return 0;

	end_with_error:
	Test_HalBoardFree();
	return 1;
}

/******************************************************************************/
void Test_HalBoardFree(void)
{
	if (Test_PalGetDMABaseAddr() != 0) {
		Test_PalUnmapAddr((void *)Test_PalGetDMABaseAddr(),
				TEST_HAL_MEM_DMA_AREA_LEN);
	}

	if (Test_PalGetUnmanagedBaseAddr() != 0) {
		Test_PalUnmapAddr((void *)Test_PalGetUnmanagedBaseAddr(),
				TEST_HAL_MEM_UNMANAGED_AREA_LEN);
	}
}
