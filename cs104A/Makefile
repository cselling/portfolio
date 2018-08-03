# test comment

all:   main.o stringtable.o
	gcc -o oc -g -posix -Wall -Wextra -O0 -std=c99 main.o stringtable.o

main.o:   main.c
	gcc -c -g -posix -Wall -Wextra -O0 -std=c99 main.c

stringtable.o:  stringtable.c
	gcc -c -g -posix -Wall -Wextra -O0 -std=c99 stringtable.c

spotless:  
	rm oc
	rm main.o stringtable.o

clean:
	rm main.o stringtable.o

