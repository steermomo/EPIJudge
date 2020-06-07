#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

struct Subarray {
  int start, end;
};

Subarray FindSmallestSubarrayCoveringSet(
    const vector<string> &paragraph, const unordered_set<string> &keywords) {
  // TODO - you fill in here.
  // 记录当前cover的关键字
  std::unordered_map<string, int> keywords_to_cover;
  for (auto &k: keywords) {
      ++keywords_to_cover[k];
  }
  int remain_to_cover = keywords_to_cover.size();

  Subarray result = {-1, -1};
  for (int left = 0, right = 0; right < paragraph.size(); ++right) {
      auto r_word = paragraph[right];
      //keywords 中的同一个单词可能会在paragraph中出现多次
      if (keywords.count(r_word) && --keywords_to_cover[r_word]>=0) {
          --remain_to_cover;
      }
      // remain_to_cover == 0 意味着当前已经找到一个满足条件的区间，将left右移至下一个关键词位置。
      while (remain_to_cover == 0) {
          if (result.start == -1 || right - left < result.end - result.start) {
              result = {left, right};
          }
          if (keywords.count(paragraph[left]) && ++keywords_to_cover[paragraph[left]] > 0){
              ++remain_to_cover;
          }
          ++left;
      }
  }
  return result;
}
int FindSmallestSubarrayCoveringSetWrapper(
    TimedExecutor &executor, const vector<string> &paragraph,
    const unordered_set<string> &keywords) {
  unordered_set<string> copy = keywords;

  auto result = executor.Run(
      [&] { return FindSmallestSubarrayCoveringSet(paragraph, keywords); });

  if (result.start < 0 || result.start >= paragraph.size() || result.end < 0 ||
      result.end >= paragraph.size() || result.start > result.end) {
    throw TestFailure("Index out of range");
  }

  for (int i = result.start; i <= result.end; i++) {
    copy.erase(paragraph[i]);
  }

  if (!copy.empty()) {
    throw TestFailure("Not all keywords are in the range");
  }

  return result.end - result.start + 1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_set.cc",
                         "smallest_subarray_covering_set.tsv",
                         &FindSmallestSubarrayCoveringSetWrapper,
                         DefaultComparator{}, param_names);
}
