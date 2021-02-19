#pragma once

#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#endif

#include <string>
#include "display.hpp"

namespace Reversi
{
    SDL_Renderer *g_renderer = nullptr;

    class image_texture
    {
    public:
        image_texture(/* args */);
        ~image_texture();
        void free();
        bool load_image(const std::string &path);
        void render(int x, int y, SDL_Rect *clip);

    private:
        SDL_Texture *m_texture;
        int m_width;
        int m_height;
    };

    image_texture::image_texture() : m_texture(nullptr), m_width(0), m_height(0)
    {
    }

    image_texture::~image_texture()
    {
        free();
    }

    bool image_texture::load_image(const std::string &path)
    {
        free();
        SDL_Texture *new_texture = nullptr;
        SDL_Surface *load = IMG_Load(path.c_str());

        SDL_SetColorKey(load, SDL_TRUE, SDL_MapRGB(load->format, 0, 0xff, 0xff));

        new_texture = SDL_CreateTextureFromSurface(g_renderer, load);

        m_width = load->w;
        m_height = load->h;

        SDL_FreeSurface(load);

        m_texture = new_texture;
        return m_texture != nullptr;
    }

    void image_texture::render(int x, int y, SDL_Rect *clip)
    {
        SDL_Rect renderQuad = {x, y, m_width, m_height};

        //Set clip rendering dimensions
        if (clip != NULL)
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        //Render to screen
        SDL_RenderCopy(g_renderer, m_texture, clip, &renderQuad);
    }

    void image_texture::free(void)
    {
        if (m_texture != nullptr)
        {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
    }
} // namespace Reversi