#include "stdio.h"
#include "syntax_tree.h"
#include "sys/ioctl.h"
#include "stdlib.h"
#include "stdarg.h"
#include "hash_table.h"
#include "semantic.h"
#include "string.h"

//extern static struct Entry *hashtable[HASHTABLE_SIZE];
//static int hash_size = 0;
static int struct_id = 0;
int var_count = 0;

void add_read_write(){
	FieldList readNode = (FieldList)malloc(sizeof(struct FieldList_));
	readNode->name = malloc(20);
	memcpy(readNode->name, "read", 20);
	readNode->type = (TypePtr)malloc(sizeof(struct Type_));
	readNode->type->kind = function;
	readNode->type->u.func.retype = (TypePtr)malloc(sizeof(struct Type_));
	readNode->type->u.func.retype->kind = basic;
	readNode->type->u.func.retype->u.basic = 0;
	readNode->type->u.func.num = 0;
	readNode->type->u.func.param = NULL;
	readNode->tail = NULL; 
	hash_put(readNode);

	FieldList writeNode = (FieldList)malloc(sizeof(struct FieldList_));
	writeNode->name = malloc(20);
	memcpy(writeNode->name, "write", 20);
	writeNode->type = (TypePtr)malloc(sizeof(struct Type_));
	writeNode->type->kind = function;
	writeNode->type->u.func.retype = (TypePtr)malloc(sizeof(struct Type_));
	writeNode->type->u.func.retype->kind = basic;
	writeNode->type->u.func.retype->u.basic = 0;
	writeNode->type->u.func.num = 1;
	writeNode->type->u.func.param = (FieldList)malloc(sizeof(struct FieldList_));
	writeNode->type->u.func.param->name = malloc(20);
	memcpy(writeNode->type->u.func.param->name, "wtemp", 20);
	writeNode->type->u.func.param->type = (TypePtr)malloc(sizeof(struct Type_));
	writeNode->type->u.func.param->type->kind = basic;
	writeNode->type->u.func.param->type->u.basic = 0;
	writeNode->type->u.func.param->tail = NULL;
	writeNode->tail = NULL;  
	hash_put(writeNode);
}

