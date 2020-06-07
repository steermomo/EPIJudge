#include <string>

#include "test_framework/generic_test.h"
using std::string;

string LookAndSay(int n) {
  // TODO - you fill in here.
  string start_str = "1";
  for (int i = 1; i < n; ++i) {
      int iter_idx = 0;
      string c_str;
      while (iter_idx < start_str.size()) {
          char c_val = start_str[iter_idx];
          int cnt = 1;
          while (iter_idx < start_str.size() - 1 && start_str[iter_idx] == start_str[iter_idx+1]) {
              ++iter_idx;
              ++cnt;
          }
          ++iter_idx;
          c_str += std::to_string(cnt) + std::to_string(c_val-'0');
      }
      start_str = c_str;
  }
  return start_str;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
