#include "tokenise.h"
#include <memory>
#include <iostream>

const std::string file = R"(subscriber add(int x, int y, int result) {
    result = x + y;
}

subscriber init(int x, int y) {
    x = ((x == 0) ? 10 : x);
    y = ((y == 0) ? 11 : x);
}

subscriber main(const string[] args) {
    event cool_thing = { init, add };

    while (true) {
        @cool_thing;
        int cool_result = cool_thing[result];
        int other_result = (@(cool_thing[] = { x: 20, y: 5 }))[result];
    }

    @(exit[] = { err: 1 } );
}

subscriber die(int err) {
    err = 10;
}
)";;

int main() {
    std::vector<std::string> keywords = {"subscriber", "int", "event", "while", "true", "const"};
    std::vector<char> key_symbols = {'=', '+', ';', '?', '(', ')', ':', '[',']', '{','}','@', ','};
    std::vector<Tokeniser::token> x = Tokeniser::tokenise(file, keywords, key_symbols);


    for (Tokeniser::token t : x)
    {
        std::cout << (int)t.type << ": \"" << (t.content) << "\"" <<std::endl;
    }
}