#include <string>

#include "test_framework/generic_test.h"
using std::string;
int Evaluate(const string& expression) {
  // TODO - you fill in here.
  std::stack<int> intermediate_result;
  std::stringstream ss(expression);
  std::string token;
  const char kDelimiter = ',';
  while (getline(ss, token, kDelimiter)) {
      if (token == "+" || token == "-" || token == "*" || token == "/") {
          const int y = intermediate_result.top();
          intermediate_result.pop();
          const int x = intermediate_result.top();
          intermediate_result.pop();
          switch (token.front()) {
              case '+':
                  intermediate_result.emplace(x + y);
                  break;
              case '-':
                  intermediate_result.emplace(x - y);
                  break;
              case '*':
                  intermediate_result.emplace(x * y);
                  break;
              case '/':
                  intermediate_result.emplace(x / y);
                  break;
          }
      }
      else {
          const int val = std::stoi(token);
          intermediate_result.emplace(val);
      }
  }
  return intermediate_result.top();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
