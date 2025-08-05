#include "jsminia.h"

EMSCRIPTEN_BINDINGS(jsminia) {
  emscripten::class_<minia::JSMinia>("JSMinia")
      .constructor<emscripten::val>()
      .function("call", &minia::JSMinia::call);
}