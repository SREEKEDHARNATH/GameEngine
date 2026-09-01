#include "Sound.h"
#include "soloud.h"
#include "soloud_wav.h"
#include <algorithm>
#include <iostream>

namespace Sound {
    SoLoud::Soloud SoundSystem::system;
    void SoundSystem::init(){
        system.init();
    }

    void SoundSystem::destroy(){
        system.deinit();
    }

    void Sound::create(const char* path, bool ismusic, bool doesLoop){
        SoLoud::result res;
        if (ismusic){
            res = wavStreamSound.load(path);
        }
        else{
            res = wavSound.load(path);
        }
        if (res != SoLoud::SO_NO_ERROR) {
            std::cout << "Error loading sound\n";
            return;
        }
        filePath=path;
        isMusic=ismusic;

        if (ismusic){
            wavStreamSound.setLooping(doesLoop);
        }
        else{
            wavSound.setLooping(doesLoop);
        }

    }
    void Sound::play(){
        if (!SoundSystem::system.isValidVoiceHandle(handle)) {
            if (isMusic){
                handle = SoundSystem::system.play(wavStreamSound);
            }
            else {
                handle = SoundSystem::system.play(wavSound);
            }
        }

    }
    void Sound::stop(){
        if (SoundSystem::system.isValidVoiceHandle(handle)) {
            SoundSystem::system.stop(handle);
            handle = 0;
        }
    }
    void Sound::setVolume(float vol){
        vol = std::clamp(vol, 0.0f, 1.0f);

        if (isMusic){
            wavStreamSound.setVolume(vol);
        }
        else {
            wavSound.setVolume(vol);
        }

        if (SoundSystem::system.isValidVoiceHandle(handle)) {
            SoundSystem::system.setVolume(handle, vol);
        }
    }
    bool Sound::isPlaying() const {
        return SoundSystem::system.isValidVoiceHandle(handle);
    }


}
