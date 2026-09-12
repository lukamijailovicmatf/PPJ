parser: lexer.o parser.o skup.o
	g++ $^ -o $@

skup.o: skup.cpp skup.hpp
	g++ -c $< -o $@

parser.o: parser.tab.cpp parser.tab.hpp
	g++ -c $< -o $@

lexer.o: lex.yy.c
	g++ -c $< -o $@

lex.yy.c: lexer.l parser.tab.hpp
	flex -l $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<

.PHONY: clean
clean:
	rm parser *.o *.yy.* *.tab.* *.output
