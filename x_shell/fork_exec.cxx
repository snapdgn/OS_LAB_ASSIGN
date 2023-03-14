#include <csignal>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/wait.h>

void redirect_fd(const char *file_name, int redirection_fd, int append_mode);

void remove_string(char ***tok) {
  if (!*tok || !*((*tok) + 1)) {
    return;
  }
  // handle this better by implementing `getchar`
  int idx = 0;
  for (int i = 0; (*tok)[i] != NULL; i++) {
    if (strcmp((*tok)[i], "<") == 0 || strcmp((*tok)[i], ">") == 0 ||
        strcmp((*tok)[i], ">>") == 0) {
      idx = i;
      // std::cout << "caught >>" << std::endl;
      break;
    }
  }

  for (int i = idx; (*tok)[i]; i++) {
    (*tok)[i] = nullptr;
  }
}

void fork_exec_new(char **tok, const char *filename, bool redirection,
                   int redirection_fd, bool run_in_background,
                   int append_mode) {

  pid_t wpid;
  int status;
  pid_t pid = fork();

  if (pid == 0) {
    if (redirection) {
      if (filename != NULL) {
        redirect_fd(filename, redirection_fd, append_mode);
      }

      remove_string(&tok);
    }

    if (execvp(tok[0], tok) == -1) {
      fprintf(stderr, "Invalid Command: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  } else if (pid < 0) {
    perror("forking error");
  } else {
    if (!run_in_background) {
      wpid = waitpid(pid, &status, WUNTRACED);
      // while (!WIFEXITED(status) && !WIFSIGNALED(status))
    }
  }
}

void redirect_fd(const char *file_name, int redirection_fd, int append_mode) {

  ssize_t fd = 0;

  // TODO: handle ">>" append properly here, doesn't work for now
  if (redirection_fd == STDIN_FILENO) {
    fd = open(file_name, O_RDONLY);
  } else if (redirection_fd == STDOUT_FILENO) {
    if (append_mode) {
      fd = open(file_name, (O_WRONLY | O_CREAT | O_APPEND), 0644);
    } else {
      fd = open(file_name, (O_WRONLY | O_CREAT | O_TRUNC), 0644);
    }
  }
  //} else if (redirection_fd == STDOUT_FILENO) {
  // fd = open(file_name, (O_WRONLY | O_CREAT | O_TRUNC), 0644);
  //}

  if (fd == -1) {
    perror("Error Opening File");
    exit(EXIT_FAILURE);
  }

  if (dup2(fd, redirection_fd) == -1) {
    perror("error, dup-ing");
    exit(EXIT_FAILURE);
  }
  // if (dup2(original_fd, redirection_fd ? STDOUT_FILENO : STDIN_FILENO) ==
  // -1) { perror("dup2"); exit(EXIT_FAILURE);
  //}
  close(fd);
  fflush(stdout);
}
