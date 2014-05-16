#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "semantic.h"
#define HASH_SIZE 103

typedef struct _Entry{
	FieldList value;
	struct _Entry *next;
}Entry;

extern struct _Entry *hashtable[HASH_SIZE];
extern struct _Entry *dec_func;
extern char *curr_func;

unsigned int hash_pjw(char* name);
//int hash_put(Entry **table, FieldList value);
//FieldList hash_get(Entry **table, char* value);
int hash_put(FieldList value);
FieldList hash_get(char* value);

#endif
