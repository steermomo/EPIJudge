#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;
shared_ptr<ListNode<int>> ListPivoting(const shared_ptr<ListNode<int>>& l,
                                       int x) {
  // TODO - you fill in here.
  auto less_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  auto greater_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  auto eq_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  auto l_iter = less_head, g_iter = greater_head, eq_iter = eq_head, iter = l;
  while (iter) {
      if (iter->data < x) {
          l_iter->next = iter;
          l_iter = l_iter->next;
      }
      else if (iter->data == x) {
          eq_iter->next = iter;
          eq_iter = eq_iter->next;
      }
      else {
          g_iter->next = iter;
          g_iter = g_iter->next;
      }
      iter = iter->next;
  }

  l_iter->next = eq_head->next == nullptr ? greater_head->next : eq_head->next; // 相等的元素不一定存在
  eq_iter->next = greater_head->next;
  g_iter->next = nullptr;
  return less_head->next;
}
std::vector<int> ListToVector(const shared_ptr<ListNode<int>>& l) {
  std::vector<int> v;
  ListNode<int>* it = l.get();
  while (it) {
    v.push_back(it->data);
    it = it->next.get();
  }
  return v;
}

void ListPivotingWrapper(TimedExecutor& executor,
                         const shared_ptr<ListNode<int>>& l, int x) {
  std::vector<int> original = ListToVector(l);

  std::shared_ptr<ListNode<int>> pivoted_list =
      executor.Run([&] { return ListPivoting(l, x); });

  std::vector<int> pivoted = ListToVector(pivoted_list);
  enum class Mode { kLess, kEq, kGreater } mode = Mode::kLess;
  for (auto& i : pivoted) {
    switch (mode) {
      case Mode::kLess:
        if (i == x) {
          mode = Mode::kEq;
        } else if (i > x) {
          mode = Mode::kGreater;
        }
        break;
      case Mode::kEq:
        if (i < x) {
          throw TestFailure("List is not pivoted");
        } else if (i > x) {
          mode = Mode::kGreater;
        }
        break;
      case Mode::kGreater:
        if (i <= x) {
          throw TestFailure("List is not pivoted");
        }
    }
  }
  std::sort(begin(original), end(original));
  std::sort(begin(pivoted), end(pivoted));
  if (original != pivoted) {
    throw TestFailure("Result list contains different values");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l", "x"};
  return GenericTestMain(args, "pivot_list.cc", "pivot_list.tsv",
                         &ListPivotingWrapper, DefaultComparator{},
                         param_names);
}
