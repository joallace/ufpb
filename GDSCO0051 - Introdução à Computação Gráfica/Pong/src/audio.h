#ifndef AUDIO_H
#define AUDIO_H
#define MINIAUDIO_IMPLEMENTATION
#include <string>
#include <stdio.h>
#include "miniaudio.h"

class Audio{
    private:
        char* files[5] = {"assets/music.mp3", "assets/goal.wav", "assets/hit.wav", "assets/menu.wav", "assets/wallHit.wav"};
        ma_sound sounds[5];
        ma_engine engine;
        ma_result result;

    public:
        Audio();
        ~Audio();

        void goal();
        void hit();
        void wallHit();
        void menu();
        void pause();
};

#endif
