CC=g++
CFLAGS=-std=c++11 -c

all: clean csvreader

csvreader: main.o csv.o
	$(CC) main.o csv.o -o csvreader

main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp

csv.o: src/csv.cpp
	$(CC) $(CFLAGS) src/csv.cpp

test:
	./csvreader test1.csv
	./csvreader test2.csv
	./csvreader test3.csv
	./csvreader test4.csv
	./csvreader test5.csv

clean:
	rm -rf *.o csvreader
