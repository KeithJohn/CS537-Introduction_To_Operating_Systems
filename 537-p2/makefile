CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = prodcomm
SCAN_BUILD_DIR = scan-build-out

all: main.o queue.o
	$(CC) -o $(EXE) main.o queue.o -lpthread

main.o: main.c
	$(CC) $(WARNING_FLAGS) -c main.c

queue.o: queue.c queue.h 
	$(CC) $(WARNING_FLAGS) -c queue.c

clean:
	rm -f *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html  
