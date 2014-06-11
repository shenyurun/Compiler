#ifndef __IR_H__
#define __IR_H__

#include "syntax_tree.h"
#include "semantic.h"
#include "stdio.h"

typedef enum { IR_ASSIGN, IR_ADD, IR_SUB, IR_MUL, IR_DIV, IR_LABEL, IR_RETURN, IR_GOTO, IR_CALL, 
		IR_DEC, IR_ARG, IR_RELOP, IR_READ, IR_WRITE, IR_FUNCTION, IR_PARAM } IrType;
typedef enum { OP_VARIABLE, OP_TEMP, OP_CONSTANT, OP_REFERENCE, OP_ADDRESS, OP_LABEL, OP_FUNCTION, OP_PARAM } OpType;
typedef enum { EQ, NE, MT, LT, ME, LE } RelType;

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct InterCodes_* InterCodes;

struct Operand_ {
	OpType kind;
	int flag;
	int toload;//for lab4
	//int tostore;
	union {
		int var_no;
		int value;
		int temp_no;
		int label_no;
		int addr_no;
		char *func_name;
		char *param_name;		
	} u;
};

struct InterCode_ {
	IrType kind;
	union {
		struct { Operand right, left; } assign;
		struct { Operand result, op1, op2; } binop;
		struct { Operand op; } uniop;
		struct { Operand label, relop1, relop2; RelType reltype; } cond;
	} u;
};

struct InterCodes_ { 
	InterCode code; 
	struct InterCodes_ *prev, *next; 
};

//output
void output_operand(Operand op);
void output_reltype(RelType type);
void output_assign(InterCode code);
void output_add(InterCode code);
void output_sub(InterCode code);
void output_mul(InterCode code);
void output_div(InterCode code);
void output_label(InterCode code);
void output_return(InterCode code);
void output_goto(InterCode code);
void output_call(InterCode code);
void output_dec(InterCode code);
void output_arg(InterCode code);
void output_relop(InterCode code);
void output_read(InterCode code);
void output_write(InterCode code);
void output_function(InterCode code);
void output_param(InterCode code);
void output_ir(InterCodes ir);

//generate
Operand new_variable(int id);
Operand new_temp();
Operand new_temp_id(int id);
Operand new_constant(int value);
Operand new_reference(int id);
Operand new_label();
Operand new_function(char *func_name);
Operand new_param(char *param_name);
InterCodes gen_assign(IrType kind, Operand left, Operand right);
InterCodes gen_binop(IrType kind, Operand result, Operand op1, Operand op2);
InterCodes gen_uniop(IrType kind, Operand op);
InterCodes gen_cond(RelType type, Operand label, Operand op1, Operand op2);

//translate
InterCodes translate_Exp(NodePtr node, Operand place);
InterCodes translate_Stmt(NodePtr node);
InterCodes translate_Cond(NodePtr node, Operand label_true, Operand label_false);
InterCodes translate_Compst(NodePtr node);
InterCodes translate_Stmtlist(NodePtr node);
InterCodes translate_Args(NodePtr node, Operand *arg_list, int *arg_num);
InterCodes translate_Extdef(NodePtr node);
InterCodes translate_Extdeclist(NodePtr node);
InterCodes translate_Fundec(NodePtr node);
InterCodes translate_Vardec(NodePtr node, Operand *place);
InterCodes translate_Deflist(NodePtr node);
InterCodes translate_Def(NodePtr node);
InterCodes translate_Declist(NodePtr node);
InterCodes translate_Dec(NodePtr node);
InterCodes translate_structure(NodePtr node, Operand place, FieldList *list);
InterCodes translate_array(NodePtr node, Operand place, TypePtr *list);

//optimize
int optimize_ir(InterCodes *ir);

//other functions
InterCodes link_ir(InterCodes l1, InterCodes l2);
int remove_ir(InterCodes *table, InterCodes icode);
int get_structure_size(TypePtr type);
RelType get_relop(NodePtr node);

//global variables
FILE *fp;

#endif
