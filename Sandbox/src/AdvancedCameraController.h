#pragma once
#include "Hazel.h"

class AdvancedCameraController :
	public Hazel::ScriptableEntity
{
public:
	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void OnUpdate(Hazel::Timestep ts) override;

	void SetPlayer(Hazel::Ref<Hazel::Entity> player);

private:
	Hazel::Ref<Hazel::Entity> m_Player;
};

