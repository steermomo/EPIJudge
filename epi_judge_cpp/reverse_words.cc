#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

//void ReverseWords(string* s) {
//  // TODO - you fill in here.
//  string &ss = *s;
//  int s_len = (*s).size();
//  std::vector<string> words;
//  int word_st_idx = 0, word_end_idx = 0;
//  while (word_end_idx < s_len) {
//      // find next word
//      while (word_end_idx < s_len && ss[word_end_idx] != ' ') {
//          ++word_end_idx;
//      }
//      words.push_back(ss.substr(word_st_idx, word_end_idx-word_st_idx));
//      // deal with space
//      if (word_end_idx < s_len && ss[word_end_idx] == ' ') {
//          words.push_back(" ");
//      }
//      // move idx to next word
//      ++word_end_idx;
//      word_st_idx = word_end_idx;
//  }
//  // fill words reversely
//  int s_idx = 0;
//  for (int w_idx = words.size() - 1; w_idx >= 0; --w_idx) {
//      for (int idx_in_word = 0; idx_in_word < words[w_idx].size(); ++idx_in_word) {
//          ss[s_idx++] = words[w_idx][idx_in_word];
//      }
//  }
//  return;
//}

void ReverseWords(string* s) {
    std::reverse(s->begin(), s->end());
    size_t start = 0, end;
    while ((end = s->find(' ', start)) != string::npos) {
        std::reverse(s->begin()+start, s->begin()+end);
        start = end + 1;
    }
    std::reverse(s->begin() + start, s->end());
    return;
}
string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}
