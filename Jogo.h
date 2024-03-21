#pragma once
#ifndef JOGO_H
#define JOGO_H

#include "Tela.h"

    class Jogo
    {
    private:
        Tela &tela;
        SDL_Renderer *rendererRef = nullptr;

    public:
        Jogo(Tela &tela_);

        void comecaJogo();
    };


#endif 