#pragma once
#include "stdlib.h"

#ifdef __cplusplus
// C++ function declaration
#include <memory>
#include <string>
#include <vector>
namespace Tokeniser { 
extern "C" {
#endif

#define KEY_SYMBOL_TOKEN 0
#define KEY_WORD_TOKEN 1
#define OTHER_TOKEN 2
#define ERROR_TOKEN 3
#define END_OF_TOKENS 4
#define STRING_TOKEN 5

#define MAX_TOKEN_LENGTH 256

struct token
{
    size_t line_number;
    size_t start_index;
    size_t end_index;
    unsigned char type;
    char content[MAX_TOKEN_LENGTH];
} typedef token;

/*
    If fails, [0].type = ERROR_TOKEN, with [0].content = Reason.
*/
token* tokenise(const char* string_to_tokenise, const char** keywords, size_t keywords_length, const char* key_symbols);

#ifdef __cplusplus
} // extern "C"


/*
    If fails, [0].type = ERROR_TOKEN, with [0].content = Reason.
*/
std::vector<token> tokenise(const std::string& string_to_tokenise, const std::vector<std::string>& keywords, const std::vector<char>& key_symbols);
}
#endif
