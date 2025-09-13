#include <matplot/freestanding/plot.h>
#include <matplot/axes_objects/line.h>
#include <matplot/freestanding/axes_lim.h>
#include <matplot/util/common.h>

#include <memory>
#include <vector>
#include <utility>
#include <ranges>
#include <functional>

double trapmf(double x, double a, double b, double c, double d) {
  if (x < a) return 0.0;
  if (x >= a && x < b) return (x - a) / (b - a);
  if (x >= b && x <= c) return 1;
  if (x > c && x <= d) return (d - x) / (d - c);
  return 0.0;
}

std::function<double(double)> makeTrapmf(double a, double b, double c, double d) {
  return [a, b, c, d](double x) -> double { return trapmf(x, a, b, c, d); };
}

int main(const int argc, const char* argv[]) {
  std::vector<double> x_numbers = matplot::linspace(-5, 5);
  std::vector<double> y_numbers =
    x_numbers | std::views::transform(makeTrapmf(-3, -1, 1, 3)) | std::ranges::to<std::vector>();

  matplot::plot(x_numbers, y_numbers)->line_width(2);
  matplot::ylim({ 0, 2 });
  matplot::show();
  return 0;
}
