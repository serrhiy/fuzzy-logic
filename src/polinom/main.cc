#include <matplot/axes_objects/line.h>
#include <matplot/core/axes_type.h>
#include <matplot/core/figure_registry.h>
#include <matplot/core/figure_type.h>
#include <matplot/freestanding/axes_functions.h>
#include <matplot/freestanding/axes_lim.h>
#include <matplot/freestanding/plot.h>
#include <matplot/util/common.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <memory>
#include <ranges>
#include <vector>

double zmf(double x, double a, double b) {
  if (x <= a) return 1;
  if (a <= x && x <= (a + b) / 2) {
    return 1 - 2 * std::pow((x - a) / (b - a), 2);
  }
  if ((a + b) / 2.0 <= x && x <= b) {
    return 2 * std::pow((x - b) / (b - a), 2);
  }
  return 0.0;
}

double smf(double x, double a, double b) {
  if (x <= a) return 0;
  if (a <= x && x <= (a + b) / 2) {
    return 2 * std::pow((x - a) / (b - a), 2);
  }
  if ((a + b) / 2 <= x && x <= b) {
    return 1 - 2 * std::pow((x - b) / (b - a), 2);
  }
  return 1;
}

double pimf(double x, double a, double b, double c, double d) {
  if (x >= d) return 0;
  return x <= (a + b) / 2 ? smf(x, a, b) : zmf(x, c, d);
}

std::function<double(double)> makeZmf(double a, double b) {
  return [a, b](double x) -> double { return zmf(x, a, b); };
}

std::function<double(double)> makeSmf(double a, double b) {
  return [a, b](double x) -> double { return smf(x, a, b); };
}

std::function<double(double)> makePimf(double a, double b, double c, double d) {
  return [a, b, c, d](double x) -> double { return pimf(x, a, b, c, d); };
}

int main(const int argc, const char* argv[]) {
  using std::views::transform, std::ranges::to;

  const std::vector<double> x_numbers = matplot::linspace(-15, 15);
  const std::vector<double> y_numbers1 =
      x_numbers | transform(makeZmf(-10, 10)) | to<std::vector>();
  const std::vector<double> y_numbers2 =
      x_numbers | transform(makeSmf(-10, 10)) | to<std::vector>();
  const std::vector<double> y_numbers3 =
      x_numbers | transform(makePimf(-10, -3, 3, 10)) | to<std::vector>();

  matplot::figure()->size(800, 600);

  auto ax1 = matplot::subplot(2, 2, 0);
  matplot::plot(x_numbers, y_numbers1)->line_width(2);
  matplot::title("Z-Shaped Membership Function");

  auto ax2 = matplot::subplot(2, 2, 1);
  matplot::plot(x_numbers, y_numbers2)->line_width(2);
  matplot::title("S-Shaped Membership Function");

  auto ax3 = matplot::subplot(2, 2, {2, 3});
  matplot::plot(x_numbers, y_numbers3)->line_width(2);
  matplot::title("Pi-Shaped Membership Function");

  for (const auto& axis : {ax1, ax2, ax3}) {
    matplot::ylim(axis, {0, 1.1});
    matplot::grid(axis, true);
    axis->minor_grid(true);
  }

  matplot::show();
  return 0;
}
