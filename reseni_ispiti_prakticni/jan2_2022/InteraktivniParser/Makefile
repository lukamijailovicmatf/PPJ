parser: parser.o lexer.o Razlomak.o
	g++ $^ -o $@

Razlomak.o: Razlomak.cpp Razlomak.hpp
	g++ -c $< -o $@

lexer.o: lex.yy.c parser.tab.hpp
	g++ -c $< -o $@

parser.o: parser.tab.cpp parser.tab.hpp
	g++ -c $< -o $@

lex.yy.c: lexer.l parser.tab.hpp
	flex -l $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<

.PHONY: clean
clean:
	rm -f *.tab.* *.yy.* *.o *.output parser