all : final
final :  cs335parser.tab.h cs335parser.tab.c lex.yy.c
	g++ -o final lex.yy.c cs335parser.tab.c 
lex.yy.c : cs335lexer.l cs335parser.tab.h
	flex cs335lexer.l
cs335parser.tab.h cs335parser.tab.c : cs335parser.y
	bison -t -d cs335parser.y
clean :
	rm -f final cs335parser.tab.c cs335parser.tab.h lex.yy.c 

