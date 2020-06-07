#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsWellFormed(const string& s) {
  // TODO - you fill in here.
  std::stack<char> stk;
  for (auto ch: s) {
      if (ch == '{' || ch == '(' || ch == '['){
          stk.emplace(ch);
      } else {
          if (stk.empty()) {
              return false;
          }
          if ((ch == '}' && stk.top() != '{') ||
              (ch == ')' && stk.top() != '(') ||
              (ch == ']' && stk.top() != '[')) {
              return false;
          }
          stk.pop();
      }
  }
  if (!stk.empty()) {
      return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
