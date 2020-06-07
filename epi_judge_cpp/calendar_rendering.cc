#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Event {
  int start, finish;
};

struct EndPoint {
    bool operator<(const EndPoint& e) const{
        // 将时间靠前的拍在前面 如果时间相同 将start 排在 end 前面
        return this->time != e.time ? this->time < e.time : (this->isStart && !e.isStart);
    }
    int time;
    bool isStart;
};
int FindMaxSimultaneousEvents(const vector<Event>& A) {
  // TODO - you fill in here.
  vector<EndPoint> E;
  for (auto &each : A) {
      E.push_back({each.start, true});
      E.push_back({each.finish, false});
  }
  //按照时间排序
  std::sort(E.begin(), E.end());

  int max_event_cnt = 0, event_cnt = 0;
  for (auto &each : E) {
      if (each.isStart) {
          ++event_cnt;
          max_event_cnt = std::max(event_cnt, max_event_cnt);
      } else {
          --event_cnt;
      }
  }
  return max_event_cnt;
}
namespace test_framework {
template <>
struct SerializationTrait<Event> : UserSerTrait<Event, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}
