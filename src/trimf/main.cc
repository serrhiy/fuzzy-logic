#include <matplot/axes_objects/line.h>
#include <matplot/core/axes_type.h>
#include <matplot/freestanding/axes_functions.h>
#include <matplot/freestanding/axes_lim.h>
#include <matplot/freestanding/plot.h>
#include <matplot/util/common.h>

#include <algorithm>
#include <functional>
#include <memory>
#include <ranges>
#include <vector>

double trimf(double x, double a, double b, double c) {
  if (x < a) return 0.0;
  if (x >= a && x < b) return (x - a) / (b - a);
  if (x >= b && x <= c) return (c - x) / (c - b);
  return 0.0;
}

std::function<double(double)> makeTrimf(double a, double b, double c) {
  return [a, b, c](double x) -> double { return trimf(x, a, b, c); };
}

int main(const int argc, const char* argv[]) {
  using std::views::transform, std::ranges::to;

  const std::vector<double> x_numbers = matplot::linspace(-5, 5);
  const std::vector<double> y_numbers =
      x_numbers | transform(makeTrimf(-3, 0, 3)) | to<std::vector>();

  matplot::plot(x_numbers, y_numbers)->line_width(2);
  matplot::ylim({0, 1.5});
  matplot::grid(true);
  matplot::gca()->minor_grid(true);
  matplot::title("Triangular membership function");
  matplot::show();
  return 0;
}
