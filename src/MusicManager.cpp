#include "stdafx.h"
#include "MusicManager.h"

MusicManager & MusicManager::getInstance()
{
	static MusicManager m_Instance;
	return m_Instance;
}

void MusicManager::loadSong(std::string path)
{
	m_CurrentSong.openFromFile(path);
	m_CurrentSong.setLoop(true);
	MusicManager::getInstance().playCurrentSong();
}

void MusicManager::playCurrentSong()
{
	m_CurrentSong.play();
}

void MusicManager::stopPlaying()
{
	m_CurrentSong.stop();
}

void MusicManager::changeRoomSong(int roomId, bool battle)
{
	if (battle)
	{
		MusicManager::loadSong("../assets/music/Battle.wav");
		lastPlayedRoomId = 1;
	}
	else
	{
		if (roomId < 4 && lastPlayedRoomId > 3 || lastPlayedRoomId == 0) MusicManager::loadSong("../assets/music/Dark Woods.wav");
		else if (roomId > 3 && lastPlayedRoomId < 4) MusicManager::loadSong("../assets/music/Overworld.wav");
		lastPlayedRoomId = roomId;
	}
}

