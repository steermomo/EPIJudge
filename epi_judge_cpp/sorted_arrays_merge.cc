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

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
