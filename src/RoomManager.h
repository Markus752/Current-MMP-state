#pragma once
#include <vector>
#include "GameObject.h"
#include "RoomTriggerCollision.h"

class RoomManager
{

public:
	static RoomManager& getInstance();
	void addObserver(std::shared_ptr<GameObject> observer);
	void removeObserver(std::shared_ptr<GameObject> observer);
	void notifyObserver(std::shared_ptr<GameObject> object, std::shared_ptr<GameObject> objectToChange);
	void resetAllColliderTrigger();

	std::vector<std::shared_ptr<GameObject>>& getScoreObserver();
private:
	RoomManager(void) = default;
	~RoomManager(void) = default;
	RoomManager(const RoomManager& p) = delete;
	RoomManager& operator=(RoomManager const&) = delete;

	std::vector<std::shared_ptr<GameObject>> m_RoomObservers;
};