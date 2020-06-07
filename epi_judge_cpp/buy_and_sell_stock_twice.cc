#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockTwice(const vector<double>& prices) {
  // TODO - you fill in here.
  vector<double> max_profit_first_buy(prices.size(), 0);
  double total_max_profit = 0;

  double min_price_so_far = std::numeric_limits<double>::max();
  for (int i = 0; i < prices.size(); ++i) {
      min_price_so_far = std::min(min_price_so_far, prices[i]);
      total_max_profit = std::max(total_max_profit, prices[i] - min_price_so_far);
      max_profit_first_buy[i] = total_max_profit;
  }

  double max_price_so_far = std::numeric_limits<double>::min();
  for (int i = prices.size() - 1; i > 0; --i) {
      max_price_so_far = std::max(max_price_so_far, prices[i]);
      total_max_profit = std::max(total_max_profit, max_price_so_far - prices[i] + max_profit_first_buy[i - 1]);
  }
  return total_max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
