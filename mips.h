#ifndef __MIPS_H__
#define __MIPS_H__

#include "syntax_tree.h"
#include "semantic.h"
#include "IR.h"

typedef enum { 
	MIPS_LABEL,
	MIPS_LI,
	MIPS_LA,
	MIPS_MOVE,
	MIPS_ADDI,
	MIPS_ADD,
	MIPS_SUB,
	MIPS_MUL,
	MIPS_DIV,
	MIPS_MFLO,
	MIPS_LW,
	MIPS_SW,
	MIPS_J,
	MIPS_JAL,
	MIPS_JR,
	MIPS_BEQ,
	MIPS_BNE,
	MIPS_BGT,
	MIPS_BLT,
	MIPS_BGE,
	MIPS_BLE
} MipsInsType;

typedef enum { 
	MIPS_OP_LABEL,
	MIPS_OP_FUNC,
	MIPS_OP_REG, 
	MIPS_OP_IMM,
	MIPS_OP_ADDR
} MipsOpType;

typedef struct Operands_* Operands;
typedef struct Instruction_* Instruction;
typedef struct Instructions_* Instructions;

struct Operands_ {
	MipsOpType kind;
	union {
		int reg_no;
		int imm_value;
		int label_no;
		char *func_name;
		struct{
			int reg_no;
			int offset;
		}addr;
	}u;
};

struct Instruction_ {
	enum { ONE_OP, TWO_OP, THREE_OP} kind;
	union {
		struct{
			MipsInsType instype;
			Operands op;
		}oneop;
		struct {
			MipsInsType instype;
			Operands op1, op2;
		}twoop;
		struct {
			MipsInsType instype;
			Operands op1, op2, op3;
		}threeop;
	}u;
};

struct Instructions_ { 
	Instruction inst; 
	struct Instructions_ *prev, *next; 
};

typedef struct Variable_* Variable;
typedef struct Temp_* Temp;
typedef struct Register_* Register;

struct Variable_ {
	int var_id;
	int reg_no;
	int offset;
};

struct Temp_ {
	int temp_id;
	int reg_no;
};

struct Register_ {
	int use_id;	//who is using it?
	int enable;	//Can it be used?
	int used;	//have it been used?
	int flag;	//mark var or tmp
};



//register name list
static char* reg_name[] = {
	"$zero",
	"$at",
	"$v0", "$v1",
	"$a0", "$a1", "$a2", "$a3",
	"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
	"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
	"$t8", "$t9", 
	"$k0", "$k1",
	"$gp",
	"$sp",
	"$fp",//we use $30 as $fp here
	"$ra"
};


//generate operands
Operands mips_new_label(int label_no);
Operands mips_new_func(char *func_name);
Operands mips_new_addr(int reg_no, int offset);
Operands mips_new_reg(int reg_no);
Operands mips_new_imm(int value);
//generate sentences
Instructions mips_gen_sw(int reg, int base, int offset);
Instructions mips_gen_lw(int reg, int base, int offset);
Instructions mips_gen_addi(int result, int reg, int imm);
//universal generation
Instructions mips_gen_one(MipsInsType type, Operands op);
Instructions mips_gen_two(MipsInsType type, Operands op1, Operands op2);
Instructions mips_gen_three(MipsInsType type, Operands op1, Operands op2, Operands op3);
Instructions gen_inst(InterCode icode);
//generate mips instructions from irtable
void gen_mips(InterCodes table);

//output functions
void output_inst(Instruction inst);
void output_mips_op(Operands op);
void output_read_write();

//register functions
int get_reg(Instructions inst, Operand op, int flag);
int store_reg(Operand op, int cur_reg);
int alloc_reg(int id, int flg);
int free_reg(int reg_no, int id);
void init_regs();

//variable handle
Instructions store_live_variable(Instructions table);
int set_variable_reg(int var_no, int reg_no, int flag);

//other functions
Instructions link_inst(Instructions l1, Instructions l2);
int max(int a, int b);

#endif
