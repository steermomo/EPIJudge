#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;

bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
  // TODO - you fill in here.
  std::unordered_map<char, int> cnt;
  for (const char& ch: letter_text) {
      ++cnt[ch];
  }
  for (const char& ch: magazine_text) {
      auto iter = cnt.find(ch);
      if (iter != cnt.end()) {
          --iter->second;
          if (iter->second == 0) {
              cnt.erase(iter);
              if (cnt.empty()) {
                  break;
              }
          }

      }
  }
  return cnt.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
