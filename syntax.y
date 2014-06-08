%{
#include "stdio.h"
#include "syntax_tree.h"
#include "lex.yy.c"
#include "sys/ioctl.h"
#include "stdlib.h"
#include "stdarg.h"
#include "semantic.h"
#include "hash_table.h"
#include "assert.h"
#include "IR.h"
#include "mips.h"
//global table
InterCodes irtable = NULL;
%}

/*declared types*/
%union {
	int int_value;
	float float_value;
	char *str_value;
	NodePtr node_value;
};

/*declared tokens*/
%token <node_value> INT 
%token <node_value> FLOAT
%token <node_value> ID
%token <node_value> SEMI COMMA ASSIGNOP RELOP
%token <node_value> PLUS MINUS STAR DIV
%token <node_value> AND OR NOT
%token <node_value> DOT
%token <node_value> TYPE
%token <node_value> LP RP LB RB LC RC
%token <node_value> STRUCT RETURN IF ELSE WHILE
//%token <node_value> NEWLINE

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%left NOT UNARY_MINUS
%left LP RP LB RB DOT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%nonassoc LOWER_THAN_error
%nonassoc error

/* declared non-terminals */
%type <node_value> Program ExtDefList ExtDef ExtDecList
%type <node_value> Specifier StructSpecifier OptTag Tag
%type <node_value> VarDec FunDec VarList ParamDec
%type <node_value> CompSt StmtList Stmt 
%type <node_value> DefList Def DecList Dec
%type <node_value> Exp Args

%%

/* high-level definitions */
Program		:	ExtDefList{
				//printf("Program -> ExtDefList\n");
				$$ = create_tree(1, $1);
				set_content(&$$, "Program", @$.first_line);
				root = $$;
			}
		;
ExtDefList	:	ExtDef ExtDefList{
				//printf("ExtDefList -> ExtDef ExtDefList\n");
				$$ = create_tree(2, $1, $2);
				set_content(&$$, "ExtDefList", @$.first_line);
			}
		|	{
				//printf("ExtDefList -> NULL\n");
				$$ = create_tree(1, NULL);
				set_content(&$$, "null", @$.first_line);	
			}
		;
ExtDef		:	Specifier ExtDecList SEMI{
				//printf("ExtDef -> Specifier ExtDecList SEMI\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "ExtDef", @$.first_line);
			}
		|	Specifier SEMI{
				//printf("ExtDef -> Specifier SEMI\n");
				$$ = create_tree(2, $1, $2);
				set_content(&$$, "ExtDef", @$.first_line);
			}
		|	Specifier FunDec CompSt{
				//printf("ExtDef -> Specifier FunDec CompSt\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "ExtDef", @$.first_line);
			}
		|	Specifier FunDec SEMI{
				//printf("ExtDef -> Specifier FunDec CompSt\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "ExtDef", @$.first_line);
			}
		|	error SEMI{}
		;
ExtDecList	:	VarDec{
				//printf("ExtDecList -> VarDec\n");
				$$ = create_tree(1, $1);
				set_content(&$$, "ExtDecList", @$.first_line);
			}
		|	VarDec COMMA ExtDecList{
				//printf("ExtDecList -> VarDec COMMA ExtDecList\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "ExtDecList", @$.first_line);
			}
		;

/* specifiers */
Specifier	:	TYPE{
				//printf("Specifier -> TYPE(%s)\n", $1->content.str_value);
				$$ = create_tree(1, $1);
				set_content(&$$, "Specifier", @$.first_line);
			}
		|	StructSpecifier{
				//printf("Specifier -> StructSpecifier\n");
				$$ = create_tree(1, $1);
				set_content(&$$, "Specifier", @$.first_line);
			}
		;
StructSpecifier	:	STRUCT OptTag LC DefList RC{
				//printf("StructSpecifier -> STRUCT OptTag LC DefList RC\n"); 
				$$ = create_tree(5, $1, $2, $3, $4, $5);
				set_content(&$$, "StructSpecifier", @$.first_line);
			}
		|	STRUCT Tag{
				//printf("StructSpecifier -> STRUCT Tag\n");
				$$ = create_tree(2, $1, $2);
				set_content(&$$, "StructSpecifier", @$.first_line);
			}
		;
OptTag		:	ID{
				//printf("OptTag -> ID(%s)\n", $1->content.str_value);
				$$ = create_tree(1, $1);
				set_content(&$$, "OptTag", @$.first_line);
			}
		|	{
				//printf("OptTag -> NULL\n");
				$$ = create_tree(1, NULL);
				set_content(&$$, "null", @$.first_line);
			}
		;
