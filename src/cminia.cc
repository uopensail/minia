
#include "cminia.h"
#include "go.hpp"
#include "minia.h"

void *minia_create(const char *config_path) {
  try {
    return new minia::Minia(config_path);
  } catch (const std::exception &e) {
    std::cerr << "minia_create exception:" << e.what() << std::endl;
  } catch (...) {
    std::cerr << "minia_create Unknown exception caught!" << std::endl;
  }
  return nullptr; // Ensure return on failure
}

void minia_release(void *m) { delete static_cast<minia::Minia *>(m); }

void *minia_features(void *m) {
  if (!m)
    return nullptr;
  try {
    auto *mn = static_cast<minia::Minia *>(m);
    return new minia::StringSlice(mn->features());
  } catch (...) {
    return nullptr;
  }
}

void *minia_call(void *m, const char *data) {
  if (!m || !data)
    return nullptr;

  try {
    auto *mn = static_cast<minia::Minia *>(m);
    auto *feas = new minia::Features(data);
    mn->call(*feas);
    return feas;
  } catch (const std::exception &e) {
    std::cerr << "minia_call exception:" << e.what() << std::endl;
  } catch (...) {
    std::cerr << "minia_call unknown exception caught!" << std::endl;
  }
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
