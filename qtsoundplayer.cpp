#include "qtsoundplayer.h"

namespace game {
QTSoundPlayer* QTSoundPlayer::qtSoundPlayerInstance = 0;
QTSoundPlayer* QTSoundPlayer::getInstance(){
    if(!qtSoundPlayerInstance)
        qtSoundPlayerInstance = new QTSoundPlayer;
    return qtSoundPlayerInstance;
}

QTSoundPlayer::~QTSoundPlayer(){
    delete qtSoundPlayerInstance;
}

void QTSoundPlayer::play(SoundType soundType){
    sounds[soundType].play();
}

void QTSoundPlayer::playBgMusic(){
    bgMusicPlayer.play();
}

void QTSoundPlayer::pauseBgMusic(){
    bgMusicPlayer.pause();
}

int QTSoundPlayer::getBgMusicVolumeLevel(){
    return this->bgMusicVolumeLevel;
}

void QTSoundPlayer::setBgMusicVolumeLevel(int value){
    this->bgMusicVolumeLevel = value;
    bgMusicPlayer.setVolume(bgMusicVolumeLevel);

}

QTSoundPlayer::QTSoundPlayer()
{
    // initialise all the sound effects type
    sounds[SOUND_bullet].setSource(QUrl::fromLocalFile(":/Sounds/invader.wav"));
    sounds[SOUND_bullet].setVolume(0.3f);

    sounds[SOUND_Ship_Fire].setSource(QUrl::fromLocalFile(":/Sounds/shoot.wav"));
    sounds[SOUND_Ship_Fire].setVolume(0.3);

    // init background music
    // background music
    bgMusicPlayList.addMedia(QUrl("qrc:/Sounds/BackgroundMusic.mp3"));
    bgMusicPlayList.setPlaybackMode(QMediaPlaylist::Loop);

    // bg music player
    bgMusicPlayer.setPlaylist(&bgMusicPlayList);

    setBgMusicVolumeLevel(35); //default
}
}
