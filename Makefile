lab3: syntax.tab.c lex.yy.c semantic.c hash_table.c IR.c mips.c
	gcc -g syntax.tab.c hash_table.c semantic.c IR.c mips.c -lfl -ly -o lab4
syntax.tab.c: syntax.y lexical.l
	bison -d -v syntax.y 
lex.yy.c: lexical.l
	flex lexical.l
clean: 
	rm lex.yy.c syntax.tab.c syntax.tab.h lab4
