#include "includes/fork_exec.h"
#include "includes/helper.h"
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

    char *check = fgets(buf, 1024, stdin);
    if (check == NULL) {
      exit(0);
    }
    // clearerr(stdin);

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
    // char **filename = get_filenames(tok);

    std::vector<RedirectionInfo> redir = getRedirectionInfo(tok);

    Redirection red_token = check_redirection_type(tok);

    switch (red_token) {
    case Redirection::nothing:
      handle_vanilla(tok, run_in_background);
      break;

    case Redirection::redirection:
      // cout << "comes into both" << endl;
      handl_both_redirection(tok, redir);
      break;

    case Redirection::piping:
      std::cout << "comes in piping" << std::endl;
      handle_piping(tok, redir);
      // handle piping here
      break;
    default:
      break;
    }

    free(tok);
  }
  return 0;
}
