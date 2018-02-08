#pragma once

#include <utility>

namespace monseri
{

class Serializable;
class Storage;

//! Serialization attorney, able to call private serialize method
class Attorney
{
    //! Dispatches serialize call either to member or non-member function
    //! \note called by a friend-class serializable
    template <typename T>
    static inline void dispatch_serialize(T& data, Storage& storage)
    {
        constexpr bool has_member = Has_member_serialize<T>::value;
        constexpr bool has_free = Has_free_serialize<T>::value;

        // produce an informative message if serialization is not found
        constexpr bool is_serializable = has_member || has_free;
        // clang-format off
        static_assert( is_serializable, "Missing member or non-member `serialize` function for T.");
        static_assert( is_serializable, "Member signature for T: [ T::serialize(monseri::Storage&) ]");
        static_assert( is_serializable, "Free-function signature for T: [ monseri::serialize(T&, monseri::Storage&) ]");
        // clang-format on

        Serialization_dispatcher<T, has_member>::dispatch_serialize(
            data, storage);
    }
    friend class monseri::Serializable;

private:
    // c++11 alternative to std::void_t
    template <typename...>
    using Void = void;

    // Checking if type has a member serialize
    template <typename T, typename = void>
    struct Has_member_serialize : public std::false_type
    {};

    template <typename T>
    struct Has_member_serialize<
        T,
        Void<decltype(std::declval<T>().serialize(std::declval<Storage&>()))> >
        : public std::true_type
    {};

    // Check if type has a free-function serialize
    template <typename T, typename = void>
    struct Has_free_serialize : public std::false_type
    {};

    template <typename T>
    struct Has_free_serialize<
        T,
        Void<decltype(
            serialize(std::declval<T&>(), std::declval<Storage&>()))> >
        : public std::true_type
    {};

    // Dispatch based on which serialize is present: member or non-member
    template <typename T, bool HasMemberSerialize>
    struct Serialization_dispatcher
    {};

    // Dispatch as method
    template <typename T>
    struct Serialization_dispatcher<T, true>
    {
        static inline void dispatch_serialize(T& data, Storage& storage)
        {
            data.serialize(storage);
        }
    };

    // Dispatch as free function
    template <typename T>
    struct Serialization_dispatcher<T, false>
    {
        static inline void dispatch_serialize(T& data, Storage& storage)
        {
            serialize(data, storage);
        }
    };
};

} // namespace monseri
