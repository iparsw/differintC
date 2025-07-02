#pragma once

#include <vector>
#include <cstddef>


namespace differint {

// Templated versions
template <typename T>
std::vector<T> GL(T alpha, const std::vector<T>& f_vals, T a, T b, std::size_t N);

template <typename T>
std::vector<T> RL(T alpha, const std::vector<T>& f_vals, T a, T b, std::size_t N);

template <typename T>
T GLpoint(T alpha, const std::vector<T>& f_vals, T a, T b, std::size_t N);

template <typename T>
T RLpoint(T alpha, const std::vector<T>& f_vals, T a, T b, std::size_t N);

template <typename T>
std::vector<T> GLcoeffs(T alpha, std::size_t n);

// Concrete declarations for pybind11 linkage
std::vector<double> GL(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N);
std::vector<double> RL(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N);
double GLpoint(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N);
double RLpoint(double alpha, const std::vector<double>& f_vals, double a, double b, std::size_t N);

std::vector<double> GLcoeffs(double alpha, std::size_t n);
}