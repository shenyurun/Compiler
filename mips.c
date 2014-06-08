#include "stdio.h"
#include "syntax_tree.h"
#include "sys/ioctl.h"
#include "stdlib.h"
#include "stdarg.h"
#include "semantic.h"
#include "hash_table.h"
#include "assert.h"
#include "IR.h"
#include "mips.h"

#define RAMDOM_ALLOC 999
#define MIPS_FRAMESIZE 128

//global variables
Variable vars[100];
Temp tmps[100];
Register regs[32];
int args_count = 0;
int args_num = 0;
int args_total = 0;
int params_num = 0;
int vardec_count = 0;
int var_num = 0;//total var number
Instructions func_lw = NULL;
int local_level = 0;
int locals[10] = {0};
//FILE *fp2;
int relieve = 0;
int cur_regid = -1;

void gen_mips(InterCodes table){
	//fp2 = fopen("output.s", "w+");
	InterCodes curcode = NULL;
	Instructions curinst = NULL;
	assert(table != NULL);
	init_regs();
	output_read_write();
	curcode = table;
	while(curcode != NULL){
		assert(curcode->code != NULL);
		if(args_count == 0 && curcode->code->kind == IR_ARG)
			args_count++;
		curinst = gen_inst(curcode->code);
		while(curinst != NULL){
			assert(curinst->inst != NULL);
			output_inst(curinst->inst);
			curinst = curinst->next;
		}
		curcode = curcode->next;
	}
}

