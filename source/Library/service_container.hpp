#pragma once

#include "common.hpp"

namespace Library {

class ServiceContainer {
public:
  ServiceContainer() : mServices() {}
  ServiceContainer(const ServiceContainer&) = delete;

  ServiceContainer& operator=(const ServiceContainer&) = delete;
  ~ServiceContainer() = default;

  void AddService(UINT typeID, void* service);
  void* GetService(UINT typeID) const;
  void RemoveService(UINT typeID);

private:
  std::map<UINT, void*> mServices;
}; // class ServiceContainer

} // namespace Library