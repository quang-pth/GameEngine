#include"PhysicSystem.h"
#include"Core/Component/Box2DComponent.h"
#include"Core/Component/RigidBodyComponent.h"
#include"Core/Component/TransformComponent.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(PhysicSystem)

	constexpr float WORLD_LENGTH_UNITS_PER_METER = 5.0f;

	float PixelToWorld(float pixels) { return pixels / WORLD_LENGTH_UNITS_PER_METER; }

	float WorldToPixel(float meters) { return meters * WORLD_LENGTH_UNITS_PER_METER; }

	const std::unordered_map<EBodyType, b2BodyType> BODY_TYPE_MAP = {
		{EBodyType::STATIC, b2_staticBody},
		{EBodyType::DYNAMIC, b2_dynamicBody},
		{EBodyType::KINEMATIC, b2_kinematicBody}
	};

	PhysicSystem::PhysicSystem(ECS::SystemID id, ECS::ESystemPriority priority) 
		: ECS::System<PhysicSystem>(id, priority)
	{
	}

	PhysicSystem::~PhysicSystem() {

	}

    void PhysicSystem::OnInit() {
        mWorldDef = b2DefaultWorldDef();
        mWorldDef.gravity = b2Vec2{ 0.0f, -10.0f };
        mWorldID = b2CreateWorld(&mWorldDef);
	}

	void PhysicSystem::OnShutdown() {

	}

	void PhysicSystem::OnStart() {
		for (RigidBodyComponent* rigidBody : mCoordinator->GetComponentArray<RigidBodyComponent>()) {
			Actor actor = rigidBody->GetOwner();
			
			TransformComponent& transform = actor.GetComponent<TransformComponent>();
			b2BodyDef bodyDef = b2DefaultBodyDef();
			bodyDef.type = BODY_TYPE_MAP.at(rigidBody->GetBodyType());
			bodyDef.gravityScale =  rigidBody->GetGravityScale();
			bodyDef.linearDamping = rigidBody->GetLinearDamping();
			bodyDef.fixedRotation = rigidBody->GetFixedRotation();
			
			if (actor.HasComponent<Box2DComponent>()) {
				Box2DComponent& box2DComponent = actor.GetComponent<Box2DComponent>();

				bodyDef.position = b2Vec2{
					PixelToWorld(transform.GetPosition().x), 
					PixelToWorld(transform.GetPosition().y)
				};

				b2BodyId bodyId = b2CreateBody(mWorldID, &bodyDef);
				rigidBody->SetBodyID(bodyId);
				b2Body_SetUserData(bodyId, rigidBody);
				
				b2Polygon boxCollider = b2MakeBox(PixelToWorld(box2DComponent.GetWidth() * 0.5), PixelToWorld(box2DComponent.GetHeight() * 0.5));
				b2ShapeDef shapeDef = b2DefaultShapeDef();
				shapeDef.density = box2DComponent.GetDensity();
				shapeDef.friction = box2DComponent.GetFriction();
				b2CreatePolygonShape(bodyId, &shapeDef, &boxCollider);
			}
			else {
				VI_ASSERT(false && "Actor with RigidbodyComponent attached should have at least one shape collider component");
			}
		}
	}

	void PhysicSystem::OnUpdate(Time time) {
		float timeStep = 1.0f / 60.0f;
		int subStepCount = 4;

		for (RigidBodyComponent* rigidBody : mCoordinator->GetComponentArray<RigidBodyComponent>()) {
			if (!rigidBody->GetIsActive()) continue;

			TransformComponent& transform = rigidBody->GetOwner().GetComponent<TransformComponent>();
			b2Vec2 physicWorldPosition = b2Body_GetPosition(rigidBody->GetBodyID());
			if (rigidBody->GetBodyType() == EBodyType::KINEMATIC) {
				b2Vec2 velocity = b2Vec2{
					PixelToWorld(transform.GetPosition().x) - physicWorldPosition.x, 
					PixelToWorld(transform.GetPosition().y) - physicWorldPosition.y
				};
				b2Body_SetLinearVelocity(rigidBody->GetBodyID(), velocity);
			}
			else if (rigidBody->GetBodyType() == EBodyType::DYNAMIC) {
			}
		}

		// Update physic world
		b2World_Step(mWorldID, timeStep, subStepCount);
		
		// Reflect back position from physic world to the game
		b2BodyEvents bodyEvents = b2World_GetBodyEvents(mWorldID);
		for (int32_t i = 0; i < bodyEvents.moveCount; ++i) {
			const b2BodyMoveEvent* event = bodyEvents.moveEvents + i;
			RigidBodyComponent* rigidBody = reinterpret_cast<RigidBodyComponent*>(event->userData);
			Actor actor = rigidBody->GetOwner();
			if (actor.HasComponent<Box2DComponent>()) {
				Box2DComponent& box = actor.GetComponent<Box2DComponent>();
				TransformComponent& transform = actor.GetComponent<TransformComponent>();
				b2Vec2 physicWorldPosition = b2Body_GetPosition(rigidBody->GetBodyID());
				// transform.SetPositionX(WorldToPixel(physicWorldPosition.x) + box.GetWidth() * 0.5);
				// transform.SetPositionY(-WorldToPixel(physicWorldPosition.y) - box.GetHeight() * 0.5);

				transform.SetPositionX(WorldToPixel(physicWorldPosition.x));
				transform.SetPositionY(WorldToPixel(physicWorldPosition.y));
			}
			else {
				VI_ASSERT(false && "Actor with RigidbodyComponent attached should have at least one shape collider component");
			}
		}
	}

	void PhysicSystem::OnDestroyed() {
		b2DestroyWorld(mWorldID);
	}
}