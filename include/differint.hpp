#pragma once

#include <vector>
#include <cstddef>


namespace differint {

// Templated versions
template <typename T>
std::vector<T> GL(T alpha, const std::vector<T>& f_vals, T a, T b, std::size_t N);

template <typename T>
std::vector<T> GLthread(T alpha, const std::vector<T>& f_vals, T a, T b, std::size_t N);

template <typename T>
std::vector<T> GLfull(T alpha, const std::vector<T>& f_vals, T a, T b, std::size_t N);

template <typename T>
std::vector<T> RL(T alpha, const std::vector<T>& f_vals, T a, T b, std::size_t N);

template <typename T>
T GLpoint(T alpha, const std::vector<T>& f_vals, T a, T b, std::size_t N);

template <typename T>
T RLpoint(T alpha, const std::vector<T>& f_vals, T a, T b, std::size_t N);



// Concrete declarations for pybind11 linkage
std::vector<double> GL(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N);
std::vector<double> GLthread(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N);
std::vector<double> GLfull(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N);
std::vector<double> RL(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N);
double GLpoint(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N);
double RLpoint(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N);

template <typename T>
std::vector<T> GLcoeffs(T alpha, std::size_t n);

std::vector<double> GLcoeffs(double alpha, std::size_t n);

// Only the template definition should be in the header
template <typename T>
std::vector<T> GLcoeffs(T alpha, std::size_t n) {
    std::vector<T> b;
    b.reserve(n + 1);
    b.push_back(T(1));
    for (std::size_t j = 1; j <= n; ++j) {
        T j_t = static_cast<T>(j);
        b.push_back(b.back() * (j_t - 1 - alpha) / j_t);
    }
    return b;

}

} // namespace differint