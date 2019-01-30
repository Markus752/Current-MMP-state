#pragma once
#include "SFML/Audio.hpp"
#include "IMainStates.h"

class MusicManager
{

public:
	static MusicManager& getInstance();

	void loadSong(std::string path);
	void playCurrentSong();
	void stopPlaying();
	void changeRoomSong(int roomId, bool battle);

private:
	MusicManager(void) = default;
	~MusicManager(void) = default;
	MusicManager(const MusicManager& p) = delete;
	MusicManager& operator=(MusicManager const&) = delete;

	sf::Music m_CurrentSong;
	int lastPlayedRoomId = 0;
};
