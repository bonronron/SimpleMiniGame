#include "../../include/utils/AudioLocator.h"
#include "../../include/utils/AudioService.h"


NullService AudioLocator::nullService{ NullService() };
AudioManager* AudioLocator::service{ &nullService };

AudioManager& AudioLocator::getAudioManager() {
    return *service;
}

void AudioLocator::provide(AudioManager* audioManager) {
    if (!audioManager) service = &nullService;
    service = audioManager;
}
