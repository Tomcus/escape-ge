#ifndef ESCAPE_DATA_BASE_HPP
#define ESCAPE_DATA_BASE_HPP

#include <cstddef>
#include <cstdint>
#include <functional>
#include <vector>
#include <compare>

namespace esc::data {

namespace impl {

struct PointerRange {
    std::uintptr_t min, max;
    std::size_t distance() const noexcept {
        return max - min;
    }
};

class MemoryManager {
public:
    MemoryManager(std::function<std::size_t(std::size_t)> resizeStrategy);
    template <typename Type>
    Type* getMemory();
    template <typename Type>
    void freeMemory(const Type *);
protected:
};
}

class Base {

};

}

#endif//ESCAPE_DATA_BASE_HPP