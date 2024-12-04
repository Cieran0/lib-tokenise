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
    char string_buff[MAX_TOKEN_LENGTH] = {0};
    int buff_index = 0;


    //TODO: This is hideous
    for (size_t i = 0; string_to_tokenise[i] != 0; i++)
    {
        char current_char = string_to_tokenise[i];
        if(current_char == '\"') {
            if(buff_index > 0) {
                token* previous_token = (token*)arena_alloc(arena, sizeof(token));
                previous_token->type = is_keyword(buff, keywords, keywords_length) ? KEY_WORD_TOKEN : OTHER_TOKEN;
                memcpy(previous_token->content, buff, buff_index);
            }
            buff_index = 0;


            int k = 0;
            int j = i+1;
            while (string_to_tokenise[j] != 0)
            {
                if(string_to_tokenise[j] == '\"') {
                    if(string_to_tokenise[j-1] == '\\') {
                        string_buff[--k] = '\"';
                    } else {
                        break;
                    }
                }
                string_buff[k++] = string_to_tokenise[j];
                j++;
            }
            string_buff[k++] = '\0';
            
            token* this_token = (token*)arena_alloc(arena, sizeof(token));
            this_token->type = STRING_TOKEN;
            memcpy(this_token->content, string_buff, k);
            i = j;
            
            continue;
        }
        
        
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
            continue;
        }
        
        if (current_char == ' ' || current_char == '\t' || current_char == '\n') {
            if(buff_index > 0) {
                token* previous_token = (token*)arena_alloc(arena, sizeof(token));
                previous_token->type = is_keyword(buff, keywords, keywords_length) ? KEY_WORD_TOKEN : OTHER_TOKEN;;
                memcpy(previous_token->content, buff, buff_index);
                memset(buff,0,MAX_TOKEN_LENGTH);
                buff_index = 0;
            }
            continue;
        }

        buff[buff_index] = current_char;
        buff_index++;
    }
    
    ((token*) arena_alloc(arena, sizeof(token)))->type = END_OF_TOKENS;
    
    token* tokens = arena->start;

    free(arena);

    if (!tokens) {
        tokens = malloc(sizeof(token) * 2);
        tokens[0].type = ERROR_TOKEN;
        //TODO: actually have a reason why it failed.
        strcpy(tokens[0].content, "Failed to tokenise string");

        tokens[1].type = END_OF_TOKENS;
    }

    return tokens;
}