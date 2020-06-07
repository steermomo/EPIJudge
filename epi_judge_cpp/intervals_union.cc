#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::vector;

struct Interval {
  struct Endpoint {
    bool is_closed;
    int val;
  };

  Endpoint left, right;
};

struct Point {
    bool operator<(const Point& p) const {
//        return val != p.val ? val < p.val : (is_left && !p.is_left);
        if (val != p.val) {
            return val < p.val;
        }
        // 元素相等 两个都是开区间
        if (!is_closed && !p.is_closed) {
            // 一前一后 将right 放在left前
            return !is_left && p.is_left;
        }

        // 元素相等 一开一闭 都是right 开区间放前
        if (!is_left && !p.is_left) {
            return !is_closed && p.is_closed;
        }
        // 元素相等 一开一闭 都是left 闭区间放前
        if (is_left && p.is_left) {
            return is_closed && !p.is_closed;
        }
        // 元素相等 一开一闭 left放在right前
        return is_left && !p.is_left;
    }
    int val;
    bool is_left;
    bool is_closed;
};
vector<Interval> UnionOfIntervals(vector<Interval> intervals) {
  // TODO - you fill in here.
  vector<Point> P;
  for (auto &each : intervals) {
      P.push_back({each.left.val, true, each.left.is_closed});
      P.push_back({each.right.val, false, each.right.is_closed});
  }
  std::sort(P.begin(), P.end());
  vector<Interval> ret;

  bool is_new_intervals = true, left_closed = false;
  int left_idx = 0, left_cnt = 0;
  for (auto &each : P) {
    if (each.is_left) {
        ++left_cnt;
        if (is_new_intervals) {
            left_idx = each.val;
            left_closed = each.is_closed;
            is_new_intervals = false;
        }
    } else {
        --left_cnt;
    }
    if (left_cnt == 0) {
        ret.push_back({{left_closed, left_idx},{each.is_closed, each.val}});
        is_new_intervals = true;
    }
  }
  return ret;
}
struct FlatInterval {
  int left_val;
  bool left_is_closed;
  int right_val;
  bool right_is_closed;

  FlatInterval(int left_val, bool left_is_closed, int right_val,
               bool right_is_closed)
      : left_val(left_val),
        left_is_closed(left_is_closed),
        right_val(right_val),
        right_is_closed(right_is_closed) {}

  explicit FlatInterval(Interval in)
      : left_val(in.left.val),
        left_is_closed(in.left.is_closed),
        right_val(in.right.val),
        right_is_closed(in.right.is_closed) {}

  operator Interval() const {
    return {{left_is_closed, left_val}, {right_is_closed, right_val}};
  }

  bool operator==(const FlatInterval& rhs) const {
    return std::tie(left_val, left_is_closed, right_val, right_is_closed) ==
           std::tie(rhs.left_val, rhs.left_is_closed, rhs.right_val,
                    rhs.right_is_closed);
  }
};

namespace test_framework {
template <>
struct SerializationTrait<FlatInterval>
    : UserSerTrait<FlatInterval, int, bool, int, bool> {};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const FlatInterval& i) {
  return out << (i.left_is_closed ? '<' : '(') << i.left_val << ", "
             << i.right_val << (i.right_is_closed ? '>' : ')');
}

std::vector<FlatInterval> UnionOfIntervalsWrapper(
    TimedExecutor& executor, const std::vector<FlatInterval>& intervals) {
  std::vector<Interval> casted;
  for (const FlatInterval& i : intervals) {
    casted.push_back(static_cast<Interval>(i));
  }

  std::vector<Interval> result =
      executor.Run([&] { return UnionOfIntervals(casted); });

  return {begin(result), end(result)};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "intervals"};
  return GenericTestMain(args, "intervals_union.cc", "intervals_union.tsv",
                         &UnionOfIntervalsWrapper, DefaultComparator{},
                         param_names);
}
