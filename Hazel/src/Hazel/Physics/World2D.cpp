#include "hzpch.h"
#include "World2D.h"

namespace Hazel {
	World2D::World2D(b2Vec2 gravity) : m_World(gravity)
	{
		m_Gravity = gravity;

		// Ground
		/*
		m_GroundDef.position.Set(0.0f, -10.0f);
		m_Ground = m_World.CreateBody(&m_GroundDef);

		m_GroundBox.SetAsBox(50.0f, 10.0f);
		m_Ground->CreateFixture(&m_GroundBox, 0.0f);

		// Cube
		m_CubeDef.type = b2_dynamicBody;
		m_CubeDef.position.Set(0.0f, 4.0f);
		m_Cube = m_World.CreateBody(&m_CubeDef);

		m_CubeBox.SetAsBox(1.0f, 1.0f);

		m_CubeFixtureDef.shape = &m_CubeBox;
		m_CubeFixtureDef.density = 1.0f;
		m_CubeFixtureDef.friction = 0.3f;
		

		m_Cube->CreateFixture(&m_CubeFixtureDef);
		*/
	}

	World2D::~World2D()
	{
	}

	void World2D::OnUpdate(Timestep ts)
	{
		m_World.Step(ts.GetSeconds(), VELOCITY_ITERATIONS, POSITION_ITERATIONS);
		/*b2Vec2 position = m_Cube->GetPosition();
		float angle = m_Cube->GetAngle();
		#ifdef HZ_DEBUG
			HZ_CORE_TRACE("{} {} {}", position.x, position.y, angle);
		#endif*/
	}

	b2Body* World2D::GetDefaultBody()
	{
		b2BodyDef defaultBodyDef;
		defaultBodyDef.type = b2_dynamicBody;
		defaultBodyDef.position.Set(0.0f, 4.0f);
		b2Body* defaultBody = m_World.CreateBody(&defaultBodyDef);

		b2PolygonShape defaultBodyBox;
		defaultBodyBox.SetAsBox(1.0f, 1.0f);

		b2FixtureDef defaultBodyFixtureDef;
		defaultBodyFixtureDef.shape = &defaultBodyBox;
		defaultBodyFixtureDef.density = 1.0f;
		defaultBodyFixtureDef.friction = 0.3f;


		defaultBody->CreateFixture(&defaultBodyFixtureDef);

		return defaultBody;
	}

}
