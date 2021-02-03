#pragma once

#include "Hazel.h"

class LogoLayer : public Hazel::Layer {
public:
	LogoLayer();
	virtual ~LogoLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hazel::Event & e) override;
private:
	// viewport
	Hazel::OrthographicCameraController m_CameraController;
	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

	// state
	enum AnimationState {
		START,
		HZ_LOGO_START,
		HZ_LOGO_DISPLAY,
		HZ_LOGO_END,
		END
	};

	AnimationState m_State;

	// miscellaneous timers
	float timer1 = 0.0f;

	// hazel logo
	Hazel::Ref<Hazel::Texture2D> m_HazelLogo;
	float m_HZLogoTransparency = 0.0f;
	float m_HZLogoFadeSpeed = 0.25f;
	float m_HZLogoOnScreenTime = 1.0f;
	float m_HZLogoStartSize = 1.0f;
	float m_HZLogoStaySize = 2.0f;
	float m_HZLogoEndSize = 3.0f;
	glm::vec2 m_HZLogoSize = { m_HZLogoStartSize, m_HZLogoStartSize };
};
