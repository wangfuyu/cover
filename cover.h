/***********************************************************
*
* Copyright (C), 2013-2017, wangfuyu 
* All rights reserved.
*
* File name  : cover.h
* Version    : 1.0
* Description: header for cover
*
* Author     : Wang FuYu <yufuwang1989@126.com>
* Create Date: 2017-09-22
*
* History    :
*------------------------------------------------------------
*
*01, 22Apr17, Wang FuYu, create file.
************************************************************/

#ifndef __COVER_H__
#define __COVER_H__

#include <stdio.h>

/* 根据题目要求，输入参数限制为6个，且w*h在(0, 1600]范围 */
#define INPUT_PARAS_NUM		7
#define RECTANGLE_AREA_MAX	1600

#define COVER_OK	0
#define COVER_ERR	-1

/* 错误类型枚举 */
typedef enum
{
    ERR_MISSING_ARGS = 0,
    ERR_ARGS_COUNT_MISMATCH = 1,
    ERR_INVALID_CASE = 2,
    ERR_UNEXPECT_OCCURED = 3,
    __ERROR_TYPE_MAX
} COVER_ERROR_TYPE;

/* 坐标采用(x, y)表示 */
typedef struct
{
	int x;
	int y;
} RECT_POINT;

/* 遮挡参数信息 */
typedef struct 
{
	int w;           /* width */
	int h;           /* height */
	RECT_POINT p[2]; /* topper left and lower right point */ 
} COVER_INFO;

//#define COVER_DEBUG 1
#ifdef COVER_DEBUG
#define MSG_LOG(...) do { \
	printf("Function is:%s, Line is:%d.", __FUNCTION__, __LINE__); \
	printf(__VA_ARGS__); \
	printf("\n"); \
} while(0)

#define MSG_ERR(...) do { \
	printf("Function is:%s, Line is:%d.", __FUNCTION__, __LINE__); \
	printf(__VA_ARGS__); \
	printf("\n"); \
} while(0)
#else
#define MSG_LOG(...)
#define MSG_ERR(...) do { \
	printf(__VA_ARGS__); \
	printf("\n"); \
} while(0)
#endif

#define MSG_PRINT printf

#endif
