#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsPalindrome(const string& s) {
  // TODO - you fill in here.
  int l_idx = 0, r_idx = s.size() - 1;
  while (l_idx < r_idx) {
      while(l_idx < r_idx && !std::isalnum(s[l_idx])) {
          ++l_idx;
      }
      while (r_idx > l_idx && !std::isalnum(s[r_idx])) {
          --r_idx;
      }
      if (std::tolower(s[l_idx++]) != std::tolower(s[r_idx--])) {
          return false;
      }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
