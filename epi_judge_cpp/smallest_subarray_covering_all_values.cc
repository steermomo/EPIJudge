#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
using std::numeric_limits;
using std::unordered_map;

struct Subarray {
  // Represent subarray by starting and ending indices, inclusive.
  int start, end;
};

Subarray FindSmallestSequentiallyCoveringSubset(
    const vector<string>& paragraph, const vector<string>& keywords) {
  // TODO - you fill in here.
  // 记录keyword的位置
  std::unordered_map<string, int> keyword_to_idx;
  for (int i = 0; i < keywords.size(); ++i) {
//      keyword_to_idx[keywords[i]] = i;
      keyword_to_idx.emplace(keywords[i] , i);
  }

  vector<int> key_latest_occurrence(keywords.size(), -1);

  vector<int> shortest_subarray(keywords.size(), std::numeric_limits<int>::max());
  Subarray ret = {-1, -1};
  int shortest_array_len = std::numeric_limits<int>::max();
  for (int i = 0; i < paragraph.size(); ++i) {
      if (keyword_to_idx.count(paragraph[i])) {
          int key_idx = keyword_to_idx[paragraph[i]];
          if (key_idx == 0) {
              // 第一个keyword
              shortest_subarray[key_idx] = 1;
          } else if (shortest_subarray[key_idx-1] != std::numeric_limits<int>::max()) {

              shortest_subarray[key_idx] = shortest_subarray[key_idx-1] + i - key_latest_occurrence[key_idx-1];
          }
          key_latest_occurrence[key_idx] = i;

          if (key_idx == keywords.size() - 1 && shortest_array_len > shortest_subarray.back()) {
              shortest_array_len = shortest_subarray.back();
              ret = {i - shortest_subarray.back() + 1, i};
          }
      }
  }
  return ret;
}


int FindSmallestSequentiallyCoveringSubsetWrapper(
    TimedExecutor& executor, const vector<string>& paragraph,
    const vector<string>& keywords) {
  auto result = executor.Run([&] {
    return FindSmallestSequentiallyCoveringSubset(paragraph, keywords);
  });

  int kw_idx = 0;
  if (result.start < 0) {
    throw TestFailure("Subarray start index is negative");
  }
  int para_idx = result.start;

  while (kw_idx < keywords.size()) {
    if (para_idx >= paragraph.size()) {
      throw TestFailure("Not all keywords are in the generated subarray");
    }
    if (para_idx >= paragraph.size()) {
      throw TestFailure("Subarray end index exceeds array size");
    }
    if (paragraph[para_idx] == keywords[kw_idx]) {
      kw_idx++;
    }
    para_idx++;
  }
  return result.end - result.start + 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_all_values.cc",
                         "smallest_subarray_covering_all_values.tsv",
                         &FindSmallestSequentiallyCoveringSubsetWrapper,
                         DefaultComparator{}, param_names);
}
