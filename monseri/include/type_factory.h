#pragma once

#include "serializable.h"

#include <string>
#include <unordered_map>

namespace monseri
{
namespace factory
{
namespace detail
{

/// Factory function creating serializable
using Make_serializable = Serializable (*)();

/// Map of factory functions
using Factory_by_type_name = std::unordered_map<std::string, Make_serializable>;

Factory_by_type_name& factories()
{
    static Factory_by_type_name factories_;
    return factories_;
}

//! Static instance is created for each registered serializable type name
template <typename T>
struct Serializable_registrar
{
    //! Constructor registers the type.
    Serializable_registrar(const char* type_name)
    {
        factories()[type_name] = []() { return Serializable(T()); };
    }
};

} // namespace detail

//! Creates a concrete serializable type by its class name.
inline Serializable create(const std::string& type_name)
{
    using namespace detail;
    const auto it = factories().find(type_name);
    if(it != factories().end())
        return it->second();
    throw std::runtime_error(
        std::string("This type name was not registered: '") + type_name + "'");
}

} // namespace factory
} // namespace monseri
