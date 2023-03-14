#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#define BUFSIZE 1024
#define DELIMS " \t\r\n\a"

#include <iostream>
#include <vector>
using namespace std;

char **convert_vector_to_array(vector<std::string> tok) {
  // allocate memory for the c-style array of strings(char**)
  char **cstr_arr = new char *[tok.size() + 1];

  size_t len = tok.size();
  for (size_t i = 0; i < len; i++) {
    cstr_arr[i] = new char[tok[i].size() + 1];
    std::strcpy(cstr_arr[i], tok[i].c_str());
  }
  cstr_arr[len] = NULL;

  return cstr_arr;
}

// char *convert_string_to_cstr(std::string) {

//}

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
