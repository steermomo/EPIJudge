#include <string>
#include <map>
#include "test_framework/generic_test.h"
using std::string;

const std::map<char, int> mp = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M',1000}
};
int RomanToInteger(const string& s) {
  // TODO - you fill in here.
  int cnt = 0;
  for (int i = 0; i < s.size(); ++i) {
      char ch = s[i];
      if (i > 0) {
          if ((ch == 'V' || ch == 'X') && s[i-1] == 'I') {
              cnt -= 1 * 2;
          }
          if ((ch == 'L' || ch == 'C') && s[i-1] == 'X') {
              cnt -= 10 * 2;
          }
          if ((ch == 'D' || ch == 'M') && s[i-1] == 'C') {
              cnt -= 100 * 2;
          }
      }
      cnt += mp.at(ch);
  }
  return cnt;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "roman_to_integer.cc", "roman_to_integer.tsv",
                         &RomanToInteger, DefaultComparator{}, param_names);
}
