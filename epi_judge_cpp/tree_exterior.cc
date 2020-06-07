#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
bool IsLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
    if (tree->left == nullptr && tree->right == nullptr) {
        return true;
    }
    return false;
}

vector<const unique_ptr<BinaryTreeNode<int>>*> LeftBoundaryLeaf(
        const unique_ptr<BinaryTreeNode<int>>& tree, bool is_boundary) {
    vector<const unique_ptr<BinaryTreeNode<int>>*> ret;
    if (!tree) {
        return {};
    }
    if (is_boundary || IsLeaf(tree)) {
        ret.emplace_back(&tree);
    }
    // 向左一直是保持boundary
    auto left_part = LeftBoundaryLeaf(tree->left, is_boundary);
    ret.reserve(ret.size() + left_part.size());
    ret.insert(ret.end(), left_part.begin(), left_part.end());
    // 向右的情况下，如果一个结点没有左子树，该结点仍然是boundary 的一部分
    auto right_part = LeftBoundaryLeaf(tree->right, is_boundary && tree->left == nullptr);
    ret.insert(ret.end(), right_part.begin(), right_part.end());
    return ret;
}

vector<const unique_ptr<BinaryTreeNode<int>>*> RightBoundaryLeaf(
        const unique_ptr<BinaryTreeNode<int>>& tree, bool is_boundary) {
    if (!tree) {
        return {};
    }
    vector<const unique_ptr<BinaryTreeNode<int>>*> ret;
    // 向左的情况下，如果上一个结点是boundary 当前结点没有左子树，该结点仍然是boundary 的一部分
    auto left_part = RightBoundaryLeaf(tree->left, is_boundary && tree->right == nullptr);
    ret.reserve(ret.size() + left_part.size());
    ret.insert(ret.end(), left_part.begin(), left_part.end());

    // 向左一直是保持boundary
    auto right_part = RightBoundaryLeaf(tree->right, is_boundary);
    ret.insert(ret.end(), right_part.begin(), right_part.end());
    if (is_boundary || IsLeaf(tree)) {
        ret.emplace_back(&tree);
    }
    return ret;
}

vector<const unique_ptr<BinaryTreeNode<int>>*> ExteriorBinaryTree(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  vector<const unique_ptr<BinaryTreeNode<int>>*> ret;
  if (!tree) {
      return {};
  }
  ret.emplace_back(&tree);
  auto left_part = LeftBoundaryLeaf(tree->left, true);
  auto right_part = RightBoundaryLeaf(tree->right, true);

  ret.insert(ret.end(), left_part.begin(), left_part.end());
  ret.insert(ret.end(), right_part.begin(), right_part.end());
  return ret;
}
vector<int> CreateOutputVector(
    const vector<const unique_ptr<BinaryTreeNode<int>>*>& L) {
  if (std::find(std::begin(L), std::end(L), nullptr) != std::end(L)) {
    throw TestFailure("Resulting list contains nullptr");
  }
  std::vector<int> output;
  for (const auto* l : L) {
    output.push_back((*l)->data);
  }
  return output;
}

vector<int> ExteriorBinaryTreeWrapper(
    TimedExecutor& executor, const unique_ptr<BinaryTreeNode<int>>& tree) {
  auto result = executor.Run([&] { return ExteriorBinaryTree(tree); });

  return CreateOutputVector(result);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(args, "tree_exterior.cc", "tree_exterior.tsv",
                         &ExteriorBinaryTreeWrapper, DefaultComparator{},
                         param_names);
}
