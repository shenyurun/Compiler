#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "hash_table.h"

/*It's important not to choose a prime number that is too close to exact powers of 2.*/
#define HASH_SIZE 103
//#define KEY_SIZE 32

struct _Entry *hashtable[HASH_SIZE];
struct _Entry *dec_func;
char *curr_func;

/* Hashing function P.J.W */
unsigned int hash_pjw(char* name){
	unsigned int val = 0, i;
	for (; *name; ++name){
		val = (val << 2) + *name;
		if (i = val & ~0x3fff) val = (val ^ (i >> 12)) & 0x3fff;
	}
	return val;
}

int hash_put(FieldList value){
	unsigned int key;
	struct _Entry *curr;
	struct _Entry *head;
	if(hashtable == NULL || value == NULL) return 0;
	key = hash_pjw(value->name) % HASH_SIZE;
	curr = (Entry *)malloc(sizeof(Entry));
    	curr->value = value;
	curr->next = NULL;
	if(hashtable[key] == NULL){
		hashtable[key] = curr;
	}
	else{
		head = hashtable[key];
		while(head->next != NULL){
			head = head->next;
		}
		head->next = curr;
	}
    	//size++;
	return 1;
}

FieldList hash_get(char* value){
	unsigned int key;
	struct _Entry *head;
	if(hashtable == NULL || value == NULL) return NULL;
	key = hash_pjw(value) % HASH_SIZE;
	if(hashtable[key] == NULL) return NULL;
	for(head = hashtable[key]; head != NULL; head = head->next){
		if (strcmp(head->value->name, value) == 0) 
			return head->value;
	}
	//Not found
	return NULL;
}

