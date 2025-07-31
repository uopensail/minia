#include "jsminia.h"

EMSCRIPTEN_BINDINGS(jsminia) {
  emscripten::register_vector<std::string>("VectorString");
  emscripten::class_<minia::JSMinia>("JSMinia")
      .constructor<const std::vector<std::string> &>()
      .function("call", &minia::JSMinia::call);
}