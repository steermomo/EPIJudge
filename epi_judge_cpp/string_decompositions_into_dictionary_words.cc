#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

bool FindAllSubstringsHelper(const string& s, std::unordered_map<string, int> word_cnt, int st_idx, int word_len, int num_words) {
    int nb = 0;
    for (int i = st_idx; nb < num_words;) {
        string c_sub = s.substr(i, word_len);
        auto iter = word_cnt.find(c_sub);
        if (iter == word_cnt.end()) {
            return false; //不匹配
        }
        if (--(iter->second) < 0) {
            return false; // 出现过多次
        }
        ++nb;
        i = st_idx + nb * word_len;
    }
    return true;
}
vector<int> FindAllSubstrings(const string& s, const vector<string>& words) {
  // TODO - you fill in here.
  std::unordered_map<string, int> word_cnt;
  for (auto &each: words) {
      ++word_cnt[each];
  }
  int word_len = words[0].size();
  vector<int> ret;
  // 下面的条件是 <=
  for (int i = 0; i + word_len * words.size() <= s.size(); ++i) {
      if (FindAllSubstringsHelper(s, word_cnt, i, word_len, words.size())) {
          ret.emplace_back(i);
      }
  }

  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s", "words"};
  return GenericTestMain(args, "string_decompositions_into_dictionary_words.cc",
                         "string_decompositions_into_dictionary_words.tsv",
                         &FindAllSubstrings, DefaultComparator{}, param_names);
}
