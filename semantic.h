#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__

#include "syntax_tree.h"

#define INT_TYPE 0
#define FLOAT_TYPE 1
#define OTHER_TYPE 2

typedef struct Type_* TypePtr;
typedef struct FieldList_* FieldList;

struct Type_{
	enum { basic, array, structure, function } kind;
	union{
		// 基本类型
		int basic;
		// 数组类型信息包括元素类型与数组大小构成
		struct { TypePtr elem; int size; } array;
		// 结构体类型信息是一个链表
		FieldList structure;
		// 增加：记录函数信息
		struct {	
			FieldList param;
			TypePtr retype;
			int num;
		} func;
	} u;
};
struct FieldList_{
	int id;
	int flag;
	char* name;	// 域的名字
	TypePtr type;	// 域的类型
	FieldList tail;	// 下一个域
};

//int semantic(NodePtr node, int level);
TypePtr exp_handler(NodePtr node);
//int variable_match(FieldList ls, FieldList rs);
int extdef_handler(NodePtr node, FieldList* list, int tail);
TypePtr specifier_handler(NodePtr node);
TypePtr structspecifier_handler(NodePtr node);
int extdeclist_handler(NodePtr node, TypePtr type, FieldList* list, int tail);
FieldList fundec_handler(NodePtr node);
int varlist_handler(NodePtr node, FieldList *list, int tail);
FieldList paramdec_handler(NodePtr node);
FieldList vardec_handler(NodePtr node, TypePtr type);
int deflist_handler(NodePtr node, FieldList *list, int tail, int flag);
int def_handler(NodePtr node, FieldList *list, int tail, int flag);
int declist_handler(NodePtr node, TypePtr type, FieldList *list, int tail, int flag);
int dec_handler(NodePtr node, TypePtr type, FieldList *list, int tail, int flag);
int param_handler(FieldList list, NodePtr node);
int type_handler(TypePtr type1, TypePtr type2);
void declare_handler();
int leftvalue_handler(NodePtr node);

#endif
