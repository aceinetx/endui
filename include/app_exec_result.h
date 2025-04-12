#if !defined(APP_EXEC_RESULT)
#define APP_EXEC_RESULT

#include <stdbool.h>

typedef struct {
	bool success;
	void* handle;
	char* _dlerror;
} app_exec_result;

#endif /* APP_EXEC_RESULT */
