#include "employees.h"

#define SEC_IN_DAY 86400

int scan_employees(Employee **res_arr, FILE* input_file) {
    int length = 0;
	resize_array(res_arr, length);
    Employee row;
    while ((fread(&row, sizeof(Employee), 1, input_file)) == 1) {
        (*res_arr)[length] = row;
        length += 1;
        resize_array(res_arr, length);
    }
    printf("DEBUG: length %d\n", length);
   return length;
}

void edit_row(Employee output_arr[], int pos) {
    Employee row;
    printf("Enter new employee.\nExample: 5 OGK Ivanov 80 25.02.2018 28.03.2024\n");
    scanf("%d %s %s %d %d.%d.%d %d.%d.%d",
        &row.id, row.dep, row.name, &row.salary,
        &row.begin.day, &row.begin.month, &row.begin.year,
        &row.end.day, &row.end.month, &row.end.year);
    output_arr[pos] = row;
}

void write_employees(Employee out_arr[], int length, FILE* output_file) {
    fwrite(out_arr, sizeof(Employee), length, output_file);

    // for (int i = 0; i < length; i++) {
    //     Employee row = out_arr[i];
    //     fprintf(output_file, "%d %s %s %d %d.%d.%d %d.%d.%d\n",
    //      row.id, row.dep, row.name, row.salary, 
    //      row.begin.day, row.begin.month, row.begin.year,
    //      row.end.day, row.end.month, row.end.year);
	// }
}

void print_employees(Employee out_arr[], int length) {
    for (int i = 0; i < length; i++) {
        Employee row = out_arr[i];
        printf("row %d: %d %s %s %d %d.%d.%d %d.%d.%d\n",
         i, row.id, row.dep, row.name, row.salary, 
         row.begin.day, row.begin.month, row.begin.year,
         row.end.day, row.end.month, row.end.year);
	}
}

void swap_arr_elements(Employee *pa, Employee *pb) {
    Employee temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void sort_employees_by_id(Employee input_arr[], int length, int desc) {
    for (int i = 0; i < length; i++) {
        for (int j = 1; j < length - i; j++) {
            if (
                desc == 1 && input_arr[j-1].id < input_arr[j].id ||
                desc == 0 && input_arr[j-1].id > input_arr[j].id 
            ) {
                swap_arr_elements(&input_arr[j-1], &input_arr[j]);
            }
        }
    }
}

void sort_employees_by_salary(Employee input_arr[], int length, int desc) {
    for (int i = 0; i < length; i++) {
        for (int j = 1; j < length - i; j++) {
            if (
                desc == 1 && input_arr[j-1].salary < input_arr[j].salary ||
                desc == 0 && input_arr[j-1].salary > input_arr[j].salary 
            ) {
                swap_arr_elements(&input_arr[j-1], &input_arr[j]);
            }
        }
    }
}

void sort_employees_by_dep(Employee input_arr[], int length, int desc) {
    int compare;
    for (int i = 0; i < length; i++) {
        for (int j = 1; j < length - i; j++) {
            compare = strcmp(input_arr[j-1].dep, input_arr[j].dep);
            if (
                desc == 1 && compare < 0 || 
                desc == 0 && compare > 0
            ) {
                swap_arr_elements(&input_arr[j-1], &input_arr[j]);
            }
        }
    }
}

void sort_employees_by_name(Employee input_arr[], int length, int desc) {
    int compare;
    for (int i = 0; i < length; i++) {
        for (int j = 1; j < length - i; j++) {
            compare = strcmp(input_arr[j-1].name, input_arr[j].name);
            if (
                desc == 1 && compare < 0 || 
                desc == 0 && compare > 0
            ) {
                swap_arr_elements(&input_arr[j-1], &input_arr[j]);
            }
        }
    }
}

int get_experience(Employee emp) {
    struct tm begin_tm = {0}, end_tm = {0};

    begin_tm.tm_year = emp.begin.year - 1900;
    begin_tm.tm_mon = emp.begin.month - 1;
    begin_tm.tm_mday = emp.begin.day;

    end_tm.tm_year = emp.end.year - 1900;
    end_tm.tm_mon = emp.end.month - 1;
    end_tm.tm_mday = emp.end.day;

    time_t begin_t, end_t;
    begin_t = mktime(&begin_tm);
    end_t = mktime(&end_tm);

    double experience;
    experience = difftime(end_t, begin_t);
    return experience / SEC_IN_DAY;
}

void sort_employees_by_experience(Employee input_arr[], int length, int desc) {
    int compare;
    for (int i = 0; i < length; i++) {
        for (int j = 1; j < length - i; j++) {
            if (
                desc == 1 && get_experience(input_arr[j-1]) < get_experience(input_arr[j]) || 
                desc == 0 && get_experience(input_arr[j-1]) > get_experience(input_arr[j])
            ) {
                swap_arr_elements(&input_arr[j-1], &input_arr[j]);
            }
        }
    }
}

void resize_array(Employee **p_arr, int cur_len) {
    *p_arr = (Employee*)realloc(*p_arr, (cur_len + STORAGE_SEGMENT_LEN) * sizeof(Employee));
}