Tag		:	ID{
				//printf("Tag -> ID(%s)\n", $1->content.str_value);
				$$ = create_tree(1, $1);
				set_content(&$$, "Tag", @$.first_line);
			}
		;

/* declarators */
VarDec		:	ID{
				//printf("VarDec -> ID(%s)\n", $1->content.str_value);
				$$ = create_tree(1, $1);
				set_content(&$$, "VarDec", @$.first_line);
			}
		|	VarDec LB INT RB{
				//printf("VarDec -> VarDec LB INT RB\n");
				$$ = create_tree(4, $1, $2, $3, $4);
				set_content(&$$, "VarDec", @$.first_line);
			}
		;
FunDec		:	ID LP VarList RP{
				//printf("FunDec -> ID LP VarList RP\n");
				$$ = create_tree(4, $1, $2, $3, $4);
				set_content(&$$, "FunDec", @$.first_line);
			}
		|	ID LP RP{
				//printf("FunDec -> ID LP RP\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "FunDec", @$.first_line);
			}
		|	error RP{}
		;
VarList		:	ParamDec COMMA VarList{
				//printf("VarList -> ParamDec COMMA VarList\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "VarList", @$.first_line);
			}
		|	ParamDec{
				//printf("VarList -> ParamDec\n");
				$$ = create_tree(1, $1);
				set_content(&$$, "VarList", @$.first_line);
			}
		;
ParamDec	:	Specifier VarDec{
				//printf("ParamDec -> Specifier VarDec\n");
				$$ = create_tree(2, $1, $2);
				set_content(&$$, "ParamDec", @$.first_line);
			}
		;

/* statements */
CompSt		:	LC DefList StmtList RC{
				//printf("CompSt -> LC DefList StmtList RC\n");
				$$ = create_tree(4, $1, $2, $3, $4);
				set_content(&$$, "CompSt", @$.first_line);
			}
		|	error RC{}
		;
StmtList	:	Stmt StmtList{
				//printf("StmtList -> Stmt StmtList\n");
				$$ = create_tree(2, $1, $2);
				set_content(&$$, "StmtList", @$.first_line);
			}
		|	{
				//printf("StmtList -> NULL\n");
				$$ = create_tree(1, NULL);
				set_content(&$$, "null", @$.first_line);
			}
		;
Stmt		:	Exp SEMI{
				//printf("Stmt -> Exp SEMI\n");
				$$ = create_tree(2, $1, $2);
				set_content(&$$, "Stmt", @$.first_line);
			}
		|	CompSt{
				//printf("Stmt -> CompSt\n");
				$$ = create_tree(1, $1);
				set_content(&$$, "Stmt", @$.first_line);
			}
		|	RETURN Exp SEMI{
				//printf("Stmt -> RETURN Exp SEMI\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Stmt", @$.first_line);
			}
		|	IF LP Exp RP Stmt	%prec LOWER_THAN_ELSE{
				//printf("Stmt -> IF LP Exp RP Stmt\n");
				$$ = create_tree(5, $1, $2, $3, $4, $5);
				set_content(&$$, "Stmt", @$.first_line);
			}
		|	IF LP Exp RP Stmt ELSE Stmt{
				//printf("Stmt -> IF LP Exp RP Stmt ELSE Stmt\n");
				$$ = create_tree(7, $1, $2, $3, $4, $5, $6, $7);
				set_content(&$$, "Stmt", @$.first_line);
			}
		|	WHILE LP Exp RP Stmt{
				//printf("Stmt -> WHILE LP Exp RP Stmt\n");
				$$ = create_tree(5, $1, $2, $3, $4, $5);
				set_content(&$$, "Stmt", @$.first_line);
			}
		|	error SEMI{}
		//|	IF LP error RP Stmt{}
		//|	IF LP error RP Stmt ELSE Stmt{}
		//|	WHILE LP error RP Stmt{}
		;

/* local definitions */
DefList		:	Def DefList{
				//printf("DefList -> Def DefList\n");
				$$ = create_tree(2, $1, $2);
				set_content(&$$, "DefList", @$.first_line);
			}
		|	%prec LOWER_THAN_error{
				//printf("DefList -> NULL\n");
				$$ = create_tree(1, NULL);
				set_content(&$$, "null", @$.first_line);
			}
		;
Def		:	Specifier DecList SEMI{
				//printf("Def -> Specifier DecList SEMI\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Def", @$.first_line);
			}
		|	Specifier error SEMI{}
		;
