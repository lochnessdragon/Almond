#pragma once

#include "Hazel/Core/Timestep.h"

#ifdef HZ_DEBUG
#include "Hazel/Core/Log.h" // For testing purposes
#endif

#include "box2d/b2_common.h"
#include "box2d/b2_collision.h"
#include "box2d/b2_body.h"
#include "box2d/b2_world.h"
#include "box2d//b2_polygon_shape.h"
#include "box2d//b2_fixture.h"

#ifndef HZ_DEFAULT_GRAVITY
#define HZ_DEFAULT_GRAVITY -9.81f
#endif

#ifndef HZ_VITERATIONS
#define HZ_VITERATIONS 8
#endif

#ifndef HZ_PITERATIONS
#define HZ_PITERATIONS 3
#endif

namespace Hazel {
	class World2D
	{
	public:
		World2D(b2Vec2 gravity = b2Vec2{0.0f, HZ_DEFAULT_GRAVITY});
		~World2D();

		void OnUpdate(Timestep ts);
		b2World& GetWorld() { return m_World;  };
		b2Body* GetDefaultBody();

	private:
		// box 2d gravity and world
		b2Vec2 m_Gravity;
		b2World m_World;

		/*
		// Ground
		b2BodyDef m_GroundDef;
		b2PolygonShape m_GroundBox;
		b2Body* m_Ground;

		// cube
		b2BodyDef m_CubeDef;
		b2FixtureDef m_CubeFixtureDef;
		b2PolygonShape m_CubeBox;
		b2Body* m_Cube;
		*/

		// Velocity interations and position iterations. Tune to your liking.
		const static int32 VELOCITY_ITERATIONS = HZ_VITERATIONS;
		const static int32 POSITION_ITERATIONS = HZ_PITERATIONS;
	};
}
