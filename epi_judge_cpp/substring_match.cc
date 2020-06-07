#include <string>

#include "test_framework/generic_test.h"
using std::string;

// Returns the index of the first character of the substring if found, -1
// otherwise.
int RabinKarp(const string &t, const string &s) {
  // TODO - you fill in here.
  if (t.size() < s.size()) {
      return -1;
  }
  const int kBase = 26;
  int t_hash = 0, s_hash = 0;
  int power_s = 1; // kBase ^|s|
  for (int i = 0; i < s.size(); ++i) {
      power_s = i ? power_s * kBase : 1;
      t_hash = t_hash * kBase + t[i] - '0';
      s_hash = s_hash * kBase + s[i] - '0';
  }

  for (int i = s.size(); i < t.size(); ++i) {
      // 匹配成功
      if (t_hash == s_hash && t.compare(i - s.size(), s.size(), s) == 0) {
          return i - s.size();
      }

      // 滚动更新hash
      t_hash -= (t[i-s.size()] - '0') * power_s;
      t_hash = t_hash * kBase + t[i] - '0';
  }
    if (t_hash == s_hash && t.compare(t.size() - s.size(), s.size(), s) == 0) {
        return t.size() - s.size();
    }
  return -1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"t", "s"};
  return GenericTestMain(args, "substring_match.cc", "substring_match.tsv",
                         &RabinKarp, DefaultComparator{}, param_names);
}
