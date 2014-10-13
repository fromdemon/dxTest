#pragma once

#include <string>

namespace Library {

  class RTTI {
  public:
    virtual const unsigned int&  TypeIdInstance() const = 0;

    virtual RTTI* QueryInterface(const unsigned int id) const {
      return nullptr;
    }

    virtual bool Is(const unsigned int id) const {
      return false;
    }

    virtual bool Is(const std::string& name) const {
      return false;
    }

    template <typename T>
    T* As() const {
      if (Is(T::TypeIdClass()))
        return (T*)this;
      else
        return nullptr;
    }
  }; // class RTTI

#define RTTI_DECLARATION(Type, ParentType)                                                      \
    public:                                                                                     \
      typedef ParentType Parent;                                                                \
      static const std::string TypeName() { return std::string(#Type); }                        \
      virtual const unsigned int& TypeInstance() const { return Type::TypeIdClass(); }          \
      static const unsigned int& TypeIdClass() { return sRunTimeTypeId; }                       \
      virtual RTTI* QueryInterface(const unsigned int id) {                                     \
        if (id == sRunTimeTypeId)                                                               \
          return (RTTI*)this;                                                                   \
        else                                                                                    \
          return Parent::QueryInterface(id);                                                    \
      }                                                                                         \
      virtual bool Is(const unsigned int& id) const {                                           \
        if (id == sRunTimeTypeId)                                                               \
          return true;                                                                          \
        else                                                                                    \
          return Parent::Is(id);                                                                \
      }                                                                                         \
      virtual bool Is(const std::string& name) {                                                \
        if (name == TypeName())                                                                   \
          return true;                                                                          \
        else                                                                                    \
          return Parent::Is(name);                                                              \
      }                                                                                         \
    private:                                                                                    \
        static unsigned int sRunTimeTypeId;                                            
  
  #define RTTI_DEFINITIONS(Type)  unsigned int Type::sRunTimeType = static_cast<unsigned int>(&Type::sRunTimeTypeId);

} // namespace Library