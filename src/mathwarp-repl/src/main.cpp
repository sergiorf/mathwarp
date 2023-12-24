#include "evaluation.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "terminal_shell.h"
#include "CLI11/CLI11.hpp"
#include "linenoise/linenoise.hpp"

using namespace mathwarp;

class Definitions {
    // Assume Definitions class implementation
};

class Evaluation {
    // Assume Evaluation class implementation
};

class TerminalOutput {
    // Assume TerminalOutput class implementation
};

class MathicsFileLineFeeder {
    // Assume MathicsFileLineFeeder class implementation
};

// Assume BuiltinRule, TraceBuiltins, and other necessary classes are implemented

int main(int argc, char* argv[]) {
    int exit_rc = 0;

    CLI::App app{"A simple command-line interface to MathWarp"};
    CLI11_PARSE(app, argc, argv);

    // Setup completion words every time when a user types
    linenoise::SetCompletionCallback(
        [](const char* editBuffer, std::vector<std::string>& completions) {
          if (editBuffer[0] == 'h') {
            completions.push_back("hello");
            completions.push_back("hello there");
          }
        });

    linenoise::SetMultiLine(true);
    linenoise::SetHistoryMaxLen(4);

    int lineCounter = 1;

     while (true) {
      try {
        std::string line;
        auto quit = linenoise::Readline(
            ("In [" + std::to_string(lineCounter) + "]: ").c_str(), line);

        if (quit) {
          std::cout << "\n\nGoodbye!\n";
          break;
        }

        if (line.empty()) {
          continue;
        }

        std::string result = "";
        std::cout << "Out[" << lineCounter << "]: " << result << std::endl;

        // Add text to history
        linenoise::AddHistory(line.c_str());

        // Increase line counter
        lineCounter++;
      } catch (...) {
        std::cout << "\nAn error occurred\n";
        break;
      }
    }


    return exit_rc;
}
