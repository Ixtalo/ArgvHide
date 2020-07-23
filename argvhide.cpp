
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <ostream>
#include <sstream>
#include <string>
#include <iomanip>      // std::setfill, std::setw
#include <vector>

using namespace std;



/// https://stackoverflow.com/questions/3381614/c-convert-string-to-hexadecimal-and-vice-versa
std::string str2hex(const std::string& input)
{
    static const char hex_digits[] = "0123456789abcdef";

    std::string output;
    output.reserve(input.length() * 2);
    for (unsigned char c : input)
    {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}

#include <stdexcept>

int hex_value(unsigned char hex_digit)
{
    static const signed char hex_values[256] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    };
    int value = hex_values[hex_digit];
    if (value == -1) throw std::invalid_argument("invalid hex digit");
    return value;
}

std::string hex2str(const std::string& input)
{
    const auto len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (auto it = input.begin(); it != input.end(); )
    {
        int hi = hex_value(*it++);
        int lo = hex_value(*it++);
        output.push_back(hi << 4 | lo);
    }
    return output;
}


/// https://create.stephan-brumme.com/hide-strings-executable/
std::string d(const std::string& input)
{
  // choose a power of two => then compiler can replace "modulo x" by much faster "and (x-1)"
  const size_t pl = 16;
  // at least as long as passwordLength, can be longer, too ...
  static const char p[pl] = "\xf0\xe4\xfa\xfb\xe1\xfb\xf4\xaa\xe1\xe4\xa4";

  // out = in XOR NOT(p)
  std::string result = input;
  for (size_t i = 0; i < input.length(); i++)
    result[i] ^= ~p[i % pl];
  return result;
}

/// https://thispointer.com/how-to-split-a-string-in-c/
std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

std::string argv2string(int argc, char** argv, int startpos = 0)
{
    std::stringstream ss;
    for (int i = startpos; i < argc; i++)
    {
        ss << argv[i] << " ";
    }
    std::string res(ss.str());
    res.erase(res.rfind(' ')); // Trim from ' ' to the end of the string
    return res;
}

//size_t string2argv(const std::string s, char* buf[])
//{
//    auto elems = split(s, ' ');
//    const size_t n = elems.size();
//    char* arr[n];
//    for (size_t i = 0; i < n; i++)
//    {
//        /// https://www.techiedelight.com/convert-std-string-char-cpp/
//        arr[i] = const_cast<char*>(elems[i].c_str());
//    }
//
//    return n;
//}

int main(int argc, char** argv)
{
    cout << argc << endl;
    cout << argv2string(argc, argv, 1) << endl;

    if (argc < 3) {
        cerr << "usage: " << argv[0] << " <[-e|-d|-x] [string|-]>" << endl;
        return 1;
    }

    if (argc >= 3) {
        const string params = string(argv2string(argc, argv, 2));
        //cout << params << endl;
        string line;
        if (params == "-") {
            std::getline(std::cin, line);
        } else {
            line = params;
        }

        if (string(argv[1]) == "-e") {
            cout << str2hex(d(line)) << endl;
        }
        else if (string(argv[1]) == "-d") {
            cout << d(hex2str(line)) << endl;
        }
        else if (string(argv[1]) == "-x") {
            
            // hex -> encoded -> decoded string
            const string s = d(hex2str(line));
            
            // string -> char*[]
            const auto elems = split(s, ' ');
            const size_t argc_new = elems.size() + 1;  // +1 for argv[0]
            char* argv_new[n];
            // always add first argv element
            argv_new[0] = argv[0];
            for (size_t i = 0; i < argc_new; i++)
            {
                /// const_cast: https://www.techiedelight.com/convert-std-string-char-cpp/
                argv_new[i+1] = const_cast<char*>(elems[i].c_str());
            }

            // show that
            cout << argv2string(argc_new, argv_new) << endl;

            // now, what we've done:
            // 1. encoded parameters with XOR
            // 2. encoded it as hex
            // 
            // 3. decoded hex
            // 4. decoded XOR
            // 5. created an own char**/char*[] from that
            //
            // This can then be used by e.g., CLI parsers

            // e.g.:
            // old argc:3, argv:./argvhide -x 224b2562716b2b78683b6b
            // new argc:5, argv:./argvhide -P foo -v 0
            cout << "old argc:" << argc << ", argv:" << argv2string(argc, argv) << endl;
            cout << "argc_new:" << argc_new << ", argv_new:" << argv2string(argc_new, argv_new) << endl;

            // overwrite
            argc = argc_new;
            argv = argv_new;
        }        
    }

}
