#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchSmallest(const vector<int>& A) {
  // TODO - you fill in here.
  int L = 0, U = A.size() - 1;
  int M = -1;
  while (L <= U) {
      M = L + (U - L) / 2; //向下取整 M>= L && M < U
      if (A[M] >= A[U]) { // 尖峰在右半部份
          L = M + 1;  // 例如[3][1]时，L将前进1， 保证M为最小值
      } else if (A[M] < A[L]){ //尖峰在左半部分
          U = M; //只更新到M的位置 如果等于M-1可能会跳过最小值
      } else {
          return L;
      }
  }
  return M;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}