Instructions gen_inst(InterCode icode){
	Operand op1 = NULL, op2 = NULL, op3 = NULL;
	Operands s1 = NULL, s2 = NULL, s3 = NULL, s4 = NULL;
	Instructions instable = NULL;
	Instructions inst = NULL;
	int reg_no, reg_no_1;
	int flag = 0;
	char *wr_label = NULL;

	switch(icode->kind){
	case IR_ASSIGN:
		op1 = icode->u.assign.left;
		op2 = icode->u.assign.right;
		if(op1 == NULL || op2 == NULL)
			return NULL;
		//*x := y
		if(op1->kind == OP_ADDRESS && op2->kind != OP_ADDRESS){
			if(op2->kind == OP_VARIABLE)
				flag = 1;
			//sw reg(y), 0(reg(x))
			reg_no = get_reg(instable, op2, flag);
			s1 = mips_new_reg(reg_no);
			reg_no = get_reg(instable, op1, 0);
			s2 = mips_new_addr(reg_no, 0);
			inst = mips_gen_two(MIPS_SW, s1, s2);
			instable = link_inst(instable, inst);
			cur_regid = reg_no;
			return instable;
		}
		//x := *y
		if(op2->kind == OP_ADDRESS && op1->kind != OP_ADDRESS){
			//lw reg(x), 0(reg(y))
			reg_no = get_reg(instable, op1, 0);
			s1 = mips_new_reg(reg_no);    
			reg_no = get_reg(instable, op2, 0);
			s2 = mips_new_addr(reg_no, 0);
			inst = mips_gen_two(MIPS_LW, s1, s2);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op1, s1->u.reg_no);
			//cur_regid = reg_no;
			return instable;
		}
		//*x := *y
		if(op1->kind == OP_ADDRESS && op2->kind == OP_ADDRESS){
			//lw reg(0), 0(reg(y))
			reg_no = get_reg(instable, op2, 0);
			s2 = mips_new_addr(reg_no, 0);
			reg_no = get_reg(instable, NULL, 0);
			s1 = mips_new_reg(reg_no);
			inst = mips_gen_two(MIPS_LW, s1, s2);
			instable = link_inst(instable, inst);
			//reg_no = store_reg(op1, s1->u.reg_no);
			//sw reg(0), 0(reg(x))
			reg_no = get_reg(instable, op1, 0);
			s2 = mips_new_addr(reg_no, 0);
			inst = mips_gen_two(MIPS_SW, s1, s2);
			free_reg(reg_no, -1);
			//free_reg(reg_no_1, -1);
			instable = link_inst(instable, inst);
			cur_regid = reg_no;
			return instable;
		}
		reg_no = get_reg(instable, op1, 0);
		s1 = mips_new_reg(reg_no);
		//x := #k
		if(op2->kind == OP_CONSTANT){
			//li reg(x), k
			s2 = mips_new_imm(op2->u.value);
			inst = mips_gen_two(MIPS_LI, s1, s2);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op1, s1->u.reg_no);
			return instable;
		}
		//x := y
		if(op2->kind == OP_TEMP || op2->kind == OP_VARIABLE){
			if(op2->kind == OP_VARIABLE)
				flag = 1;
			//move reg(x), reg(y)
			reg_no = get_reg(instable, op2, flag);
			s2 = mips_new_reg(reg_no);  
			inst = mips_gen_two(MIPS_MOVE, s1, s2);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op1, s1->u.reg_no);
			return instable;
		}
		printf("Unknown ASSIGN!!\n");
	case IR_ADD:
		op1 = icode->u.binop.op1;
		op2 = icode->u.binop.op2;
		op3 = icode->u.binop.result;
		if(op1 == NULL || op2 == NULL || op3 == NULL)
			return NULL;
		//handle result reg
		reg_no = get_reg(instable, op3, 0);
		s1 = mips_new_reg(reg_no);
		//TODO:x = &y + z
		if(op1->kind == OP_REFERENCE && op2->kind == OP_TEMP){
			//add reg(x), reg(z), $sp
			reg_no = get_reg(instable, op2, 0);
			//printf("reg no: %d\n", reg_no);
			s2 = mips_new_reg(reg_no);
			s3 = mips_new_reg(29);
			inst = mips_gen_three(MIPS_ADD, s1, s2, s3);
			instable = link_inst(instable, inst);
			cur_regid = reg_no;
			return instable;
		}
		//TODO:x = *y + *z
		if(op1->kind == OP_ADDRESS && op2->kind == OP_ADDRESS){
			//lw reg(x), 0(reg(y))   
			reg_no = get_reg(instable, op1, 0);
			s2 = mips_new_addr(reg_no, 0);
			inst = mips_gen_two(MIPS_LW, s1, s2);
			instable = link_inst(instable, inst);
			//lw reg(0), 0(reg(z))
			reg_no = get_reg(instable, NULL, 0);
			s3 = mips_new_reg(reg_no);    
			reg_no = get_reg(instable, op2, 0);
			s4 = mips_new_addr(reg_no, 0);
			inst = mips_gen_two(MIPS_LW, s3, s4);
			instable = link_inst(instable, inst);
			//add reg(x), reg(x), reg(0)
			inst = mips_gen_three(MIPS_ADD, s1, s1, s3);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			cur_regid = reg_no;
			return instable;
		}
		//x := #k + y
		if(op1->kind == OP_CONSTANT && op2->kind != OP_CONSTANT){
			if(op2->kind == OP_VARIABLE)
				flag = 1;
			//addi reg(x), reg(y), k
			s2 = mips_new_imm(op1->u.value);
			reg_no = get_reg(instable, op2, flag);
			s3 = mips_new_reg(reg_no);
			inst = mips_gen_three(MIPS_ADDI, s1, s3, s2);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//x := y + #k
		if(op1->kind != OP_CONSTANT && op2->kind == OP_CONSTANT){
			if(op1->kind == OP_VARIABLE)
				flag = 1;
			//addi reg(x), reg(y), k
			s3 = mips_new_imm(op2->u.value);
			reg_no = get_reg(instable, op1, flag);
			s2 = mips_new_reg(reg_no);
			inst = mips_gen_three(MIPS_ADDI, s1, s2, s3);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//x := #k + #j
		if(op1->kind == OP_CONSTANT && op2->kind == OP_CONSTANT){
			//li reg(0), k
			reg_no = get_reg(instable, NULL, 0);//use a register temporarily
			free_reg(reg_no, -1);
			s2 = mips_new_reg(reg_no);
			s3 = mips_new_imm(op1->u.value);
			inst = mips_gen_two(MIPS_LI, s2, s3);
			instable = link_inst(instable, inst);
			//addi reg(x), reg(0), j
			s4 = mips_new_imm(op2->u.value);
			inst = mips_gen_three(MIPS_ADDI, s1, s2, s4);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//x := y + z
		//add reg(x), reg(y), reg(z)
		if(op1->kind == OP_VARIABLE)
			flag = 1;
		reg_no = get_reg(instable, op1, flag);
		if(op2->kind == OP_TEMP)
			flag = 0;
		else
			flag = 1;
		s2 = mips_new_reg(reg_no);
		reg_no = get_reg(instable, op2, flag);
		s3 = mips_new_reg(reg_no);
		inst = mips_gen_three(MIPS_ADD, s1, s2, s3);
		instable = link_inst(instable, inst);
		reg_no = store_reg(op3, s1->u.reg_no);
		cur_regid = reg_no;
		return instable;
	case IR_SUB:
		op1 = icode->u.binop.op1;
		op2 = icode->u.binop.op2;
		op3 = icode->u.binop.result;
		if(op1 == NULL || op2 == NULL || op3 == NULL)
			return NULL;
		reg_no = get_reg(instable, op3, 0);
		s1 = mips_new_reg(reg_no);
		//TODO: Could it be possible??
		//x := #k - y
		if(op1->kind == OP_CONSTANT && op2->kind != OP_CONSTANT){
			if(op2->kind == OP_VARIABLE)
				flag = 1;
			//li reg(0), k
			reg_no = get_reg(instable, NULL, 0);
			free_reg(reg_no, -1);            
			s2 = mips_new_reg(reg_no);
			s3 = mips_new_imm(op1->u.value);
			inst = mips_gen_two(MIPS_LI, s2, s3);
			instable = link_inst(instable, inst);
			//sub reg(x), reg(0), reg(y)
			reg_no = get_reg(instable, op2, flag);
			s4 = mips_new_reg(reg_no);
			inst = mips_gen_three(MIPS_SUB, s1, s2, s4);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//x := y - #k
		if(op1->kind != OP_CONSTANT && op2->kind == OP_CONSTANT){
			if(op1->kind == OP_VARIABLE)
				flag = 1;
			//addi reg(x), reg(y), -k
			s3 = mips_new_imm(-op2->u.value);
			reg_no = get_reg(instable, op1, flag);
			s2 = mips_new_reg(reg_no);
			inst = mips_gen_three(MIPS_ADDI, s1, s2, s3);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//x := #k - #j
		if(op1->kind == OP_CONSTANT && op2->kind == OP_CONSTANT){
			//li reg(0), k
			reg_no = get_reg(instable, NULL, 0);
			free_reg(reg_no, -1);            
			s2 = mips_new_reg(reg_no);
			s3 = mips_new_imm(op1->u.value);
			inst = mips_gen_two(MIPS_LI, s2, s3);
			instable = link_inst(instable, inst);
			//addi reg(x), reg(0), -j
			s4 = mips_new_imm(-op2->u.value);
			inst = mips_gen_three(MIPS_ADDI, s1, s2, s4);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//TODO:x = *y - *z
		if(op1->kind == OP_ADDRESS && op2->kind == OP_ADDRESS){
			//lw reg(x), 0(reg(y))   
			reg_no = get_reg(instable, op1, 0);
			s2 = mips_new_addr(reg_no, 0);
			inst = mips_gen_two(MIPS_LW, s1, s2);
			instable = link_inst(instable, inst);
			//lw reg(0), 0(reg(z))
			reg_no = get_reg(instable, NULL, 0);
			s3 = mips_new_reg(reg_no);    
			reg_no = get_reg(instable, op2, 0);
			s4 = mips_new_addr(reg_no, 0);
			inst = mips_gen_two(MIPS_LW, s3, s4);
			instable = link_inst(instable, inst);
			//sub reg(x), reg(x), reg(0)
			inst = mips_gen_three(MIPS_SUB, s1, s1, s3);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//x := y - z
		//sub reg(x), reg(y), reg(z)
		if(op1->kind == OP_VARIABLE)
			flag = 1;
		reg_no = get_reg(instable, op1, flag);
		s2 = mips_new_reg(reg_no);
		if(op2->kind == OP_TEMP)
			flag = 0;
		else 
			flag = 1;
		reg_no = get_reg(instable, op2, flag);
		s3 = mips_new_reg(reg_no);
		inst = mips_gen_three(MIPS_SUB, s1, s2, s3);
		instable = link_inst(instable, inst);
		reg_no = store_reg(op3, s1->u.reg_no);
		return instable;
	case IR_MUL:
		op1 = icode->u.binop.op1;
		op2 = icode->u.binop.op2;
		op3 = icode->u.binop.result;
		if(op1 == NULL || op2 == NULL || op3 == NULL)
			return NULL;
		reg_no = get_reg(instable, op3, 0);
		s1 = mips_new_reg(reg_no);
		//x := #k * y
		if(op1->kind == OP_CONSTANT && op2->kind != OP_CONSTANT){
			if(op2->kind == OP_VARIABLE)
				flag = 1;
			//li reg(0), k
			reg_no = get_reg(instable, NULL, 0);
			free_reg(reg_no, -1);              
			s2 = mips_new_reg(reg_no);
			s3 = mips_new_imm(op1->u.value);
			inst = mips_gen_two(MIPS_LI, s2, s3);
			instable = link_inst(instable, inst);
			//mul reg(x), reg(0), reg(y)
			reg_no = get_reg(instable, op2, flag);
			s4 = mips_new_reg(reg_no);
			inst = mips_gen_three(MIPS_MUL, s1, s2, s4);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//x := y * #k
		if(op1->kind != OP_CONSTANT && op2->kind == OP_CONSTANT){
			if(op1->kind == OP_VARIABLE)
				flag = 1;
			//li reg(0), k
			reg_no = get_reg(instable, NULL, 0);
			free_reg(reg_no, -1);            
			s2 = mips_new_reg(reg_no);
			s3 = mips_new_imm(op2->u.value);
			inst = mips_gen_two(MIPS_LI, s2, s3);
			instable = link_inst(instable, inst);
			//mul reg(x), reg(y), reg(0)
			reg_no = get_reg(instable, op1, flag);
			s4 = mips_new_reg(reg_no);
			inst = mips_gen_three(MIPS_MUL, s1, s4, s2);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//x := #k * #j
		if(op1->kind == OP_CONSTANT && op2->kind == OP_CONSTANT){
			//li reg(0), k
			reg_no = get_reg(instable, NULL, 0);              
			s2 = mips_new_reg(reg_no);
			s3 = mips_new_imm(op1->u.value);
			inst = mips_gen_two(MIPS_LI, s2, s3);
			instable = link_inst(instable, inst);
			//li reg(0), j
			reg_no_1 = get_reg(instable, NULL, 0);
			free_reg(reg_no, -1);
			free_reg(reg_no_1, -1);           
			s4 = mips_new_reg(reg_no_1);
			s3 = mips_new_imm(op2->u.value);
			inst = mips_gen_two(MIPS_LI, s4, s3);
			instable = link_inst(instable, inst);
			//mul reg(x), reg(0), reg(0)
			inst = mips_gen_three(MIPS_MUL, s1, s2, s4);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//TODO:x = *y * *z
		if(op1->kind == OP_ADDRESS && op2->kind == OP_ADDRESS){
			//lw reg(x), 0(reg(y))   
			reg_no = get_reg(instable, op1, 0);
			s2 = mips_new_addr(reg_no, 0);
			inst = mips_gen_two(MIPS_LW, s1, s2);
			instable = link_inst(instable, inst);
			//lw reg(0), 0(reg(z))
			reg_no = get_reg(instable, NULL, 0);
			s3 = mips_new_reg(reg_no);    
			reg_no = get_reg(instable, op2, 0);
			s4 = mips_new_addr(reg_no, 0);
			inst = mips_gen_two(MIPS_LW, s3, s4);
			instable = link_inst(instable, inst);
			//mul reg(x), reg(x), reg(0)
			inst = mips_gen_three(MIPS_MUL, s1, s1, s3);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//x := y * z
		//mul reg(x), reg(y), reg(z)
		if(op1->kind == OP_VARIABLE)
			flag = 1;
		reg_no = get_reg(instable, op1, flag);
		s2 = mips_new_reg(reg_no);
		if(op2->kind == OP_TEMP)
			flag = 0;
		else
			flag = 1;
		reg_no = get_reg(instable, op2, flag);
		s3 = mips_new_reg(reg_no);
		inst = mips_gen_three(MIPS_MUL, s1, s2, s3);
		instable = link_inst(instable, inst);
		reg_no = store_reg(op3, s1->u.reg_no);
		return instable;
	case IR_DIV:
		op1 = icode->u.binop.op1;
		op2 = icode->u.binop.op2;
		op3 = icode->u.binop.result;
		if(op1 == NULL || op2 == NULL || op3 == NULL)
			return NULL;
		reg_no = get_reg(instable, op3, 0);
		s1 = mips_new_reg(reg_no);
		//x := #k / y
		if(op1->kind == OP_CONSTANT && op2->kind != OP_CONSTANT){
			if(op2->kind == OP_VARIABLE)
				flag = 1;
			//li reg(0), k
			reg_no = get_reg(instable, NULL, 0); 
			free_reg(reg_no, -1);             
			s2 = mips_new_reg(reg_no);
			s3 = mips_new_imm(op1->u.value);
			inst = mips_gen_two(MIPS_LI, s2, s3);
			instable = link_inst(instable, inst);
			//div reg(0), reg(y)
			reg_no = get_reg(instable, op2, flag);
			s4 = mips_new_reg(reg_no);
			inst = mips_gen_two(MIPS_DIV, s2, s4);
			instable = link_inst(instable, inst);
			//mflo reg(x)
			inst = mips_gen_one(MIPS_MFLO, s1);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//x := y / #k
		if(op1->kind != OP_CONSTANT && op2->kind == OP_CONSTANT){
			if(op1->kind == OP_VARIABLE)
				flag = 1;
			//li reg(0), k
			reg_no = get_reg(instable, NULL, 0);
			free_reg(reg_no, -1);        
			s2 = mips_new_reg(reg_no);
			s3 = mips_new_imm(op2->u.value);
			inst = mips_gen_two(MIPS_LI, s2, s3);
			instable = link_inst(instable, inst);
			//div reg(y), reg(0)
			reg_no = get_reg(instable, op1, flag);
			s4 = mips_new_reg(reg_no);
			inst = mips_gen_two(MIPS_DIV, s4, s2);
			instable = link_inst(instable, inst);
			//mflo reg(x)
			inst = mips_gen_one(MIPS_MFLO, s1);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//x := #k * #j
		if(op1->kind == OP_CONSTANT && op2->kind == OP_CONSTANT){
			//li reg(0), k
			reg_no = get_reg(instable, NULL, 0);          
			s2 = mips_new_reg(reg_no);
			s3 = mips_new_imm(op1->u.value);
			inst = mips_gen_two(MIPS_LI, s2, s3);
			instable = link_inst(instable, inst);
			//li reg(0), j
			reg_no_1 = get_reg(instable, NULL, 0);
			free_reg(reg_no, -1);
			free_reg(reg_no_1, -1);             
			s4 = mips_new_reg(reg_no_1);
			s3 = mips_new_imm(op2->u.value);
			inst = mips_gen_two(MIPS_LI, s4, s3);
			instable = link_inst(instable, inst);
			//div reg(0), reg(0)
			inst = mips_gen_two(MIPS_DIV, s2, s4);
			instable = link_inst(instable, inst);
			//mflo reg(x)
			inst = mips_gen_one(MIPS_MFLO, s1);
			instable = link_inst(instable, inst);
			reg_no = store_reg(op3, s1->u.reg_no);
			return instable;
		}
		//x := y / z
		//div reg(x), reg(y), reg(z)
		if(op1->kind == OP_VARIABLE)
			flag = 1;
		reg_no = get_reg(instable, op1, flag);
		s2 = mips_new_reg(reg_no);
		if(op2->kind == OP_TEMP)
			flag = 0;
		else
			flag = 1;
		reg_no = get_reg(instable, op2, flag);
		s3 = mips_new_reg(reg_no);
		inst = mips_gen_two(MIPS_DIV, s2, s3);
		instable = link_inst(instable, inst);
		//mflo reg(x)
		inst = mips_gen_one(MIPS_MFLO, s1);
		instable = link_inst(instable, inst);
		reg_no = store_reg(op3, s1->u.reg_no);
		return instable;
	case IR_LABEL:
		//x:
		op1 = icode->u.uniop.op;
		s1 = mips_new_label(op1->u.label_no);
		inst = mips_gen_one(MIPS_LABEL, s1);
		instable = link_inst(instable, inst);
		cur_regid = reg_no;
		return instable;
	case IR_GOTO:
		//j x
		op1 = icode->u.uniop.op;
		if(op1->kind == OP_LABEL)
			s1 = mips_new_label(op1->u.label_no);
		else
			s1 = mips_new_func(op1->u.func_name);
		inst = mips_gen_one(MIPS_J, s1);
		instable = link_inst(instable, inst);
		cur_regid = reg_no;
		return instable;
	case IR_RELOP:
		op1 = icode->u.cond.relop1;
		op2 = icode->u.cond.relop2;
		op3 = icode->u.cond.label;
		//handle relop1
		//if *x < y goto z
		if(op1->kind == OP_ADDRESS){
			//lw reg(0), 0(reg(x))
			reg_no = get_reg(instable, NULL, 0);
			s1 = mips_new_reg(reg_no);
			reg_no = get_reg(instable, op1, 0);
			s2 = mips_new_addr(reg_no, 0);
			inst = mips_gen_two(MIPS_LW, s1, s2);
			instable = link_inst(instable, inst);
		}
		//if #k < y goto z
		else if(op1->kind == OP_CONSTANT){
			//li reg(0), k
			reg_no = get_reg(instable, NULL, 0);
			s1 = mips_new_reg(reg_no);   
			s2 = mips_new_imm(op1->u.value);
			inst = mips_gen_two(MIPS_LI, s1, s2);
			instable = link_inst(instable, inst);
		}
		//if x < y goto z
		else{
			if(op1->kind == OP_VARIABLE)
				flag = 1;
			//reg(x)
			reg_no = get_reg(instable, op1, flag);
			s1 = mips_new_reg(reg_no);
		}

		flag = 0;
		//handle relop2
		//if x < *y goto z
		if(op2->kind == OP_ADDRESS){
			//lw reg(0), 0(reg(x))
			reg_no = get_reg(instable, op2, 0);
			s4 = mips_new_addr(reg_no, 0);
			reg_no_1 = get_reg(instable, NULL, 0);
			s2 = mips_new_reg(reg_no_1);
			//free_reg(reg_no_1, -1);
			inst = mips_gen_two(MIPS_LW, s2, s4);
			instable = link_inst(instable, inst);
		}
		//if x < #j goto z
		else if(op2->kind == OP_CONSTANT){
			//li reg(0), j
			reg_no_1 = get_reg(instable, NULL, 0);
			//free_reg(reg_no_1, -1);
			s2 = mips_new_reg(reg_no_1);   
			s3 = mips_new_imm(op2->u.value);
			inst = mips_gen_two(MIPS_LI, s2, s3);
			instable = link_inst(instable, inst);
		}
		//if x < y goto z
		else{
			if(op2->kind == OP_VARIABLE)
				flag = 1;
			//reg(y)
			reg_no = get_reg(instable, op2, flag);
			s2 = mips_new_reg(reg_no);
		}

		//handle label
		s3 = mips_new_label(op3->u.label_no);
		switch(icode->u.cond.reltype){
		case EQ:
			//beq reg(x), reg(y), z
			inst = mips_gen_three(MIPS_BEQ, s1, s2, s3);
			instable = link_inst(instable, inst);
			break;
		case NE:
			//bne reg(x), reg(y), z
			inst = mips_gen_three(MIPS_BNE, s1, s2, s3);
			instable = link_inst(instable, inst);
			break;
		case LT:
			//blt reg(x), reg(y), z
			inst = mips_gen_three(MIPS_BLT, s1, s2, s3);
			instable = link_inst(instable, inst);
			break;
		case MT:
			//bgt reg(x), reg(y), z
			inst = mips_gen_three(MIPS_BGT, s1, s2, s3);
			instable = link_inst(instable, inst);
			break;
		case LE:
			//ble reg(x), reg(y), z
			inst = mips_gen_three(MIPS_BLE, s1, s2, s3);
			instable = link_inst(instable, inst);
			break;
		case ME:
			//bge reg(x), reg(y), z
			inst = mips_gen_three(MIPS_BGE, s1, s2, s3);
			instable = link_inst(instable, inst);
			break;
		}

		//!!now can free op1 & op2's regs
		if(op1->kind == OP_CONSTANT || op1->kind == OP_ADDRESS){
			free_reg(reg_no, -1);
		}
		if(op2->kind == OP_CONSTANT || op2->kind == OP_ADDRESS){
			free_reg(reg_no_1, -1);
		}		
		cur_regid = reg_no;
		return instable;
	case IR_WRITE:
		wr_label = "write";
		op1 = icode->u.uniop.op;
		//handle the param
		if(op1->kind == OP_CONSTANT){
			//li $a0 #k
			s1 = mips_new_reg(4);
			s2 = mips_new_imm(op1->u.value);
			inst = mips_gen_two(MIPS_LI, s1, s2);
		}
		else if(op1->kind == OP_VARIABLE){
			//if(op1->kind == OP_VARIABLE)
			flag = 1;
			//TODO:What if $a0 has value(nested function)
			//move reg(0) $a0 -> --- ->move $a0 reg(0)
			reg_no_1 = get_reg(instable, NULL, 1);
			s1 = mips_new_reg(reg_no_1);
			s2 = mips_new_reg(4);
			inst = mips_gen_two(MIPS_MOVE, s1, s2);
			instable = link_inst(instable, inst);
			//move $a0 reg(x)
			reg_no = get_reg(instable, op1, flag);
			s1 = mips_new_reg(4);
			s2 = mips_new_reg(reg_no);
			inst = mips_gen_two(MIPS_MOVE, s1, s2);
		}
		else if(op1->kind == OP_ADDRESS){
			//lw reg(0), 0(reg(x))
			reg_no = get_reg(instable, op1, 0);
			s2 = mips_new_addr(reg_no, 0);
			reg_no = get_reg(instable, NULL, 0);	
			s1 = mips_new_reg(reg_no);
			inst = mips_gen_two(MIPS_LW, s1, s2);
			instable = link_inst(instable, inst);
			//move reg(0) $a0 -> --- ->move $a0 reg(0)
			reg_no_1 = get_reg(instable, NULL, 1);
			s1 = mips_new_reg(reg_no_1);
			s2 = mips_new_reg(4);
			inst = mips_gen_two(MIPS_MOVE, s1, s2);
			instable = link_inst(instable, inst);
			//move $a0 reg(0)
			//reg_no = get_reg(instable, op1, 0);
			s1 = mips_new_reg(4);
			s2 = mips_new_reg(reg_no);
			inst = mips_gen_two(MIPS_MOVE, s1, s2);
		}
		instable = link_inst(instable, inst);
		goto READ_WRITE_HANDLE;//keep on handling
	case IR_READ:
		wr_label = "read";
		op1 = icode->u.uniop.op;
		READ_WRITE_HANDLE:
		//addi $sp, $sp, -4
		s1 = mips_new_reg(29);
		s2 = mips_new_reg(29);
		s3 = mips_new_imm(-4);
		inst = mips_gen_three(MIPS_ADDI, s1, s2, s3);
		instable = link_inst(instable, inst);
		//sw $ra 0($sp)
		s1 = mips_new_reg(31);
		s2 = mips_new_addr(29, 0);
		inst = mips_gen_two(MIPS_SW, s1, s2);
		instable = link_inst(instable, inst);
		//jal read/write
		s1 = mips_new_func(wr_label);
		inst = mips_gen_one(MIPS_JAL, s1);
		instable = link_inst(instable, inst);
		//lw $ra, 0($sp)
		s1 = mips_new_reg(31);
		s2 = mips_new_addr(29, 0);
		inst = mips_gen_two(MIPS_LW, s1, s2);
		instable = link_inst(instable, inst);
		//addi $sp, $sp, 4
		s1 = mips_new_reg(29);
		s2 = mips_new_reg(29);
		s3 = mips_new_imm(4);
		inst = mips_gen_three(MIPS_ADDI, s1, s2, s3);
		instable = link_inst(instable, inst);
		if(icode->kind == IR_READ){
			//save the result
			//move reg(x) $v0
			reg_no = get_reg(instable, op1, 0);
			s1 = mips_new_reg(reg_no);
			s2 = mips_new_reg(2);
			inst = mips_gen_two(MIPS_MOVE, s1, s2);
			instable = link_inst(instable, inst);
		}
		//Don't forget!!
		//move $a0 reg(0)
		s1 = mips_new_reg(reg_no_1);
		s2 = mips_new_reg(4);
		inst = mips_gen_two(MIPS_MOVE, s2, s1);
		instable = link_inst(instable, inst);
		free_reg(reg_no_1, -1);
		cur_regid = reg_no;
		return instable;
	case IR_FUNCTION:
		op1 = icode->u.uniop.op;
		//func:
		s1 = mips_new_func(op1->u.func_name);
		inst = mips_gen_one(MIPS_LABEL, s1);
		instable = link_inst(instable, inst);
		//addi $sp, $sp, -framesize
		s1 = mips_new_reg(29);
		s2 = mips_new_reg(29);
		s3 = mips_new_imm(-MIPS_FRAMESIZE);
		inst = mips_gen_three(MIPS_ADDI, s1, s2, s3);
		instable = link_inst(instable, inst);    
		//sw $ra, (framesize-4)($sp)
		inst = mips_gen_sw(31, 29, MIPS_FRAMESIZE-4);
		instable = link_inst(instable, inst);
		//sw $fp, (framesize-8)($sp)
		inst = mips_gen_sw(30, 29, MIPS_FRAMESIZE-8);
		instable = link_inst(instable, inst);
		//addi $fp, $sp, framesize
		inst = mips_gen_addi(30, 29, MIPS_FRAMESIZE);
		instable = link_inst(instable, inst);
		cur_regid = reg_no;
		return instable; 
	case IR_CALL:
		//store all live variable.
		if(args_num == 0)
			func_lw = store_live_variable(instable);
		op1 = icode->u.assign.left;
		op2 = icode->u.assign.right;
		//jal func
		s1 = mips_new_func(op2->u.func_name);
		inst = mips_gen_one(MIPS_JAL, s1);
		instable = link_inst(instable, inst);
		//move reg(x), $v0
		reg_no = get_reg(instable, op1, 0);
		s2 = mips_new_reg(reg_no);
		s3 = mips_new_reg(2);
		inst = mips_gen_two(MIPS_MOVE, s2, s3);
		instable = link_inst(instable, inst);
		//store the result
		reg_no = store_reg(op1, s2->u.reg_no);	
		//addi $sp, $sp, max{0, 4*(n-4)}
		s1 = mips_new_reg(29);
		s2 = mips_new_reg(29);
		if(args_num > 4)
			s3 = mips_new_imm(4*(args_num-4));
		else
			s3 = mips_new_imm(0);
		inst = mips_gen_three(MIPS_ADDI, s1, s2, s3);
		//reset the args
		args_num = 0;
		args_total = 0;
		//load all live variable
		instable = link_inst(instable, func_lw);
		func_lw = NULL;
		cur_regid = reg_no;
		return instable;
	case IR_RETURN:
		op1 = icode->u.uniop.op;
		//lw $ra, (framesize-4)($sp)
		inst = mips_gen_lw(31, 29, MIPS_FRAMESIZE-4);
		instable = link_inst(instable, inst);
		//lw $fp, (framesize-8)($sp)
		inst = mips_gen_lw(30, 29, MIPS_FRAMESIZE-8);
		instable = link_inst(instable, inst);
		//addi $ra, $ra framesize
		inst = mips_gen_addi(29, 29, MIPS_FRAMESIZE);
		instable = link_inst(instable, inst);
		//move $v1 ...
		s1 = mips_new_reg(2);
		if(op1->kind == OP_CONSTANT){
			if(op1->u.value == 0){
				//move $v0 $zero
				reg_no = 0;
				s2 = mips_new_reg(reg_no);
				inst = mips_gen_two(MIPS_MOVE, s1, s2);
			}
			else{
				//li $v0 #k
				s2 = mips_new_imm(op1->u.value);
				inst = mips_gen_two(MIPS_LI, s1, s2);
			}
		}
		else{
			if(op1->kind == OP_VARIABLE)
				flag = 1;
			//move $v1 reg(x)
			reg_no = get_reg(instable, op1, flag);
			s2 = mips_new_reg(reg_no);
			inst = mips_gen_two(MIPS_MOVE, s1, s2);
		}
		instable = link_inst(instable, inst);
		//jr $ra
		s3 = mips_new_reg(31);
		inst = mips_gen_one(MIPS_JR, s3);
		instable = link_inst(instable, inst);
		cur_regid = reg_no;
		return instable;
	case IR_ARG:
		//store all live variable 
		if(args_num == 0){
			//addi $sp, $sp, max{0, -4(n-4)}
			if(args_total > 4)
				inst = mips_gen_addi(29, 29, -4*(args_total-4));
			else
				inst = mips_gen_addi(29, 29, 0);
			instable = link_inst(instable, inst);
			func_lw = store_live_variable(instable);
		}
		//move the args
		op1 = icode->u.uniop.op;
		if(op1->kind == OP_CONSTANT){
			//li reg(0) #k
			s2 = mips_new_imm(op1->u.value);
			reg_no = get_reg(instable, NULL, 0); 
			s1 = mips_new_reg(reg_no);
			inst = mips_gen_two(MIPS_LI, s1, s2);
			instable = link_inst(instable, inst);
		}
		else{
			if(op1->kind == OP_VARIABLE)
				flag = 1;
			reg_no = get_reg(instable, op1, flag);
			s1 = mips_new_reg(reg_no);
		}
		//store args according to arg numbers
		if(args_num < 4){
			//store args into registers
			//move $a.., reg(x)
			s2 = mips_new_reg(4+args_num);
			inst = mips_gen_two(MIPS_MOVE, s2, s1);
		}
		else{
			//store args into stack
			//sw reg(x), (4(x+n-3))($sp)
			s2 = mips_new_addr(29, 4*(args_num - 4)); 
			inst = mips_gen_two(MIPS_SW, s1, s2);
		}
		args_num ++;
		instable = link_inst(instable, inst); 
		cur_regid = reg_no;
		return instable;
	case IR_PARAM:
		op1 = icode->u.uniop.op;
		assert(op1->u.param_name != NULL);
		//int var_id = hash_get(op1->u.param_name)->id;
		int var_id = op1->u.var_no;
		if(params_num < 4){
			set_variable_reg(var_id, 4+params_num, 1);
		}
		else{
			//lw $sp framesize+4+4(n-4)
			reg_no = get_reg(instable, op1, 0);
			//inst = mips_gen_lw(reg_no, 29, MIPS_FRAMESIZE+4+4*(params_num-4));
			inst = mips_gen_lw(reg_no, 29, MIPS_FRAMESIZE + 4*(params_num - 4));
			instable = link_inst(instable, inst); 
		}
		params_num++;
		cur_regid = reg_no;
		return instable;
	case IR_DEC:
		//eg. DEC v1 12
		//sw reg(v1), vardec_count($sp)
		//TODO:Is it necessary??
		/*op1 = icode->u.assign.left;
		reg_no = get_reg(instable, op1, 1);
		s1 = mips_new_reg(reg_no);
		s2 = mips_new_addr(29, vardec_count); 
		vardec_count += icode->u.assign.right->u.value;
		inst = mips_gen_two(MIPS_SW, s1, s2);
		instable = link_inst(instable, inst);
		return instable;*/
		break;
	default:
		printf("Unknown IR type!\n");
		break;
	}
	return NULL;
}

int get_reg(Instructions inst, Operand op, int flag){
	Instructions ins = NULL;
	Operands op1 = NULL, op2 = NULL, op3 = NULL;
	int reg_no = -1;
	int id;
	if(op == NULL){
		reg_no = alloc_reg(RAMDOM_ALLOC, 1);
		assert(reg_no >= 0 && reg_no < 32);
		//free_reg(reg_no, -1);
		return reg_no;
	}
	if(op->kind == OP_VARIABLE || op->kind == OP_PARAM || op->kind == OP_REFERENCE){
		if(op->kind == OP_VARIABLE || op->kind == OP_REFERENCE)
			id = op->u.var_no;
		else
			id = hash_get(op->u.param_name)->id;
		assert(id != 0);
		//if var is not in table
		if(vars[id] == NULL){
			vars[id] = (Variable)malloc(sizeof(struct Variable_));
			vars[id]->var_id = id;
			//offset increase by 4
			vars[id]->offset = (locals[local_level]++) * 4;
			vars[id]->reg_no = -1;
		}
		//if var is not in register
		if(vars[id]->reg_no == -1){
			reg_no = alloc_reg(id, 0);
			assert(reg_no >= 0 && reg_no < 32);
			vars[id]->reg_no = reg_no;
			//if register is new allocated, load the value from the memory to the register
			if(flag == 1){
				//lw reg(x), offset($sp)
				op1 = mips_new_addr(29, vars[id]->offset);
				op2 = mips_new_reg(reg_no);
				ins = mips_gen_two(MIPS_LW, op2, op1);
				inst = link_inst(inst, ins);
			}
		}
		return vars[id]->reg_no;
	}
	if(op->kind == OP_TEMP || op->kind == OP_ADDRESS){
		id = op->u.temp_no;
		assert(id != 0);
		//if tmp is not in table
		if(tmps[id] == NULL){
			tmps[id] = (Temp)malloc(sizeof(struct Temp_));
			tmps[id]->temp_id = id;
			tmps[id]->reg_no = -1;
		}
		//if tmp is not in register
		if(tmps[id]->reg_no == -1){
			reg_no = alloc_reg(id, 1);
			assert(reg_no >= 0 && reg_no < 32);
			tmps[id]->reg_no = reg_no;
		}
		return tmps[id]->reg_no;
	}
	printf("Wrong with get_reg()!!\n");
	exit(-1);
}

int store_reg(Operand op, int cur_reg){
	int reg_no = -1;
	int id;
	if(op == NULL || op->kind == OP_TEMP)
		return cur_reg;
	assert(op->kind == OP_VARIABLE);
	id = op->u.var_no;
	assert(id > 0);
	//if var is not in table
	if(vars[id] == NULL){
		vars[id] = (Variable)malloc(sizeof(struct Variable_));
		vars[id]->var_id = id;
		vars[id]->offset = (locals[local_level]++) * 4;
		vars[id]->reg_no = -1;
	}
	//if var is not in register
	if(vars[id]->reg_no == -1) {
		reg_no = alloc_reg(id, 0);
		assert(reg_no >= 0 && reg_no < 32);
		vars[id]->reg_no = reg_no;
	}
	return vars[id]->reg_no;
}

void init_regs(){
	int i;
	for(i=0; i<32; i++){
		regs[i] = (Register)malloc(sizeof(struct Register_));
		regs[i]->use_id = -1;
		regs[i]->used = 0;
		//$zero cannot be used
		if(i==0) regs[i]->enable = 0;
		else regs[i]->enable = 1;
		//mark temp's flag = 1
		regs[i]->flag = 0;
	}
}

int alloc_reg(int id, int flg){
	int i;
	//find a unused register from $8-$15 and $24-$25
	ALLOC_REG:
	for(i=8; i<26; i++){
		if(i>15 && i<24)
			continue;
		if(regs[i]->enable == 1 && regs[i]->used == 0){
			assert(regs[i]->use_id == -1);
			regs[i]->used = 1;
			regs[i]->use_id = id;
			regs[i]->flag = flg;
			return i;
		}
	}
	//TODO:if there's no free register, try to sweep away some temps
	relieve++;
	if(relieve%2 == 1){
		for(i=8; i<16; i++){
			//if(i>15 && i<24)
			//	continue;
			if(regs[i]->enable == 1 && regs[i]->used == 1){
				//if the register is a temp variable
				if(regs[i]->flag == 1 && i != cur_regid){
					if(regs[i]->use_id == RAMDOM_ALLOC){
						free_reg(i, regs[i]->use_id);
					}
					else{
						assert(tmps[regs[i]->use_id]->temp_id == regs[i]->use_id);
						assert(tmps[regs[i]->use_id]->reg_no == i);
						//remove register of the temp;
						tmps[regs[i]->use_id]->reg_no = -1;
						free_reg(i, regs[i]->use_id);
						//return i;
					}
				}
			}
		}
	}
	else{
		for(i=24; i<26; i++){
			//if(i>15 && i<24)
			//	continue;
			if(regs[i]->enable == 1 && regs[i]->used == 1){
				//if the register is a temp variable
				if(regs[i]->flag == 1){
					if(regs[i]->use_id == RAMDOM_ALLOC){
						free_reg(i, regs[i]->use_id);
					}
					else{
						assert(tmps[regs[i]->use_id]->temp_id == regs[i]->use_id);
						assert(tmps[regs[i]->use_id]->reg_no == i);
						//remove register of the temp;
						tmps[regs[i]->use_id]->reg_no = -1;
						free_reg(i, regs[i]->use_id);
						//return i;
					}
				}
			}
		}
	}
	goto ALLOC_REG;
	//fail to allocate
	printf("Fail to allocate a reg!\n");
	return -1;
}

int free_reg(int reg_no, int id){
	int i;
	//if reg_no is active
	if(reg_no != -1){
		regs[reg_no]->used = 0;
		regs[reg_no]->use_id = -1;
		regs[reg_no]->flag = 0;
		return 1;
	}
	//if reg_no = -1, use id to free regs
	for(i=8; i<26; i++){
		if(i>15 && i<24)
			continue;
		if(regs[i]->enable == 1 && regs[i]->used == 1){
			if(regs[i]->use_id == id){
				regs[i]->used = 0;
				regs[i]->use_id = -1;
				regs[i]->flag = 0;
				return 1;
			}
		}
	}
	//fail to free the reg
	return 0;
}

Instructions store_live_variable(Instructions table){
	Instructions lw_list = NULL;
	Instructions inst = NULL;
	//int var_num = 0;//total var number
	var_num = 0;
	int var_count = 0;//count var to calculate offset
	int i;
	for(i=1; i<100; i++){
		if(vars[i] != NULL && vars[i]->reg_no != -1)
			var_num++;
	}
	//addi $sp (-4(n+1))($sp)
	inst = mips_gen_addi(29, 29, -4*(var_num + max(params_num-4, 0) + 1));
	table = link_inst(table, inst);
	//sw & lw handle together
	for(i=0; i<100; i++){
		if(vars[i] != NULL && vars[i]->reg_no != -1){
			//TODO
			//sw reg(i) (4x)($sp)
			inst = mips_gen_sw(vars[i]->reg_no, 29, (max(params_num-4, 0) + var_count)*4);
			table = link_inst(table, inst);
			//lw reg(i) (4x)($sp)
			inst = mips_gen_lw(vars[i]->reg_no, 29, (max(params_num-4, 0) + var_count)*4);
			lw_list = link_inst(lw_list, inst);
			var_count++;
		}
	}
	//sw $ra (4x)($sp)
	inst = mips_gen_sw(31, 29, (max(params_num-4, 0) + var_count)*4);
	table = link_inst(table, inst);
	//lw $ra (4x)($sp)
	inst = mips_gen_lw(31, 29, (max(params_num-4, 0) + var_count)*4);
	lw_list = link_inst(lw_list, inst);
	//addi $sp $sp 4(n+1)
	inst = mips_gen_addi(29, 29, 4*(max(params_num-4, 0) + var_num + 1));
	lw_list = link_inst(lw_list, inst);
	return lw_list;
}

int set_variable_reg(int var_no, int reg_no, int flag){
	int using_no;
	assert(reg_no >= 0 && reg_no < 32);
	assert(regs[reg_no]->enable == 1);
	//if the reg is being used by others
	if(regs[reg_no]->used == 1){
		using_no = regs[reg_no]->use_id;
		if(regs[reg_no]->flag == 1) 
			tmps[using_no]->reg_no = -1;
		else 
			vars[using_no]->reg_no = -1;
	}
	regs[reg_no]->used = 1;
	regs[reg_no]->use_id = var_no;
	//if the variable is not in the var table, insert it
	if(vars[var_no] == NULL){
		vars[var_no] = (Variable)malloc(sizeof(struct Variable_));
		vars[var_no]->var_id = var_no;
	}
	vars[var_no]->reg_no = reg_no;
	if(flag == 1)
		vars[var_no]->offset = (locals[local_level]++) * 4;
	return 1;
}


Operands mips_new_label(int label_no){
	Operands op = (Operands)malloc(sizeof(struct Operands_));
	op->kind = MIPS_OP_LABEL;
	op->u.label_no = label_no;
	return op;
}

Operands mips_new_func(char *func_name){
	Operands op = (Operands)malloc(sizeof(struct Operands_));
	op->kind = MIPS_OP_FUNC;
	op->u.func_name = func_name;
	return op;
}
Operands mips_new_addr(int reg_no, int offset){
	Operands op = (Operands)malloc(sizeof(struct Operands_));
	op->kind = MIPS_OP_ADDR;
	op->u.addr.reg_no = reg_no;
	op->u.addr.offset = offset;
	return op;
}

Operands mips_new_reg(int reg_no){
	Operands op = (Operands)malloc(sizeof(struct Operands_));
	op->kind = MIPS_OP_REG;
	op->u.reg_no = reg_no;
	return op;
}

Operands mips_new_imm(int value){
	Operands op = (Operands)malloc(sizeof(struct Operands_));
	op->kind = MIPS_OP_IMM;
	op->u.imm_value = value;
	return op;
}


Instructions mips_gen_sw(int reg, int base, int offset){
	Operands op1, op2;
	op1 = mips_new_reg(reg);
	op2 = mips_new_addr(base, offset);
	return mips_gen_two(MIPS_SW, op1, op2);
}

Instructions mips_gen_lw(int reg, int base, int offset){
	Operands op1, op2;
	op1 = mips_new_reg(reg);
	op2 = mips_new_addr(base, offset);
	return mips_gen_two(MIPS_LW, op1, op2);
}

Instructions mips_gen_addi(int result, int reg, int imm){
	Operands op1, op2, op3;
	op1 = mips_new_reg(result);
	op2 = mips_new_reg(reg);
	op3 = mips_new_imm(imm);
	return mips_gen_three(MIPS_ADDI, op1, op2, op3);
}

Instructions mips_gen_one(MipsInsType type, Operands op){
	Instructions ins = (Instructions)malloc(sizeof(struct Instructions_));
	ins->next = ins->prev = NULL;
	ins->inst = (Instruction)malloc(sizeof(struct Instruction_));
	ins->inst->kind = ONE_OP;
	ins->inst->u.oneop.instype = type;
	ins->inst->u.oneop.op = op;
	return ins;
}

Instructions mips_gen_two(MipsInsType type, Operands op1, Operands op2){
	Instructions ins = (Instructions)malloc(sizeof(struct Instructions_));
	ins->next = ins->prev = NULL;
	ins->inst = (Instruction)malloc(sizeof(struct Instruction_));
	ins->inst->kind = TWO_OP;
	ins->inst->u.twoop.instype = type;
	ins->inst->u.twoop.op1 = op1;
	ins->inst->u.twoop.op2 = op2;
	return ins;
}

Instructions mips_gen_three(MipsInsType type, Operands op1, Operands op2, Operands op3){
	Instructions ins = (Instructions)malloc(sizeof(struct Instructions_));
	ins->next = ins->prev = NULL;
	ins->inst = (Instruction)malloc(sizeof(struct Instruction_));
	ins->inst->kind = THREE_OP;
	ins->inst->u.threeop.instype = type;
	ins->inst->u.threeop.op1 = op1;
	ins->inst->u.threeop.op2 = op2;
	ins->inst->u.threeop.op3 = op3;
	return ins;
}

Instructions link_inst(Instructions l1, Instructions l2){
	Instructions tmp;
	if(l1 == NULL) return l2;
	if(l2 == NULL) return l1;
	tmp = l1;
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = l2;
	l2->prev = tmp;
	return l1;
}

void output_inst(Instruction inst){
	//fp2 = fopen("output.s", "w+"); 
	//assert(inst->kind != NULL);
	if(inst->kind == ONE_OP){
		switch(inst->u.oneop.instype){
		case MIPS_LABEL:
			if(inst->u.oneop.op->kind == MIPS_OP_LABEL)
				fprintf(fp2, "label%d:\n", inst->u.oneop.op->u.label_no);
			else if(inst->u.oneop.op->kind == MIPS_OP_FUNC)
				fprintf(fp2, "\n%s:\n", inst->u.oneop.op->u.func_name);
			else
				printf("LABEL is wrong?\n");
			return;
		case MIPS_J:
			fputs("\tj ", fp2); 
			break;
		case MIPS_JAL:
			fputs("\tjal ", fp2); 
			break;
		case MIPS_JR:
			fputs("\tjr ", fp2); 
			break;
		case MIPS_MFLO:
			fputs("\tmflo ", fp2); 
			break;
		}
		output_mips_op(inst->u.oneop.op);
		fputs("\n", fp2);
	}
	else if(inst->kind == TWO_OP){
		switch(inst->u.twoop.instype){
		case MIPS_LI:
			fputs("\tli ", fp2); 
			break;
		case MIPS_LA:
			fputs("\tla ", fp2); 
			break;
		case MIPS_MOVE:
			fputs("\tmove ", fp2); 
			break;
		case MIPS_LW:
			fputs("\tlw ", fp2); 
			break;
		case MIPS_SW:
			fputs("\tsw ", fp2); 
			break;
		case MIPS_DIV:
			fputs("\tdiv ", fp2); 
			break;
		}
		output_mips_op(inst->u.twoop.op1); 
		fputs(", ", fp2);
		output_mips_op(inst->u.twoop.op2);
		fputs("\n", fp2);
	}
	else{
		switch(inst->u.threeop.instype){
		case MIPS_ADDI:
			fputs("\taddi ", fp2); 
			break;
		case MIPS_ADD:
			fputs("\tadd ", fp2); 
			break;
		case MIPS_SUB:
			fputs("\tsub ", fp2); 
			break;
		case MIPS_MUL:
			fputs("\tmul ", fp2); 
			break;
		case MIPS_BEQ:
			fputs("\tbeq ", fp2); 
			break;
		case MIPS_BNE:
			fputs("\tbne ", fp2); 
			break;
		case MIPS_BGT:
			fputs("\tbgt ", fp2); 
			break;
		case MIPS_BLT:
			fputs("\tblt ", fp2); 
			break;
		case MIPS_BGE:
			fputs("\tbge ", fp2); 
			break;
		case MIPS_BLE:
			fputs("\tble ", fp2); 
			break;
		}
		output_mips_op(inst->u.threeop.op1); 
		fputs(", ", fp2);
		output_mips_op(inst->u.threeop.op2); 
		fputs(", ", fp2);
		output_mips_op(inst->u.threeop.op3); 
		fputs("\n", fp2);
	}
}

void output_mips_op(Operands op){
	switch(op->kind){
	case MIPS_OP_LABEL:
		fprintf(fp2, "label%d", op->u.label_no);
		break;
	case MIPS_OP_FUNC:
		fprintf(fp2, "%s", op->u.func_name);
		break;
	case MIPS_OP_REG:
		//fprintf(fp2, "$%d", op->u.reg_no);
		fprintf(fp2, "%s", reg_name[op->u.reg_no]);
		break;
	case MIPS_OP_IMM:
		fprintf(fp2, "%d", op->u.imm_value);
		break;
	case MIPS_OP_ADDR:
		//fprintf(fp2, "%d($%d)", op->u.addr.offset, op->u.addr.reg_no);
		fprintf(fp2, "%d(%s)", op->u.addr.offset, reg_name[op->u.addr.reg_no]);
	    	break;
	}
}

void output_read_write(){
	//fp2 = fopen("output.s", "w+"); 
	fputs(".data\n", fp2);
	fputs("_prompt: .asciiz \"Enter an integer:\"\n", fp2);
	fputs("_ret: .asciiz \"\\n\"\n", fp2);
	fputs(".globl main\n", fp2);
	fputs(".text\n", fp2);

	fputs("read:\n", fp2);
	fputs("\tli $v0, 4\n", fp2);
	fputs("\tla $a0, _prompt\n", fp2);
	fputs("\tsyscall\n", fp2);
	fputs("\tli $v0, 5\n", fp2);
	fputs("\tsyscall\n", fp2);
	fputs("\tjr $ra\n", fp2);

	fputs("\nwrite:\n", fp2);
	fputs("\tli $v0, 1\n", fp2);
	fputs("\tsyscall\n", fp2);
	fputs("\tli $v0, 4\n", fp2);
	fputs("\tla $a0, _ret\n", fp2);
	fputs("\tsyscall\n", fp2);
	fputs("\tmove $v0, $0\n", fp2);
	fputs("\tjr $ra\n", fp2);
}

int max(int a, int b)
{
    if(a>b) return a;
    else return b;
}
