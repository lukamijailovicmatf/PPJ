izvrsni: lex.yy.o parser.o
	g++ $^ -o $@

lex.yy.o: lex.yy.c
	g++ -c $<

parser.o: parser.cpp tokeni.hpp
	g++ -c $<

lex.yy.c: lexer.l tokeni.hpp
	flex $<

.PHONY: clean
clean:
	rm -f *.yy.* *.o izvrsni