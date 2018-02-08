# monseri
**M**inimalistic take **ON** **SERI**alization in C++ using type-erasure

- Monseri is a tiny, header-only, prove-of-concept C++ serialization library

- It uses type-erasure, for a serializable object and storage classes

- Not intrusive: no inheritance is needed. Serialization could be performed via a method or a free function

- License: MIT

## Complete and simple example

```c++
#include <iostream_storage/shift_operators.h>
#include <registration_macros.h>

#include <iostream>

struct Grid2d
{
    int size_x;
    int size_y;

    // serialization via method
    void serialize(monseri::Storage& storage)
    {
        storage | size_x | size_y;
    }
};

int main()
{
    std::string buffer;
    { // serialize
        std::ostringstream storage;
        storage << monseri::Serializable{Grid2d{42, 42}};
        buffer = storage.str();
        std::cout << buffer;
    }

    monseri::Serializable tmp;
    { // deserialize
        std::istringstream storage(buffer);
        storage >> tmp;
        std::cout << tmp << std::endl;
    }

    Grid2d data;
    { // get data
        if(monseri::registry::type_name<Grid2d>() == tmp.type_name())
            data = tmp.get<Grid2d>();
        std::cout << "[" << data.size_x << ", " << data.size_y << "]";
    }
}
```

## Example of using with a built-in type: free-function serialization
```c++
MONSERI_REGISTER_TYPE(int) // built-in types can be registered too

namespace monseri
{
  // serialization of a build-in type as a free function
  inline void serialize(int& data, monseri::Storage& storage)
  {
      storage | data;
  }
} // namespace monseri
```

## Private serialization method example
```c++
struct Grid2d
{
    int size_x;
    int size_y;
private:
    friend class monseri::Attorney; // give monseri access to serialize()
    // serialization via method
    void serialize(monseri::Storage& storage)
    {
        storage | size_x | size_y;
    }
};
```

For more examples see provided `example.cpp`