#include <vector>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  BinaryTreeNode<int> *prev = nullptr, *curr = tree.get();
  vector<int> ret;
  while (curr != nullptr) {
      BinaryTreeNode<int>* next;
      if (curr->parent == prev) {
          // 是从上往下访问
          if (curr->left != nullptr) {
              // 有左子树，继续往下
              next = curr->left.get();
          } else {
              // 到达叶结点， 访问数据
              ret.emplace_back(curr->data);
              // 如果有右子树， 继续向右，否则当前分支结束，向上
              next = (curr->right != nullptr) ? curr->right.get() : curr->parent;
          }
      } else if (curr->left.get() == prev) {
          // 是从左子树向上回溯
          ret.emplace_back(curr->data);
          next = (curr->right != nullptr) ? curr->right.get() : curr->parent;
      } else {
          next = curr->parent;
      }
      prev = curr;
      curr = next;
  }

  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
