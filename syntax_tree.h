#ifndef __SYNTAXTREE_H__
#define __SYNTAXTREE_H__


typedef enum Type {
	NIL_T, RES_T, STR_T, INT_T, FLOAT_T
}Type;


typedef struct Content {
	char* name;
	Type type;
	int lineno;
	union {
		int int_value;
		float float_value;
		char* str_value;
	};
}Content;

struct TreeNode {
	Content content;
	unsigned int level;
	int flag;
	struct TreeNode *first_child, *next_sibling;
};

typedef struct TreeNode Node;
typedef struct TreeNode* NodePtr;

NodePtr root;

void traverse(int (*func)(NodePtr, int), NodePtr root, int level);
NodePtr create_tree(int num, ...);
void set_content(NodePtr* ptr, char* name, int lineno);
int print_node(NodePtr node, int level);

#endif
