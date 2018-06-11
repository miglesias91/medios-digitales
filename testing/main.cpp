// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// vld
#if defined(DEBUG) || defined(_DEBUG)

#include <vld.h>

#endif

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

int main(int argc, char* argv[]) {

    int result = Catch::Session().run(argc, argv);

    std::getchar();

    return result;
}

// That's it

// Compile implementation of Catch for use with files that do contain tests:
// - g++ -std=c++11 -Wall -I$(CATCH_SINGLE_INCLUDE) -c 000-CatchMain.cpp
// - cl -EHsc -I%CATCH_SINGLE_INCLUDE% -c 000-CatchMain.cpp