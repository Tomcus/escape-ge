#ifndef ESCAPE_RENDER_DATA_BASE_HPP
#define ESCAPE_RENDER_DATA_BASE_HPP

#include "error/error.hpp"
#include <raylib.h>

namespace esc::render {

/**
 * @brief Abstract class for any renderer, that render some basic data type
 * 
 * @tparam DataType Base Data type that is renderered.
 */
template<typename DataType>
class BaseDataTypeRenderer {
public:
    /// Basic constructor that assigns reference to the data
    explicit BaseDataTypeRenderer(const DataType& refData): data(refData) { }
    
    /// Deleted copy constructor, to force moving
    BaseDataTypeRenderer(const BaseDataTypeRenderer<DataType> &) = delete;
    /// Defaulted move constructor
    BaseDataTypeRenderer(BaseDataTypeRenderer<DataType> &&) = default;

    /// Deleted copy operator=, to force moving
    BaseDataTypeRenderer<DataType> operator=(const BaseDataTypeRenderer<DataType> &) = delete;
    /// Defaulted move operator=
    BaseDataTypeRenderer<DataType> operator=(BaseDataTypeRenderer<DataType> &&) = default;

    /// Virtual destructo to prevent memory leaks in inherited instances
    virtual ~BaseDataTypeRenderer() {}

    /// Virtual not implemented render function that needs to be implemented by other renderers
    virtual Error render(const Vector2& at) const noexcept = 0;
protected:
    /// Stored reference to rendered data.
    const DataType& data;
};

}

#endif//ESCAPE_RENDER_DATA_BASE_HPP