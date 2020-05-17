CC=g++ -std=c++0x

all: solution

solution: main.o expression.o tokenizer.o parser.o
	$(CC) -o solution main.o expression.o tokenizer.o parser.o

main.o: main.cpp
	$(CC) -c main.cpp

expression.o: expression.cpp
	$(CC) -c expression.cpp

tokenizer.o: tokenizer.cpp
	$(CC) -c tokenizer.cpp

parser.o: parser.cpp
	$(CC) -c parser.cpp

run: solution
	./solution

clean:
	rm -rf *.o solution
