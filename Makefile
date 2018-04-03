CFLAGS=-fpic 

all: main
	./main

anso.so: anso.o
	gcc -shared -o libanso.so anso.o -ldl 

main: main.o anso.so
	gcc -o main main.o -L. -lanso -Wl,-rpath,'$$ORIGIN'

clean:
	rm -f *.o *.so main
