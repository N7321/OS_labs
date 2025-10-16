#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


int main()
{
    int pipe1[2];
    int pipe2[2];
    pid_t pid;
    char filename[50];

    

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1){
      perror("Не удалось создать pipe1 или pipe2\n");
      exit(1);
    }

    printf("%s", "Введите имя файла: ");

    if (fgets(filename, sizeof(filename), stdin) == NULL){
      perror("Не получилось прочитать название!\n");
      exit(1);
    }

    filename[strcspn(filename, "\n")] = 0;

    pid = fork();

    if(pid<0){
      perror("Сегодня без fork\n");
      exit(1);
    }
    else if(pid == 0){
      close(pipe1[1]);
      close(pipe2[0]);

      dup2(pipe1[0], STDIN_FILENO);
      close(pipe1[0]);
      execl("./child", "child", filename, NULL);

      perror("Ничего ты не понимаешь в execl\n");
      exit(1);

    }
    else{
      close(pipe1[0]);
      close(pipe2[1]);
      char input[1024];
      printf("%s", "Введите числа, разделенные пробелом, а затем нажмите enter\n");

      if (fgets(input, sizeof(input), stdin) == NULL) {
          perror("У меня что то при чтении случилось\n");
        }
      write(pipe1[1], input, strlen(input));

      close(pipe1[1]);
      wait(NULL);
      printf("%s", "Родительский процесс успешно завершился\n");
      
    }
    return 0;
}
