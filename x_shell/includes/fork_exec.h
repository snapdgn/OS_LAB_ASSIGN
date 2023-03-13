#ifndef FORKEXEC_H
#define FORKEXEC_H

void fork_exec_new(char **tok, char *filename, bool redirection,
                   int redirection_fd, bool run_in_background, int append_mode);

void redirect_fd(char *file_name, int redirection_fd, int append_mode);

#endif
