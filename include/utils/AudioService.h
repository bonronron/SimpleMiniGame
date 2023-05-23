#include <string>
#include <unordered_map>
#include <SFML/Audio.hpp>


class AudioManager {
public:
    virtual void playSound(const std::string& soundName) = 0;
};

class NullService : public AudioManager{
public:
    virtual void playSound(const std::string& soundName) override { };
};


class AudioService : public AudioManager {
public:
    AudioService();
    virtual void playSound(const std::string& soundName) override;

private:
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
    sf::Sound m_sound;
};
