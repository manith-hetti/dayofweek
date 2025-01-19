#include <boost/math/distributions/chi_squared.hpp>
#include <vector>

struct Helper {
  bool chi_squared(const std::vector<int>& observed,
                     double expected_proportion,
                     double significance = 0.05) {
        int total = 0;
        for (int count : observed) {
            total += count;
        }
        double expected = total * expected_proportion;

        double chi_squared = 0;
        for (int count : observed) {
            double diff = count - expected;
            chi_squared += (diff * diff) / expected;
        }

        int degrees_freedom = observed.size() - 1;

        boost::math::chi_squared_distribution<double> dist(degrees_freedom);

        double p_value = 1 - boost::math::cdf(dist, chi_squared);

        return p_value > significance;
    }
};
