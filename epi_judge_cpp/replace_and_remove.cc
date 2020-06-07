#include <iterator>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

int ReplaceAndRemove(int size, char s[]) {
  // TODO - you fill in here.
  int a_cnt = 0;
  int write_idx = 0, last_idx = 0;
  while(last_idx < size) {
      if (s[last_idx] == 'b') {
          ++last_idx;
          continue;
      }
      if (s[last_idx] == 'a') {
          ++a_cnt;
      }
      s[write_idx++] = s[last_idx++];
  }

  int back_write_idx = write_idx + a_cnt-1, back_idx = write_idx - 1;
  int ret_cnt = back_write_idx+1;
  while (back_write_idx >= 0) {
      if (s[back_idx] == 'a') {
          s[back_write_idx--] = 'd';
          s[back_write_idx--] = 'd';
          --back_idx;
      }
      else {
          s[back_write_idx--] = s[back_idx--];
      }
  }
  return ret_cnt;
}
vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
                                       const vector<string>& s) {
  std::vector<char> s_copy(s.size(), '\0');
  for (int i = 0; i < s.size(); ++i) {
    if (!s[i].empty()) {
      s_copy[i] = s[i][0];
    }
  }

  int res_size =
      executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

  vector<string> result;
  for (int i = 0; i < res_size; ++i) {
    result.emplace_back(string(1, s_copy[i]));
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "size", "s"};
  return GenericTestMain(args, "replace_and_remove.cc",
                         "replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
                         DefaultComparator{}, param_names);
}
