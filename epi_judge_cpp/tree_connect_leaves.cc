#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
using std::vector;

void CreateListOfLeavesHelper(const unique_ptr<BinaryTreeNode<int>>& tree,
                              vector<const unique_ptr<BinaryTreeNode<int>>*> &ret){
    if (!tree.get()) {
        return;
    }
    if (!tree->left.get() && !tree->right.get()) {
        ret.push_back(&tree);
        return;
    }
    CreateListOfLeavesHelper(tree->left, ret);
    CreateListOfLeavesHelper(tree->right, ret);
}

vector<const unique_ptr<BinaryTreeNode<int>>*> CreateListOfLeaves(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
    vector<const unique_ptr<BinaryTreeNode<int>>*> ret;
    CreateListOfLeavesHelper(tree, ret);
    return ret;
}
vector<int> CreateListOfLeavesWrapper(
    TimedExecutor& executor, const unique_ptr<BinaryTreeNode<int>>& tree) {
  auto result = executor.Run([&] { return CreateListOfLeaves(tree); });

  if (std::any_of(std::begin(result), std::end(result),
                  [](const unique_ptr<BinaryTreeNode<int>>*& x) {
                    return !x || !*x;
                  })) {
    throw TestFailure("Result list can't contain nullptr");
  }

  vector<int> extracted_result;
  for (const auto& x : result) {
    extracted_result.push_back(x->get()->data);
  }
  return extracted_result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(args, "tree_connect_leaves.cc",
                         "tree_connect_leaves.tsv", &CreateListOfLeavesWrapper,
                         DefaultComparator{}, param_names);
}
