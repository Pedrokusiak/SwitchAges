#ifndef TELA_H
#define TELA_H

#include <SDL.h>

class Tela {
    private:
        SDL_Window *ponteiroJanela = nullptr;
        int tamanho;
        int largura;
    public:
        Tela(int tamanho, int largura);
        void criarJanela();
        SDL_Window* getPonteiroJanela();
}

#endif 