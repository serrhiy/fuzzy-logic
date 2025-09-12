#include <matplot/freestanding/plot.h>
#include <matplot/util/common.h>

#include <vector>
#include <numbers>
#include <cmath>
#include <utility>

int main(const int argc, const char* argv[]) {
  std::vector<double> x_numbers;
  std::vector<double> y_numbers;
  for (const double x: matplot::linspace(0, 2 * std::numbers::pi)) {
    x_numbers.push_back(std::cos(x));
    y_numbers.push_back(std::sin(x));
  }

  matplot::plot(x_numbers, y_numbers);
  matplot::show();
  return 0;
}
