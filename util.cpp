#include "util.h"

using namespace std;

string ltrim(const string &s) {
    return regex_replace(s, regex("^\\s+"), string(""));
}
 
string rtrim(const string &s) {
    return regex_replace(s, regex("\\s+$"), string(""));
}
 
string trim(const string &s) {
    return ltrim(rtrim(s));
}

void toLower(string &original){
    for_each(original.begin(), original.end(), [](char & c){
    c = ::tolower(c);
    });
}

string trimAndLower(string &original){
    string result = trim(original);
    toLower(result);
    return result;
}