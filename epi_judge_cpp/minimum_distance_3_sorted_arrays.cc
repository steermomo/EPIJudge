#include <vector>
#include <map>
#include "test_framework/generic_test.h"
using std::vector;

int FindClosestElementsInSortedArrays(
    const vector<vector<int>>& sorted_arrays) {
  // TODO - you fill in here.
  int min_distance_so_far = std::numeric_limits<int>::max();
  struct IterTail {
      vector<int>::const_iterator iter, tail;
  };
  // 存在多个相同值的情况，使用multimap
  std::multimap<int, IterTail> iter_and_tail;
    for (const vector<int>& sorted_array : sorted_arrays) {
        iter_and_tail.emplace(sorted_array.front(),
                              IterTail{cbegin(sorted_array), cend(sorted_array)});
    }
  while (true) {
      // 更新间距
      int min_val = iter_and_tail.cbegin()->first;
      int max_val = iter_and_tail.crbegin()->first;
      min_distance_so_far = std::min(max_val - min_val, min_distance_so_far);
      // 推进迭代器
      const auto next_min_iter = std::next(cbegin(iter_and_tail)->second.iter),
                 next_min_end = cbegin(iter_and_tail)->second.tail;
      if (next_min_iter == next_min_end) {
          return min_distance_so_far;
      }
      // 插入新迭代器位置
      iter_and_tail.emplace(
              *next_min_iter,
              IterTail{next_min_iter, next_min_end}
              );
      // 删除最小元素
      iter_and_tail.erase(iter_and_tail.cbegin());

  }
  return 0;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "minimum_distance_3_sorted_arrays.cc",
                         "minimum_distance_3_sorted_arrays.tsv",
                         &FindClosestElementsInSortedArrays,
                         DefaultComparator{}, param_names);
}
