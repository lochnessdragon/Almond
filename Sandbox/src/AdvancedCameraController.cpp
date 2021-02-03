#include "AdvancedCameraController.h"

void AdvancedCameraController::OnCreate()
{
	
}

void AdvancedCameraController::OnDestroy()
{
}

void AdvancedCameraController::OnUpdate(Hazel::Timestep ts)
{
	auto& translation = GetComponent<Hazel::TransformComponent>().Translation;
	if (m_Player != nullptr) {
		translation.x = m_Player->GetComponent<Hazel::TransformComponent>().Translation.x;
		translation.y = m_Player->GetComponent<Hazel::TransformComponent>().Translation.y;
	}
}

void AdvancedCameraController::SetPlayer(Hazel::Ref<Hazel::Entity> player)
{
	this->m_Player = player;
}
