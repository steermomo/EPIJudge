#include "test_framework/generic_test.h"

int SquareRoot(int k) {
  // TODO - you fill in here.
  int L = 1, U = k;
  while (L <= U) {
      long M = L + (U - L) / 2;
      long prod = M * M;
      if (prod > k) {
          U = M - 1;
      } else if (prod <= k) { // 要求计算<=k的值
          L = M + 1;
      }
  }
  return L - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
