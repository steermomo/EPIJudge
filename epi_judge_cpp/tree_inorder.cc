#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  std::stack<BinaryTreeNode<int>*> stk;
  auto curr = tree.get();
  vector<int> ret;
  while (!stk.empty() || curr) {
      if (curr) {
          stk.push(curr);
          curr = curr->left.get();
      } else {
          // curr 为空, 上一个结点为叶结点
          curr = stk.top();
          stk.pop();
          ret.push_back(curr->data); // 访问当前结点
          curr = curr->right.get(); // 向右访问一次
      }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
