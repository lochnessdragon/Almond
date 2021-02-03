#pragma once

#include "Hazel.h"
#include "AdvancedCameraController.h"
#include "PlayerController.h"
#include "box2d/b2_common.h"
#include "box2d/b2_collision.h"

class Sandbox2D : public Hazel::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hazel::Event& e) override;
private:
	bool OnKeyPressed(Hazel::KeyPressedEvent& e);
	void OnEntitiesInstatiated();

private:
	Hazel::OrthographicCameraController m_CameraController;

	Hazel::Ref<Hazel::Texture2D> m_CheckerboardTexture;

	// Viewport Size
	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

	// Player Settings
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	//glm::vec2 m_PlayerPosition = { 0.0f, 0.0f };
	//glm::vec2 m_PlayerVelocity = { 0.0f, 0.0f };
	//float m_PlayerSpeed = 1.0f;
	//float m_Gravity = 9.81f;
	//float m_JumpBoost = 10.0f;

	// Framerate counter
	float m_MillisPerFrame = 0.0f;

	// Scene
	Hazel::Ref<Hazel::Scene> m_Scene;

	// Camera Entity
	Hazel::Ref<Hazel::Entity> m_Camera;

	// Player Entity
	Hazel::Ref<Hazel::Entity> m_Player;

	bool m_EntitiesInstatiatedFired = false;

	// Gui Globals
#ifdef HZ_DEBUG
	bool m_ShowStats = true;
	bool m_ShowControls = true;
#endif

	// Physics (Box2d)
	bool runPhysics = false;
};
