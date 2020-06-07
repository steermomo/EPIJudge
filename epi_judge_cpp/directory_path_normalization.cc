#include <string>

#include "test_framework/generic_test.h"
using std::string;
string ShortestEquivalentPath(const string& path) {
  // TODO - you fill in here.
  std::vector<string> path_names;
  if (path.front() == '/') {
      path_names.push_back("/");
  }
  std::stringstream ss(path);
  string token;
  while (getline(ss, token, '/')) {
      if (token == "..") {
          // .. 进入上级目录 需要判断当前是pop back 还是插入..
          if (path_names.empty() || path_names.back() == "..") {
              path_names.push_back(token);
          } else {
              //
              path_names.pop_back();
          }
      } else if (token != "." && token != "") {
          path_names.push_back(token);
      }
  }
  string ret;
  if (!path_names.empty()) {
      ret = path_names.front(); // front 单独处理 防止开始既是 /
      for (int i = 1; i < path_names.size(); ++i) {
          if (i == 1 && ret == "/") {
              ret += path_names[i];
          } else {
              ret += "/" + path_names[i];
          }
      }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}
