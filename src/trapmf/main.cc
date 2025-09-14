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

double trapmf(double x, double a, double b, double c, double d) {
  if (x < a) return 0.0;
  if (x >= a && x < b) return (x - a) / (b - a);
  if (x >= b && x <= c) return 1;
  if (x > c && x <= d) return (d - x) / (d - c);
  return 0.0;
}

std::function<double(double)> makeTrapmf(double a, double b, double c,
                                         double d) {
  return [a, b, c, d](double x) -> double { return trapmf(x, a, b, c, d); };
}

int main(const int argc, const char* argv[]) {
  using std::views::transform, std::ranges::to;

  const std::vector<double> x_numbers = matplot::linspace(-5, 5);
  const std::vector<double> y_numbers =
      x_numbers | transform(makeTrapmf(-3, -1, 1, 3)) | to<std::vector>();

  matplot::plot(x_numbers, y_numbers)->line_width(2);
  matplot::ylim({0, 1.5});
  matplot::grid(true);
  matplot::gca()->minor_grid(true);
  matplot::title("Trapezoid membership function");
  matplot::show();
  return 0;
}
