/* The ifndef... define... endif pattern is common when creating header files
   in C++. It prevents the header file from being included multiple times by
   using pre-preocessor macros (search HEADER GUARDS)

   Including the same header file multiple times in C++ can 1) increase compile
   time and 2) cause compilation errors due to re-defining functions,
   classes, etc. (search ONE DEFINITION RULE) */

#ifndef COLOURS_H
#define COLOURS_H

#include <string>

using std::string;

/* Usage: 1) print the color name, which causes all subsequent text to be that
   color, then 2) print RESET when you want to revert to the shell's default
   color.

   e.g.
   cout << RED << "hello world" << RESET << "\n"; */

const string RESET = "\x1B[0m";
const string RED =  "\x1B[31m";
const string GREEN = "\x1B[32m";
const string YELLOW = "\x1B[33m";
const string BLUE = "\x1B[34m";
const string MAGENTA = "\x1B[35m";
const string CYAN = "\x1B[36m";
const string WHITE = "\x1B[37m";

#endif
