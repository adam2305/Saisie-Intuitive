main.o: main.c data.h prediction.h 
	gcc -c main.c -lncurses `pkg-config --cflags --libs gtk+-3.0` 

data.o: data.c data.h
	gcc -c data.c -lm

prediction.o: prediction.c prediction.h data.h
	gcc -c prediction.c -lm

main: main.o data.o prediction.o 
	gcc main.o data.o prediction.o -o main -lm -Wno-format `pkg-config --cflags --libs gtk+-3.0` -Wno-deprecated-declarations -Wno-fromat-security -export-dynamic
