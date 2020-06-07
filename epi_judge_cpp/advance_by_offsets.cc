#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
bool CanReachEnd(const vector<int>& max_advance_steps) {
  // TODO - you fill in here.
  int furthest_so_far = 0, last_idx = max_advance_steps.size() - 1;
  for (int i = 0; i <= furthest_so_far && i <= last_idx; ++i) {
      furthest_so_far = std::max(furthest_so_far, max_advance_steps[i] + i);
  }
  return furthest_so_far >= last_idx;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}
