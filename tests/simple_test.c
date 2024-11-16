#include "tokenise.h"
#include "stdio.h"

const char* file = "subscriber add(int x, int y, int result) {\n"
"    result = x + y;\n"
"}\n"
"\n"
"subscriber init(int x, int y) {\n"
"    x = ((x == 0) ? 10 : x);\n"
"    y = ((y == 0) ? 11 : x);\n"
"}\n"
"\n"
"subscriber main(const string[] args) {\n"
"    event cool_thing = { init, add };\n"
"\n"
"    while (true) {\n"
"        @cool_thing;\n"
"        int cool_result = cool_thing[result];\n"
"        int other_result = (@(cool_thing[] = { x: 20, y: 5 }))[result];\n"
"    }\n"
"\n"
"    @(exit[] = { err: 1 } );\n"
"}\n"
"\n"
"subscriber die(int err) {\n"
"    err = 10;\n"
"}";


int main() {
    const char* keywords[] = {"subscriber", "int", "event", "while", "true", "const"};
    char key_symbols[] = {'=', '+', ';', '?', '(', ')', ':', '[',']', '{','}','@', ','};
    token* tokens = tokenise(file, keywords, 6, key_symbols);


    for (size_t i =0; tokens[i].type != END_OF_TOKENS; ++i) {
        printf("%d: \"%s\"\n", tokens[i].type, tokens[i].content);

    }

}