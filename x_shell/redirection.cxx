#include <cstring>
#include <iostream>

#include "includes/redirection.h"

bool check_bg_process(char **tok, int len) {
  if (strcmp(tok[len - 1], "&") == 0) {
    return true;
  }
  return false;
}

Redirection check_redirection_type(char **tok) {
  int index = 0;
  Redirection red_token = nothing;
  while (tok[index] != NULL) {
    if (strcmp(tok[index], "<") == 0) {
      red_token = left;
    } else if (strcmp(tok[index], ">") == 0) {
      red_token = right;
    } else if (strcmp(tok[index], ">>") == 0) {
      red_token = append;
    }
    index++;
  }
  // if (strcmp(tok[index - 1], "&") == 0) {
  // red_token = background;
  //}
  return red_token;
}

char *get_filename(char **tok) {
  char *filename = NULL;
  int i = 0;
  while (tok[i] != NULL) {
    if ((strcmp(tok[i], "<") == 0) || (strcmp(tok[i], ">") == 0)) {
      filename = strdup(tok[i + 1]);
      return filename;
    }
    i++;
  }
  return NULL;
}
