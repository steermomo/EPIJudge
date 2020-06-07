#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;
// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int>* A_ptr) {
  // TODO - you fill in here.
  vector<int> &A = *A_ptr;
  if (A.size() == 0) {
      return 0;
  }
  int valid_idx = 0, cur_idx = 1, length = A.size();
  while (cur_idx < length) {
      if (A[cur_idx] == A[valid_idx]) {
          ++cur_idx;
      }
      else{
          A[++valid_idx] = A[cur_idx++];
      }
  }
  return valid_idx+1;
}
vector<int> DeleteDuplicatesWrapper(TimedExecutor& executor, vector<int> A) {
  int end = executor.Run([&] { return DeleteDuplicates(&A); });
  A.resize(end);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(
      args, "sorted_array_remove_dups.cc", "sorted_array_remove_dups.tsv",
      &DeleteDuplicatesWrapper, DefaultComparator{}, param_names);
}
