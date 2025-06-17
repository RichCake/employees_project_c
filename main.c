// Выполнил Карпов Арсений 313ИС-22
// ToDo-list
// 1.  [x] Меню
// 2.  [x] На оценку 4 и выше (4+). Запуск с аргументами командной строки
// 3.  [x] Чтение-запись в текстовый файл
// 4.  [x] Сортировка
// 5.  [x] Сортировка с выбором поля (4+)
// 6.  [x] Добавление, удаление, редактирование
// 7.  [x] Использование бинарного файла (4+)
// 8.  [x] Добавление, удаление, редактирование в файл (4+)
// 9.  [x] Сортировка файла (4+)
// 10. [ ] Использование индексного файла (4+)
/*
5 OGK Ivanov 80 25.02.2018 28.03.2024
2 OGT Petrov 100 26.02.2018 28.03.2025
3 OGBuh Dryahlova 150 12.03.2011 20.04.2025
4 OGK Vanyan 70 15.02.2013 11.03.2021
*/
#include "employees.h"

char input_filename[50];
char output_filename[50];

void start_menu() {
    Employee *storage = (Employee*)malloc(STORAGE_SEGMENT_LEN * sizeof(Employee));

    FILE *file, *out_f;
    int length = 0;
    int command;
    int exit = 0;
    int row_number;
    int ok;
    do {
        printf("Menu\n");
        printf("0.  Exit\n");
        printf("1.  Read file\n");
        printf("2.  Print storage\n");
        printf("3.  Add employee\n");
        printf("4.  Edit employee\n");
        printf("5.  Delete employee\n");
        printf("6.  Sort by id desc\n");
        printf("7.  Sort by id asc\n");
        printf("8.  Sort by dep desc\n");
        printf("9.  Sort by name desc\n");
        printf("10. Sort by salary desc\n");
        printf("11. Sort by experience desc\n");
        printf("12. Write file\n");
        if (scanf("%d", &command) != 1) {
            exit = 1;
        }
        switch (command)
        {
        case 0:
            exit = 1;
            break;
        case 1:
            file = fopen(input_filename, "rb");
            length = scan_employees(&storage, file);
            fclose(file);
            break;
        case 2:
            print_employees(storage, length);
            break;
        case 3:
            if (length % STORAGE_SEGMENT_LEN == 0) {
                resize_array(&storage, length);
            }
            edit_row(storage, length);
            length++;
            break;
        case 4:
            printf("Enter row number\n");
            ok = scanf("%d", &row_number);
            if (ok != 1 || row_number < 0 || row_number >= length) {
                printf("Error: incorrect row\n");
                break;
            }
            edit_row(storage, row_number);
            break;
        case 5:
            printf("Enter row number\n");
            ok = scanf("%d", &row_number);
            if (ok != 1 || row_number < 0 || row_number >= length) {
                printf("Error: incorrect row\n");
                break;
            }
            swap_arr_elements(&storage[length], &storage[row_number]);
            length--;
            break;
        case 6:
            if (length == 0) {
                printf("Error: storage is empty\n");
                break;
            }
            sort_employees_by_id(storage, length, 1);
            break;
        case 7:
            if (length == 0) {
                printf("Error: storage is empty\n");
                break;
            }
            sort_employees_by_id(storage, length, 0);
            break;
        case 8:
            if (length == 0) {
                printf("Error: storage is empty\n");
                break;
            }
            sort_employees_by_dep(storage, length, 1);
            break;
        case 9:
            if (length == 0) {
                printf("Error: storage is empty\n");
                break;
            }
            sort_employees_by_name(storage, length, 1);
            break;
        case 10:
            if (length == 0) {
                printf("Error: storage is empty\n");
                break;
            }
            sort_employees_by_salary(storage, length, 1);
            break;
        case 11:
            if (length == 0) {
                printf("Error: storage is empty\n");
                break;
            }
            sort_employees_by_experience(storage, length, 1);
            break;
        case 12:
            if (length == 0) {
                printf("Error: storage is empty\n");
                break;
            }
            out_f = fopen(output_filename, "wb");
            write_employees(storage, length, out_f);
            fclose(out_f);
            exit = 1;
            break;
        default:
            printf("Error: unknown command\n");
            break;
        }
        printf("\n");
    } while (exit != 1);
    free(storage);
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        strcpy(input_filename, argv[1]);
        strcpy(output_filename, argv[2]);
    } else {
        strcpy(input_filename, "input.txt");
        strcpy(output_filename, "output.txt");
    }

    start_menu();

	return 0;
}