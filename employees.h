#ifndef __EMP__
#define __EMP__
#define STORAGE_SEGMENT_LEN 5

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int id;
    char dep[20];
    char name[20];
    int salary;
    Date begin;
    Date end;
} Employee;

void free_storage(Employee*);
int scan_employees(Employee **res_arr, FILE* input_file);
void add_row(Employee output_arr[]);
void edit_row(Employee output_arr[], int pos);
void write_employees(Employee out_arr[], int length, FILE* output_file);
void print_employees(Employee out_arr[], int length);
void swap_arr_elements(Employee *pa, Employee *pb);
void sort_employees_by_id(Employee input_arr[], int length, int desc);
void sort_employees_by_salary(Employee input_arr[], int length, int desc);
void sort_employees_by_dep(Employee input_arr[], int length, int desc);
void sort_employees_by_name(Employee input_arr[], int length, int desc);
int get_experience(Employee emp);
void sort_employees_by_experience(Employee input_arr[], int length, int desc);
void resize_array(Employee**, int);
#endif