#pragma once
#include <vector>
#include "Collider.h"
#include "Rigidbody.h"
#include <Object.h>
#include "Time/Time.h"


namespace Math {
	extern const glm::mat4 identity4;
	extern const glm::mat3 identity3;

}

class Physics
{
public:
	Physics();
	void GatherAllPhysicObjects();
	void Simulate(const float& aDeltaTime, Time* physicsTime);

	void UpdateColliderProperties(std::vector<Collider*> colliders);
	void UpdateRigidbodyProperties(std::vector<Rigidbody*> rigidbodies);

	void ApplyVelocity(std::vector<Rigidbody*> rbs, float dt);
	void ApplyGravity(std::vector<Rigidbody*> rbs, float dt);

	void HandleCollisions(std::vector<Collision*> collisions, std::vector<Rigidbody*> rbs);
	

	void UpdateVisuals(Time* physicsTime);


	glm::vec3 SafeNormalise(glm::vec3 vector);
	
	bool BoolCheckIntersect(Collider* c1, Collider* c2);
	std::vector<Collider*> UpdateCollidersScene();
	std::vector<Rigidbody*> UpdateRigidbodiesScene();
	std::vector<Collision*> CheckIntersections(std::vector<Collider*> colliders);
	glm::mat3 ComputeMomentOfInertiaSPhere(float mass, float radius);
	bool SphereSphereIntersect(SphereCollider& c1, SphereCollider& c2);
	bool CubeSphereIntersect(CubeCollider& aCube1, SphereCollider& aSpher2);
	bool CubeCubeIntersect(CubeCollider& aCube1, CubeCollider& aCube2);

	bool RayCast(Ray& aRay, RayHit& aHit);

	bool CheckRayIntersect(Ray& aRay, Collider* aCollider);

	bool RayCubeIntersect(Ray& aRay, CubeCollider aCube);
	bool RaySphereIntersect(Ray& aRay, SphereCollider aSphere);

	bool RayOBBIntersect(Ray& aRay, CubeCollider& aCube);
	
	bool Testgravity = true;

	bool TimeTicking = true;
	std::vector<Collision*> collisions;
	std::vector<Rigidbody*> rigidbodies;


	std::vector<Collider*> colliders;
	//ColliderType* type;
private:
	


	//std::vector<Object*> m_Objects;
};

