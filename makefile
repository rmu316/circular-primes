circular: circular.o
	gcc -o circular -g circular.o
circular.o: circular.c
	gcc -g -c -Wall circular.c
clean:
	rm -f *.o circular  
