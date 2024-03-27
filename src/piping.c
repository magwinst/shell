#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/parsing.h"
#include "../include/piping.h"
#include "../include/resolve.h"

// part c, successfully implemented piping

int execute_piping(char ***commands) {
  int n = 0;
  while (commands[n])
    ++n;
  int pipe_arr[n - 1][2];

  for (int i = 0; i < n - 1; ++i) {
    if (pipe(pipe_arr[i]) == -1) {
      perror("error: pipe failed");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < n; ++i) {
    pid_t pid = fork();
    if (pid == 0) {
      if (i > 0)
        dup2(pipe_arr[i - 1][0], STDIN_FILENO);
      if (i < n - 1)
        dup2(pipe_arr[i][1], STDOUT_FILENO);
      for (int i = 0; i < n - 1; ++i) {
        close(pipe_arr[i][0]);
        close(pipe_arr[i][1]);
      }

      char *path = resolve_path(commands[i][0]);
      if (path != NULL) {
        execv(path, commands[i]);
        perror("execv");
        free(path);
      } else {
        fprintf(stderr, "error: command not found: %s\n", commands[i][0]);
      }
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < n - 1; ++i) {
    close(pipe_arr[i][0]);
    close(pipe_arr[i][1]);
  }

  for (int i = 0; i < n; ++i) {
    wait(NULL);
  }

  return 1;
}
