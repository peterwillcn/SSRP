#include "color.h"
#include <string>

using namespace std;

const string ansi(string code){
    return "\033[" + code + "m";
}