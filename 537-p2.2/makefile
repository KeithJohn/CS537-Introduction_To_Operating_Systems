CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = prodcomm
SCAN_BUILD_DIR = scan-build-out

all: main.o queue.o writer.o reader.o munch1.o munch2.o
	$(CC) -o $(EXE) main.o queue.o writer.o reader.o munch1.o munch2.o -lpthread

main.o: main.c
	$(CC) $(WARNING_FLAGS) -c main.c

queue.o: queue.c queue.h 
	$(CC) $(WARNING_FLAGS) -c queue.c

writer.o: writer.c writer.h
	$(CC) $(WARNING_FLAGS) -c writer.c
reader.o: reader.c reader.h
	$(CC) $(WARNING_FLAGS) -c reader.c
munch1.o: munch1.c munch1.h
	$(CC) $(WARNING_FLAGS) -c munch1.c
munch2.o: munch2.c munch2.h
	$(CC) $(WARNING_FLAGS) -c munch2.c
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
