#include <string>

#include "test_framework/generic_test.h"
using std::string;

int SSDecodeColID(const string& col) {
  // TODO - you fill in here.
  int id = 0;
  for (auto &code : col) {
       id *= 26;
       id += code - 'A' + 1;
  }
  return id;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"col"};
  return GenericTestMain(args, "spreadsheet_encoding.cc",
                         "spreadsheet_encoding.tsv", &SSDecodeColID,
                         DefaultComparator{}, param_names);
}
