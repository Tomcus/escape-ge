#ifndef ESCAPE_RENDER_DATA_ENTITY_HPP
#define ESCAPE_RENDER_DATA_ENTITY_HPP

#include "base.hpp"

namespace esc::render {

template<typename EntityData>
class EntityRenderer : public BaseDataTypeRenderer<EntityData> {
};

}

#endif//ESCAPE_RENDER_DATA_ENTITY_HPP