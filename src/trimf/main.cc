#include <matplot/freestanding/plot.h>
#include <matplot/axes_objects/line.h>
#include <matplot/freestanding/axes_lim.h>
#include <matplot/util/common.h>
#include <matplot/core/axes_type.h>
#include <matplot/freestanding/axes_functions.h>

#include <memory>
#include <vector>
#include <algorithm>
#include <ranges>
#include <functional>

double trimf(const double x, const double a, const double b, const double c) {
  if (x < a) return 0.0;
  if (x >= a && x < b) return (x - a) / (b - a);
  if (x >= b && x <= c) return (c - x) / (c - b);
  return 0.0;
}

std::function<double(const double)> makeTrimf(const double a, const double b, const double c) {
  return [a, b, c](const double x) -> double { return trimf(x, a, b, c); };
}

int main(const int argc, const char* argv[]) {
  std::vector<double> x_numbers = matplot::linspace(-5, 5);
  std::vector<double> y_numbers =
    x_numbers | std::views::transform(makeTrimf(-3, 0, 3)) | std::ranges::to<std::vector>();

  matplot::plot(x_numbers, y_numbers)->line_width(2);
  matplot::ylim({ 0, 1.5 });
  matplot::grid(true);
  matplot::gca()->minor_grid(true);
  matplot::title("Triangular membership function");
  matplot::show();
  return 0;
}
