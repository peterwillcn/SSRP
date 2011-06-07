#ifndef _COMMAND_PARSER_
#define _COMMAND_PARSER_

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class commandParser {
private:

    typedef string commandArgument;

    vector<commandArgument> argList;

    int numErrors;

    bool assembleOutput;

    vector<string> argumentVector(int argc, const char* const argv[]);

    bool inputFromFile;

    string inputFilename;

    int statRunCount;

protected:

    string usage() const;

    bool isValid(const string&) const;

    void error(const string&);

    int activate(int ref, const vector<string>& args);

    int lookup(const string&) const;

    static const int npos = -1;

public:

    commandParser();

    void parse(const int, const char* const []);

    bool error() const;

    bool success() const;

    bool fileInput() const;

    string inputFile() const;

    int statRuns() const;
};

#endif