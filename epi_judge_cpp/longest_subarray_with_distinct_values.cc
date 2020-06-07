#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::vector;

int LongestSubarrayWithDistinctEntries(const vector<int>& A) {
  // TODO - you fill in here.
  std::unordered_map<int, int> last_appearance; //记录元素上次出现的位置
  int longest_array_start_idx = 0, result = 0;
  for (int i = 0; i < A.size(); ++i) {
      auto insert_ret = last_appearance.insert({A[i], i});
      if (!insert_ret.second) {  // 插入不成功, 说明A[i]之前出现过
          int prev_idx = insert_ret.first->second;
          if (prev_idx >= longest_array_start_idx) { // A[i] 在滑窗内
              longest_array_start_idx = prev_idx + 1;
          }
          insert_ret.first->second = i; // 更新位置
      }
      result = std::max(result, i - longest_array_start_idx + 1);
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "longest_subarray_with_distinct_values.cc",
                         "longest_subarray_with_distinct_values.tsv",
                         &LongestSubarrayWithDistinctEntries,
                         DefaultComparator{}, param_names);
}