TypePtr exp_handler(NodePtr node){
	//NodePtr child = node->first_child;
	node->flag = 1;
	TypePtr sType = (TypePtr)malloc(sizeof(struct Type_));
	if(strcmp(node->content.name, "INT") == 0){
		sType->kind = basic;
		sType->u.basic = 0;
		return sType;
	}
	if(strcmp(node->content.name, "FLOAT") == 0){
		sType->kind = basic;
		sType->u.basic = 1;
		return sType;
	}
	if(strcmp(node->content.name, "ID") == 0 && node->next_sibling == NULL){
		FieldList fun = hash_get(node->content.str_value);
		if(fun == NULL){
			printf("Error type 1 at line %d: Undefined variable '%s'\n",node->content.lineno,node->content.str_value);
			//node->flag = 1;
			return NULL;
		}
		if(fun->type->kind != function){
			if(fun->type->kind == basic){
				sType->kind = basic;
				sType->u.basic = fun->type->u.basic;
			}
			else if(fun->type->kind == array){
				sType->kind = array;
				sType->u.array = fun->type->u.array;
			}
			else{
				sType->kind = structure;
				sType->u.structure = fun->type->u.structure;
			}
		}
		else{
			sType->kind = fun->type->u.func.retype->kind;
			if(fun->type->u.func.retype->kind == basic) {
				sType->kind = basic;
				sType->u.basic = fun->type->u.func.retype->u.basic;
			}
			else if (fun->type->u.func.retype->kind == array ) {
				sType->kind = array;
				sType->u.array = fun->type->u.func.retype->u.array;
			}
			else{
				sType->kind = structure;
				sType->u.structure = fun->type->u.func.retype->u.structure;
			}
		}
		return sType;
	}
	if(strcmp(node->content.name, "ID") == 0 && node->next_sibling != NULL){
		FieldList fun = hash_get(node->content.str_value);
		Entry *tmp_fun = dec_func;
		if(fun == NULL){
			while(tmp_fun != NULL){
				if(strcmp(tmp_fun->value->name, node->content.str_value) == 0)
					break;
				tmp_fun = tmp_fun->next;
			}
			if(tmp_fun == NULL){
				printf("Error type 2 at line %d: Undefined function '%s'\n",node->content.lineno,node->content.str_value);
				return NULL;
			}
			//return NULL;
			fun = tmp_fun->value;
		}
		if(fun->type->kind != function){
			printf("Error type 11 at line %d: '%s' must be a function\n",node->content.lineno,node->content.str_value);
			return NULL;
		}
		if(fun->type->u.func.param == NULL && strcmp(node->next_sibling->next_sibling->content.name, "RP") == 0){
			sType->kind = fun->type->u.func.retype->kind;
			if(fun->type->u.func.retype->kind == basic) {
				sType->kind = basic;
				sType->u.basic = fun->type->u.func.retype->u.basic;
			}
			else if (fun->type->u.func.retype->kind == array ) {
				sType->kind = array;
				sType->u.array = fun->type->u.func.retype->u.array;
			}
			else{
				sType->kind = structure;
				sType->u.structure = fun->type->u.func.retype->u.structure;
			}
			return sType;
		}
		if(fun->type->u.func.param == NULL && strcmp(node->next_sibling->next_sibling->content.name, "RP") != 0){
			printf("Error Type 9 at line %d: The method '%s' is not applicable for the arguments\n", 
				node->content.lineno, fun->name);
			//return NULL;
		}
		else if(fun->type->u.func.param != NULL && strcmp(node->next_sibling->next_sibling->content.name, "RP") == 0){
			printf("Error Type 9 at line %d: The method '%s' is not applicable for the arguments\n", 
				node->content.lineno, fun->name);
			//return NULL;
		}
		else if(param_handler(fun->type->u.func.param, node->next_sibling->next_sibling) == 0 ){
			printf("Error Type 9 at line %d: The method '%s' is not applicable for the arguments\n", 
				node->content.lineno, fun->name);
			//return NULL;
		}
		sType->kind = fun->type->u.func.retype->kind;
		if(fun->type->u.func.retype->kind == basic) {
			sType->kind = basic;
			sType->u.basic = fun->type->u.func.retype->u.basic;
		}
		else if (fun->type->u.func.retype->kind == array ) {
			sType->kind = array;
			sType->u.array = fun->type->u.func.retype->u.array;
		}
		else{
			sType->kind = structure;
			sType->u.structure = fun->type->u.func.retype->u.structure;
		}
		return sType;
        }
	if(strcmp(node->content.name, "LP") == 0 || strcmp(node->content.name, "MINUS") == 0 || strcmp(node->content.name, "NOT") == 0){
		sType = exp_handler(node->next_sibling);
		return sType;
	}
	if(strcmp(node->content.name, "Exp" ) == 0){
		if(node->next_sibling != NULL && strcmp(node->next_sibling->content.name, "ASSIGNOP") == 0){
			if(leftvalue_handler(node) != 1){
				printf("Error Type 6 at line %d: The left-hand side of an assignment must be a variable\n", 
					node->content.lineno);
				//return NULL;
			}
			TypePtr firstType = (TypePtr)malloc(sizeof(struct Type_));
			TypePtr thirdType = (TypePtr)malloc(sizeof(struct Type_));
			firstType = exp_handler(node->first_child);
			thirdType = exp_handler(node->next_sibling->next_sibling->first_child);
			if(firstType == NULL || thirdType == NULL) return NULL;
			if(type_handler(firstType, thirdType) == 0){
				printf("Error Type 5 at line %d: Type mismatched\n", node->content.lineno);
				//return NULL;
			}
			return NULL;
		}
		if(node->next_sibling != NULL && strcmp(node->next_sibling->content.name, "DOT") == 0){
			TypePtr firstType = (TypePtr)malloc(sizeof(struct Type_));
			firstType = exp_handler(node->first_child);
			if(firstType != NULL){
				if(firstType->kind != structure){
					printf("Error Type 13 at line %d: Illegal use of '.'\n", node->content.lineno);
					return NULL;
				}
				FieldList tmp = firstType->u.structure;
				while(tmp != NULL){
					if(strcmp(tmp->name, node->next_sibling->next_sibling->content.str_value) == 0)
						break;
					tmp = tmp->tail;
				}
				if(tmp == NULL){
					printf("Error type 14 at line %d: Un-existed field '%s'\n", 
						node->content.lineno, node->next_sibling->next_sibling->content.str_value);
					return NULL;
				}
				return exp_handler(node->next_sibling->next_sibling);
			}
			return NULL;
		}
		if(node->next_sibling != NULL &&(strcmp(node->next_sibling->content.name, "RELOP") == 0 ||
						strcmp(node->next_sibling->content.name, "PLUS") == 0 ||
						strcmp(node->next_sibling->content.name, "MINUS") == 0 ||
						strcmp(node->next_sibling->content.name, "STAR") == 0 ||
						strcmp(node->next_sibling->content.name, "DIV") == 0 )){
			TypePtr firstType = (TypePtr)malloc(sizeof(struct Type_));
			TypePtr thirdType = (TypePtr)malloc(sizeof(struct Type_));
			firstType = exp_handler(node->first_child);
			thirdType = exp_handler(node->next_sibling->next_sibling->first_child);
			if(type_handler(firstType, thirdType) == 0){
				printf("Error Type 7 at line %d: Operands type mismatched\n", node->content.lineno);
				return NULL;
			}
			if(strcmp(node->next_sibling->content.name, "RELOP") == 0){
				sType->kind = basic;
				sType->u.basic = 0;
				return sType;
			}
			//return sType;
		}
		if(node->next_sibling != NULL && (strcmp(node->next_sibling->content.name, "AND") == 0 || 
						strcmp(node->next_sibling->content.name, "OR") == 0)){
			TypePtr firstType = (TypePtr)malloc(sizeof(struct Type_));
			TypePtr thirdType = (TypePtr)malloc(sizeof(struct Type_));
			firstType = exp_handler(node->first_child);
			thirdType = exp_handler(node->next_sibling->next_sibling->first_child);
			if(firstType->kind != basic || thirdType->kind != basic || firstType->u.basic != 0 || thirdType->u.basic != 0){
				printf("Error Type 7 at line %d: Operands type mismatched\n", node->content.lineno);
				return NULL;
			}
			sType->kind = basic;
			sType->u.basic = 0;
			return sType;
		}
		if(node->next_sibling != NULL && (strcmp(node->next_sibling->content.name, "LB") == 0)){
			TypePtr firstType = (TypePtr)malloc(sizeof(struct Type_));
			TypePtr thirdType = (TypePtr)malloc(sizeof(struct Type_));
			firstType = exp_handler(node->first_child);
			thirdType = exp_handler(node->next_sibling->next_sibling->first_child);
			if(firstType != NULL && thirdType != NULL){
				if(firstType->kind != array){
					printf("Error Type 10 at line %d: '%s'must be an array\n", 
						node->content.lineno, node->first_child->content.str_value);
					return NULL;
				}
				else{
					if(thirdType->kind != basic || thirdType->u.basic != 0){
						printf("Error Type 12 at line %d: Operands type mistaken\n", node->content.lineno);
						return NULL;
					}
					else {
						sType->kind = firstType->u.array.elem->kind;
						if(sType->kind == basic)
							sType->u.basic = firstType->u.array.elem->u.basic;
						else if (sType->kind == array)
							sType->u.array = firstType->u.array.elem->u.array;
						else
							sType->u.structure = firstType->u.array.elem->u.structure;
					}
				}
			}
			return sType;
		}
		sType = exp_handler(node->first_child);
		return sType;
	}
	return NULL;
}

