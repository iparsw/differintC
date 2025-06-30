# Todo List 1 (6/30/2025) (AI Generated)

---

### ✅ Immediate TODOs (essential for adding new functions)

These are required for each additional fractional differintegral method you want to port:

#### For each new C++ function:

1. **`include/differint/differint.hpp`**

   * Add the `template <typename T> T|std::vector<T> FunctionName(...)` declaration.

2. **`src/differint/differint.cpp`**

   * Implement the function.
   * Add `template` instantiation at the bottom:
     `template double FunctionName<double>(...);`

3. **`python/module.cpp`**

   * Bind the function to Python using `m.def(...)`.

4. **Optional: `src/differint/sanity.cpp`**

   * Add a manual C++ test to verify numeric accuracy.

---

### 📦 Packaging & Distribution

* ~~**Add `README.md` and `LICENSE` files** in the root for PyPI display.~~
* [ ] **Set versioning strategy** (e.g., `semver`, calendar versioning).
* ~~**Add a `setup.cfg` or more advanced `pyproject.toml`** with classifiers, long description from `README.md`, etc.~~

---

### 🧪 Usability Improvements

* [ ] **Support `Callable` Python functions directly** via `py::function` overloads.

  * This will let users call C++ methods with `lambda x: ...` directly.
  * Requires defining Python overloads (already mostly done).

* [ ] **Add NumPy array support directly via `py::array_t<double>`**:

  * Improves interop and reduces unnecessary Python → C++ copies.

---

### 🧹 Code Quality & Developer Experience

* [ ] **Add CMake options to toggle building:**

  * `DIFFERINT_BUILD_SANITY`
  * `DIFFERINT_BUILD_PYTHON`
  * Cleaner, configurable builds.

* [ ] **Write a test script in Python**:

  * `tests/test_rl.py` with assertions
  * Could use `pytest` later, but start with simple scripts

* [ ] **Add Doxygen-style comments** to your headers

  * Enables future documentation generation.

---

### 📘 Longer-Term / Optional

* [ ] **Benchmarking tools** for RL vs GL methods.
* [ ] **CI/CD automation** (GitHub Actions or similar for testing + PyPI deploy).
* [ ] **Optional GUI or CLI** interface for experimentation.
* [ ] **Add support for complex-valued functions** if useful.
* [ ] **Support mixed precision or `float`, `long double`**, if needed.

---

Would you like to continue by:

* Implementing the next function (e.g., `GLpoint`)
* Or tackling one of the improvements from above (e.g., better Python interop)?
