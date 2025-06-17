all: main

main: main.c employees.c employees.h
	gcc employees.c main.c -o main