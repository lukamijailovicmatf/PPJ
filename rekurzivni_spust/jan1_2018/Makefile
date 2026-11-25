(CXX) = g++

izvrsni: lex.yy.o parser.o
	$(CXX) $^ -o $@

lex.yy.o: lex.yy.c
	$(CXX) -c $<

parser.o: parser.cpp tokeni.hpp
	$(CXX) -c $<

lex.yy.c: lexer.l tokeni.hpp
	flex $<

.PHONY: clean
clean:
	rm -f *.yy.* *.o izvrsni