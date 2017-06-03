#ifndef QTSOUNDPLAYER_H
#define QTSOUNDPLAYER_H

#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <vector>
#include <memory>

/**
    Singleton to implement the q sound player
*/

namespace game {
enum SoundType{SOUND_bullet, SOUND_Ship_Fire};

class QTSoundPlayer
{
public:
    static QTSoundPlayer* getInstance();
    void play(SoundType soundType);
    void playBgMusic();
    void pauseBgMusic();
    void setBgMusicVolumeLevel(int value);
    int getBgMusicVolumeLevel();
    ~QTSoundPlayer();
protected:
    QTSoundPlayer();
private:
    static QTSoundPlayer* qtSoundPlayerInstance;
    std::map<SoundType, QSoundEffect> sounds;
    QMediaPlaylist bgMusicPlayList;
    QMediaPlayer bgMusicPlayer;
    int bgMusicVolumeLevel;
};
}
#endif // QTSOUNDPLAYER_H
