//
// `Minia` - A C++ tool for feature transformation and hashing
// Copyright (C) 2019 - present Uopensail <timepi123@gmail.com>
// This software is distributed under the GNU Affero General Public License
// (AGPL3.0) For more information, please visit:
// https://www.gnu.org/licenses/agpl-3.0.html
//
// This program is free software: you are free to redistribute and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Refer to the
// GNU Affero General Public License for more details.
//

#ifndef JS_MINIA_H_
#define JS_MINIA_H_

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <vector>

#include "minia.h"

namespace minia {
class JSMinia {
public:
  /**
   * @brief Deleted default constructor.
   *
   * The default constructor is deleted to enforce the use of `expressions`
   * for initialization.
   */
  JSMinia() = delete;

  /**
   * @brief Constructs a JSMinia object using `expressions`.
   *
   * This constructor initializes the underlying Minia object with the
   * specified `expressions`.
   *
   * @param expressions The expressions to be processed.
   */
  explicit JSMinia(emscripten::val expressions) {
    if (!expressions.isArray()) {
      std::cerr << "Expressions Is Not an array!" << std::endl;
      exit(-1);
    }

    int length = expressions["length"].as<int>();
    std::vector<std::string> ret;
    ret.reserve(length);
    for (int i = 0; i < length; i++) {
      ret.push_back(expressions[i].as<std::string>());
    }

    minia_ = std::make_unique<Minia>(ret);
  }

  /**
   * @brief Release minia
   */
  void release() { minia_.reset(); }

  /**
   * @brief Default destructor.
   */
  ~JSMinia() = default;

  /**
   * @brief Processes features and returns the results as a JSObject(JSON).
   *
   * This function applies the configured operations to the input features and
   * returns a dictionary of results, with type conversions handled for JS
   * compatibility.
   *
   * @param features A buffer representing the features to process.
   * @return A JSObject(JSON) containing the processed feature values.
   */
  emscripten::val call(emscripten::val features) {
    Features feas;
    emscripten::val object = emscripten::val::global("Object");
    emscripten::val keys = object.call<emscripten::val>("keys", features);
    int length = keys["length"].as<int>();

    for (int i = 0; i < length; i++) {
      std::string key = keys[i].as<std::string>();
      emscripten::val data = features[key];
      DataType type = DataType(data["type"].as<int>());
      emscripten::val value = data["value"];
      FeaturePtr ptr = nullptr;
      switch (type) {
      case DataType::kInt64:
        ptr = std::make_shared<Feature>(value.as<int64_t>());
        break;
      case DataType::kFloat32:
        ptr = std::make_shared<Feature>(value.as<float>());
        break;
      case DataType::kString:
        ptr = std::make_shared<Feature>(value.as<std::string>());
        break;
      case DataType::kInt64s: {
        std::vector<int64_t> array;
        int size = value["length"].as<int>();
        array.reserve(size);

        for (int j = 0; j < size; j++) {
          array.push_back(value[j].as<int64_t>());
        }

        ptr = std::make_shared<Feature>(array);
        break;
      }
      case DataType::kFloat32s: {
        std::vector<float> array;
        int size = value["length"].as<int>();
        array.reserve(size);

        for (int j = 0; j < size; j++) {
          array.push_back(value[j].as<float>());
        }

        ptr = std::make_shared<Feature>(array);
        break;
      }
      case DataType::kStrings: {
        std::vector<std::string> array;
        int size = value["length"].as<int>();
        array.reserve(size);

        for (int j = 0; j < size; j++) {
          array.push_back(value[j].as<std::string>());
        }

        ptr = std::make_shared<Feature>(array);
        break;
      }
      default:
        break;
      }

      if (ptr != nullptr) {
        feas.insert(key, ptr);
      }
    }

    minia_->call(feas);

    const auto &fkeys = minia_->features();

    emscripten::val ret = emscripten::val::object();

    for (const auto &k : fkeys) {
      FeaturePtr f = feas.get(k);
      if (!f) {
        continue;
      }
      switch (f->type) {
      case minia::DataType::kFloat32: {
        emscripten::val value = emscripten::val::object();
        value.set("type", int(minia::DataType::kFloat32));
        value.set("value", f->get<float>());
        ret.set(k, value);
        break;
      }
      case minia::DataType::kFloat32s: {
        emscripten::val array = emscripten::val::array();
        const auto &values = f->get<std::vector<float>>();
        for (const auto &v : values) {
          array.call<void>("push", v);
        }
        emscripten::val value = emscripten::val::object();
        value.set("type", int(minia::DataType::kFloat32s));
        value.set("value", array);
        ret.set(k, value);
        break;
      }
      case minia::DataType::kInt64: {
        emscripten::val value = emscripten::val::object();
        value.set("type", int(minia::DataType::kInt64));
        value.set("value", f->get<int64_t>());
        ret.set(k, value);
        break;
      }
      case minia::DataType::kInt64s: {
        emscripten::val array = emscripten::val::array();
        const auto &values = f->get<std::vector<int64_t>>();
        for (const auto &v : values) {
          array.call<void>("push", v);
        }
        emscripten::val value = emscripten::val::object();
        value.set("type", int(minia::DataType::kInt64s));
        value.set("value", array);
        ret.set(k, value);
        break;
      }
      case minia::DataType::kString: {
        emscripten::val value = emscripten::val::object();
        value.set("type", int(minia::DataType::kString));
        value.set("value", f->get<std::string>());
        ret.set(k, value);
        break;
      }
      case minia::DataType::kStrings: {
        emscripten::val array = emscripten::val::array();
        const auto &values = f->get<std::vector<std::string>>();
        for (const auto &v : values) {
          array.call<void>("push", v);
        }
        emscripten::val value = emscripten::val::object();
        value.set("type", int(minia::DataType::kStrings));
        value.set("value", array);
        ret.set(k, value);
        break;
      }
      default:
        break;
      }
    }
    return ret;
  }

private:
  std::unique_ptr<Minia> minia_; /**< An instance of the Minia class to
                   perform feature processing. */
};

} // namespace minia

#endif // JS_MINIA_H_
