#include "entities/resources/Metal.h"

Metal::Metal(std::string id, Map *map, Vector position) : Resource(id, map, position)
{
    name = "Metal";

    color = {128, 128, 128, 255};
}

Metal::~Metal()
{
}