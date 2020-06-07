#include <vector>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Interval {
  int left, right;
};
struct EndPoint {
    bool operator<(const EndPoint& e) const {
        return point != e.point ? point < e.point : (isLeft && !e.isLeft);
    }
    int point;
    bool isLeft;
};
vector<Interval> AddInterval(const vector<Interval>& disjoint_intervals,
                             Interval new_interval) {
  // TODO - you fill in here.
  vector<EndPoint> E;
  for (auto &each: disjoint_intervals) {
      E.push_back({each.left, true});
      E.push_back({each.right, false});
  }
  E.push_back({new_interval.left, true});
  E.push_back({new_interval.right, false});

  std::sort(E.begin(), E.end());

  vector<Interval> ret;
  bool is_new_interval = true;
  int st = 0, left_cnt = 0;
  for (auto &each : E) {
      if (each.isLeft) {
          ++left_cnt;
          if (is_new_interval) {
              st = each.point;
              is_new_interval = false;
          }
      } else {
          --left_cnt;
      }
      if (left_cnt == 0) {
          ret.push_back({st, each.point});
          is_new_interval = true;
      }
  }
  return ret;
}
namespace test_framework {
template <>
struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("length({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Interval& x) {
    return {x.right - x.left};
  }
};
}  // namespace test_framework
bool operator==(const Interval& a, const Interval& b) {
  return a.left == b.left && a.right == b.right;
}

std::ostream& operator<<(std::ostream& out, const Interval& i) {
  return PrintTo(out, std::make_tuple(i.left, i.right));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"disjoint_intervals", "new_interval"};
  return GenericTestMain(args, "interval_add.cc", "interval_add.tsv",
                         &AddInterval, DefaultComparator{}, param_names);
}
