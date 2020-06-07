#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  // TODO - you fill in here.
    auto even_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  auto odd_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});

  bool even_idx = true;
  auto iter = L, even_iter = even_head, odd_iter = odd_head;
  while (iter) {
      if (even_idx) {
          even_iter->next = iter;
          even_iter = even_iter->next;
      }
      else {
          odd_iter->next = iter;
          odd_iter = odd_iter->next;
      }
      iter = iter->next;
      even_idx = !even_idx;
  }
  even_iter->next = odd_head->next, odd_iter->next = nullptr;
  return even_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
