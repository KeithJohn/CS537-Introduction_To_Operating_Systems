CC=gcc
SCAN_BUILD_DIR = scan-build-out
EXE=output
main=error_testcase4

all: main.o 537malloc.o AVL.o
	$(CC) -o $(EXE) main.o 537malloc.o AVL.o

# main.c is your testcase file name
main.o: $(main).c
	$(CC) -Wall -Wextra -c $(main).c
	mv $(main).o main.o

# Include all your .o files in the below rule
obj: 537malloc.o AVL.o

537malloc.o: 537malloc.c 537malloc.h AVL.h
	$(CC) -Wall -Wextra -g -O0 -c 537malloc.c

AVL.o: AVL.c AVL.h
	$(CC) -Wall -Wextra -g -O0 -c AVL.c

clean:
	rm *.o $(EXE)

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
