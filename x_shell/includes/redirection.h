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

std::vector<RedirectionInfo> getRedirectionInfo(char **tok);

enum Redirection { nothing, redirection, piping };
bool check_bg_process(char **tok, int len);
Redirection check_redirection_type(char **tok);
void handle_piping(char **tok, std::vector<RedirectionInfo>);

void handl_both_redirection(char **tok, std::vector<RedirectionInfo>);

#endif
