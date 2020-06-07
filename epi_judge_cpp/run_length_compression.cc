#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;
string Decoding(const string &s) {
  // TODO - you fill in here.
  string ret;
  for (size_t i = 0; i < s.size();) {
      size_t ed = i;
      // ed 为字符位置
      while (std::isdigit(s[ed])) {
          ++ed;
      }
      int cnt = std::stoi(s.substr(i, ed-i));
      char ch = s[ed];
      while(cnt--) {
          ret.push_back(ch);
      }
      i = ed+1;
  }
  return ret;
}
string Encoding(const string &s) {
  // TODO - you fill in here.
  string ret;
  size_t start = 0;
  while (start < s.size()) {
      int cnt = 1;
      char ch = s[start];
      while (start < s.size() - 1 && s[start] == s[start+1]) {
          ++cnt;
          ++start;
      }
      ret += std::to_string(cnt);
      ret.push_back(ch);
      ++start;
  }
  return ret;
}
void RleTester(const string &encoded, const string &decoded) {
  if (Decoding(encoded) != decoded) {
    throw TestFailure("Decoding failed");
  }
  if (Encoding(decoded) != encoded) {
    throw TestFailure("Encoding failed");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"encoded", "decoded"};
  return GenericTestMain(args, "run_length_compression.cc",
                         "run_length_compression.tsv", &RleTester,
                         DefaultComparator{}, param_names);
}
