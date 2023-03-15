#ifndef REDIRECTION_H
#define REDIRECTION_H

#include <cstring>
#include <iostream>
#include <vector>

struct RedirectionInfo {
  std::string filename;
  bool isInputRedirection;
  bool isOutputRedirection;
  bool isOutputAppendRedirection;
};

std::vector<RedirectionInfo> getRedirectionInfo(char **);

enum Redirection { nothing, redirection, piping };

bool check_bg_process(char **, int);

Redirection check_redirection_type(char **tok);

void handle_vanilla(char **, bool);
void handle_piping(char **, std::vector<RedirectionInfo>);

void handl_both_redirection(char **, std::vector<RedirectionInfo>);

#endif
