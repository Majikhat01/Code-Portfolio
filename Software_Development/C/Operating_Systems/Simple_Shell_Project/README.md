# Simple Shell Project

## Overview
This project is a simple Unix shell implementation.  
It supports features like sequences, pipelines, I/O redirection,  
and built-in commands such as 'cd' , 'pwd', 'exit', and 'history'.

## Features
- **Command Execution**: Execute standard Unix commands like 'ls', 'grep', etc.
- **Built-in Commands**: Includes 'cd', 'pwd', 'exit', and 'history'.
- **Sequences**: Execute commands in sequence using ';' and '&'.
- **Pipelines**: Use the pipe '|' operator to direct the output of one command to the input of another.
- **I/O Redirection**: Redirect input and output using '<', '>'.

## Requirements
- GCC Compiler
- GNU Readline Library

## Compilation
Compile the shell using the provided makefile:
```bash
make
```

### Usage
Run the shell executable:
```bash
./shell
```

Once the shell is running, you can enter commands just like in any other Unix shell:
```bash
$ ls -l
$ cat file.txt | grep search_term
./my_script.sh
```

## Testing
Compile the regression tester:
```bash
make test
```

Once the program is done compiling it will iterate through the test directories in Tests/  
Each Tests/Test_xxx directory contains three files (exp, inp, out).  
The tests compare the expected output with the actual output using the inp file as commands.


## Valgrind
To use valgrind on this project to check for memory leaks, first compile to program:
```bash
make
```

Once the program is done compiling, you can run the program using:
```bash
valgrind --leak-check=full ./shell
```

### Valgrind Output
```bash
[calvinhatfield@onyx hw3]$ make
gcc -o Pipeline.o -c Pipeline.c -g -Wall -MMD -D_GNU_SOURCE
gcc -o Parser.o -c Parser.c -g -Wall -MMD -D_GNU_SOURCE
gcc -o Interpreter.o -c Interpreter.c -g -Wall -MMD -D_GNU_SOURCE
gcc -o Sequence.o -c Sequence.c -g -Wall -MMD -D_GNU_SOURCE
gcc -o Jobs.o -c Jobs.c -g -Wall -MMD -D_GNU_SOURCE
gcc -o deq.o -c deq.c -g -Wall -MMD -D_GNU_SOURCE
gcc -o Command.o -c Command.c -g -Wall -MMD -D_GNU_SOURCE
gcc -o Shell.o -c Shell.c -g -Wall -MMD -D_GNU_SOURCE
gcc -o Scanner.o -c Scanner.c -g -Wall -MMD -D_GNU_SOURCE
gcc -o Tree.o -c Tree.c -g -Wall -MMD -D_GNU_SOURCE
gcc -o shell Pipeline.o Parser.o Interpreter.o Sequence.o Jobs.o deq.o Command.o Shell.o Scanner.o Tree.o -lreadline -lncurses -g
[calvinhatfield@onyx hw3]$ valgrind --leak-check=full ./shell
==1787571== Memcheck, a memory error detector
==1787571== Copyright (C) 2002-2022, and GNU GPL, by Julian Seward et al.
==1787571== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==1787571== Command: ./shell
==1787571==
$ pwd
/home/CalvinHatfield/CS452/homework3/hw3
$ ls
In child process, executing command: ls
Command.c  deq.h	  Interpreter.d  Jobs.o     Pipeline.c	Scanner.c   Sequence.h	Test	vg
Command.d  deq.o	  Interpreter.h  libdeq.so  Pipeline.d	Scanner.d   Sequence.o	Tree.c
Command.h  error.h	  Interpreter.o  Parser.c   Pipeline.h	Scanner.h   shell	Tree.d
Command.o  GNUmakefile	  Jobs.c	 Parser.d   Pipeline.o	Scanner.o   Shell.c	Tree.h
deq.c	   grammar.txt	  Jobs.d	 Parser.h   README.md	Sequence.c  Shell.d	Tree.o
deq.d	   Interpreter.c  Jobs.h	 Parser.o   rl.supp	Sequence.d  Shell.o	try
$ cd Test
$ pwd
Test
$ ls
In child process, executing command: ls
run  Test_cd  Test_history  Test_pwd
$ cd ..
$ pwd
..
$ ls
In child process, executing command: ls
Command.c  deq.h	  Interpreter.d  Jobs.o     Pipeline.c	Scanner.c   Sequence.h	Test	vg
Command.d  deq.o	  Interpreter.h  libdeq.so  Pipeline.d	Scanner.d   Sequence.o	Tree.c
Command.h  error.h	  Interpreter.o  Parser.c   Pipeline.h	Scanner.h   shell	Tree.d
Command.o  GNUmakefile	  Jobs.c	 Parser.d   Pipeline.o	Scanner.o   Shell.c	Tree.h
deq.c	   grammar.txt	  Jobs.d	 Parser.h   README.md	Sequence.c  Shell.d	Tree.o
deq.d	   Interpreter.c  Jobs.h	 Parser.o   rl.supp	Sequence.d  Shell.o	try
$ exit
==1787571==
==1787571== HEAP SUMMARY:
==1787571==     in use at exit: 139,744 bytes in 218 blocks
==1787571==   total heap usage: 769 allocs, 551 frees, 175,745 bytes allocated
==1787571==
==1787571== 393 (24 direct, 369 indirect) bytes in 1 blocks are definitely lost in loss record 27 of 54
==1787571==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1787571==    by 0x4020AA: deq_new (deq.c:218)
==1787571==    by 0x4019C2: newJobs (Jobs.c:12)
==1787571==    by 0x402DEB: main (Shell.c:16)
==1787571==
==1787571== LEAK SUMMARY:
==1787571==    definitely lost: 24 bytes in 1 blocks
==1787571==    indirectly lost: 369 bytes in 21 blocks
==1787571==      possibly lost: 0 bytes in 0 blocks
==1787571==    still reachable: 139,351 bytes in 196 blocks
==1787571==         suppressed: 0 bytes in 0 blocks
==1787571== Reachable blocks (those to which a pointer was found) are not shown.
==1787571== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==1787571==
==1787571== For lists of detected and suppressed errors, rerun with: -s
==1787571== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
