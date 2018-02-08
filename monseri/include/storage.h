#pragma once

#include <memory>
#include <string>

#if(!defined(_MSC_VER) || _MSC_VER < 1900) && (__cplusplus <= 201103L)
#include "make_shared_cpp11.h"
#endif

namespace monseri
{

//! Type-erased storage used for reading/writing serialized data.
class Storage
{
public:
    //! Type-erasing ctor
    template <typename T>
    Storage(T obj)
        : m_self(std::make_unique<Model<T> >(std::move(obj)))
    {}

    // rule of 5
    Storage() noexcept = default;
    Storage(const Storage& obj)
        : m_self(obj.m_self->copy())
    {}
    Storage& operator=(const Storage& obj)
    {
        return *this = Storage(obj);
    }
    Storage(Storage&& obj) noexcept = default;
    Storage& operator=(Storage&& obj) noexcept = default;

    //! Push/pop bool
    Storage& operator|(bool& obj)
    {
        m_self->operator|(obj);
        return *this;
    }

    //! Push/pop short
    Storage& operator|(short& obj)
    {
        m_self->operator|(obj);
        return *this;
    }

    //! Push/pop unsigned
    Storage& operator|(unsigned short& obj)
    {
        m_self->operator|(obj);
        return *this;
    }

    //! Push/pop int from
    Storage& operator|(int& obj)
    {
        m_self->operator|(obj);
        return *this;
    }

    //! Push/pop unsigned int
    Storage& operator|(unsigned int& obj)
    {
        m_self->operator|(obj);
        return *this;
    }

    //! Push/pop long
    Storage& operator|(long& obj)
    {
        m_self->operator|(obj);
        return *this;
    }

    //! Push/pop unsigned long
    Storage& operator|(unsigned long& obj)
    {
        m_self->operator|(obj);
        return *this;
    }

    //! Process float
    Storage& operator|(float& obj)
    {
        m_self->operator|(obj);
        return *this;
    }

    //! Push/pop double
    Storage& operator|(double& obj)
    {
        m_self->operator|(obj);
        return *this;
    }

    //! Push/pop long double
    Storage& operator|(long double& obj)
    {
        m_self->operator|(obj);
        return *this;
    }

    //! Push/pop string
    Storage& operator|(std::string& obj)
    {
        m_self->operator|(obj);
        return *this;
    }

private:
    struct Concept
    {
        virtual void operator|(bool& obj) = 0;
        virtual void operator|(short& obj) = 0;
        virtual void operator|(unsigned short& obj) = 0;
        virtual void operator|(int& obj) = 0;
        virtual void operator|(unsigned int& obj) = 0;
        virtual void operator|(long& obj) = 0;
        virtual void operator|(unsigned long& obj) = 0;
        virtual void operator|(float& obj) = 0;
        virtual void operator|(double& obj) = 0;
        virtual void operator|(long double& obj) = 0;
        virtual void operator|(std::string& obj) = 0;
        virtual std::unique_ptr<Concept> copy() = 0;
    };

    template <typename T>
    class Model final : public Concept
    {
    public:
        Model(T x)
            : m_data(std::move(x))
        {}

    private:
        std::unique_ptr<Concept> copy() override
        {
            return std::make_unique<Model>(*this);
        }

        void operator|(bool& obj) override
        {
            m_data.operator|(obj);
        }

        void operator|(short& obj) override
        {
            m_data.operator|(obj);
        }

        void operator|(unsigned short& obj) override
        {
            m_data.operator|(obj);
        }

        void operator|(int& obj) override
        {
            m_data.operator|(obj);
        }

        void operator|(unsigned int& obj) override
        {
            m_data.operator|(obj);
        }

        void operator|(long& obj) override
        {
            m_data.operator|(obj);
        }

        void operator|(unsigned long& obj) override
        {
            m_data.operator|(obj);
        }

        void operator|(float& obj) override
        {
            m_data.operator|(obj);
        }

        void operator|(double& obj) override
        {
            m_data.operator|(obj);
        }

        void operator|(long double& obj) override
        {
            m_data.operator|(obj);
        }

        void operator|(std::string& obj) override
        {
            m_data.operator|(obj);
        }

    private:
        T m_data;
    };

    std::unique_ptr<Concept> m_self;
};

} // namespace monseri
