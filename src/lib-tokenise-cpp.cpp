#include "tokenise.h"

namespace Tokeniser {

// C++ implementation of tokenise
std::vector<token> tokenise(const std::string& string_to_tokenise, const std::vector<std::string>& keywords, const std::vector<char>& key_symbols) {
    
    const char** keywords_c_array = new const char*[keywords.size()]; 

    for (size_t i = 0; i < keywords.size(); i++)
    {
        keywords_c_array[i] = keywords[i].c_str();
    }
    
    std::unique_ptr<token[]> token_array (tokenise(string_to_tokenise.c_str(), keywords_c_array, keywords.size(), key_symbols.data()));

    std::vector<token> tokens;

    if (!token_array) {
        return tokens;
    }

    for (size_t i = 0; token_array[i].type != END_OF_TOKENS; ++i) {
        tokens.push_back(token_array[i]);
    }

    return tokens;
}
}