int extdef_handler(NodePtr node, FieldList* list, int tail){
	//node->flag = 1;
	NodePtr child;
	TypePtr type;
	child = node->first_child;
	type = specifier_handler(child);
	child = child->next_sibling;
	if(strcmp(child->content.name, "ExtDecList") == 0) {
		return extdeclist_handler(child, type, list, tail);
	}
	else if(strcmp(child->content.name, "SEMI") == 0) 
		return 0;
	else if(strcmp(child->content.name, "FunDec") == 0){
		if(strcmp(child->next_sibling->content.name, "CompSt") == 0){
			FieldList new_list;
 			new_list = fundec_handler(child);
			new_list->type->u.func.retype = type;
			if(hash_get(new_list->name) != NULL){
				//if(hash_get(new_list->name)->type->kind != declare){
				printf("Error type 4 at line %d: Redefined function '%s'\n", child->content.lineno, new_list->name);
				return 0;
				//}
			}
			hash_put(new_list);
			//deflist_handler(child->next_sibling->first_child, list, 0, 0);
			return 0;
		}
		else{
			Entry *func = (Entry *)malloc(sizeof(Entry));;
			FieldList dec_list = (FieldList)malloc(sizeof(struct FieldList_));
			dec_list = fundec_handler(child);
			dec_list->type->u.func.retype = type;
			Entry *tmp_func = dec_func;
			while(tmp_func != NULL && dec_list != NULL){
				if(strcmp(tmp_func->value->name, dec_list->name) == 0){
					FieldList tmp1 = dec_list->type->u.func.param;
					FieldList tmp2 = tmp_func->value->type->u.func.param;
					if(type_handler(dec_list->type->u.func.retype, tmp_func->value->type->u.func.retype) != 1){
						printf("Error type 19 at line %d: Inconsistent declaration of function '%s'\n", 
							child->content.lineno, dec_list->name);
						return 0;
					}
					else if(tmp1 == NULL && tmp2 == NULL);
					else if(tmp1 == NULL || tmp2 == NULL){
						printf("Error type 19 at line %d: Inconsistent declaration of function '%s'\n", 
							child->content.lineno, dec_list->name);
						return 0;
					}
					else{
						while(tmp1 != NULL && tmp2 != NULL){
							if(type_handler(tmp1->type,tmp2->type)!=1){
								break;
							}
							tmp1 = tmp1->tail;
							tmp2 = tmp2->tail;
						}
						if(tmp1 != NULL || tmp2 != NULL){
							printf("Error type 19 at line %d: Inconsistent declaration of function '%s'\n", 
								child->content.lineno, dec_list->name);
							return 0;
						}
					}
				}
				tmp_func = tmp_func->next;
				
			}
			if(tmp_func == NULL){
				dec_list->type->u.func.retype = type;
				//dec_list->type->kind = declare;
				dec_list->type->u.func.num = child->content.lineno;
				func->value = dec_list;
				//hash_put(dec_list);
				if(dec_func == NULL){
					func->next = NULL;
					dec_func = func;
				}
				else{
					func->next = dec_func;
					dec_func = func;
				}
				return 0;
			}
		}
	}
	else{
		printf("Wrong with ExtDef\n");
		exit(-1);
	}
}

