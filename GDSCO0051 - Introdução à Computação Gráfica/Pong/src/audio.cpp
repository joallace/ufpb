#include "audio.h"

Audio::Audio(){
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS)
        printf("Failed to initialize audio engine.");
}

Audio::~Audio(){
    ma_engine_uninit(&engine);
}

void Audio::goal(){
    ma_engine_play_sound(&engine, files[0], NULL);
}

void Audio::hit(){
    ma_engine_play_sound(&engine, files[1], NULL);
}

void Audio::wallHit(){
    ma_engine_play_sound(&engine, files[3], NULL);
}

void Audio::menu(){
    ma_engine_play_sound(&engine, files[2], NULL);
}