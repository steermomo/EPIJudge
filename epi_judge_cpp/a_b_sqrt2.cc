#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
struct ABSqrt2{
    ABSqrt2(int a, int b) : a(a), b(b), val(a + b * sqrt(2)){}
    bool operator <(const ABSqrt2& rhs) const { return val < rhs.val;}
    int a, b;
    double val;
};
vector<double> GenerateFirstKABSqrt2(int k) {
  // TODO - you fill in here.
  std::set<ABSqrt2> candidates;
  candidates.emplace(0, 0);

  vector<double> ret;
  while (ret.size() < k) {
      auto next_smallest = candidates.cbegin();
      ret.emplace_back(next_smallest->val);

      candidates.emplace(next_smallest->a + 1, next_smallest->b);
      candidates.emplace(next_smallest->a, next_smallest->b+1);

      candidates.erase(next_smallest);
  }

  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "a_b_sqrt2.cc", "a_b_sqrt2.tsv",
                         &GenerateFirstKABSqrt2, DefaultComparator{},
                         param_names);
}
