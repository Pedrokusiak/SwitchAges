#pragma once
#include <SDL.h>
#include <iostream>
#include <string_view>
#include "RenderizadorPorta.h"
#include "RenderizadorDTO.h"


    class SDLRenderizadorAdaptador : public RenderizadorPorta
    {
    private:
        SDL_Renderer *renderer;
        Uint8 vermelhoColor = 0;
        Uint8 verdeColor = 0;
        Uint8 azulColor = 0;
        Uint8 alphaColor = 0;

        void setRGBAColors(std::string_view hexColor);

    public:
        SDLRenderizadorAdaptador(SDL_Renderer *sdlRenderer) : renderer(sdlRenderer) {}

        virtual void renderizarElemento(const RenderizadorDTO &renderizadorDTO) override;
    };
