#include <cstring>
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

// char **parseInput() {

//}

//// Free the memory allocated for the char array
//// for (size_t i = 0; i < len; i++) {
//// delete[] cstr_arr[i];
////}
//// delete[] cstr_arr;
////
//// char input;
//// char *word;
//// char buffer[1024] = {0};

// while ((input = getchar() != '\n')) {
// if (input == '\t' || input == ' ') {
//// push the word
//} else {
// word += input;
//}
//}
// char input;
// string word;
// vector<string> buf;
// while ((input = getchar()) != '\n') {
// input = getchar();
// if (input == '\t' || input == ' ') {
// if (!word.empty()) {
// buf.push_back(word);
// word.clear();
//}
//} else {
// word += input;
//}
//}

//// if (!word.empty()) {
//// buf.push_back(word);
////}
