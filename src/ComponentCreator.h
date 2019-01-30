#pragma once
#include "MoveInput.h"
#include "Transform.h"
#include "Render.h" 
#include "LayerComponent.h"
#include "MapLoader.h"
#include "Camera.h"
#include "MapLoader.h"
#include "Collision.h"
#include "RigidBody.h"
#include "PhysicsManager.h"
#include "RoomManager.h"
#include "Animation.h"
#include "InteractionManager.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "InteractionManager.h"
#include "InteractiveCollision.h"
#include "TGUI/TGUI.hpp"
#include "AiComponent.h"

class ComponentCreator
{
public:
	void createTransform(GameObject& object, string name);
	void createRender(GameObject& object, string name, std::shared_ptr<GameObject> parent);
	void createRoomCollision(GameObject& object, string name, std::shared_ptr<GameObject> parent);
	void createInteractionCollision(GameObject& object, string name, std::shared_ptr<GameObject> parent, tgui::Gui& gui, bool& paused, string text);
	void createPlayerCollision(GameObject& object, string name, std::shared_ptr<GameObject> parent);
	void createObjectCollision(GameObject& object, string name, std::shared_ptr<GameObject> parent, bool isAnimation);
	void createAnimation(GameObject& object, string name, std::shared_ptr<GameObject> parent, bool canMove);
	void createMoveInput(GameObject& object, int playerIndex);
	void createAiComponent(GameObject& object);

};