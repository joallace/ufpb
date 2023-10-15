#include "audio.h"

Audio::Audio(){
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS)
        printf("Failed to initialize audio engine.");

    for (int i = 0; i < 6; i++) {
        result = ma_sound_init_from_file(&engine, files[i], MA_SOUND_FLAG_DECODE, NULL, NULL, &sounds[i]);

        if (result != MA_SUCCESS)
            printf("Failed to open %s", files[i]);
    }

    ma_sound_set_volume(&sounds[0], 0.35f);
    ma_sound_set_looping(&sounds[0], true);
    ma_sound_start(&sounds[0]);
}

Audio::~Audio(){
    ma_engine_uninit(&engine);
    for (int i = 0; i < 5; i++)
        ma_sound_uninit(&sounds[i]);
}

void Audio::goal(){
    ma_sound_start(&sounds[1]);
}

void Audio::hit(){
    ma_sound_start(&sounds[2]);
}

void Audio::wallHit(){
    ma_sound_start(&sounds[3]);
}

void Audio::powerup(){
    // ma_sound_set_start_time_in_pcm_frames(&sounds[4], ma_engine_get_time_in_pcm_frames(&engine) + (ma_engine_get_sample_rate(&engine) * 1));
    ma_sound_seek_to_pcm_frame(&sounds[4], 0);
    ma_sound_start(&sounds[4]);
}

void Audio::kick(){
    ma_sound_stop(&sounds[4]);
    ma_sound_start(&sounds[5]);
}

void Audio::pause(){
    if(ma_sound_is_playing(&sounds[0]))
        ma_sound_stop(&sounds[0]);
    else
        ma_sound_start(&sounds[0]);
}

bool Audio::isPoweringUp(){
    return ma_sound_is_playing(&sounds[4]);
}