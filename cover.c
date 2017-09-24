/***********************************************************
*
* Copyright (C), 2013-2017, wangfyu 
* All rights reserved.
*
* File name  : cover.c
* Version    : 1.0
* Description: 实现cover题目功能
*
* Author     : Wang FuYu <yufuwang1989@126.com>
* Create Date: 2017-09-22
*
* History    :
*------------------------------------------------------------
*
*01, 22Apr17, Wang FuYu, create file.
************************************************************/

#include <string.h>
#include "cover.h"

COVER_INFO cover_info = {0};

/******************************************************************************
* FUNCTION		: print_error()
* AUTHOR		: wangfuyu <yufuwang1989@126.com>
* DESCRIPTION	: print error message.
* INPUT			: error_type
* OUTPUT		: void
* RETURN		: sucessed return 0, else -1.
******************************************************************************/
static int print_error(COVER_ERROR_TYPE error_type)
{
	switch (error_type)
	{
	case ERR_MISSING_ARGS:
		MSG_ERR("Missing argument");
		break;
	case ERR_ARGS_COUNT_MISMATCH:
		MSG_ERR("Argument count mismatch");
		break;
	case ERR_INVALID_CASE:
		MSG_ERR("Invalid case");
		break;
	case ERR_UNEXPECT_OCCURED:
	default:
		MSG_ERR("An unexpected error occurred");
		break;
	}

	return COVER_OK;
}

/******************************************************************************
* FUNCTION		: parse_paras()
* AUTHOR		: wangfuyu <yufuwang1989@126.com>
* DESCRIPTION	: parse input parameters.
* INPUT			: @argc: para nums, @argv: para array
* OUTPUT		: void
* RETURN		: sucessed return 0, else -1.
******************************************************************************/
static int parse_paras(int argc, char *argv[])
{
#ifdef COVER_DEBUG
	int i = 0;
	MSG_LOG("argc is: %d.", argc);
	for (i = 0; i < argc; i++)
	{
		MSG_LOG("arg[%d]: %s", i, argv[i]);
	}
#endif
	
	if (1 == argc)
	{
		print_error(ERR_MISSING_ARGS);
		return COVER_ERR;
	}
	else if (INPUT_PARAS_NUM != argc)
	{
		print_error(ERR_ARGS_COUNT_MISMATCH);
		return COVER_ERR;
	}

	cover_info.w = atoi(argv[1]);
	cover_info.h = atoi(argv[2]);
	cover_info.p[0].x = atoi(argv[3]);
	cover_info.p[0].y = atoi(argv[4]);
	cover_info.p[1].x = atoi(argv[5]);
	cover_info.p[1].y = atoi(argv[6]);

	MSG_LOG("COVER INFO: w[%d], h[%d], (x1[%d], y1[%d]), (x2[%d], y2[%d])",
			cover_info.w, cover_info.h, cover_info.p[0].x, cover_info.p[0].y, 
			cover_info.p[1].x, cover_info.p[1].y);

	if (
		/* w*h: (0, 1600] */
		(cover_info.w <= 0 || cover_info.h <= 0 || (cover_info.w * cover_info.h > RECTANGLE_AREA_MAX))
		/* point not in the rectangle */
		|| (cover_info.p[0].x < 0 || cover_info.p[0].y < 0 || cover_info.p[1].x < 0 || cover_info.p[1].y < 0
		|| cover_info.p[0].x > cover_info.w || cover_info.p[0].y > cover_info.h 
		|| cover_info.p[1].x > cover_info.w || cover_info.p[1].y > cover_info.h)
		)
	{
		print_error(ERR_INVALID_CASE);
		return COVER_ERR;
	}

	return COVER_OK;
}

/******************************************************************************
* FUNCTION		: print_mask()
* AUTHOR		: wangfuyu <yufuwang1989@126.com>
* DESCRIPTION	: print result mask.
* INPUT			: @mask: result, @area: region need to be printed
* OUTPUT		: region's mask
* RETURN		: sucessed return 0, else -1.
******************************************************************************/
static int print_mask(unsigned char mask[], int area)
{
	int i = 0;
	int blocks = 0;
	
	if (NULL == mask || 0 >= area)
	{
		return COVER_ERR;
	}

	blocks = area / 8;
	
	MSG_PRINT("%02x", mask[0]);
	for (i = 1; i < blocks; i++)
	{
		MSG_PRINT(" %02x", mask[i]);
	}
	MSG_PRINT("\n");
	
	return COVER_OK;
}

/******************************************************************************
* FUNCTION		: calculate_mask()
* AUTHOR		: wangfuyu <yufuwang1989@126.com>
* DESCRIPTION	: calculate mask.
* INPUT			: mask
* OUTPUT		: 
* RETURN		: sucessed return 0, else -1.
******************************************************************************/
static int calculate_mask(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int pa_x = 0;
	int pa_y = 0;
	int pb_x = 0;
	int pb_y = 0;
	int area = 0;
	unsigned char mask[RECTANGLE_AREA_MAX] = {0};

	area = cover_info.w * cover_info.h;
	if (0 != area % 8)
	{
		area = ((area / 8) + 1) * 8;
	}
	
	memset(mask, 0, RECTANGLE_AREA_MAX);

	/* (x1, y2) and (x2, y2) is the same point, or can not construct a rectangle. */
	if (cover_info.p[0].x == cover_info.p[1].x || cover_info.p[0].y == cover_info.p[1].y)
	{
		MSG_LOG("(x1, y2) and (x2, y2) is the same point, or can not construct a rectangle.");
		/* output mask */
		print_mask(mask, area);
		return COVER_OK;
	}

	/* 矩形表示方式，规范化，统一采用左上角和右下角顶点表示 */
	if (cover_info.p[0].x < cover_info.p[1].x)
	{
		pa_x = cover_info.p[0].x;
		pb_x = cover_info.p[1].x;
	}
	else
	{
		pa_x = cover_info.p[1].x;
		pb_x = cover_info.p[0].x;
	}

	if (cover_info.p[0].y < cover_info.p[1].y)
	{
		pa_y = cover_info.p[0].y;
		pb_y = cover_info.p[1].y;
	}
	else
	{
		pa_y = cover_info.p[1].y;
		pb_y = cover_info.p[0].y;
	}

	/* 计算mask */
	for (j = pa_y; j < pb_y; j++)
	{
		for (i = pa_x; i < pb_x; i++)
		{
			k = j * cover_info.w + i; /* 方块编号 */
			mask[k / 8] += (1 << (k % 8));
			MSG_LOG("j %d, i %d, k %d, mask[%d]: [%d] %02x", j, i, k, k/8, mask[k/8], mask[k/8]);
		}
	}

	/* output mask */
	print_mask(mask, area);
	
	return COVER_OK;
}

/******************************************************************************
* FUNCTION		: main()
* AUTHOR		: wangfuyu <yufuwang1989@126.com>
* DESCRIPTION	: program entry.
* INPUT			: 
* OUTPUT		: 
* RETURN		: sucessed return 0, else -1.
******************************************************************************/
int main(int argc, char *argv[])
{
	int ret = COVER_ERR;

	/* 解析入参，并做合法性判断 */
	ret = parse_paras(argc, argv);
	if (COVER_OK != ret)
	{
		return COVER_ERR;
	}

	/* 计算图形掩码, 并打印结果 */
	ret = calculate_mask();
	if (COVER_OK != ret)
	{
		return COVER_ERR;
	}

	return COVER_OK;
}
