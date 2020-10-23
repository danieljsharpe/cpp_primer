/* vector<string> to char * conversion */

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> symbols = {"IF1209", "IF1210"};
    std::vector<const char *> chars(symbols.size());

    std::for_each(symbols.begin(), symbols.end(), [](std::string& s) {
        std::cout << s << std::endl;
    });

    std::transform(symbols.begin(), symbols.end(), chars.begin(), std::mem_fun_ref(&std::string::c_str));

    std::for_each(chars.begin(), chars.end(), [](const char *s) {
        std::cout << s << std::endl;
    });

    return 0;
}
