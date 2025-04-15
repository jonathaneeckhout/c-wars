#include "entities/resources/Metal.h"

Metal::Metal(std::string id, Vector position) : Resource(id, position)
{
    name = "Metal";

    color = {128, 128, 128, 255};
}

Metal::~Metal()
{
}