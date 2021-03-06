#include <string>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;

bool CanFormPalindrome(const string& s) {
  // TODO - you fill in here.
  std::unordered_map<char, int> cnt;
  for (const char& ch: s) {
      ++cnt[ch];
  }
  int odd_cnt = 0;
  for (const auto& p: cnt) {
      if (p.second % 2 != 0) {
          ++odd_cnt;
      }
      if (odd_cnt > 1) {
          return false;
      }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
