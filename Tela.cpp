#include "Tela.h"

#include <iostream>

Tela::Tela(int tamanho, int largura)
{
    this->tamanho = tamanho;
    this->largura = largura;
}

void Tela::criarJanela() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Ocorreu um erro!");
    }

    this->ponteiroJanela = SDL_CreateWindow(
        "Moving Square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->largura, this->tamanho, SDL_WINDOW_SHOWN
    );
    if (this->windowRef == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::runtime_error("Ocorreu um erro!");
    }
}

SDL_Window* Tela::getJanela() {
    return this->ponteiroJanela;
}
