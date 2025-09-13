#include <matplot/freestanding/plot.h>
#include <matplot/axes_objects/line.h>
#include <matplot/freestanding/axes_lim.h>
#include <matplot/util/common.h>
#include <matplot/core/axes_type.h>
#include <matplot/freestanding/axes_functions.h>

#include <memory>
#include <vector>
#include <ranges>
#include <functional>
#include <algorithm>
#include <cmath>

double gaussmf(const double x, const double c, const double sig) {
  return std::exp(-((x - c) * (x - c)) / (2 * sig * sig));
}

std::function<double(double)> makeGaussmf(const double c, const double sig) {
  return [c, sig](double x) -> double { return gaussmf(x, c, sig); };
}

int main(const int argc, const char* argv[]) {
  std::vector<double> x_numbers = matplot::linspace(-5, 5);
  std::vector<double> y_numbers =
    x_numbers | std::views::transform(makeGaussmf(0, 1.2)) | std::ranges::to<std::vector>();

  matplot::plot(x_numbers, y_numbers)->line_width(2);
  matplot::ylim({ 0, 1.5 });
  matplot::grid(true);
  matplot::gca()->minor_grid(true);
  matplot::title("Gaussian membership function");
  matplot::show();
  return 0;
}
