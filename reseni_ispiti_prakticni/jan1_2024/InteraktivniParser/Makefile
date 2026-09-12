parser: lexer.o parser.o
	g++ $^ -o $@

lex.yy.c: lexer.l parser.tab.hpp
	flex -l $<

lexer.o: lex.yy.c
	g++ -c $< -o $@

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<

parser.o: parser.tab.cpp parser.tab.hpp
	g++ -c $< -o $@

.PHONY: clean
clean:
	rm -rf *.o *.tab.* *.output *.gch lex.yy.c parser