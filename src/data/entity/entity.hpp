#ifndef ESCAPE_DATA_ENTITY_HPP
#define ESCAPE_DATA_ENTITY_HPP

#include <limits>

#include "ray.hpp"

#define RANGED_VALUE(type, name)\
type name;\
const type name ## Min, name ## Max

namespace esc::data {

class Entity {
public:
    Entity(Vector2 initPosition);
protected:
    Vector2 position;
    RANGED_VALUE(float, health);
};

}

#endif//ESCAPE_DATA_ENTITY_HPP