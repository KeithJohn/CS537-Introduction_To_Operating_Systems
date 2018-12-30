CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537ps
SCAN_BUILD_DIR = scan-build-out

all: main.o options_processing.o process_processing.o check_proc.o cmdln_parser.o statm_parser.o stat_parser.o
	$(CC) -o $(EXE) main.o options_processing.o process_processing.o check_proc.o cmdln_parser.o statm_parser.o stat_parser.o

main.o: main.c options_processing.h process_processing.h check_proc.h
	$(CC) $(WARNING_FLAGS) -c main.c

options_processing.o: options_processing.c options_processing.h
	$(CC) $(WARNING_FLAGS) -c options_processing.c

process_processing.o: process_processing.c process_processing.h check_proc.h stat_parser.h statm_parser.h cmdln_parser.h
	$(CC) $(WARNING_FLAGS) -c process_processing.c

check_proc.o: check_proc.c check_proc.h
	$(CC) $(WARNING_FLAGS) -c check_proc.c
cmdln_parser.o: cmdln_parser.c cmdln_parser.h
	$(CC) $(WARNING_FLAGS) -c cmdln_parser.c
stat_parser.o: stat_parser.c stat_parser.h
	$(CC) $(WARNING_FLAGS) -c stat_parser.c
statm_parser.o: statm_parser.c statm_parser.h
	$(CC) $(WARNING_FLAGS) -c statm_parser.c

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
