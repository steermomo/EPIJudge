#include <vector>
#include <numeric>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  // TODO - you fill in here.
  double min_price = std::numeric_limits<double>::max(), max_profit = 0;
  for (auto& price: prices) {
      double profit_today = price - min_price;
      max_profit = std::max(max_profit, profit_today);
      min_price = std::min(min_price, price);
  }
  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
