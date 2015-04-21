#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "dbg.h"


int print_a_message(const char *msg)
{
	printf("A STRING: %s\n", msg);
	return 0;
}

int uppercase(const char *msg)
{
	int i = 0;
	int len = strlen(msg);
	
	assert(msg != NULL && "message can't be NULL");
	if(len <= 0) return -1;
	printf("len: %d\n",len);
	// BUG: \0 termination problems
	for(i = 0; i < len; i++)
	{
		printf("%c", toupper(msg[i]));
	}
	
	printf("\n");
	
	return 0;
}

int lowercase(const char *msg)
{
	int i = 0;
	int len = strlen(msg);
	
	assert(msg != NULL && "message can't be NULL");
	if(len <= 0) return -1;
	
	// BUG: \0 termination problems
	for(i = 0; i < len; i++)
	{
		printf("%c", tolower(msg[i]));
	}
	
	printf("\n");
	
	return 0;
}

int fail_on_purpose(const char *msg)
{
	return 1;
}
