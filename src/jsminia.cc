#include "jsminia.h"

EMSCRIPTEN_BINDINGS(jsminia) {
  // export DataType
  emscripten::enum_<minia::DataType>("DataType")
      .value("kInt64", minia::DataType::kInt64)
      .value("kFloat32", minia::DataType::kFloat32)
      .value("kString", minia::DataType::kString)
      .value("kInt64s", minia::DataType::kInt64s)
      .value("kFloat32s", minia::DataType::kFloat32s)
      .value("kStrings", minia::DataType::kStrings)
      .value("kError", minia::DataType::kError);

  // export JSMinia
  emscripten::class_<minia::JSMinia>("JSMinia")
      .constructor<emscripten::val>()
      .function("call", &minia::JSMinia::call);
}