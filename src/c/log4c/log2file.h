#ifndef _INCLUDED_LOG2FILE
#define _INCLUDED_LOG2FILE

#include <stdio.h>

extern const char * E_INVALID_ARGUMENT;
extern const char * E_OUT_OF_MEMORY;

#define logi(message)   log2file(NULL, message, __FILE__, __LINE__, stdout)
#define loge(message)   log2file(NULL, message, __FILE__, __LINE__, stderr)

void log2file(const char * category, const char * message,
        const char * filepath, const int fileline, FILE * fp);

#endif // _INCLUDED_LOG2FILE
