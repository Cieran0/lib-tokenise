#include "tokenise.h"
#include "stdio.h"

const char* file = "{\"employees\":[{ \"firstName\":\"Jo\\\"h\\\"n\", \"lastName\":\"Doe\", \"salary\":100.50 },{ \"firstName\":\"Anna\", \"lastName\":\"Smith\", \"salary\":-100.32 },{ \"firstName\":\"Peter\", \"lastName\":\"Jones\", \"salary\":-8.50 }]}";


int main() {
    const char* keywords[] = {"null", "true", "false"};
    const char* key_symbols = "{}:,[]";
    token* tokens = tokenise(file, keywords, 0, key_symbols);


    for (size_t i =0; tokens[i].type != END_OF_TOKENS; ++i) {
        printf("%d: \"%s\"\n", tokens[i].type, tokens[i].content);
    }

}