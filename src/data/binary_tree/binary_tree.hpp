#ifndef ESCAPE_DATA_BINARY_TREE_HPP
#define ESCAPE_DATA_BINARY_TREE_HPP

#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>
#include <limits>
#include <functional>
#include <unordered_set>

namespace esc::data {

template<typename Type>
class DefaultOrderer {
    inline int operator()(const Type& a, const Type & b) const noexcept {
        if (a < b) {
            return -1;
        }
        if (b < a) {
            return 1;
        }
        return 0;
    }
};

template<typename Type, typename Orderer = DefaultOrderer<Type>>
class BinaryTreeHeap {
public:
    static constexpr std::size_t npos = std::numeric_limits<std::size_t>::max();
    using SearchFunction = std::function<bool (const Type&)>;

    BinaryTreeHeap(): data() {
        data.reserve(50);
    }

    BinaryTreeHeap<Type, Orderer>& push(Type&& value) {
        if (data.size() == data.capacity()) {
            data.reserve(data.capacity() * 2);
        }
        data.push_back(value);
        bubbleUp(data.size() - 1);
        return *this;
    }

    Type pop(const std::size_t index) {
        const auto lastIndex = data.size() - 1;
        auto tmp = data.at(index);
        data.at(index) = data.at(lastIndex);
        data.at(lastIndex) = tmp;
        data.pop_back();
        bubbleDown(index);
        return tmp;
    }

    inline void bubbleDown(const std::size_t index) {
        auto& val = data.at(index);
        const auto leftChildIndex = index * 2;
        // left child index is out of scope, then right index is too (this node doesn't have children)
        if (leftChildIndex >= data.size()) {
            return;
        }
        auto& leftChild = data.at(leftChildIndex);
        const auto rightChildIndex = (index * 2) + 1;
        if (rightChildIndex >= data.size()) {
            // only left child exists
            if (orderer(val, leftChild) < 0) {
                std::swap(val, leftChild);
                // end here - if only left child exists, than it doesn't have any children itself.
            }
        } else {
            // right child exists - needs to get the bigger of those two
            auto& rightChild = data.at(rightChildIndex);
            // get the bigger value of the two children
            auto maxIndex = leftChildIndex;
            if (orderer(rightChild, leftChild) > 0) {
                maxIndex = rightChildIndex;
            }
            // Check if order is wrong
            if (orderer(val, data.at(maxIndex)) < 0) {
                std::swap(val, data.at(maxIndex));
                bubbleDown(maxIndex);
            }
        }
    }

    inline void bubbleUp(const std::size_t index) {
        if (index == 0) {
            return;
        }
        auto val = data.at(index);
        auto parentIndex = (index - 1) / 2;
        if (orderer(val, data.at(parentIndex)) > 0) {
            data.at(index) = data.at(parentIndex);
            data.at(parentIndex) = val;
            bubbleUp(parentIndex);
        }
    }

    
    inline Type& peak(const std::size_t index) { return data.at(index); }
    inline const Type& peakTop(const std::size_t index) const { return data.at(index); }
    inline Type& peakTop() { return peak(0); }
    inline const Type& peakTop() const { return peak(0); }

    std::size_t size() const noexcept { return data.size(); }

    inline std::size_t searchFromTopToBottomBFS(SearchFunction searchFunction) const noexcept {
        for (std::size_t i = 0; i < data.size(); ++i) {
            if (searchFunction(data.at(i))) {
                return i;
            }
        }
        return npos;
    }

    inline std::size_t searchFromBottomToTopBFS(SearchFunction searchFunction) const noexcept {
        for (std::size_t i = data.size() - 1; i != npos; --i) {
            if (searchFunction(data.at(i))) {
                return i;
            }
        }
        return npos;
    }

    inline std::size_t searchFromBottomToTopDFS(SearchFunction searchFunction) const noexcept {
        std::unordered_set<std::size_t> visited{};
        std::size_t startIndex = data.size() - 1;
        while (visited.size() != data.size()) {
            std::size_t index = startIndex;
            if (visited.contains(index)) {
                return npos;
            }
            while(true) {
                if (searchFunction(data.at(index))) {
                    return index;
                }
                visited.emplace(index);
                if (index == 0) {
                    break;
                }
                index /= 2;
                if (visited.contains(index)) {
                    break;
                }            
            }
            --startIndex;
        }
        return npos;
    }

protected:
    static Orderer orderer{};
    std::vector<Type> data;
};
}

#endif//ESCAPE_DATA_BINARY_TREE_HPP