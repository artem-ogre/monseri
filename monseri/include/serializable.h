#pragma once

#include "attorney.h"
#include "storage.h"
#include "type_registry.h"

#include <memory>
#include <string>
#include <utility>

#if(!defined(_MSC_VER) || _MSC_VER < 1900) && (__cplusplus <= 201103L)
#include "make_shared_cpp11.h"
#endif

namespace monseri
{

//!  Type-erased serializable type
class Serializable
{
public:
    //! Type-erasing ctor
    template <typename T>
    Serializable(T obj)
        : m_self(std::make_unique<Model<T> >(std::move(obj)))
    {}

    //! Writes itself to a write storage
    void serialize(Storage& storage)
    {
        return m_self->serialize(storage);
    }

    //! Get registered name of erased serializable type
    std::string type_name() const
    {
        return m_self->type_name();
    }

    //! Get erased type data
    template <typename T>
    T get() const
    {
        return static_cast<Model<T>*>(m_self.get())->get();
    }

    // rule of 5
    Serializable() noexcept = default;
    Serializable(const Serializable& obj)
        : m_self(obj.m_self->copy())
    {}
    Serializable& operator=(const Serializable& obj)
    {
        return *this = Serializable(obj);
    }
    Serializable(Serializable&& obj) noexcept = default;
    Serializable& operator=(Serializable&& obj) noexcept = default;

private:
    struct Concept
    {
        virtual ~Concept() = default;
        virtual void serialize(Storage& stream) = 0;
        virtual std::unique_ptr<Concept> copy() = 0;
        virtual std::string type_name() const = 0;
    };

    template <typename T>
    class Model final : public Concept
    {
    public:
        Model(T x)
            : m_data(std::move(x))
        {}

        T get() const
        {
            return m_data;
        }

    private:
        void serialize(Storage& storage) override
        {
            Attorney::dispatch_serialize(m_data, storage);
        }

        std::string type_name() const override
        {
            return registry::type_name<T>();
        }

        virtual std::unique_ptr<Concept> copy() override
        {
            return std::make_unique<Model>(*this);
        }

    private:
        T m_data;
    };

private:
    std::unique_ptr<Concept> m_self;
};

} // namespace monseri
