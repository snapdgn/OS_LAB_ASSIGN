#ifndef HELPER_H
#define HELPER_H

#include <cstring>
#include <fcntl.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

#include <string>
#include <vector>

char **get_tokens(char *buf);
// void fork_exec(char **tok, bool run_in_background);
// void fork_exec_single(char *cmd, bool run_in_background);
// void redirect_fd(char *cmd, char file_name[], int redirect_fd);

#endif
