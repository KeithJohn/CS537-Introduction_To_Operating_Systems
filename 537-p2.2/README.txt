This program was created by Keith Ecker and Andy Achenreiner for CS 537
assignment 2. For this assignment we created a program that uses semaphores to 
create a shared queue between multiple threads. The program reads lines of 
input from stdin then replaces all spaces with asteriks and all lowercase with 
uppercase. We create 4 threads which process the line of text in different 
ways. First we have a reader thread which reads each line, a munch1 thread that 
replaces all spaces with a asterisk, munch 2 which replaces all lowercase with 
upper case, and finally writer which prints the new string to stdout. Each 
thread passes there string through a shared queue with the next thread in the 
process.