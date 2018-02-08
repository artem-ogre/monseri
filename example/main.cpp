#include <iostream_storage/shift_operators.h>
#include <registration_macros.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Grid
{
    int size_x;
    int size_y;
};

namespace monseri
{
// serialization as a free function
void serialize(Grid& data, monseri::Storage& storage)
{
    storage | data.size_x | data.size_y;
}
} // namespace monseri

template <typename T>
struct Point_2d
{
    Point_2d() = default;
    Point_2d(const T& x, const T& y)
        : x(x)
        , y(y)
    {}

    T x;
    T y;

protected:
    friend class monseri::Attorney; // give monseri access to serialize()

    // serialization as a protected method
    void serialize(monseri::Storage& storage)
    {
        storage | x | y;
    }
};

template <typename T>
struct Point_3d final : Point_2d<T>
{
    Point_3d() = default;
    Point_3d(const T& x, const T& y, const T& z)
        : Point_2d<T>(x, y)
        , z(z)
    {}

    T z;

private:
    friend class monseri::Attorney; // give monseri access to serialize()

    // serialization as a private method
    void serialize(monseri::Storage& storage)
    {
        Point_2d<T>::serialize(storage);
        storage | z;
    }
};

// we need to register types for serialization
// serialization is matching a string to each registered type

MONSERI_REGISTER_TYPE(Grid)            // same name as type
MONSERI_REGISTER_TYPE(Point_2d<float>) // same name as type, template class
MONSERI_REGISTER_TYPE(Point_3d<float>) // same name as type, template class
// arbitrary name can be specified too
MONSERI_REGISTER_TYPE_WITH_NAME(Point_3d<double>, "Point_3d_of_doubles")
MONSERI_REGISTER_TYPE(int) // built-in types can be registered too

namespace monseri
{
// serialization of a build-in type as a free function
inline void serialize(int& data, monseri::Storage& storage)
{
    storage | data;
}
} // namespace monseri

static std::string buffer;

//! Test serialization
void serialize()
{
    // prepare data
    const std::vector<monseri::Serializable> serializables = {
        Point_2d<float>{1.f, 2.f},
        Point_3d<float>(1.1f, 2.1f, 3.1f),
        Point_3d<double>(1.2, 2.2, 3.2),
        Grid{6, 9},
        int(42)};

    // serialize
    std::ostringstream storage;
    for(auto& s : serializables)
        storage << s;

    // print summary
    buffer = storage.str();
    std::cout << "Storage after serialization: \n";
    std::cout << "=============" << buffer << "\n=============\n";
}

//! Test deserialization
std::vector<monseri::Serializable> deserialize()
{
    std::istringstream storage(buffer);
    std::vector<monseri::Serializable> serializables;

    // deserialize
    while(true)
    {
        monseri::Serializable tmp;
        try
        {
            storage >> tmp;
        }
        catch(const std::runtime_error&)
        {
            break;
        }
        serializables.push_back(tmp);
    }

    // print summary
    std::cout << std::endl << "Deserialized data: \n=============";
    for(auto& s : serializables)
        std::cout << s;
    std::cout << "\n=============\n";

    return serializables;
}

//! Test getting data from serializable
void extract_data(const std::vector<monseri::Serializable>& serializables)
{
    // get data from serializable
    Point_3d<float> pt;
    if(monseri::registry::type_name<Point_3d<float> >() ==
       serializables[1].type_name())
    {
        pt = serializables[1].get<Point_3d<float> >();
    }

    // print results
    std::cout << "\nTesting Serilizable::get():\n"
              << "Point is: ";
    std::cout << "[x:" << pt.x << " y:" << pt.y << " z:" << pt.z << "]";
}

int main(int /*argc*/, char* /*argv*/ [])
{
    serialize();
    std::vector<monseri::Serializable> serializables = deserialize();
    extract_data(serializables);
#if defined(_MSC_VER)
    std::cin.get(); // freeze on Windows to observe output in console
#endif
}
