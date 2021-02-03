#include "LogoLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

LogoLayer::LogoLayer() : Layer("Logo Layer"), m_CameraController(1280.0f / 720.0f)
{
	m_State = START;
}

void LogoLayer::OnAttach()
{
	HZ_PROFILE_FUNCTION();

	m_HazelLogo = Hazel::Texture2D::Create("assets/textures/hazel_logo.png");
}

void LogoLayer::OnDetach()
{
	HZ_PROFILE_FUNCTION();
}

void LogoLayer::OnUpdate(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();
	// Resize
	if (Hazel::Application::Get().GetWindow().GetWidth() != m_ViewportSize.x || Hazel::Application::Get().GetWindow().GetHeight() != m_ViewportSize.y) {
		m_ViewportSize.x = (float)Hazel::Application::Get().GetWindow().GetWidth();
		m_ViewportSize.y = (float)Hazel::Application::Get().GetWindow().GetHeight();

		m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
	}

	// Update
	m_CameraController.OnUpdate(ts);

	float sizeStride = 0.0f;

	// Splash Screen Animation
	switch (m_State) {
	case START:
		m_State = HZ_LOGO_START;
		break;
	case HZ_LOGO_START:
		m_HZLogoTransparency += m_HZLogoFadeSpeed * ts.GetSeconds();
		sizeStride = (m_HZLogoStaySize - m_HZLogoStartSize) * m_HZLogoFadeSpeed * ts.GetSeconds();
		m_HZLogoSize.x += sizeStride;
		m_HZLogoSize.y += sizeStride;

		if (m_HZLogoTransparency > 1.0f) {
			m_State = HZ_LOGO_DISPLAY;
			timer1 = m_HZLogoOnScreenTime;
			m_HZLogoTransparency = 1.0f;
		}
		break;
	case HZ_LOGO_DISPLAY:
		timer1 -= ts.GetSeconds();

		if (timer1 < 0.0f) {
			m_State = HZ_LOGO_END;
		}

		break;
	case HZ_LOGO_END:
		m_HZLogoTransparency -= m_HZLogoFadeSpeed * ts.GetSeconds();
		sizeStride = (m_HZLogoEndSize - m_HZLogoStaySize) * m_HZLogoFadeSpeed * ts.GetSeconds();
		m_HZLogoSize.x += sizeStride;
		m_HZLogoSize.y += sizeStride;

		if (m_HZLogoTransparency < 0.0f) {
			m_State = END;
			m_HZLogoTransparency = 0.0f;
		}
		break;
	case END:
		//Hazel::Application::Get().PushLayer(new Sandbox2D());
		break;
	default:
		break;
	}

	// Render
	Hazel::Renderer2D::ResetStats();
	{
		HZ_PROFILE_SCOPE("Renderer Prep");
		Hazel::RenderCommand::SetClearColor({ 1.0f, 1.0f, 1.0f, 1 });
		Hazel::RenderCommand::Clear();
	}

	{

		HZ_PROFILE_SCOPE("Renderer Draw");
		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f }, m_HZLogoSize, m_HazelLogo, 1.0f, {1.0f, 1.0f, 1.0f, m_HZLogoTransparency});
		Hazel::Renderer2D::EndScene();
	}
}

void LogoLayer::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();
#ifdef HZ_DEBUG
	ImGui::Begin("Splash Screen Settings");
	//ImGui::SliderFloat("Hazel Logo Tranparency", &m_HZLogoTransparency, 0.0f, 1.0f);
	ImGui::SliderFloat("Hazel Logo Fade Speed", &m_HZLogoFadeSpeed, 0.0f, 20.0f);
	ImGui::DragFloat("Hazel Logo On Screen Time", &m_HZLogoOnScreenTime, 1.0f, 0.0f, 100.0f);
	ImGui::DragFloat("Hazel Logo Start Size", &m_HZLogoStartSize, 1.0f, 0.0f, 100.0f);
	ImGui::DragFloat("Hazel Logo Stay Size", &m_HZLogoStaySize, 1.0f, 0.0f, 100.0f);
	ImGui::DragFloat("Hazel Logo End Size", &m_HZLogoEndSize, 1.0f, 0.0f, 100.0f);
	
	if (ImGui::Button("Animate Splash Screen")) {
		m_State = START;
		m_HZLogoTransparency = 0.0f;
		m_HZLogoSize.x = 2.0f;
		m_HZLogoSize.y = 2.0f;
		m_HZLogoSize.x = m_HZLogoStartSize;
		m_HZLogoSize.y = m_HZLogoStartSize;
	}

	ImGui::End();
#endif
}

void LogoLayer::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}
