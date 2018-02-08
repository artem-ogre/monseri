#pragma once

#include <iostream>

namespace monseri
{

//! Storage writing serialized data to ostream
struct Iostream_write_storage
{
    //! Ctor taking \param outStream ostream that the storage uses.
    explicit Iostream_write_storage(std::ostream& stream)
        : m_stream(stream)
    {}

private:
    friend class Storage;
    //! Write object to storage.
    template <class T>
    void operator|(T&& obj) const
    {
        m_stream << std::endl << std::forward<T>(obj);
    }

private:
    std::ostream& m_stream;
};

} // namespace monseri