TypePtr specifier_handler(NodePtr node){
	NodePtr child = node->first_child;
	TypePtr type;
	char *name = (char *)malloc(sizeof(char));
	if(strcmp(child->content.name, "TYPE") == 0) {
		type = (TypePtr)malloc(sizeof(struct Type_));
		type->kind = basic;
		//name = child->content.str_value;
		strcpy(name, child->content.str_value);
		if (strcmp(name, "int") == 0)
			type->u.basic = INT_TYPE;
		else if (strcmp(name, "float") == 0)
			type->u.basic = FLOAT_TYPE;
		else 
			type->u.basic = OTHER_TYPE;
        	return type;
	}
	else if(strcmp(child->content.name, "StructSpecifier") == 0){
		//if(child->flag != 1)
			return structspecifier_handler(child);
		//return;
	}
	else{
		printf("Wrong with Specifier\n");
		exit(-1);
	}
}

TypePtr structspecifier_handler(NodePtr node){
	NodePtr child = node->first_child;
	if(strcmp(child->next_sibling->content.name, "OptTag") == 0 || strcmp(child->next_sibling->content.name, "null") == 0){
		FieldList struct_node = (FieldList)malloc(sizeof(struct FieldList_));
		FieldList *list = (FieldList *)malloc(20 * sizeof(FieldList));
		TypePtr type = (TypePtr)malloc(sizeof(struct Type_));
		int num = deflist_handler(child->next_sibling->next_sibling->next_sibling, list, 0, 1);
		type->kind = structure;
		type->u.structure = list[0];
		struct_node->type = type;
		FieldList curr_node = type->u.structure;
		int i;
		for (i=1; i < num; ++i) {
			curr_node->tail = list[i];
			curr_node = curr_node->tail;
		}
		if(node->flag != 1){
			struct_node->name = (char *)malloc(20);
			if (child->next_sibling->first_child != NULL)
				strcpy(struct_node->name, child->next_sibling->first_child->content.str_value);
			else
				//strcpy(struct_node->name, (char *)struct_id+1);
				sprintf(struct_node->name, "%d", ++struct_id);
			if(hash_get(struct_node->name) != NULL){
				printf("Error type 16 at line %d: Duplicated name '%s'\n", child->content.lineno, struct_node->name);
				return NULL;
			}
			struct_node->tail = NULL;		
			node->flag = 1;
        		hash_put(struct_node);
		}
		//struct_node->tail = NULL;
        	return struct_node->type;
	}
	else if(strcmp(child->next_sibling->content.name, "Tag") == 0){
		char *struct_name = (char *)malloc(20);
		strcpy(struct_name, child->next_sibling->first_child->content.str_value);
        	FieldList struct_node = (FieldList)malloc(sizeof(struct FieldList_));
		struct_node = hash_get(struct_name);
        	if(struct_node == NULL){
			if(child->next_sibling->first_child->flag != 1){
				printf("Error type 17 at line %d: Undefined struct '%s'\n", child->content.lineno, struct_name);
				child->next_sibling->first_child->flag = 1;
			}
			return NULL;
		}
        	return struct_node->type;
	}
	/*else {
		printf("Wrong with StructSpecifier\n");
		exit(-1);
	}*/
}

