#include "cover.h"

int print_error(COVER_ERROR_TYPE error_type)
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

	return 0;
}

int main(int argc, char *argv[])
{
	MSG_LOG("argc is: %d.", argc);
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

	
	
	return 0;
}
