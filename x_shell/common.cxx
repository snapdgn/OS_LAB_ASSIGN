#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#define BUFSIZE 1024
#define DELIMS " \t\r\n\a"

char **get_tokens(char *buf) {
  // assumes that user passes atmost 1024 bytes
  // TODO: use reallocation if bytes exceed 1024
  char **tok = (char **)malloc(BUFSIZE * sizeof(char *));

  if (!tok) {
    fprintf(stderr, "Allocation Error\n");
    exit(EXIT_FAILURE);
  }
  // currently doesn't support escaping characters
  // just splits and gets the tokens on whitespace characters
  // TODO: Handle escape characters
  char *token = strtok(buf, DELIMS);

  int pos = 0;
  while (token != nullptr) {
    tok[pos++] = token;
    token = strtok(nullptr, DELIMS);
  }
  tok[pos] = NULL;
  return tok;
}

// void fork_exec_single(char *cmd) {
// pid_t wpid;
// int status;
// pid_t pid = fork();

// if (pid == 0) {
// signal(SIGINT, SIG_DFL);
// if (execlp(cmd, cmd, NULL)) {
// exit(0);
//}
// if (execlp(cmd, cmd, NULL) == -1) {
// fprintf(stderr, "Invalid Command: %s\n", strerror(errno));
//}
// exit(EXIT_FAILURE);
//} else if (pid < 0) {
// perror("forking error");
//} else {
// wpid = waitpid(pid, &status, WUNTRACED);
//}
//}
// void fork_exec(char **tok, bool run_in_background) {
// pid_t wpid;
// int status;
// pid_t pid = fork();
// if (pid == 0) {
// signal(SIGINT, SIG_DFL);
// if (execvp(tok[0], tok)) {
// exit(0);
//}
// if (execvp(tok[0], tok) == -1) {
// fprintf(stderr, "Invalid Command: %s\n", strerror(errno));
//}
// exit(EXIT_FAILURE);
//} else if (pid < 0) {
// perror("forking error");
//} else {
// if (!run_in_background) {
// wpid = waitpid(pid, &status, WUNTRACED);
//}
//}
//// while (!WIFEXITED(status) && !WIFSIGNALED(status))
//}

// void redirect_fd(char *cmd, char *file_name, int redirection_fd) {
// int original_fd = redirection_fd ? dup(STDOUT_FILENO) : dup(STDIN_FILENO);

// int fd = open(file_name,
// redirection_fd ? (O_WRONLY | O_CREAT | O_TRUNC | O_APPEND)
//: O_RDONLY,
// 0644);
// if (fd == -1) {
// perror("Error Opening File");
// exit(EXIT_FAILURE);
//}

// if (dup2(fd, redirection_fd ? STDOUT_FILENO : STDIN_FILENO) == -1) {
// perror("error, dup-ing");
// exit(EXIT_FAILURE);
//}
// fork_exec_single(cmd);
// close(fd);

// if (dup2(original_fd, redirection_fd ? STDOUT_FILENO : STDIN_FILENO) == -1) {
// perror("dup2");
// exit(EXIT_FAILURE);
//}
// close(original_fd);
//}
