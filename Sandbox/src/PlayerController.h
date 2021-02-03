#include "Hazel.h"

class PlayerController : public Hazel::ScriptableEntity {
public:
	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void OnUpdate(Hazel::Timestep ts) override;

public:
	float speed = 2.0f;
	float jumpPower = 8.0f;
	float maxHorizontalVelocity = 4.0f;
};