DecList		:	Dec{
				//printf("DecList -> Dec\n");
				$$ = create_tree(1, $1);
				set_content(&$$, "DecList", @$.first_line);
			}
		|	Dec COMMA DecList{
				//printf("DecList -> Dec COMMA DecList\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "DecList", @$.first_line);
			}
		;
Dec		:	VarDec{
				//printf("Dec -> VarDec\n");
				$$ = create_tree(1, $1);
				set_content(&$$, "Dec", @$.first_line);
			}
		|	VarDec ASSIGNOP Exp{
				//printf("Dec -> VarDec ASSIGNOP Exp\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Dec", @$.first_line);
			}
		;

/* expressions */
Exp		:	Exp ASSIGNOP Exp{
				//printf("Exp -> Exp ASSIGNOP Exp\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	Exp AND Exp{
				//printf("Exp -> Exp AND Exp\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	Exp OR Exp{
				//printf("Exp -> Exp OR Exp\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	Exp RELOP Exp{
				//printf("Exp -> Exp RELOP Exp\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	Exp PLUS Exp{
				//printf("Exp -> Exp PLUS Exp\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	Exp MINUS Exp{
				//printf("Exp -> Exp MINUS Exp\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	Exp STAR Exp{
				//printf("Exp -> Exp STAR Exp\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	Exp DIV	Exp{
				//printf("Exp -> Exp DIV Exp\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	LP Exp RP{
				//printf("Exp -> LP Exp RP\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	MINUS Exp %prec UNARY_MINUS{
				//printf("Exp -> Exp MINUS Exp\n");
				$$ = create_tree(2, $1, $2);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	NOT Exp{
				//printf("Exp -> NOT Exp\n");
				$$ = create_tree(2, $1, $2);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	ID LP Args RP{
				//printf("Exp -> ID LP Args RP\n");
				$$ = create_tree(4, $1, $2, $3, $4);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	ID LP RP{
				//printf("Exp -> ID LP RP\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	Exp LB Exp RB{
				//printf("Exp -> Exp LB Exp RB\n");
				$$ = create_tree(4, $1, $2, $3, $4);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	Exp DOT ID{
				//printf("Exp -> Exp DOT ID\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	ID{
				//printf("Exp -> ID(%s)\n", $1->content.str_value);
				$$ = create_tree(1, $1);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	INT{
				//printf("Exp -> INT(%d)\n", $1->content.int_value);
				$$ = create_tree(1, $1);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	FLOAT{
				//printf("Exp -> FLOAT(%f)\n", $1->content.float_value);
				$$ = create_tree(1, $1);
				set_content(&$$, "Exp", @$.first_line);
			}
		|	LP error RP{}
		|	Exp LB error RB{}
		;
Args		:	Exp COMMA Args{
				//printf("Args -> Exp COMMA Args\n");
				$$ = create_tree(3, $1, $2, $3);
				set_content(&$$, "Args", @$.first_line);
			}
		|	Exp{
				//printf("Args -> Exp\n");
				$$ = create_tree(1, $1);
				set_content(&$$, "Args", @$.first_line);
			}
		;

%%


int gen_ir(NodePtr node , int level){
	InterCodes icode;
	//if(level == 0) printf("------------------------\n");
	if(strcmp(node->content.name, "null") == 0) return 0;
	else if(strcmp(node->content.name, "Exp") == 0){
		icode = translate_Exp(node, NULL);
		irtable = link_ir(irtable, icode);
		return 0;
	}
	else if(strcmp(node->content.name, "Stmt") == 0){
		icode = translate_Stmt(node);
		irtable = link_ir(irtable, icode);
		return 0;
	}
	else if(strcmp(node->content.name, "ExtDef") == 0){
		icode = translate_Extdef(node);
		irtable = link_ir(irtable, icode);
		return 0;
	}
	return 1;
}


int semantic(NodePtr node, int level){
	int num;
	int i;
	NodePtr child;
	TypePtr type = (TypePtr)malloc(sizeof(struct Type_));
	FieldList *list = (FieldList *)malloc(20*sizeof(FieldList));
	//struct_id = 0;

	if(level == 0) printf("------------------------\n");
	//if(node == NULL) return 0;//???
	if(strcmp(node->content.name, "null") == 0) return 0;
	else if(strcmp(node->content.name, "RETURN") == 0){
		//return_handler(node->next_sibling);
		TypePtr type = (TypePtr)malloc(sizeof(struct Type_));
		type = exp_handler(node->next_sibling);
		FieldList fun = hash_get(curr_func);	
		TypePtr returnType = fun->type->u.func.retype;
		if(type_handler(type, returnType) == 0)
			printf("Error Type 8 at line %d: The return type mismatched\n", node->content.lineno);
		//return 0;
	}
	else if(strcmp(node->content.name, "Exp") == 0 && node->first_child->flag != 1){
		type = exp_handler(node->first_child);
		if(type == NULL) 
			return 0;
	}
	else if(strcmp(node->content.name, "Def") == 0){
		num = def_handler(node, list, 0, 0);
		//if(num == 0) return 1;
		for(i=0; i<num; i++){
			if(hash_get(list[i]->name) != NULL){
				printf("Error type 3 at line %d: Redefined variable '%s'\n", node->content.lineno, list[i]->name);
			}
			else
				hash_put(list[i]);
		}
		return 1;
	}
	else if(strcmp(node->content.name, "ExtDef") == 0){
		num = extdef_handler(node, list, 0);
		if(num == 0) return 1;
		for(i=0; i<num; i++){
			if(hash_get(list[i]->name) != NULL){
				printf("Error type 3 at line %d: Redefined variable '%s'\n", node->content.lineno, list[i]->name);
			}
			else
				hash_put(list[i]);
		}
		return 1;
	}
	return 1;
}


//traverse the tree from level(defined depth)
void traverse(int (*func)(NodePtr, int), NodePtr root, int level) {
	//Node is not empty
	if ((*func)(root, level) == 1) {
		if (root->first_child != NULL)
			traverse(func, root->first_child, level+1);
    		if (root->next_sibling != NULL)
			traverse(func, root->next_sibling, level);
	}
	//Node is empty, so has no children
	else {
		if (root->next_sibling != NULL)
			traverse(func, root->next_sibling, level);
	}
}

//create subtree with variable number of arguments
NodePtr create_tree(int num, ...) {
	NodePtr parent = (NodePtr)malloc(sizeof(Node));
	parent->first_child = NULL;
	parent->next_sibling = NULL;
	parent->level = 0;
	parent->content.type = NIL_T;

	NodePtr child, sibling;
	va_list arg_ptr;
	va_start(arg_ptr, num);
	int i;
	for (i=1; i<=num; ++i) {
		child = va_arg(arg_ptr, NodePtr);//node to be inserted
		NodePtr child_tmp;
		NodePtr child_tmp_p;
		if (parent == NULL || child == NULL) return parent;
		child_tmp = parent->first_child;
		//this node does not have children
		if (child_tmp == NULL) {
			parent->first_child = child;
			continue;
		}
		//this node has children, so find a null position to insert
		while (child_tmp != NULL) {
			child_tmp_p = child_tmp;
			child_tmp = child_tmp->next_sibling;
		}
		child_tmp_p->next_sibling = child;
	}
	va_end(arg_ptr);
	return parent;
}

//set the name and lineno of a node
void set_content(NodePtr* ptr, char* name, int lineno) {
	(*ptr)->content.name = name;
	(*ptr)->content.lineno = lineno;
}

//print a node
int print_node(NodePtr node, int level) {
	int i;
	if(level == 0) printf("------------------------\n");
	if(strcmp(node->content.name, "null") == 0) return 0;
	else {
		for(i=0; i<level; ++i) printf("  ");
		printf("%s", node->content.name);
		if(node->content.type == NIL_T)
			printf(" (%d)\n", node->content.lineno);
		else if(node->content.type == STR_T)
			printf(": %s\n", node->content.str_value);
		else if(node->content.type == INT_T)
			printf(": %d\n", node->content.int_value);
		else if(node->content.type == FLOAT_T)
			printf(": %f\n", node->content.float_value);
		else printf("\n");
	}
	return 1;
}

int main(int argc, char** argv) {
	int i;
	curr_func = (char *)malloc(20);
	//int totchars=0, totwords=0, totlines=0;
	if (argc < 2) { /* just read stdin */
		yylex();
	}
	for (i=1; i<argc-1; i++) {
		FILE *f = fopen(argv[i], "r");
		if (!f) {
			perror(argv[i]);
			return 1;
		}
		//FILE *fp2 = fopen(argv[i], "w+");
		yyrestart(f);
		//yylex();
		yyparse();
		fclose(f);
	}
	fp2 = fopen(argv[2], "a+");
	if(error_num == 0) {
		//traverse(&print_node, root, 0);
		add_read_write();
		traverse(&semantic, root, 0);
		declare_handler();
		traverse(&gen_ir, root, 0);
		optimize_ir(&irtable);
		optimize_ir(&irtable);
		output_ir(irtable);
		//output_read_write();
		gen_mips(irtable);
	}
}


yyerror(char* msg){
	error_num++;
	fprintf(stderr, "Error type B at line %d: Syntax error\n", yylineno);
} 
