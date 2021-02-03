#include "box2d/b2_body.h"
#include "Hazel/Scene/Entity.h"
#include "Hazel/Scene/Components.h"

namespace Hazel {
	struct RigidBodyComponent {
		b2Body* body;
		Entity* entity;

		void PhysicsUpdate() { 
			auto& transform = entity->GetComponent<Hazel::TransformComponent>();
			transform.Translation.x = body->GetPosition().x; 
			transform.Translation.y = body->GetPosition().y;

			transform.Rotation.x = std::cos(body->GetAngle());
			transform.Rotation.y = std::sin(body->GetAngle());
		};
	};
}
