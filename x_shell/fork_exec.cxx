#include <csignal>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/wait.h>

void redirect_fd(char *file_name, int redirection_fd);

void remove_string(char ***tok) {
  if (!*tok || !*((*tok) + 1)) {
    return;
  }
  for (int i = 1; (*tok)[i]; i++) {
    (*tok)[i] = nullptr;
  }
}

void fork_exec_new(char **tok, char *filename, bool redirection,
                   int redirection_fd, bool run_in_background) {

  // std::cout << *tok << std::endl;
  // std::cout << filename << std::endl;
  pid_t wpid;
  int status;
  pid_t pid = fork();
  // handles redirection of file descriptor here
  if (pid == 0) {
    if (redirection) {
      if (filename != NULL) {
        redirect_fd(filename, redirection_fd);

        // remove all the other words in the tok, except 1st one, tok should
        // remain the same
        remove_string(&tok);

        // tok = &tok[0];
        // if (execlp(tok[0], tok[0], NULL) == -1) {
        // fprintf(stderr, "Invalid Command: %s\n", strerror(errno));
        //}
        // exit(EXIT_FAILURE);
        // return;
      }
    }
    // signal(SIGINT, SIG_DFL);
    if (execvp(tok[0], tok)) {
      exit(0);
    }
    if (execvp(tok[0], tok) == -1) {
      fprintf(stderr, "Invalid Command: %s\n", strerror(errno));
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("forking error");
  } else {
    if (!run_in_background) {
      wpid = waitpid(pid, &status, WUNTRACED);
    }
  }
  // while (!WIFEXITED(status) && !WIFSIGNALED(status))
}

void redirect_fd(char *file_name, int redirection_fd) {

  // int original_fd = redirection_fd;
  int fd = open(file_name,
                redirection_fd ? (O_WRONLY | O_CREAT | O_TRUNC | O_APPEND)
                               : O_RDONLY,
                0644);
  if (fd == -1) {
    perror("Error Opening File");
    exit(EXIT_FAILURE);
  }

  if (dup2(fd, redirection_fd ? STDOUT_FILENO : STDIN_FILENO) == -1) {
    perror("error, dup-ing");
    exit(EXIT_FAILURE);
  }
  // if (dup2(original_fd, redirection_fd ? STDOUT_FILENO : STDIN_FILENO) == -1)
  // { perror("dup2"); exit(EXIT_FAILURE);
  //}
  close(fd);
}
