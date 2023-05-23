#include "../../include/utils/AudioService.h"
#include <iostream>

AudioService::AudioService() {
        m_soundBuffers["potionPickup"] = sf::SoundBuffer();
        m_soundBuffers["fireShot"] = sf::SoundBuffer();
        m_soundBuffers["playerHitting"] = sf::SoundBuffer();

        if (!m_soundBuffers["potionPickup"].loadFromFile("../audio/potionPickup.wav"))
        {
            std::cerr << "Failed to load potionPickup.wav" << std::endl;
        }

        if (!m_soundBuffers["fireShot"].loadFromFile("../audio/fireShot.wav"))
        {
            std::cerr << "Failed to load fireShot.wav" << std::endl;
        }

        if (!m_soundBuffers["playerHitting"].loadFromFile("../audio/playerHitting.wav"))
        {
            std::cerr << "Failed to load playerHitting.wav" << std::endl;
        }
}

void AudioService::playSound(const std::string& soundName) {
    std::cout << "Starting to play sounds";
    auto it = m_soundBuffers.find(soundName);
    if (it == m_soundBuffers.end()) {
        throw std::exception("Sound not found!");
        return;
    }

    m_sound.setBuffer(it->second);
    m_sound.play();
}
