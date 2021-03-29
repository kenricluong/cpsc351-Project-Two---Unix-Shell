#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


char** parse(char* s) {
  static char* words[500];
  memset(words, 0, sizeof(words));
  
  char break_chars[] = " \t";
  int i = 0;
  char* p = strtok(s, break_chars);
  words[i++] = p;
  while (p != NULL) {
    p = strtok(NULL, break_chars);
    words[i++] = p;
  }
  return words;
}


int main(int argc, const char * argv[], char ** args) {  
  char input[BUFSIZ];
  char last_command[BUFSIZ];
  
  
  memset(input, 0, BUFSIZ * sizeof(char));
  memset(last_command, 0, BUFSIZ * sizeof(char));
  bool finished = false;
  pid_t pid = fork();

  while (!finished) {
    printf("osh> ");
    fflush(stdout);

    if ((fgets(input, BUFSIZ, stdin)) == NULL) {   // or gets(input, BUFSIZ);
      fprintf(stderr, "no command entered\n");
      exit(1);
    }
    input[strlen(input) - 1] = '\0';          // wipe out newline at end of string
    printf("input was: \n'%s'\n", input);

    // check for history (!!) command
    if (strncmp(input, "!!", 2) == 0) {
      if (strlen(last_command) == 0) {
        fprintf(stderr, "no last command to execute\n");
    }
    printf("last command was: %s\n", last_command);
    args = parse(last_command);

    } else if (strncmp(input, "exit", 4) == 0) {   // only compare first 4 letters
      finished = true;
    } else {
      strcpy(last_command, input);
      printf("You entered: %s\n", input);   // you will call fork/exec
      parse(input);
      //fork
        pid = fork();
        if(pid < 0){
          printf("\nfailed to fork child\n");
        }
        if(pid > 0){
           wait(NULL);
           printf("\nParent Executed");
        }
        if(pid == 0){
          printf("\nChild process executed");
          execvp(args[0], args);
        }
			printf("after parse, what is input: %s\n", input);
      printf("\n");
    }
  }
  
  printf("osh exited\n");
  printf("program finished\n");
  
  return 0;
}

//////////////////OUTPUTS//////////////////////
////osh> cat program.c &
////osh> shell can run concurrently, e.g., osh> cat program.c &....
////osh> ls  
////a.out        fig4-23.c  out.txt     program.c     thrd-posix.c  ThreadPoolExample.java  unixshell.c  ushell1    ushell.c
////Driver.java  openmp.c   pingpong.c  SumTask.java  thrd-win32.c  unixshell               ushell       ushell1.c
////osh> exit()
////osc@ubuntu:~/final-src-osc10e/ch4$ 
////osh> ls -l
////total 124
////-rwxrwxr-x 1 osc osc 13952 Mar 24 23:10 a.out
////-rw-rw-r-- 1 osc osc  1046 Jun 19  2018 Driver.java
////-rw-rw-r-- 1 osc osc  1034 Jun 19  2018 fig4-23.c
////-rw-rw-r-- 1 osc osc   549 Dec 19  2012 openmp.c
////-rw---S--T 1 osc osc   123 Mar 24 23:13 out.txt
////-rw-rw-r-- 1 osc osc  2472 Mar 27 12:20 pingpong.c
////-rw-rw-r-- 1 osc osc    59 Mar 28 22:59 program.c
////-rw-rw-r-- 1 osc osc  1639 Jun 19  2018 SumTask.java
////-rw-rw-r-- 1 osc osc  1366 Jan  3  2018 thrd-posix.c
////-rw-rw-r-- 1 osc osc  1067 Jan  3  2018 thrd-win32.c
////-rw-rw-r-- 1 osc osc   845 Jun 19  2018 ThreadPoolExample.java
////-rwxrwxr-x 1 osc osc 13560 Mar 28 23:03 unixshell
////-rw-rw-r-- 1 osc osc  2472 Mar 28 23:03 unixshell.c
////-rwxrwxr-x 1 osc osc 13952 Mar 24 23:09 ushell
////-rwxrwxr-x 1 osc osc 13376 Mar 24 23:22 ushell1
////-rw-rw-r-- 1 osc osc  4129 Mar 24 23:22 ushell1.c
////-rw-rw-r-- 1 osc osc  6654 Mar 24 23:31 ushell.c
////osh> !!
////total 124
////-rwxrwxr-x 1 osc osc 13952 Mar 24 23:10 a.out
////-rw-rw-r-- 1 osc osc  1046 Jun 19  2018 Driver.java
////-rw-rw-r-- 1 osc osc  1034 Jun 19  2018 fig4-23.c
////-rw-rw-r-- 1 osc osc   549 Dec 19  2012 openmp.c
////-rw---S--T 1 osc osc   123 Mar 24 23:13 out.txt
////-rw-rw-r-- 1 osc osc  2472 Mar 27 12:20 pingpong.c
////-rw-rw-r-- 1 osc osc    59 Mar 28 22:59 program.c
////-rw-rw-r-- 1 osc osc  1639 Jun 19  2018 SumTask.java
////-rw-rw-r-- 1 osc osc  1366 Jan  3  2018 thrd-posix.c
////-rw-rw-r-- 1 osc osc  1067 Jan  3  2018 thrd-win32.c
////-rw-rw-r-- 1 osc osc   845 Jun 19  2018 ThreadPoolExample.java
////-rwxrwxr-x 1 osc osc 13560 Mar 28 23:03 unixshell
////-rw-rw-r-- 1 osc osc  2472 Mar 28 23:03 unixshell.c
////-rwxrwxr-x 1 osc osc 13952 Mar 24 23:09 ushell
////-rwxrwxr-x 1 osc osc 13376 Mar 24 23:22 ushell1
////-rw-rw-r-- 1 osc osc  4129 Mar 24 23:22 ushell1.c
////-rw-rw-r-- 1 osc osc  6654 Mar 24 23:31 ushell.c
////