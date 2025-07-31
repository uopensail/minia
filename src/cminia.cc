#include "cminia.h"

#include "common.h"
#include "features_generated.h"
#include "go.hpp"
#include "minia.h"

void minia_init_log(const char *log_dir, int32_t log_level) {
  enable_glog(log_dir, log_level);
}

void *minia_create(const char *expressions) {
  try {
    return new minia::Minia(expressions);
  } catch (const std::exception &e) {
    LOG(ERROR) << "Minia create exception:" << e.what() << "\n";
  } catch (...) {
    LOG(ERROR) << "Minia create unknown exception caught!\n";
  }
  return nullptr; // Ensure return on failure
}

void minia_release(void *m) {
  if (m) {
    delete static_cast<minia::Minia *>(m);
  }
}

void *minia_features(void *m) {
  if (!m) {
    return nullptr;
  }
  try {
    auto *mn = static_cast<minia::Minia *>(m);
    return new minia::StringSlice(mn->features());
  } catch (...) {
    return nullptr;
  }
}

void *minia_call(void *m, const char *data) {
  if (!m || !data) {
    return nullptr;
  }

  try {
    auto *mn = static_cast<minia::Minia *>(m);
    auto *feas = new minia::Features();

    const minia::FlatFeatures *data =
        flatbuffers::GetRoot<minia::FlatFeatures>(data);
    const size_t size = data->values()->size();
    for (size_t i = 0; i < size; i++) {
      const minia::FlatFeature *field = data->values()->Get(i);
      const minia::FlatValue type = field->value_type();
      const flatbuffers::String *key = field->name();

      minia::FeaturePtr ptr = nullptr;
      switch (type) {
      case minia::FlatValue::FlatValue_FlatInt64Value:
        ptr = std::make_shared<minia::Feature>(
            field->value_as_FlatInt64Value()->value());
        break;
      case minia::FlatValue::FlatValue_FlatFloatValue:
        ptr = std::make_shared<minia::Feature>(
            field->value_as_FlatFloatValue()->value());
        break;
      case minia::FlatValue::FlatValue_FlatStringValue:
        ptr = std::make_shared<minia::Feature>(
            field->value_as_FlatStringValue()->value()->str());
        break;
      case minia::FlatValue::FlatValue_FlatInt64Array: {
        const auto *array = field->value_as_FlatInt64Array()->value();
        std::vector<int64_t> value;
        value.reserve(array->size());
        value.assign(array->begin(), array->end());
        ptr = std::make_shared<minia::Feature>(std::move(value));
        break;
      }
      case minia::FlatValue::FlatValue_FlatFloatArray: {
        const auto *array = field->value_as_FlatFloatArray()->value();
        std::vector<float> value;
        value.reserve(array->size());
        value.assign(array->begin(), array->end());
        ptr = std::make_shared<minia::Feature>(std::move(value));
        break;
      }
      case minia::FlatValue::FlatValue_FlatStringArray: {
        const auto *array = field->value_as_FlatStringArray()->value();
        std::vector<std::string> value;
        value.reserve(array->size());
        for (const auto &s : *array) {
          value.emplace_back(s->str());
        }
        ptr = std::make_shared<minia::Feature>(std::move(value));
      }
      default:
        break;
      }

      if (ptr) {
        feas->insert(key->c_str(), ptr);
      }
    }

    mn->call(*feas);
    return feas;
  } catch (const std::exception &e) {
    LOG(ERROR) << "Minia call exception:" << e.what() << "\n";
  } catch (...) {
    LOG(ERROR) << "Minia call unknown exception caught!\n";
  }
  return nullptr;
}

void *minia_get_feature(void *features, const char *key, int32_t *type) {
  if (!features || !key || !type) {
    return nullptr;
  }

  auto *feas = static_cast<minia::Features *>(features);
  auto ptr = feas->get(key);

  if (!ptr) {
    *type = minia::DataType::kError;
    return nullptr;
  }

  *type = ptr->type;

  switch (*type) {
  case minia::DataType::kFloat32:
    return new float(ptr->get<float>());
  case minia::DataType::kFloat32s:
    return new minia::Float32Slice(ptr->get<std::vector<float>>());
  case minia::DataType::kInt64:
    return new int64_t(ptr->get<int64_t>());
  case minia::DataType::kInt64s:
    return new minia::Int64Slice(ptr->get<std::vector<int64_t>>());
  case minia::DataType::kString:
    return new minia::GoString(ptr->get<std::string>());
  case minia::DataType::kStrings:
    return new minia::StringSlice(ptr->get<std::vector<std::string>>());
  default:
    return nullptr;
  }
}

void minia_del_feature(void *feature, int32_t type) {
  if (!feature)
    return;

  switch (type) {
  case minia::DataType::kFloat32:
    delete static_cast<float *>(feature);
    break;
  case minia::DataType::kFloat32s:
    delete static_cast<minia::Float32Slice *>(feature);
    break;
  case minia::DataType::kInt64:
    delete static_cast<int64_t *>(feature);
    break;
  case minia::DataType::kInt64s:
    delete static_cast<minia::Int64Slice *>(feature);
    break;
  case minia::DataType::kString:
    delete static_cast<minia::GoString *>(feature);
    break;
  case minia::DataType::kStrings:
    delete static_cast<minia::StringSlice *>(feature);
    break;
  default:
    break;
  }
}

void minia_del_features(void *features) {
  delete static_cast<minia::Features *>(features);
}
