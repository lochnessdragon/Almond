#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
{
	m_CameraController.SetZoomLevel(3.0f);
	m_Scene = Hazel::CreateRef<Hazel::Scene>();
	
	// set up main camera
	m_Camera = Hazel::CreateRef<Hazel::Entity>(m_Scene->CreateEntity("Main Camera"));
	auto& camera = m_Camera->AddComponent<Hazel::CameraComponent>();
	camera.Primary = true;
	m_Camera->AddComponent<Hazel::NativeScriptComponent>().Bind<AdvancedCameraController>();

	// set up player
	m_Player = Hazel::CreateRef<Hazel::Entity>(m_Scene->CreateEntity("Player"));
	m_Player->AddComponent<Hazel::SpriteRendererComponent>(m_SquareColor);
	m_Player->AddComponent<Hazel::NativeScriptComponent>().Bind<PlayerController>();
	m_Player->AddComponent<Hazel::RigidBodyComponent>();
}

void Sandbox2D::OnAttach()
{
	HZ_PROFILE_FUNCTION();

	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	HZ_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();

	// Resize
	if (Hazel::Application::Get().GetWindow().GetWidth() != m_ViewportSize.x || Hazel::Application::Get().GetWindow().GetHeight() != m_ViewportSize.y) {
		m_ViewportSize.x = (float)Hazel::Application::Get().GetWindow().GetWidth();
		m_ViewportSize.y = (float)Hazel::Application::Get().GetWindow().GetHeight();

		//m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
	}

	// Framerate tracker
	m_MillisPerFrame = ts.GetMilliseconds();


	// Render
	Hazel::Renderer2D::ResetStats();
	{
		HZ_PROFILE_SCOPE("Renderer Prep");
		Hazel::RenderCommand::SetClearColor({ 0.3f, 0.3f, 0.3f, 1 });
		Hazel::RenderCommand::Clear();
	}

	{
		HZ_PROFILE_SCOPE("Renderer Draw");
		
		Hazel::Renderer2D::BeginScene(m_Scene->GetPrimaryCameraEntity().GetComponent<Hazel::CameraComponent>().Camera, m_Scene->GetPrimaryCameraEntity().GetComponent<Hazel::TransformComponent>().GetTransform());
		//Hazel::Renderer2D::DrawQuad({ m_PlayerPosition.x, m_PlayerPosition.y }, { 0.5f, 0.75f }, m_SquareColor);
		//Hazel::Renderer2D::DrawQuad({ 0.0f, -0.625f }, { 100.0f, 0.5f }, { 0.7f, 0.0f, 0.3f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		//Hazel::Renderer2D::EndScene();

		//Hazel::Renderer2D::BeginScene(m_Scene->GetPrimaryCameraEntity().GetComponent<Hazel::CameraComponent>().Camera, m_Scene->GetPrimaryCameraEntity().GetComponent<Hazel::TransformComponent>().GetTransform());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Hazel::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Hazel::Renderer2D::EndScene();
		
		m_Scene->OnUpdateRuntime(ts);
	}

	// Now that there should be a script installed and updated, we can load it with references
	if (!m_EntitiesInstatiatedFired) {
		OnEntitiesInstatiated();
		m_EntitiesInstatiatedFired = true;
	}
}

void Sandbox2D::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();
#ifdef HZ_DEBUG
	if(ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Debug")) {
			
			if (ImGui::MenuItem("Show Stats")) {
				m_ShowStats = true;
			}

			if (ImGui::MenuItem("Show Controls")) {
				m_ShowControls = true;
			}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (m_ShowStats) {
		if (ImGui::Begin("Stats", &m_ShowStats)) {
			auto stats = Hazel::Renderer2D::GetStats();
			ImGui::Text("Renderer2D Stats:");
			ImGui::Text("Draw Calls: %d", stats.DrawCalls);
			ImGui::Text("Quads: %d", stats.QuadCount);
			ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
			ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
			ImGui::Text("Milliseconds per frame: %f(ms)", m_MillisPerFrame);

			ImGui::Text("Player Stats:");
			ImGui::Text("Position: (%f, %f)", m_Player->GetComponent<Hazel::TransformComponent>().Translation.x, m_Player->GetComponent<Hazel::TransformComponent>().Translation.y);
			ImGui::Text("Velocity: (%f, %f)", ((PlayerController*) m_Player->GetComponent<Hazel::NativeScriptComponent>().Instance)->velocity.x, ((PlayerController*)m_Player->GetComponent<Hazel::NativeScriptComponent>().Instance)->velocity.y);
		}
		
		ImGui::End();
	}

	if (m_ShowControls) {
		if (ImGui::Begin("Controls", &m_ShowControls)) {
			ImGui::ColorEdit4("Player Color", glm::value_ptr(m_Player->GetComponent<Hazel::SpriteRendererComponent>().Color));
			
			PlayerController* playerController = (PlayerController*) (m_Player->GetComponent<Hazel::NativeScriptComponent>().Instance);
			
			ImGui::SliderFloat("Player Speed", &playerController->speed, 0.0f, 100.0f);
			ImGui::SliderFloat("Gravity", &playerController->gravity, 0.0f, 100.0f);
			ImGui::SliderFloat("Jump Boost", &playerController->jumpPower, 0.0f, 100.0f);

			ImGui::Spacing();
			ImGui::SliderFloat("Friction Coeffecient", &playerController->frictionCoeffecient, 0.0f, 1.0f);
			ImGui::DragFloat("Max Horizontal Speed", &playerController->maxHorizontalVelocity, 0.5f, 0.0f, 100.0f);
			//ImGui::DragFloat3("Player Position", glm::value_ptr(m_Player.GetComponent<Hazel::TransformComponent>().Translation));
			ImGui::Checkbox("Run Physics?", &runPhysics);
		}

		ImGui::End();
	}

#endif
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);

	Hazel::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(Sandbox2D::OnKeyPressed));
}

bool Sandbox2D::OnKeyPressed(Hazel::KeyPressedEvent& e)
{
	return false;
}

void Sandbox2D::OnEntitiesInstatiated()
{
	AdvancedCameraController* cameraController = (AdvancedCameraController*) m_Camera->GetComponent<Hazel::NativeScriptComponent>().Instance;
	cameraController->SetPlayer(m_Player);
}
