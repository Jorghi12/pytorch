#pragma once

// ${generated_comment}

#include <ATen/ScalarType.h>
#include <ATen/TensorOperators.h>
#include <ATen/TensorMethods.h>
#include <ATen/TensorOptions.h>

#include <array>
#include <functional>
#include <string>
#include <tuple>
#include <vector>

namespace at {
struct Generator;
class Scalar;
struct Tensor;
struct Type;
} // namespace at

namespace at {
namespace native {

inline Tensor from_blob(
    void* data,
    IntList sizes,
    const std::function<void(void*)>& deleter,
    const TensorOptions& options = {}) {
  return at::getMaybeVariableType(options).tensorFromBlob(data, sizes, deleter);
}

inline Tensor from_blob(
    void* data,
    IntList sizes,
    IntList strides,
    const std::function<void(void*)>& deleter,
    const TensorOptions& options = {}) {
  return at::getMaybeVariableType(options).tensorFromBlob(data, sizes, strides, deleter);
}

inline Tensor from_blob(
    void* data,
    IntList sizes,
    const TensorOptions& options = {}) {
  return native::from_blob(data, sizes, /*deleter=*/[](void*) {}, options);
}

// These functions are defined in native/TensorFactories.cpp.
#define TENSOR(T, S, _1)                                               \
  AT_API Tensor tensor(ArrayRef<T> values, const TensorOptions& options);     \
  inline Tensor tensor(                                                \
      std::initializer_list<T> values, const TensorOptions& options) { \
    return native::tensor(ArrayRef<T>(values), options);               \
  }                                                                    \
  inline Tensor tensor(T value, const TensorOptions& options) {        \
    return native::tensor(ArrayRef<T>(value), options);                \
  }                                                                    \
  inline Tensor tensor(ArrayRef<T> values) {                           \
    return native::tensor(std::move(values), at::dtype(k##S));         \
  }                                                                    \
  inline Tensor tensor(std::initializer_list<T> values) {              \
    return native::tensor(ArrayRef<T>(values));                        \
  }                                                                    \
  inline Tensor tensor(T value) {                                      \
    return native::tensor(ArrayRef<T>(value));                         \
  }
AT_FORALL_SCALAR_TYPES_EXCEPT_HALF(TENSOR)
#undef TENSOR

${native_function_declarations}

} // namespace native
} // namespace at
