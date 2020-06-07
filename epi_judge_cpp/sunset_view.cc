#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> ExamineBuildingsWithSunset(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end) {
    // TODO - you fill in here.
  if (sequence_begin == sequence_end) {
      return {};
  }
  vector<int> building_height(sequence_begin, sequence_begin+1);
  vector<int> building_idx(1,0);
  ++sequence_begin;
  int c_max = building_height[0], c_idx = 1;
  while (sequence_begin != sequence_end){
      int height = *sequence_begin;
      while (!building_height.empty() && building_height.back() <= height) {
          building_height.pop_back();
          building_idx.pop_back();
      }
      building_height.push_back(height);
      building_idx.push_back(c_idx);
      ++sequence_begin;
      ++c_idx;
  }
  std::reverse(begin(building_idx), end(building_idx));
  return building_idx;
}
vector<int> ExamineBuildingsWithSunsetWrapper(const vector<int>& sequence) {
  return ExamineBuildingsWithSunset(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "sunset_view.cc", "sunset_view.tsv",
                         &ExamineBuildingsWithSunsetWrapper,
                         DefaultComparator{}, param_names);
}
