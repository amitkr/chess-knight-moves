/*
Copyright (c) <2012> <amitkr@rocketmail.com> http://github.com/amitkr

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include <stdlib.h>
#include <getopt.h>
#include <error.h>
#include <errno.h>
#include <ctype.h>

#include "Piece.h"

unsigned long ALPHABET_SIZE = ('Z' - 'A') + 1;

unsigned long str2num(char *s) {
    unsigned long w = 1, value = 0;
    while (*s) {
        value += (toupper(*s) - 'A' + 1) * w;
        w *= ALPHABET_SIZE;
        ++s;
    }
    
    return value;
}

std::string& num2str(unsigned long n) {
    std::string *s = new std::string();
    s->empty();
    unsigned long q = n;
    while (q > ALPHABET_SIZE) {
        unsigned long r = q % ALPHABET_SIZE;
        s->push_back(char(r + 'A' - 1));
        q /= ALPHABET_SIZE;
    }
    s->push_back(char(q + 'A' - 1));

    return *s;
}

/**
 * tokenize a string
 */
std::vector <std::string> &split(const std::string & s, char delim,
                   std::vector <std::string> &e) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        e.push_back(item);
    }
    return e;
}

std::vector <std::string> split(const std::string & s, char delim) {
    std::vector <std::string> e;
    return split(s, delim, e);
}

void displayHelp(char* p) {
    std::cout<<
        "Knights travel on chessboard" << std::endl <<
        "Usage: " << p << " [options] --from <position> --to <position>" << std::endl <<
        "  Options:" << std::endl <<
        "    --from | --start | -s    <position>   - initial position of knight" << std::endl <<
        "    --to   | --end   | -t    <position>   - end position of knight" << std::endl <<
        "    --help | -h      | -?                 - display this help" << std::endl
        ;
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[], char *argp[]) {
    int verbose = 0;
    int help = 0;
    unsigned long ranks = 0ul, files = 0ul;
    std::string from;
    std::string to;
    int c;

    while (true) {
        int optsIndex = 0;

        static struct option longOpts[] = {
            {"verbose",       no_argument,       &verbose,  1 },
            {"help",          no_argument,       &help,     1 },
            {"files",         required_argument, 0,        'F'},
            {"board-width",   required_argument, 0,        'F'},
            {"ranks",         required_argument, 0,        'R'},
            {"board-height",  required_argument, 0,        'R'},
            {"start",         required_argument, 0,        's'},
            {"from",          required_argument, 0,        'f'},
            {"end",           required_argument, 0,        'e'},
            {"to",            required_argument, 0,        't'},
            {0,              0,                  0,         0 }
        };

        c = getopt_long(argc, argv, "vF:R:s:f:e:t:h?", longOpts, &optsIndex);

        if (c == -1)
            break;

        switch (c) {
        case 0:
            // std::cout << "option " << longOpts[optsIndex].name;
            if (longOpts[optsIndex].flag != 0) {
                // std::cout << std::endl;
                break;
            }
            /*
            if (optarg)
                std::cout << " with args " << optarg << std::endl;
            */
            break;
        case 'F': 
            // files = optarg;
            if (isalpha(optarg[0])) {
                const char* arg = optarg;
                bool flag = true;
                while (*arg) {
                    if (!isalpha(*arg)) {
                        flag = false;
                        break;
                    }
                    ++arg;
                }

                if (flag) {
                    // convert to number
                    files = str2num(optarg);
                }
            } else {
                errno = 0;
                files = strtoul(optarg, NULL, 10);
                if (errno != 0) {
                    perror("Error in option -F:");
                    exit (errno);
                }
            }

            std::cout << "option -F " << files << "(" << num2str(files) << ")" << std::endl;
            break;
        case 'R':
            // 1...n
            // ranks = optarg;
            errno = 0;
            ranks = strtoul(optarg, NULL, 10);
            if (errno != 0) {
                perror("Error in option -R:");
                exit (errno);
            }

            std::cout << "option -R " << ranks << std::endl;
            break;
        case 's':
        case 'f':
            // std::cout << "option -s " << optarg << std::endl;
            from = optarg;
            break;
        case 'e':
        case 't':
            // std::cout << "option -e " << optarg << std::endl;
            to = optarg;
            break;
        case 'v':
            // std::cout << "option -v";
            verbose = 1;
            break;
        case 'h':
        case '?':
            // std::cout << "help" << std::endl;
            displayHelp(argv[0]);
            break;
        default:
            std::cerr << "Unknown arg" << std::endl;
            break;
        }
    }

    // create a chess board
    // Chess::CHESS_BOARD *board = new Chess::CHESS_BOARD();
    // Chess::Knight k(Chess::T_COORDS(std::string(" de56  ")));
    // Chess::Knight *k = new Chess::Knight(Chess::T_COORDS(std::string(from)));
    // std::cout << *k << std::endl;
    // std::cout << k->getMoves() << std::endl;
    
    // Can do without a board for now!
    Chess::Knight k1(from);
    Chess::T_COORDS toc = Chess::T_COORDS(to);
    std::list<Chess::T_COORDS> path = k1.findPath(toc);

    std::cout << "From: " << Chess::T_COORDS(from) << std::endl;
    std::cout << "To: " << toc << std::endl;
    std::cout << "Path: ";
    if (path.empty()) {
        std::cout << "No path!" << std::endl;
    } else {
        for (std::list<Chess::T_COORDS>::const_iterator it = path.begin();
                it != path.end(); ++it) {
            std::cout << *it << ", ";
        }
        std::cout << std::endl;
    }

    exit(EXIT_SUCCESS);
}
