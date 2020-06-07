#include <string>

#include "test_framework/generic_test.h"
using std::string;

string ConvertBase(const string& num_as_string, int b1, int b2) {
  // TODO - you fill in here.
  int start_idx = num_as_string[0] == '-' ? 1 : 0;
  bool neg = num_as_string[0] == '-';
  int num = 0, len = num_as_string.size() - 1;
  for (; start_idx < num_as_string.size(); ++start_idx) {
      char ch = num_as_string[start_idx];
      int c_val;
      if (ch >= '0' && ch <= '9') {
          c_val = ch - '0';
      }
      else {
          c_val = ch - 'A' + 10;
      }
      num *= b1;
      num += c_val;
  }
  if (num == 0) {
      return "0";
  }
//  string ret = std::to_string(num) + ";";
  string ret;
  while (num) {
      int mod = num % b2;
      if (0 <= mod && mod <= 9) {
          ret.push_back('0'+mod);
      }
      else {
          ret.push_back('A' + mod - 10);
      }
      num /= b2;
  }
  if (neg) {
      ret.push_back('-');
  }
  return {ret.rbegin(), ret.rend()};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
