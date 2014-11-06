#include "service_container.hpp"

namespace Library {

void ServiceContainer::AddService(UINT typeID, void* service) {
  mServices.insert(std::pair<UINT, void*>(typeID, service));
}

void* ServiceContainer::GetService(UINT typeID) const {
  auto it = mServices.find(typeID);
  return (it != mServices.end() ? it->second : nullptr);
}

void ServiceContainer::RemoveService(UINT typeID) {
  mServices.erase(typeID);
}

} // namespace Library