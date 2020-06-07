#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {
  // TODO - you fill in here.
  std::priority_queue<int , vector<int>, std::greater<int>> min_heap;
  int cnt = 0;
  // 先存入k+1个数
  while (sequence_begin != sequence_end && cnt < k + 1) {
      int val = *sequence_begin;
      min_heap.emplace(val);
      ++sequence_begin;
  }
  vector<int> ret;
  // 每新读取一个数， 当前堆的最小值就是正确排序的最小值
  while (sequence_begin != sequence_end) {
      int val = min_heap.top();
      min_heap.pop();
      ret.emplace_back(val);
      min_heap.emplace(*sequence_begin);
      ++sequence_begin;
  }
  // 将堆中的剩余元素追加到结果中
  while (!min_heap.empty()) {
      int val = min_heap.top();
      ret.emplace_back(val);
      min_heap.pop();
  }
  return ret;
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
