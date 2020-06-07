#include <algorithm>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

// 判断ip区间十分合规
inline bool isValid(const string& s){
    if (s.size() > 3){
        return false;
    }
    if (s.size() > 1 && s[0] == '0') {
        return false;
    }
    int val = std::stoi(s);
    return val <= 255;
}

vector<string> GetValidIpAddress(const string& s) {
  // TODO - you fill in here.
  if (s.size() < 4) {
      return {};
  }
  vector<string> ret;
  // 遍历3个点的位置
  for (int first_dot = 0; first_dot < s.size()-3; ++first_dot) {
      string f_part = s.substr(0, first_dot+1);
      if (!isValid(f_part)) continue;
      for (int sec_dot = first_dot+1; sec_dot < s.size() - 2; ++sec_dot) {
          string s_part = s.substr(first_dot+1, sec_dot-first_dot);
          if (!isValid(s_part)) continue;
          for (int th_dot = sec_dot + 1; th_dot < s.size() - 1; ++th_dot) {
              string t_part = s.substr(sec_dot+1, th_dot-sec_dot);
              if (!isValid(t_part)) continue;
              string fo_part = s.substr(th_dot+1, s.size() - th_dot);
              if (!isValid(fo_part)) continue;

              ret.emplace_back(f_part + "." + s_part + "." + t_part + "." + fo_part);
          }
      }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "valid_ip_addresses.cc",
                         "valid_ip_addresses.tsv", &GetValidIpAddress,
                         UnorderedComparator{}, param_names);
}
