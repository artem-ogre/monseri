#pragma once

#include <iostream>

namespace monseri
{

//! Storage reading serialized data from istream
struct Iostream_read_storage
{
    //! Constructor taking \param inStream stream
    explicit Iostream_read_storage(std::istream& stream)
        : m_stream(stream)
    {}

private:
    friend class Storage;

    template <typename T>
    void operator|(T&& obj) const
    {
        m_stream >> std::forward<T>(obj);
    }

private:
    std::istream& m_stream;
};

} // namespace monseri
