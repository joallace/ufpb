#include "audio.h"

Audio::Audio(){
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS)
        printf("Failed to initialize audio engine.");

    for (int i = 0; i < 5; i++) {
        result = ma_sound_init_from_file(&engine, files[i], MA_SOUND_FLAG_DECODE, NULL, NULL, &sounds[i]);

        if (result != MA_SUCCESS)
            printf("Failed to open %s", files[i]);
    }

    ma_sound_set_looping(&sounds[0], true);
    ma_sound_start(&sounds[0]);
}

Audio::~Audio(){
    ma_engine_uninit(&engine);
}

void Audio::goal(){
    ma_sound_start(&sounds[1]);
}

void Audio::hit(){
    ma_sound_start(&sounds[2]);
}

void Audio::wallHit(){
    ma_sound_start(&sounds[4]);
}

void Audio::menu(){
    ma_sound_start(&sounds[3]);
}