#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> RemoveDuplicates(const shared_ptr<ListNode<int>>& L) {
  // TODO - you fill in here.
  if (!L || !L->next) {
      return L;
  }
  auto fast = L->next, slow = L;
  while (fast && slow) {
      if (fast->data == slow->data) {
          slow->next = fast->next;
          fast = fast->next;
          continue;
      }
      else {
          fast = fast->next;
          slow = slow->next;
      }
  }
//  auto iter = L;
//  while (iter) {
//      auto next_dist = iter->next;
//      while (next_dist && next_dist->data == iter->data) {
//          next_dist = next_dist->next;
//      }
//      iter->next = next_dist;
//      iter = next_dist;
//  }
  return L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "remove_duplicates_from_sorted_list.cc",
                         "remove_duplicates_from_sorted_list.tsv",
                         &RemoveDuplicates, DefaultComparator{}, param_names);
}