int extdeclist_handler(NodePtr node, TypePtr type, FieldList* list, int tail){
    	FieldList vardec;
	NodePtr child = node->first_child;
	if (strcmp(child->content.name, "VarDec") == 0) {
		vardec = vardec_handler(child, type);
		list[tail] = vardec;
		if(child->next_sibling == NULL)
        		return tail + 1;
		else
			//extdeclist_handler
        		return extdeclist_handler(child->next_sibling, type, list, tail + 1);
    	}
	else{
		printf("Wrong with ExtDecList\n");
		exit(-1);
	}
}

FieldList fundec_handler(NodePtr node){
	int num, i;
	FieldList fundec;
	FieldList* varlist;
	NodePtr child = node->first_child;
	fundec = (FieldList)malloc(sizeof(struct FieldList_));
	fundec->name = (char *)malloc(20); 
	fundec->type = (TypePtr)malloc(sizeof(struct Type_));
	strcpy(fundec->name, child->content.str_value);
	fundec->type->kind = function;
	fundec->tail = NULL;
	if(strcmp(child->next_sibling->next_sibling->content.name, "VarList") == 0){
		varlist = (FieldList *)malloc(sizeof(FieldList));
		num = varlist_handler(child->next_sibling->next_sibling, varlist, 0);
		fundec->type->u.func.param = varlist[0];
        	FieldList curr_param = fundec->type->u.func.param;
		for(i=0; i<num; ++i){
			if(varlist[i]->type->kind == structure || varlist[i]->type->kind == array){
				//printf("param %s's flag = 1\n", varlist[i]->name);
				varlist[i]->flag = 1;
			}
			hash_put(varlist[i]);
		}
            	for(i=1; i<num; ++i){
                	curr_param->tail = varlist[i];
                	curr_param = curr_param->tail;
            	}
	}
	else if(strcmp(child->next_sibling->next_sibling->content.name, "RP") == 0){
		fundec->type->u.func.param = NULL;
	}
	else{
		printf("Wrong with FunDec\n");
		exit(-1);
	}
	curr_func = fundec->name;
	return fundec;
}

