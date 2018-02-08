/// \file
/// \brief This header contains functionality needed for serializing and
/// deserealizing to/from a stream

#pragma once

#include "serializable.h"
#include "serialization.h"
#include "storage.h"

#include "iostream_storage/iostream_read_storage.h"
#include "iostream_storage/iostream_write_storage.h"

#include <iostream>

namespace monseri
{

//! Serialize object to ostream
inline std::ostream& operator<<(std::ostream& stream, const Serializable& obj)
{
    Storage storage{Iostream_write_storage(stream)};
    serialization::serialize(const_cast<Serializable&>(obj), storage);
    return stream;
}

//! Deserialize object from istream
inline std::istream& operator>>(std::istream& stream, Serializable& obj)
{
    Storage storage{Iostream_read_storage(stream)};
    obj = serialization::deserialize(storage);
    return stream;
}

} // namespace monseri
