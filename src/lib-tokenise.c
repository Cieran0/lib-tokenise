#include "tokenise.h"
#include "arena.h"
#include <string.h>
#include <stdbool.h>

//TODO: Improve this, O(N) is quite bad.
bool is_keyword(const char* buffer, const char** keywords, size_t keywords_length) {
    for (size_t i = 0; i < keywords_length; i++)
    {
        if(strcmp(buffer, keywords[i]) == 0) {
            return true;
        }
    }

    return false;
}

token* tokenise(const char* string_to_tokenise, const char** keywords, size_t keywords_length, const char* key_symbols) {
        

    bool symbols[256] = {false};

    memset(symbols, false, sizeof(symbols));

    for (size_t i = 0; key_symbols[i] != 0; i++)
    {
        symbols[(size_t)key_symbols[i]] = true;
    }
    

    arena_t* arena = new_arena();
    
    char buff[MAX_TOKEN_LENGTH] = {0};
    int buff_index = 0;


    //TODO: This is hideous
    for (size_t i = 0; string_to_tokenise[i] != 0; i++)
    {
        char current_char = string_to_tokenise[i];
        if(symbols[(size_t)current_char]) {
            if(buff_index > 0) {
                token* previous_token = (token*)arena_alloc(arena, sizeof(token));
                previous_token->type = is_keyword(buff, keywords, keywords_length) ? KEY_WORD_TOKEN : OTHER_TOKEN;
                memcpy(previous_token->content, buff, buff_index);
            }

            token* this_token = (token*)arena_alloc(arena, sizeof(token));
            this_token->type = KEY_SYMBOL_TOKEN;
            this_token->content[0] = current_char;

            memset(buff,0,MAX_TOKEN_LENGTH);
            buff_index = 0;

        } else if (current_char == ' ' || current_char == '\t' || current_char == '\n') {
            if(buff_index > 0) {
                token* previous_token = (token*)arena_alloc(arena, sizeof(token));
                previous_token->type = is_keyword(buff, keywords, keywords_length) ? KEY_WORD_TOKEN : OTHER_TOKEN;;
                memcpy(previous_token->content, buff, buff_index);
                memset(buff,0,MAX_TOKEN_LENGTH);
                buff_index = 0;
            }
        } else {
            buff[buff_index] = current_char;
            buff_index++;
        }


    }
    
    ((token*) arena_alloc(arena, sizeof(token)))->type = END_OF_TOKENS;
    
    token* tokens = arena->start;

    if (!tokens) {
        tokens = malloc(sizeof(token) * 2);
        tokens[0].type = ERROR_TOKEN;
        //TODO: actually have a reason why it failed.
        strcpy(tokens[0].content, "Failed to tokenise string");

        tokens[1].type = END_OF_TOKENS;
    }

    return tokens;
}