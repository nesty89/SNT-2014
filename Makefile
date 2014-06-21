NAME=xpavlu06
FILES=main.cpp sim.hpp node.cpp edge.cpp graph.cpp loader.cpp outPrinter.cpp
CC=g++ -std=c++0x

ALL:
	$(CC) -o $(NAME) $(FILES) 
clean:
	rm -f *.o $(NAME) *~ *.exe
tst:
	./$(NAME) test/sample.ss test/sample.gr test/sample.co
tst2:
	./$(NAME) test/sample.p2p test/sample.gr test/sample.co
