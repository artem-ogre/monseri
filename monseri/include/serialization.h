#pragma once

#include "serializable.h"
#include "storage.h"
#include "type_factory.h"

namespace monseri
{
namespace serialization
{

/*!
 * \brief Serializes a provided serializable object, saving its type-name first
 * \param obj an object to be serialized
 * \param storage lvalue reference
 */
template <typename TSerializable, typename TStorage>
inline void serialize(TSerializable&& obj, TStorage&& storage)
{
    auto type_name = obj.type_name();
    storage | type_name;
    obj.serialize(std::forward<TStorage>(storage));
}

/*!
 * \brief Deserialize a serializable object by reading its type-name first
 * \param storage lvalue reference
 * \return  A raw pointer to the newly created deserialized object
 */
template <typename TStorage>
inline Serializable deserialize(TStorage&& storage)
{
    std::string type_name;
    storage | type_name;
    Serializable serializable = factory::create(type_name);
    serializable.serialize(std::forward<TStorage>(storage));
    return serializable;
}

} // namespace serialization
} // namespace monseri
