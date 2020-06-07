#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> KLargestInBinaryHeap(const vector<int>& A, int k) {
  // TODO - you fill in here.
  if (k <= 0) {
      return {};
  }
  struct HeapEntry {
      int idx, val;
  };
  std::priority_queue<HeapEntry, vector<HeapEntry>, std::function<bool(HeapEntry, HeapEntry)>>
    candidate_max_heap([] (const HeapEntry& a, const HeapEntry& b) {return a.val < b.val;});
  // 放入根结点
  candidate_max_heap.emplace(HeapEntry{0, A[0]});
  vector<int> ret;
  // 取出k个最大的数
  for (int i = 0; i < k; ++i) {
      int candidate_idx = candidate_max_heap.top().idx;
      ret.emplace_back(A[candidate_idx]);
      candidate_max_heap.pop();

      int left_idx = candidate_idx * 2 + 1;
      if (left_idx < A.size()) {
          candidate_max_heap.emplace(HeapEntry{left_idx, A[left_idx]});
      }
      int right_idx = candidate_idx * 2 + 2;
      if (right_idx < A.size()) {
          candidate_max_heap.emplace(HeapEntry{right_idx, A[right_idx]});
      }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "k_largest_in_heap.cc", "k_largest_in_heap.tsv",
                         &KLargestInBinaryHeap, UnorderedComparator{},
                         param_names);
}
