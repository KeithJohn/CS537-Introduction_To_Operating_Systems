This program is created by Keith Ecker and Andy Achenreiner for CS537 at the 
University of Wisconsin - Madison. This
program attempts to recreate the make command. It searches the directory for a 
makefile than checks the targets and it's
dependencies. If the target is out of date it runs any commands that are 
associated with the given target.

Valgrind Errors Format
File; 
line numbers; 
errors;
Solution.

build_specification.c; 
59, 63; 
864 bytes in 6 blocks are definately lost;
Fixed by freeing the targetBuffer.

build_specification_graph.c;
92, 95;
384 (240 direct, 144 indirect) bytes in 10 blocks are defini
tely lost;
Fixed by freeing the listi.

linked_list.c;
35;
No Error;
Added a Free_list method to be used in freeing lists that
are causing many of the errors.

linked_list.h;
34;
No Error;
Added Free_list to the .h file so other files can use it.

process_execution.c;
42, 43;
96 bytes in 1 blocks are definately lost,
288 bytes in 6 blocks are definately lost;
Freed the list of args for executing command.
Freed the array of args used for executing command.

text_parser.c;
141, 142;
10,400 (160 direct, 10,240 indirect) bytes in 10 blocks are 
definitely lost;
Freed the allocated string and the allocated array.

text_parser.c;
140;
10,640 (240 direct, 10,400 indirect) bytes in 10 blocks are definitely lost;
Freed the list.

text_parser.c;
157, 162;
101,624 (744 direct, 100,880 indirect) bytes in 31 blocks are definitely lost in loss record 48 of 49;
Freed the list.

text_parser.c;
212;
101,624 (744 direct, 100,880 indirect) bytes in 31 blocks are definitely lost in loss record 49 of 49;
Freed the list.

text_parser.c;
233, 234;
10,400 (160 direct, 10,240 indirect) bytes in 10 blocks are definitely lost;
Freed the string.
Freed the array.

text_parser.c;
239, 246:
400 (240 direct, 160 indirect) bytes in 10 blocks are defini
tely lost,
544 (240 direct, 304 indirect) bytes in 10 blocks are defini
tely lost;
Freed the list in both cases.

text_parser.c;
267;
10,680 (24 direct, 10,656 indirect) bytes in 1 blocks are de
finitely lost;
Freed the list.

text_parser.c;
305;
11,464 (24 direct, 11,440 indirect) bytes in 1 blocks are de
finitely lost,
31,344 (144 direct, 31,200 indirect) bytes in 6 blocks are d
efinitely lost;
Freed the list.

