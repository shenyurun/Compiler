%{
/*definitions of manifest constants*/
#include "syntax.tab.h"
#include "syntax_tree.h"
//int yylineno = 1;
int yycolumn = 1;
unsigned int error_num = 0;

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
	yylloc.first_column = yycolumn; \
	yylloc.last_column = yycolumn + yyleng - 1; \
	yycolumn += yyleng;

struct TreeNode* create_node(char *name, enum Type tag, char *value);

%}

/*regular definitions*/
DELIM		[ \t]
WS		{DELIM}+
DIGIT		[0-9]
LETTER		[A-Za-z]
INT		0|([1-9]{DIGIT}*)
OCT		0([0-7]+)
HEX		0(x|X)[0-9a-fA-F]+
FLOAT		{INT}(\.{DIGIT}+)?
ID		({LETTER}|_)({LETTER}|{DIGIT}|_)*
LINE		[\n]

%option yylineno

%%

{WS}		{	}
";"		{ yylval.node_value = create_node("SEMI", RES_T, 0); return SEMI; }
","		{ yylval.node_value = create_node("COMMA", RES_T, 0); return COMMA; }
"="		{ yylval.node_value = create_node("ASSIGNOP", RES_T, 0); return ASSIGNOP; }
">"|"<"|">="|"<="|"=="|"!="	{ yylval.node_value = create_node("RELOP", STR_T, yytext); return RELOP; }
"+"		{ yylval.node_value = create_node("PLUS", RES_T, 0); return PLUS; }
"-"		{ yylval.node_value = create_node("MINUS", RES_T, 0); return MINUS; }
"*"		{ yylval.node_value = create_node("STAR", RES_T, 0); return STAR; }
"/"		{ yylval.node_value = create_node("DIV", RES_T, 0); return DIV; }
"&&"		{ yylval.node_value = create_node("AND", RES_T, 0); return AND; }
"||"		{ yylval.node_value = create_node("OR", RES_T, 0); return OR; }
"."		{ yylval.node_value = create_node("DOT", RES_T, 0); return DOT; }
"!"		{ yylval.node_value = create_node("NOT", RES_T, 0); return NOT; }
"("		{ yylval.node_value = create_node("LP", RES_T, 0); return LP; }
")"		{ yylval.node_value = create_node("RP", RES_T, 0); return RP; }
"["		{ yylval.node_value = create_node("LB", RES_T, 0); return LB; }
"]"		{ yylval.node_value = create_node("RB", RES_T, 0); return RB; }
"{"		{ yylval.node_value = create_node("LC", RES_T, 0); return LC; }
"}"		{ yylval.node_value = create_node("RC", RES_T, 0); return RC; }
"int"|"float"	{ yylval.node_value = create_node("TYPE", STR_T, yytext); return TYPE; }
"struct"	{ yylval.node_value = create_node("STRUCT", RES_T, 0); return STRUCT; }
"return"	{ yylval.node_value = create_node("RETURN", RES_T, 0); return RETURN; }
"if"		{ yylval.node_value = create_node("IF", RES_T, 0); return IF; }
"else"		{ yylval.node_value = create_node("ELSE", RES_T, 0); return ELSE; }
"while"		{ yylval.node_value = create_node("WHILE", RES_T, 0); return WHILE; }
{LINE}		{ yycolumn = 1; }
{INT}		{ yylval.node_value = create_node("INT", INT_T, yytext); return INT;}
{OCT}		{ 
			char *temp = (char*)malloc(20);
			sprintf(temp, "%d", oct_to_i(yytext));
			yylval.node_value = create_node("INT", INT_T, temp);
			free(temp);	
			return INT;
		}
{HEX}		{ 
			char *temp = (char*)malloc(20);
			sprintf(temp, "%d", hex_to_i(yytext));
			yylval.node_value = create_node("INT", INT_T, temp);
			free(temp);	
			return INT;
		}
{FLOAT}		{ yylval.node_value = create_node("FLOAT", FLOAT_T, yytext); return FLOAT; }
{ID}		{ yylval.node_value = create_node("ID", STR_T, yytext); return ID; }
. 		{ printf("Error type A at line %d: Mysterious character \'%s\'\n", yylineno, yytext); error_num++; }

%%

struct TreeNode* create_node(char *name, enum Type type, char *value){
	struct TreeNode *p = (NodePtr)malloc(sizeof(Node));
	p->content.name = name;
	p->content.type = type;
	p->content.lineno = yylineno;
	if(type == STR_T){
		p->content.str_value = (char*)malloc(sizeof(char)*(strlen(value)+1));
		memcpy(p->content.str_value, value, strlen(value)+1);
	}
	else if(type == INT_T){
		p->content.int_value = atoi(value);
	}
	else if(type == FLOAT_T){
		p->content.float_value = atof(value);
	}
	return p;
}

int oct_to_i(char *oct) {
	int n = *oct - '0';
	while (*(++oct) != '\0') n = n*8 + *oct - '0';
	return n;
}

int hex_to_i(char *hex) {
	int len = strlen(hex) - 2;
	int i;
	char ihex[len];
	hex += 2;
	for(i=0; i<len; i++){
		ihex[i] = *hex;
		hex++;
	}
	int m,n=0;
	for(i=0; i<len; i++){
		if(ihex[i]>='0' && ihex[i]<='9') m = ihex[i]-'0';
		else if(ihex[i]>='a' && ihex[i]<='f') m = ihex[i]-'a'+10;
		else if(ihex[i]>='A' && ihex[i]<='F') m = ihex[i]-'A'+10;
		else printf("Wrong Hex\n");
		if(m >= 0) n = n*16 + m;
	}
	return n;
}
/*
int main(int argc, char** argv){
	if (argc > 1){
		if (!(yyin = fopen(argv[1], "r"))){
			perror(argv[1]);
			return 1;
		}
	}
	while (yylex() != 0) ;
	return 0;
}
*/
