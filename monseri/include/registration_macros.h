#pragma once

#include "type_factory.h"

// Register serializable type with its own name
#define MONSERI_REGISTER_TYPE(T) MONSERI_REGISTER_TYPE_WITH_NAME(T, #T)

// Register serializable type with provided name
#define MONSERI_REGISTER_TYPE_WITH_NAME(T, type_name)                          \
    MONSERI_REGISTER_TYPE_NAME(T, type_name)                                   \
    MONSERI_REGISTER_TYPE_FACTORY(T)

// Registers given type name for a type using partial template specialization
#define MONSERI_REGISTER_TYPE_NAME(T, type_name)                               \
    namespace monseri                                                          \
    {                                                                          \
    namespace registry                                                         \
    {                                                                          \
    namespace detail                                                           \
    {                                                                          \
    template <>                                                                \
    struct Registered_type_info<T>                                             \
    {                                                                          \
        static constexpr const char* name = type_name;                         \
    };                                                                         \
    }                                                                          \
    }                                                                          \
    }

// Add a type factory-method for serializable T to the map statically
#define MONSERI_REGISTER_TYPE_FACTORY(T)                                       \
    namespace                                                                  \
    {                                                                          \
    static monseri::factory::detail::Serializable_registrar<T>                 \
        MONSERI_UID(monseri::registry::detail::Registered_type_info<T>::name); \
    }

// Create unique ID by attaching a line-number to some id
#define MONSERI_UID MONSERI_CREATE_UID(__LINE__)
#define MONSERI_CREATE_UID(line) MONSERI_CONCATENATE(monseri_uid_, line)
#define MONSERI_CONCATENATE(A, B) A##B
