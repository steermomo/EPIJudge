#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
struct IteratorCurrentAndEnd{
    // 比较迭代器指向的值
    bool operator>(const IteratorCurrentAndEnd& that) {
        return *current > *that.current;
    }
    vector<int>::const_iterator current;
    vector<int>::const_iterator end;
};
vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
    // TODO - you fill in here.
    std::priority_queue<IteratorCurrentAndEnd, vector<IteratorCurrentAndEnd>, std::greater<>>
            min_heap;
    // 保存每个数组的迭代器
    for (const vector<int>& sorted_array: sorted_arrays) {
        if (!sorted_array.empty()) {
            min_heap.emplace(IteratorCurrentAndEnd{sorted_array.cbegin(), sorted_array.cend()});
        }
    }

    vector<int> ret;
    while (!min_heap.empty()) {
        // 取出当前最小元素对应的迭代器
        auto smallest_array = min_heap.top();
        min_heap.pop();
        if (smallest_array.current != smallest_array.end) {
            // 对应的数组非空
            ret.emplace_back(*smallest_array.current);
            min_heap.emplace(IteratorCurrentAndEnd{std::next(smallest_array.current), smallest_array.end});
        }
    }
    return ret;
}
vector<int> SortKIncreasingDecreasingArray(const vector<int>& A) {
  // TODO - you fill in here.
  vector<vector<int>> sorted_subarrays;
  typedef enum {INCREASING, DECREASING} SubarrayType;
  SubarrayType subarray_type = INCREASING;
  int start_idx = 0;
  for (int i = 1; i <= A.size(); ++i) {
      // 状态发生变化或到达尾部
      if (i == A.size() || (A[i-1] < A[i] && subarray_type == DECREASING)
        || (A[i-1] >= A[i] && subarray_type == INCREASING)) {
          if (subarray_type == INCREASING) {
              // 递增的序列直接添加进ret
              sorted_subarrays.emplace_back(A.cbegin()+start_idx, A.cbegin()+i);
          } else {
              // 将递减的序列翻转后再添加到ret
              sorted_subarrays.emplace_back(A.crbegin() + A.size() - i, A.crbegin() + A.size() - start_idx);
          }
          subarray_type = subarray_type == INCREASING ? DECREASING : INCREASING;
          start_idx = i;
      }
  }
  return MergeSortedArrays(sorted_subarrays);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "sort_increasing_decreasing_array.cc",
                         "sort_increasing_decreasing_array.tsv",
                         &SortKIncreasingDecreasingArray, DefaultComparator{},
                         param_names);
}
