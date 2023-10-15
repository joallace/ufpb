#ifndef AUDIO_H
#define AUDIO_H
#define MINIAUDIO_IMPLEMENTATION
#include <string>
#include <stdio.h>
#include "miniaudio.h"

class Audio{
    private:
        char* files[6] = {"assets/music.mp3", "assets/goal.wav", "assets/hit.wav", "assets/wallHit.wav", "assets/powerup.wav", "assets/kick.wav"};
        ma_sound sounds[6];
        ma_engine engine;
        ma_result result;

    public:
        Audio();
        ~Audio();

        void goal();
        void hit();
        void powerup();
        bool isPoweringUp();
        void kick();
        void wallHit();
        void pause();
};

#endif
