#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

unique_ptr<BstNode<int>> RebuildBSTFromPreorderHelper(const vector<int>& preorder_sequence,
        int &root_idx,
        int low_bound,
        int upper_bound) {
    if (root_idx >= preorder_sequence.size()) {
        return nullptr;
    }

    int root_val = preorder_sequence[root_idx];
    if (root_val < low_bound || root_val > upper_bound) {
        return nullptr;
    }
    ++root_idx;
    auto left_subtree = RebuildBSTFromPreorderHelper(preorder_sequence, root_idx, low_bound, root_val);
    auto right_subtree = RebuildBSTFromPreorderHelper(preorder_sequence, root_idx, root_val, upper_bound);
    return std::make_unique<BstNode<int>>(BstNode<int>{
        root_val,
        std::move(left_subtree),
        std::move(right_subtree)
    });
}

unique_ptr<BstNode<int>> RebuildBSTFromPreorder(
    const vector<int>& preorder_sequence) {
  // TODO - you fill in here.
  int root_idx = 0;
  return RebuildBSTFromPreorderHelper(preorder_sequence, root_idx, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder_sequence"};
  return GenericTestMain(args, "bst_from_preorder.cc", "bst_from_preorder.tsv",
                         &RebuildBSTFromPreorder, DefaultComparator{},
                         param_names);
}
