#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){

    char *filename = argv[1];

    FILE *output_file = fopen(filename, "w");

    if (output_file == NULL) {
        perror("Не получилось открыть файл с таким названием\n");
        exit(1);
    }

    char buffer[1024];

    while (1){

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break; 
        }
        buffer[strcspn(buffer, "\n")] = 0;

        int numbers[100];
        int count = 0;
        char *token = strtok(buffer, " ");

        while (token != NULL && count < 100) {
            numbers[count++] = atoi(token);
            token = strtok(NULL, " ");
        }

        if (count < 2) {
            fprintf(output_file, "Ошибка: Нужно хотя бы два числа\n");
            fflush(output_file);
            continue;
        }
        int has_zero = 0;

        for (int i = 1; i < count; i++) {
            if (numbers[i] == 0) {
                fprintf(output_file, "Ошибка: Деление на нуль\n");
                fflush(output_file);
                has_zero = 1;
                break;
            }
        }
        if (has_zero) {

            fclose(output_file);
            exit(1);
        }
        fprintf(output_file, "%d", numbers[0]);
        int result = numbers[0];

        for (int i = 1; i < count; i++) {
            result /= numbers[i];
            fprintf(output_file, " / %d", numbers[i]);
        }

        fprintf(output_file, " = %d\n", result);
        fflush(output_file);

    }

    fclose(output_file);
    return 0;
}
