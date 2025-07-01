#ifdef _WIN32
#define NOMINMAX  // Prevent Windows min/max macros
#endif

#include "differint.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <type_traits>
#include <fftw3.h>

namespace differint {

template <typename T>
T RLpoint(T alpha,
           const std::vector<T>& f_vals,
           T domain_start,
           T domain_end,
           std::size_t num_points) {
    if (num_points < 2) {
        throw std::invalid_argument("num_points must be at least 2");
    }
    // Ensure domain ordering
    if (domain_start > domain_end) {
        std::swap(domain_start, domain_end);
    }
    // Check input vector length
    if (f_vals.size() != num_points) {
        throw std::invalid_argument("f_vals size does not match num_points");
    }
    // Compute step size
    T step = (domain_end - domain_start) / static_cast<T>(num_points - 1);

    std::size_t k = num_points - 1;
    std::vector<T> coeffs(num_points);

    // Case j == 0
    if (k > 0) {
        coeffs[0] = std::pow(static_cast<T>(k - 1), static_cast<T>(1) - alpha)
                    - (static_cast<T>(k) + alpha - static_cast<T>(1))
                      * std::pow(static_cast<T>(k), -alpha);
    } else {
        coeffs[0] = T(1);
    }

    // Case j == k
    coeffs[k] = T(1);

    // Other indices
    for (std::size_t j = 1; j < k; ++j) {
        T d = static_cast<T>(k - j);
        coeffs[j] = std::pow(d + static_cast<T>(1), static_cast<T>(1) - alpha)
                    + std::pow(d - static_cast<T>(1), static_cast<T>(1) - alpha)
                    - static_cast<T>(2) * std::pow(d, static_cast<T>(1) - alpha);
    }

    // Compute normalization constant
    T C = static_cast<T>(1) / std::tgamma(static_cast<T>(2) - alpha);

    // Dot product
    T result = T(0);
    for (std::size_t i = 0; i < num_points; ++i) {
        result += coeffs[i] * f_vals[i];
    }

    return C * std::pow(step, -alpha) * result;
}


// RL entire-grid implementation
template <typename T>
std::vector<T> RL(T alpha,
                  const std::vector<T>& f_vals,
                  T domain_start,
                  T domain_end,
                  std::size_t num_points) {
    if (num_points < 2) {
        throw std::invalid_argument("num_points must be at least 2");
    }
    if (domain_start > domain_end) {
        std::swap(domain_start, domain_end);
    }
    if (f_vals.size() != num_points) {
        throw std::invalid_argument("f_vals size does not match num_points");
    }
    T step = (domain_end - domain_start) / static_cast<T>(num_points - 1);

    // Precompute coefficient matrix D
    std::vector<std::vector<T>> D(num_points, std::vector<T>(num_points));
    // Precompute powers v[k] = (k)^(1-alpha)
    std::vector<T> v(num_points + 1);
    for (std::size_t k = 0; k <= num_points; ++k) {
        v[k] = std::pow(static_cast<T>(k), static_cast<T>(1) - alpha);
    }

    // Fill D
    for (std::size_t i = 0; i < num_points; ++i) {
        for (std::size_t j = 0; j < num_points; ++j) {
            if (j == i) {
                D[i][j] = T(1);
            } else if (j == 0 && i > 0) {
                T k = static_cast<T>(i);
                D[i][0] = v[i - 1] - (k + alpha - static_cast<T>(1)) * std::pow(k, -alpha);
            } else if (j < i) {
                std::size_t k = i - j;
                D[i][j] = v[k + 1] + v[k - 1] - static_cast<T>(2) * v[k];
            } else {
                D[i][j] = T(0);
            }
        }
    }

    // Normalize by Gamma
    T C = static_cast<T>(1) / std::tgamma(static_cast<T>(2) - alpha);

    // Multiply D @ f_vals
    std::vector<T> result(num_points, T(0));
    for (std::size_t i = 0; i < num_points; ++i) {
        T acc = T(0);
        for (std::size_t j = 0; j < num_points; ++j) {
            acc += D[i][j] * f_vals[j];
        }
        result[i] = C * std::pow(step, -alpha) * acc;
    }
    return result;
}




// Compute GL coefficients up to order n
template <typename T>
std::vector<T> GLcoeffs(T alpha, std::size_t n) {
    // b[0] = 1
    std::vector<T> b(n + 1, T(1));
    for (std::size_t j = 1; j <= n; ++j) {
        b[j] = b[j - 1] * (static_cast<T>(-alpha) + static_cast<T>(j - 1))
               / static_cast<T>(j);
    }
    return b;
}


// GL at a single point (endpoint)
template <typename T>
T GLpoint(T alpha,
          const std::vector<T>& f_vals,
          T domain_start,
          T domain_end,
          std::size_t num_points) {
    // Need at least two points to compute a meaningful step size
    if (num_points < 2) {
        throw std::invalid_argument("num_points must be at least 2");
    }
    if (domain_start > domain_end) {
        std::swap(domain_start, domain_end);
    }
    if (f_vals.size() != num_points) {
        throw std::invalid_argument("f_vals size must equal num_points");
    }
    T step = (domain_end - domain_start) / static_cast<T>(num_points - 1);
    // Compute coefficients for k = num_points - 1
    std::size_t k = num_points - 1;
    auto b = GLcoeffs(alpha, k);
    T acc = T(0);
    for (std::size_t j = 0; j <= k; ++j) {
        acc += b[j] * f_vals[k - j];
    }
    return std::pow(step, -alpha) * acc;
}

// GL over entire grid
// Optimized GL implementation with FFT acceleration
template <typename T>
std::vector<T> GL(T alpha,
                  const std::vector<T>& f_vals,
                  T domain_start,
                  T domain_end,
                  std::size_t num_points) {
    if (num_points < 1) throw std::invalid_argument("num_points must be at least 1");
    if (f_vals.size() != num_points) throw std::invalid_argument("f_vals size must equal num_points");
    if (domain_start > domain_end) std::swap(domain_start, domain_end);

    const T step = (domain_end - domain_start) / static_cast<T>(num_points - 1);
    const auto b = GLcoeffs(alpha, num_points - 1);

    // For non-double types or small inputs, use direct convolution
    if (!std::is_same<T, double>::value || num_points < 256) { // THRESHHOLD
        std::vector<T> result(num_points, T(0));
        for (std::size_t i = 0; i < num_points; ++i) {
            T acc = T(0);
            for (std::size_t j = 0; j <= i; ++j) {
                acc += b[j] * f_vals[i - j];
            }
            result[i] = std::pow(step, -alpha) * acc;
        }
        return result;
    }

    // FFT-based convolution for double precision
    const int M = 2 * num_points - 1;

    double* in1 = static_cast<double*>(fftw_malloc(sizeof(double) * M));
    double* in2 = static_cast<double*>(fftw_malloc(sizeof(double) * M));
    fftw_complex* out1 = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * (M/2 + 1)));
    fftw_complex* out2 = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * (M/2 + 1)));
    fftw_complex* out_prod = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * (M/2 + 1)));
    double* conv_result = static_cast<double*>(fftw_malloc(sizeof(double) * M));

    // Zero-padding
    std::fill_n(in1, M, 0.0);
    std::fill_n(in2, M, 0.0);
    std::copy(b.begin(), b.end(), in1);
    std::copy(f_vals.begin(), f_vals.end(), in2);

    // Create plans
    fftw_plan p1 = fftw_plan_dft_r2c_1d(M, in1, out1, FFTW_ESTIMATE);
    fftw_plan p2 = fftw_plan_dft_r2c_1d(M, in2, out2, FFTW_ESTIMATE);
    fftw_plan p_inv = fftw_plan_dft_c2r_1d(M, out_prod, conv_result, FFTW_ESTIMATE);

    // Execute FFTs
    fftw_execute(p1);
    fftw_execute(p2);

    // Complex multiplication
    for (int i = 0; i <= M/2; ++i) {
        out_prod[i][0] = out1[i][0] * out2[i][0] - out1[i][1] * out2[i][1];
        out_prod[i][1] = out1[i][0] * out2[i][1] + out1[i][1] * out2[i][0];
    }

    // Inverse transform
    fftw_execute(p_inv);

    // Prepare result
    const double scale = 1.0 / M;
    const T step_power = std::pow(step, -alpha);
    std::vector<T> result(num_points);
    for (int i = 0; i < num_points; ++i) {
        result[i] = static_cast<T>(conv_result[i] * scale) * step_power;
    }

    // Cleanup
    fftw_destroy_plan(p1);
    fftw_destroy_plan(p2);
    fftw_destroy_plan(p_inv);
    fftw_free(in1);
    fftw_free(in2);
    fftw_free(out1);
    fftw_free(out2);
    fftw_free(out_prod);
    fftw_free(conv_result);

    return result;
}


} // namespace differint

// Explicit instantiations for double
template std::vector<double> differint::GL<double>(double, const std::vector<double>&, double, double, std::size_t);
template std::vector<double> differint::RL<double>(double, const std::vector<double>&, double, double, std::size_t);
template double differint::GLpoint<double>(double, const std::vector<double>&, double, double, std::size_t);
template double differint::RLpoint<double>(double, const std::vector<double>&, double, double, std::size_t);
template std::vector<double> differint::GLcoeffs<double>(double, std::size_t);


// Expose concrete symbols
namespace differint {
    std::vector<double> GL(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N) {
        return GL<double>(alpha, f_vals, a, b, N);
    }
    std::vector<double> RL(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N) {
        return RL<double>(alpha, f_vals, a, b, N);
    }
    double GLpoint(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N) {
        return GLpoint<double>(alpha, f_vals, a, b, N);
    }
    double RLpoint(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N) {
        return RLpoint<double>(alpha, f_vals, a, b, N);
    }
}