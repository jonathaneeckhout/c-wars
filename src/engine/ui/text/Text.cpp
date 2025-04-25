#include "engine/ui/text/Text.hpp"
#include "engine/core/Resources.hpp"
#include "engine/core/Renderer.hpp"

Text::Text(Vector position, const std::string &text) : UI(position), text(text)
{
    name = "Text";

    setFont("default", size);
}

Text::~Text()
{
    if (font != nullptr)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }
    if (surface != nullptr)
    {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

bool Text::setFont(const std::string &name, unsigned int size)
{

    auto fontResource = Resources::getInstance()->fonts.find(name);
    if (fontResource == Resources::getInstance()->fonts.end())
    {
        return false;
    }

    if (font != nullptr)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }

    if (surface != nullptr)
    {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }

    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    font = TTF_OpenFontRW(fontResource->second, 0, size);

    if (font == nullptr)
    {
        return false;
    }

    surface = TTF_RenderText_Solid(font, text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(Renderer::getInstance()->renderer, surface);

    return true;
}