int varlist_handler(NodePtr node, FieldList *list, int tail){
	NodePtr child = node->first_child;
	FieldList var;
	var = paramdec_handler(child);
	list[tail] = var;
	if(child->next_sibling == NULL)
		return tail+1;
	else if(strcmp(child->next_sibling->content.name, "COMMA") == 0)
		//varlist_handler
		return varlist_handler(child->next_sibling->next_sibling, list, tail+1);
	else{
		printf("Wrong with VarList\n");
		exit(-1);
	}
}

FieldList paramdec_handler(NodePtr node){
	TypePtr type;
	NodePtr child = node->first_child;
	if(strcmp(child->content.name, "Specifier") == 0){
		type = specifier_handler(child);
		return vardec_handler(child->next_sibling, type);
	}
	else {
		printf("Wrong with ParamDec\n");
		exit(-1);
	}
}

FieldList vardec_handler(NodePtr node, TypePtr type){
	NodePtr child = node->first_child;
	FieldList vardec;
	if(strcmp(child->content.name, "ID") == 0){
		vardec = (FieldList)malloc(sizeof(struct FieldList_));
		vardec->name = child->content.str_value;
		vardec->type = type;
		vardec->id = ++var_count;
		vardec->tail = NULL;
		return vardec;
	}
	else if(strcmp(child->content.name, "VarDec") == 0){
		//vardec_handler
		vardec = vardec_handler(child, type);
		TypePtr tmp_type = vardec->type;
		TypePtr new_type = (TypePtr)malloc(sizeof(struct Type_));
		new_type->kind = array;
		new_type->u.array.size = child->next_sibling->next_sibling->content.int_value;
		if (type->kind == basic || type->kind == structure) {
			new_type->u.array.elem = vardec->type;
			vardec->type = new_type;
		}
		else if (type->kind == array) {
			while ((vardec->type->u.array.elem)->kind == array)
				vardec->type = vardec->type->u.array.elem;
			new_type->u.array.elem = vardec->type;
			vardec->type = new_type;
		}
		return vardec;    
	}
	else {
		printf("Wrong with VarDec\n");
		exit(-1);
	}
}

int deflist_handler(NodePtr node, FieldList *list, int tail, int flag){
	int num;
	//if deflist is null
	if (node->first_child == NULL) return tail;
	else{
		NodePtr child = node->first_child;
		if (strcmp(child->content.name, "Def") == 0){
			num = def_handler(child, list, tail, flag);
			num = deflist_handler(child->next_sibling, list, num, flag);
			return num;
		}
		else {
			printf("Wrong with DefList\n");
			exit(-1);
		}
	}
}

int def_handler(NodePtr node, FieldList *list, int tail, int flag){
	//node->flag = 1;
	NodePtr child = node->first_child;
	if(strcmp(child->content.name, "Specifier") == 0){
		TypePtr type = specifier_handler(child);
		return declist_handler(child->next_sibling, type, list, tail, flag);
	}
	else{
		printf("Wrong with VarDec\n");
		exit(-1);
	}
}

int declist_handler(NodePtr node, TypePtr type, FieldList *list, int tail, int flag){
	NodePtr child = node->first_child;
	if(child->next_sibling == NULL){   
		return dec_handler(child, type, list, tail, flag);
	}
	else if(strcmp(child->next_sibling->content.name, "COMMA") == 0){  
		tail = dec_handler(child, type, list, tail, flag);
		//declist_handler
		return declist_handler(child->next_sibling->next_sibling, type, list, tail, flag);
	}
	else{
		printf("Wrong with DecList\n");
		exit(-1);
	}
}

