#ifndef REDIRECTION_H
#define REDIRECTION_H

#include <cstring>
#include <iostream>

char *get_filename(char **tok);

enum Redirection { left, right, append, background, nothing };
bool check_bg_process(char **tok, int len);
Redirection check_redirection_type(char **tok);

#endif
