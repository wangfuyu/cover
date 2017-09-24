#ifndef __COVER_H__
#define __COVER_H__

#include <stdio.h>

#define INPUT_PARAS_NUM 7

#define COVER_OK	0
#define COVER_ERR	-1

typedef enum
{
    ERR_MISSING_ARGS = 0,
    ERR_ARGS_COUNT_MISMATCH = 1,
    ERR_INVALID_CASE = 2,
    ERR_UNEXPECT_OCCURED = 3,
    __ERROR_TYPE_MAX
} COVER_ERROR_TYPE;

#define COVER_DEBUG 1
#ifdef COVER_DEBUG
#define MSG_LOG(...) do { \
	printf("Function is:%s, Line is:%d.", __FUNCTION__, __LINE__); \
	printf(__VA_ARGS__); \
	printf("\n"); \
} while(0)

#else
#define MSG_LOG(...)
#endif

#define MSG_ERR(...) do { \
	printf("Function is:%s, Line is:%d.", __FUNCTION__, __LINE__); \
	printf(__VA_ARGS__); \
	printf("\n"); \
} while(0)

#define CHECK_NULL_P(x) \
    do { \
		if (NULL == (x)) \
		{ \
	        CLOUD_MSG_ERR("line: %d, NULL porinter: %s\n", __LINE__, #x); \
	        return -1; \
		} \
    }while(0)


#define FREE_P(x) \
    do { \
        if (NULL != (x)) \
		{ \
            free(x); \
            (x) = NULL; \
        } \
    } while(0)

#endif
