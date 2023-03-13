#ifndef FORKEXEC_H
#define FORKEXEC_H

void redirect_fd(char *file_name, int redirection_fd);

void fork_exec_new(char **tok, char *filename, bool redirection,
                   int redirection_fd, bool run_in_background);
#endif
