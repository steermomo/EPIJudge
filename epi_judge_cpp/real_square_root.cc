#include "test_framework/generic_test.h"

inline double f(double k, double x) {
    return k * k - x;
}
double SquareRoot(double x) {
  // TODO - you fill in here.
  bool less_one = x < 1;
  if (less_one) {
      x = 1. / x;
  }
  double L = 1, U = x, k = 0;
  while (abs(L - U) > 1e-8) {
      k = L + (U - L) / 2;
      double l_res = f(L, x), r_res = f(U, x), mid_res = f(k, x);
      if (l_res * mid_res < 0) {
          U = k;
      } else {
          L = k;
      }
  }
  k = L + (U - L) / 2;
  if (less_one) {
      k = 1. / k;
  }
  return k;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
