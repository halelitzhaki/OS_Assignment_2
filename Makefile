all: codeA.so codeB.so encode decode stshell

stshell: stshell.o
	gcc -o stshell stshell.o

encode: encode.o
	gcc -o encode encode.o ./codeA.so ./codeB.so 

decode: decode.o
	gcc -o decode decode.o ./codeA.so ./codeB.so

stshell.o: stshell.c
	gcc -c stshell.c

codeB.so: codeB.o codeB.h
	gcc -shared -o codeB.so codeB.o

codeA.so: codeA.o codeA.h
	gcc -shared -o codeA.so codeA.o
	
decode.o: decode.c codeA.h codeB.h
	gcc -c decode.c

encode.o: encode.c codeA.h codeB.h
	gcc -c encode.c

codeB.o: codeB.c codeB.h
	gcc -c codeB.c

codeA.o: codeA.c codeA.h
	gcc -c codeA.c
	
clean:
	rm *.o *.so encode decode stshell
