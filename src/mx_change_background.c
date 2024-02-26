#include "../inc/header.h"

SDL_Texture *mx_change_background(const char* imagePath, SDL_Renderer **renderer) {
    // Загрузка изображения
    SDL_Surface* backgroundSurface = IMG_Load(imagePath);
    if (backgroundSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", imagePath, IMG_GetError());
        return NULL;
    }

    // Создание текстуры из загруженного изображения
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(*renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (backgroundTexture == NULL) {
        printf("Unable to create texture from %s! SDL Error: %s\n", imagePath, SDL_GetError());
        return NULL;
    }

    // Очистка рендера и отображение новой текстуры
    /*SDL_RenderClear(*renderer);
    SDL_RenderCopy(*renderer, backgroundTexture, NULL, NULL);
    SDL_RenderPresent(*renderer);*/
    return backgroundTexture;
}

