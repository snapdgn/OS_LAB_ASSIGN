#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#include "includes/fork_exec.h"
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
    switch (tok[index][0]) {
    case '<':
      red_token = redirection;
      break;
    case '>':
      if (strcmp(tok[index], ">>") == 0) {
        red_token = redirection;
      } else {
        red_token = redirection;
      }
      break;
    case '|':
      red_token = piping;
      break;
    default:
      break;
    }
    index++;
  }
  return red_token;
}
// handle different scenarios of redirection

void handle_piping(char **tok, std::vector<RedirectionInfo> redir) {
  // handle piping
}

void handl_both_redirection(char **tok, std::vector<RedirectionInfo> redir) {

  // extract filenames and their corresponding redirection type
  std::map<std::string, int> fd_info;
  for (size_t i = 0; i < redir.size(); i++) {
    if (redir[i].isInputRedirection) {
      fd_info[redir[i].filename] = STDIN_FILENO;
    } else {
      fd_info[redir[i].filename] = STDOUT_FILENO;
    }
  }

  pid_t pid = fork();

  if (pid == -1) {
    perror("fork error");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {

    // open file
    // bool has_output_redirection = false;
    for (auto &[filename, fd] : fd_info) {
      int file_fd;
      if (fd == STDIN_FILENO) {
        file_fd = open(filename.c_str(), O_RDONLY);
      } else {
        // has_output_redirection = true;
        file_fd = open(filename.c_str(), (O_WRONLY | O_CREAT | O_TRUNC), 0644);
      }
      if (file_fd == -1) {
        perror("Error Opening File!!");
        exit(EXIT_FAILURE);
      }

      if (dup2(file_fd, fd) == -1) {
        perror("Error in IO redirection");
        exit(EXIT_FAILURE);
      }
      close(file_fd);
    }

    // if (!has_output_redirection) {
    // if (dup2(STDOUT_FILENO, STDOUT_FILENO) == -1) {
    // perror("Error in IO redirection");
    // exit(EXIT_FAILURE);
    //}
    //}

    // remove the rest of the args
    remove_string(&tok);
    if (execvp(tok[0], tok) == -1) {
      fprintf(stderr, "Invalid Command: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  } else { // parent process
    int status;
    if (waitpid(pid, &status, 0) == -1) {
      perror("waitpid error");
      exit(EXIT_FAILURE);
    }
  }

  // std::map<std::string, int>::iterator it = fd_info.begin();
  // while (it != fd_info.end()) {
  // std::cout << "Key: " << it->first << ", Value: " << it->second <<
  // std::endl;
  //++it;
  //}
  // open file descriptors accordingly
}

std::vector<RedirectionInfo> getRedirectionInfo(char **tok) {
  std::vector<RedirectionInfo> redirections;
  int i = 0;
  while (tok[i] != NULL) {
    if (strcmp(tok[i], "<") == 0) {
      if (tok[i + 1] != NULL) {
        RedirectionInfo info;
        info.filename = std::string(tok[i + 1]);
        info.isInputRedirection = true;
        info.isOutputRedirection = false;
        info.isOutputAppendRedirection = false;
        redirections.push_back(info);
      }
    } else if (strcmp(tok[i], ">") == 0) {
      if (tok[i + 1] != NULL) {
        RedirectionInfo info;
        info.filename = std::string(tok[i + 1]);
        info.isInputRedirection = false;
        info.isOutputRedirection = true;
        info.isOutputAppendRedirection = false;
        redirections.push_back(info);
      }
    } else if (strcmp(tok[i], ">>") == 0) {
      if (tok[i + 1] != NULL) {
        RedirectionInfo info;
        info.filename = std::string(tok[i + 1]);
        info.isInputRedirection = false;
        info.isOutputRedirection = false;
        info.isOutputAppendRedirection = true;
        redirections.push_back(info);
      }
    }
    i++;
  }
  return redirections;
}