int dec_handler(NodePtr node, TypePtr type, FieldList *list, int tail, int flag){
	NodePtr child = node->first_child;
	if(flag == 1){
		if(child->next_sibling != NULL){
		//if(strcmp(child->next_sibling->content.name, "ASSIGNOP") == 0){
			printf("Error type 15 at line %d: Cannot assign variables in structure\n", child->content.lineno);
			return tail;
		}
	}
	FieldList dec = vardec_handler(child, type);
	if(flag == 1){
		int i;
		for(i=0; i<tail; i++){
			if(strcmp(list[i]->name, dec->name) == 0){
				printf("Error type 15 at line %d: Redefined field '%s'\n", child->content.lineno, list[i]->name);
				return tail;
			}
		}
	}
	if(child->next_sibling != NULL && child->next_sibling->next_sibling != NULL){
		TypePtr exp_type = exp_handler(child->next_sibling->next_sibling);
		if(type_handler(dec->type, exp_type) != 1){
			printf("Error Type 5 at line %d: Type mismatched\n", node->content.lineno);
		}
	}
	list[tail] = dec;
	return tail+1; 
}

int param_handler(FieldList list, NodePtr node){
	FieldList plist = list;
	NodePtr pnode = node;
	if(plist == NULL && pnode == NULL) return 1;
	if(plist != NULL && pnode != NULL ){
		TypePtr param = plist->type;
		TypePtr expType = (TypePtr)malloc(sizeof(struct Type_));
		expType = exp_handler(pnode->first_child);
		if(type_handler(param, expType) == 1){
			plist = plist->tail;
			if(pnode->first_child->next_sibling == NULL)
				pnode = NULL;
			else
				pnode = pnode->first_child->next_sibling->next_sibling;
			return param_handler(plist, pnode);
		}
		else {
			return 0;
		}
	}
	return 0;
}

int type_handler(TypePtr type1, TypePtr type2){
	if(type1 == NULL || type2 == NULL) return 0;
	if(type1->kind != type2->kind) return 0;
	if(type1->kind == basic){
		if(type1->u.basic == type2->u.basic) return 1;
		else return 0;
	}
	if(type1->kind == array){
		return type_handler(type1->u.array.elem, type2->u.array.elem);
	}
	if(type1->kind == structure){
		if(strcmp(type1->u.structure->name, type2->u.structure->name) == 0) return 1;
		else return 0;
	}
	return 1;
}

void declare_handler(){
	while(dec_func != NULL){
		if(hash_get(dec_func->value->name) == NULL){
			printf("Error type 18 at line %d: Undefined function '%s'\n", 
				dec_func->value->type->u.func.num, dec_func->value->name);
			//return;
		}
		else{
			FieldList fun = hash_get(dec_func->value->name);
			FieldList tmp1 = fun->type->u.func.param;
			FieldList tmp2 = dec_func->value->type->u.func.param;
			if(type_handler(fun->type->u.func.retype, dec_func->value->type->u.func.retype) != 1){
				printf("Error type 19 at line %d: Inconsistent declaration of function '%s'\n", 
					dec_func->value->type->u.func.num, dec_func->value->name);
				//return;
			}
			else if(tmp1 == NULL && tmp2 == NULL);
			else if(tmp1 == NULL || tmp2 == NULL){
				printf("Error type 19 at line %d: Inconsistent declaration of function '%s'\n", 
					dec_func->value->type->u.func.num, dec_func->value->name);
				//return;
			}
			else{
				while(tmp1 != NULL && tmp2 != NULL){
					//if(strcmp(tmp1->name, tmp2->name) != 0 || type_handler(tmp1->type,tmp2->type) != 1){
					if(type_handler(tmp1->type,tmp2->type) != 1){
						break;
					}
					tmp1 = tmp1->tail;
					tmp2 = tmp2->tail;
				}
				if(tmp1 != NULL || tmp2 != NULL){
					printf("Error type 19 at line %d: Inconsistent declaration of function '%s'\n", 
						dec_func->value->type->u.func.num, dec_func->value->name);
				}
			}
		}
		dec_func = dec_func->next;
	}
}

int leftvalue_handler(NodePtr node){
	NodePtr child = node->first_child;
	if(strcmp(child->content.name, "ID") == 0 && child->next_sibling == NULL)
		return 1;
	if(strcmp(child->content.name, "Exp") == 0){
		if(strcmp(child->next_sibling->content.name, "LB") == 0 || strcmp(child->next_sibling->content.name, "DOT") == 0)
			return 1;
	}
	return 0;
}
