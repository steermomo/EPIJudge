#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseL(shared_ptr<ListNode<int>> L) {
    auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
    auto fast = dummy_head->next;
    shared_ptr<ListNode<int>> slow = nullptr;
    while (fast) {
        auto temp = fast->next;
        fast->next = slow;
        slow = fast;
        fast = temp;
    }
    return slow;
}
bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
  // TODO - you fill in here.
  if (L == nullptr) {
      return true;
  }

  auto slow = L, fast = L;
  // 当L的长度为偶数时，slow指向另一个半的前结点，当L的长度为奇数时，slow刚好指向中间的结点
  while (fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;
  }
  auto left = L, right = ReverseL(slow->next);
  while (left && right) {
      if (left->data != right->data) {
          return false;
      }
      left = left->next, right = right->next;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "is_list_palindromic.cc",
                         "is_list_palindromic.tsv", &IsLinkedListAPalindrome,
                         DefaultComparator{}, param_names);
}
