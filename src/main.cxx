#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <getopt.h>
#include <error.h>
#include <errno.h>
#include <ctype.h>
#include "Board.h"

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
            std::cout << "option " << longOpts[optsIndex].name;
            if (longOpts[optsIndex].flag != 0) {
                std::cout << std::endl;
                break;
            }
            if (optarg)
                std::cout << " with args " << optarg << std::
                    endl;
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
            std::cout << "option -s " << optarg << std::endl;
            from = optarg;
            break;
        case 'e':
        case 't':
            std::cout << "option -e " << optarg << std::endl;
            to = optarg;
            break;
        case 'v':
            std::cout << "option -v";
            verbose = 1;
            break;
        case 'h':
        case '?':
            std::cout << "help" << std::endl;
            break;
        default:
            std::cerr << "Unknown arg" << std::endl;
            break;
        }
    }

    std::istringstream is(to);
    std::istream_iterator <std::string> ii(is);
    std::istream_iterator <std::string> eos;

    std::vector <std::string> b(ii, eos);
    // std::vector <std::string> b = split(to, std::string("\n:,|;"));
    // NOTE: eventually i'd like the string to be a list of "to" cells
    std::sort(b.begin(), b.end());

    std::ostream_iterator <std::string> oo(std::cout, "\n");
    std::unique_copy(b.begin(), b.end(), oo);

    // return !is.eof() && !os;

    exit(EXIT_SUCCESS);
}
