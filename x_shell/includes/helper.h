#ifndef __HELPER_H
#define __HELPER_H
#include <string>
#include <vector>
char **convert_vector_to_array(std::vector<std::string>);
char *convert_string_to_cstr(std::string);
char **get_tokens(char *);
#endif
