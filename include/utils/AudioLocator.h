class AudioManager;
class NullService;

class AudioLocator {
public:

    static AudioManager& getAudioManager();

    static void provide(AudioManager* audioManager);

private:
    static AudioManager* service;
    static NullService nullService;
};
