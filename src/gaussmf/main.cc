#include <matplot/axes_objects/line.h>
#include <matplot/core/axes_type.h>
#include <matplot/freestanding/axes_functions.h>
#include <matplot/freestanding/axes_lim.h>
#include <matplot/freestanding/plot.h>
#include <matplot/util/common.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <memory>
#include <ranges>
#include <vector>

double gaussmf(double x, double c, double sig) {
  return std::exp(-((x - c) * (x - c)) / (2 * sig * sig));
}

std::function<double(double)> makeGaussmf(double c, double sig) {
  return [c, sig](double x) -> double { return gaussmf(x, c, sig); };
}

int main(const int argc, const char* argv[]) {
  using std::views::transform, std::ranges::to;

  std::vector<double> x_numbers = matplot::linspace(-5, 5);
  std::vector<double> y_numbers =
      x_numbers | transform(makeGaussmf(0, 1.2)) | to<std::vector>();

  matplot::plot(x_numbers, y_numbers)->line_width(2);
  matplot::ylim({0, 1.5});
  matplot::grid(true);
  matplot::gca()->minor_grid(true);
  matplot::title("Gaussian membership function");
  matplot::show();
  return 0;
}
