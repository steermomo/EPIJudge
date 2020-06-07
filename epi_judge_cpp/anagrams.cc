#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
  // TODO - you fill in here.
  std::unordered_map<string, vector<string>> sorted_string_to_anagrams;
  for (const string& s: dictionary) {
      string sorted_s(s);
      std::sort(sorted_s.begin(), sorted_s.end());
      sorted_string_to_anagrams[sorted_s].emplace_back(s);
  }

  vector<vector<string>> ret;
  for (const auto& p: sorted_string_to_anagrams) {
      if (p.second.size() >= 2) {
          ret.emplace_back(p.second);
      }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
                         UnorderedComparator{}, param_names);
}
