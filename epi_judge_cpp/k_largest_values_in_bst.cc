#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

bool FindKLargestInBSTHelper(BstNode<int>* sub_tree, int k, vector<int>& ret) {
    if (ret.size() == k) {
        return true;
    }
    if (sub_tree == nullptr) {
        return false;
    }
    bool found = FindKLargestInBSTHelper(sub_tree->right.get(), k, ret);
    if (found) {
        return true;
    }
    ret.emplace_back(sub_tree->data);
    return FindKLargestInBSTHelper(sub_tree->left.get(), k, ret);
}
vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
  // TODO - you fill in here.
  vector<int> ret;
  FindKLargestInBSTHelper(tree.get(), k, ret);
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}
