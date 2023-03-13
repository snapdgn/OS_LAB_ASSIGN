#include "includes/common.h"
#include "includes/fork_exec.h"
// #include "includes/helper.h"
#include "includes/redirection.h"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sched.h>
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
using namespace std;

// static jmp_buf env;
static volatile sig_atomic_t mod = 0;

static sigjmp_buf env;
void sigint_handler(int signo) {
  if (!mod) {
    return;
  }
  siglongjmp(env, 2);
}
int main(int argc, char **argv) {

  signal(SIGINT, sigint_handler);
  while (1) {

    char pwd[1024];
    getcwd(pwd, 1024);
    printf("$%s > ", pwd);
    fflush(stdout);
    // for now assume that 1024 is the max no of bytes a user can enter

    if (sigsetjmp(env, 1) == 2) {
      printf("%c", '\n');
      continue;
    }
    mod = 1;
    char buf[1024] = {0};

    // char **buffer = NULL;
    // char **tokens = parseInput(buffer);

    fgets(buf, 1024, stdin);

    // char **tok = convert_vector_to_array(buf);

    char **tok = get_tokens(buf);

    int len = 0;
    while (tok[len] != NULL) {
      ++len;
    }
    int size_of_tok = len;

    if (size_of_tok == 0) {
      continue;
    }

    // check is process should run in background
    bool run_in_background = check_bg_process(tok, size_of_tok);
    // get filename
    // if no redirection is present, get_filename returns NULL
    char *filename = get_filename(tok);
    // check if rediretion is present or absent
    Redirection red_token = check_redirection_type(tok);

    if (red_token == Redirection::nothing) {
      fork_exec_new(tok, NULL, false, -1, run_in_background);
    } else if (red_token == Redirection::left) {
      if (filename != NULL) {
        fork_exec_new(tok, filename, true, 0, run_in_background);
      }
    } else if (red_token == Redirection::right) {
      if (filename != NULL) {
        fork_exec_new(tok, filename, true, 1, run_in_background);
      }
    }

    free(tok);
  }
  return 0;
}
