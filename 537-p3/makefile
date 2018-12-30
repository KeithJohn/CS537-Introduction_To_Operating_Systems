537make: main.o linked_list.o text_parser.o build_specification.o build_specification_graph.o process_execution.o
	gcc -g -O0 -o 537make main.o linked_list.o text_parser.o build_specification.o build_specification_graph.o process_execution.o

main.o:main.c
	gcc -g -O0 -Wall -Wextra -c main.c
linked_list.o: linked_list.c linked_list.h
	gcc -g -O0 -Wall -Wextra -c linked_list.c

text_parser.o: text_parser.c text_parser.h
	gcc -g -O0 -Wall -Wextra -c text_parser.c
build_specification.o: build_specification.c build_specification.h
	gcc -g -O0 -Wall -Wextra -c build_specification.c
build_specification_graph.o: build_specification_graph.c build_specification_graph.h
	gcc -g -O0 -Wall -Wextra -c build_specification_graph.c
process_execution.o: process_execution.c process_execution.h
	gcc -g -O0 -Wall -Wextra -c process_execution.c
clean:
	rm -f main.o
	rm -f linked_list.o
	rm -f text_parser.o
	rm -f build_specification.o
	rm -f build_specification_graph.o
	rm -f process_execution.o
	rm -rf scan-build-out

scan-build: clean
	scan-build -o scan-build-out make

scan-view: scan-build
	firefox -new-window scan-build-out/*/index.html
