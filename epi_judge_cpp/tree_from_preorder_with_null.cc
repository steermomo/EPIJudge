#include <string>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
unique_ptr<BinaryTreeNode<int>> ReconstructPreorderHelper(
        const vector<int*> &preorder,
        int *subtree_pointer) {
    int &subtree_pointer_idx = *subtree_pointer;
    int *p_node = preorder[subtree_pointer_idx];
    ++subtree_pointer_idx;
    // 当前为空结点，返回
    if (p_node == nullptr) {
        return nullptr;
    }
    // 分别构建左右子树
    auto left = ReconstructPreorderHelper(preorder, subtree_pointer);
    auto right = ReconstructPreorderHelper(preorder, subtree_pointer);
    return std::make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
            *p_node,
            move(left),
            move(right)
    });
}
unique_ptr<BinaryTreeNode<int>> ReconstructPreorder(
    const vector<int*>& preorder) {
  // TODO - you fill in here.
  int subtree_pointer_idx = 0;
  return ReconstructPreorderHelper(preorder, &subtree_pointer_idx);
}

unique_ptr<BinaryTreeNode<int>> ReconstructPreorderWrapper(
    TimedExecutor& executor, const vector<string>& preorder) {
  vector<int> values;
  vector<int*> ptrs;
  values.reserve(preorder.size());
  for (auto& s : preorder) {
    if (s == "null") {
      ptrs.push_back(nullptr);
    } else {
      int i = std::stoi(s);
      values.push_back(i);
      ptrs.push_back(&values.back());
    }
  }

  return executor.Run([&] { return ReconstructPreorder(ptrs); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "preorder"};
  return GenericTestMain(args, "tree_from_preorder_with_null.cc",
                         "tree_from_preorder_with_null.tsv",
                         &ReconstructPreorderWrapper, DefaultComparator{},
                         param_names);
}
