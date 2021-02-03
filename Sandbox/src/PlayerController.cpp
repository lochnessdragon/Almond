#include "PlayerController.h"

void PlayerController::OnCreate()
{
	auto& translation = GetComponent<Hazel::TransformComponent>().Translation;
	translation = glm::vec3{0.0f, 0.0f, 0.01f};
}

void PlayerController::OnDestroy()
{
}

void PlayerController::OnUpdate(Hazel::Timestep ts)
{
	auto& translation = GetComponent<Hazel::TransformComponent>().Translation;
	auto& rigidbody = GetComponent<Hazel::RigidBodyComponent>();
	
	auto velocity = rigidbody.body->GetLinearVelocity();

	// get input functions
	if (Hazel::Input::IsKeyPressed(Hazel::Key::Space) && translation.y <= 0.0f) {
		velocity.y += jumpPower;
	}

	bool moved = false;
	if (Hazel::Input::IsKeyPressed(Hazel::Key::A)) {
		velocity.x -= speed * ts.GetSeconds();
		moved = true;
	}

	if (Hazel::Input::IsKeyPressed(Hazel::Key::D)) {
		velocity.x += speed * ts.GetSeconds();
		moved = true;
	}

	// cap x velocity
	velocity.x = std::min(velocity.x, maxHorizontalVelocity);
	velocity.x = std::max(velocity.x, -maxHorizontalVelocity);

	if (translation.y < 0.0f) {
		translation.y = 0.0f;
	}
}
