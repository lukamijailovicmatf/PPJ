izvrsni: parser.tab.o lex.yy.o Formula.o
	g++ $^ -o $@

Formula.o: Formula.cpp Formula.hpp
	g++ -c $<

parser.tab.o: parser.tab.cpp
	g++ -c $<

lex.yy.o: lex.yy.c
	g++ -c $<

lex.yy.c: lekser.l parser.tab.hpp
	flex $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp

.PHONY: clean
clean:
	rm *.yy.* *.tab.* *.output izvrsni *.o