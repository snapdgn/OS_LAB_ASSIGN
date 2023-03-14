#ifndef FORKEXEC_H
#define FORKEXEC_H

void fork_exec_new(char **, const char *, bool, int, bool, int);

void redirect_fd(const char *, int, int);
void remove_string(char ***);

#endif
