#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"

namespace Sound {
    class SoundSystem {
        private:
        public:
            static SoLoud::Soloud system;
            static void init();
            static void destroy();

    };
    class Sound{
        private:
            const char* filePath;
            SoLoud::Wav wavSound;
            SoLoud::WavStream wavStreamSound;
            SoLoud::handle handle;
            bool isMusic;

        public:
            void create(const char* path, bool isMusic, bool doesLoop);
            void play();
            void stop();
            void setVolume(float vol);
            bool isPlaying() const;

    };


}
