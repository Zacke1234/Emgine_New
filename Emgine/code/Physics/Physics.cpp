#define GLM_ENABLE_EXPERIMENTAL

#include "glm.hpp"
#include <ext/quaternion_trigonometric.hpp>
#include <gtc/quaternion.hpp>
#include <Object.h>
#include "Collider.h"
#include <thread>
#include "Physics.h"

const glm::mat4 Math::identity4{
	
1,0,0,0,
0,1,0,0,
0,0,1,0,
0,0,0,1
};

const glm::mat3 Math::identity3{

1,0,0,
0,1,0,
0,0,1
};


float Restitution;
float LinearDrag;


Physics::Physics()
{
	
}

void Physics::GatherAllPhysicObjects()
{
	//
}

void Physics::Simulate(const float& aDeltaTime, Time* physicsTime)
{
	UpdatePhysicsScene();
	
	std::vector<Collision> collisions = CheckIntersections(Collider::CollEntities);
		
	// gotta update this
	
	// Just setting the positions of the colliders to match the visual
	

	// checking for any intersections and storing their data in a vector of collisions
	//std::vector<Collision> collisions = CheckIntersections(cols);
	// Collider::CollEntities
	// 
	UpdateColliderProperties();
	HandleCollisions(collisions);
	
	//	//As a result of those collisions what should happen?


	if (physicsTime->IsPaused == false)
	{
		ApplyGravity(Collider::CollEntities, aDeltaTime);
		ApplyVelocity(Collider::CollEntities, aDeltaTime);

		UpdateVisuals();
	}
	
	
}

void Physics::UpdateColliderProperties()
{
	for (auto& o : Object::Entities) // Have to make it so an Entity MUST have a sphere or cube collider to be considered being a "Collider"
	{
		if (o->myCollider != NULL)
		{
			o->myCollider->position = o->Position;
			o->myCollider->extents = glm::vec3(o->Scale.x, o->Scale.y, o->Scale.z);
			o->myCollider->transform = o->trans;
		}
		
		//o->myCollider->extents



	}
}

void Physics::UpdateVisuals()
{
	/*glm::vec3 center = { 0, 0,0 }; float radius = 10; glm::vec3 pos = { 0,0,0 };
	glm::vec3 scale = { 1,1,1 };
	glm::vec3 extents = { 1,1,1 };*/
	for (auto& o : Object::Entities)
	{
		o->UpdateTransform();
		//std::thread T1(o->UpdateTransform());
		  
		if (!o->myRigidbody == NULL)
		{
			o->Position = o->myRigidbody->velocity;
		}

		
		

		//o->myCollider->transform = o->trans;
		
		

	}
}
// std::vector<Collision> coll, std::vector<Collider*> colliders,
void Physics::ApplyCollision( const float& dt, std::vector<Collision> collisions)
{
	
}

glm::vec3 Physics::SafeNormalise(glm::vec3 vector)
{
	
	float vecLength = glm::length(vector);
	if (vecLength < 0.00000001f)
	{
		return glm::vec3(0);

	}

	return glm::normalize(vector);
	//
}



void Physics::ApplyVelocity(std::vector<Collider*> colliders, const float& dt)
{
	// std::vector<Collider*> colliders
	for (auto* r : Rigidbody::rbEntities)
	{
		for (auto* c : Collider::CollEntities)
		{
			if (r->hasGravity && !r->isKinematic)
			{

				/*if (CheckCollision(c1, c2))
				{
					if (c1 != c2)
					{
					}
				}*/
				//std::cout << "apply velocity";
				r->velocity += glm::vec3(0, 0.0096f, 0) * dt;
				r->transform[3] = glm::vec4(c->position, 1.0f);

				float maxAngularVelocity = 3;
				if (glm::length(r->angularVelocity) > maxAngularVelocity)
				{
					r->angularVelocity = glm::normalize(r->angularVelocity) * maxAngularVelocity;
				}
				if (glm::length(r->angularVelocity) > 0.0001f)
				{
					glm::vec3 angularVelocityNorm = glm::normalize(r->angularVelocity);
					glm::quat angularRotation = glm::angleAxis(glm::length(r->angularVelocity) * dt, angularVelocityNorm);

					glm::mat3 rotationDelta = glm::mat3_cast(angularRotation);
					r->transform = glm::mat4(rotationDelta) * r->transform;
				}

				if (r->mass > 0)
				{
					r->velocity *= glm::pow(1.0f - LinearDrag, dt);
				}
			}

		}

	
	}


}



void Physics::ApplyGravity(std::vector<Collider*> colliders, const float& dt)
{
	
	for (auto* r : Rigidbody::rbEntities)
	{
		if (!r->isKinematic)
		{
			// && CheckCollision(r, c2)
						//std::cout << "apply gravity";
			glm::vec3 position = glm::vec3(r->transform[3]);
			//glm::vec3 scale = glm::vec3(r->scale[3]);
			// 9.84
			

			r->velocity.y -= r->gravity * dt;
			position += r->velocity * dt;
			//c->position = position;
			r->transform[3] = glm::vec4(position, 1.0f);
			//r->scale = scale;

		}
	}
}

void Physics::HandleCollisions(std::vector<Collision> collisions)
{

	for (auto* r : Rigidbody::rbEntities)
	{
		for (auto* c : Collider::CollEntities)
		{
			//std::cout << "handle Collision";
			if (!r->isKinematic)
			{

				r->velocity *= -1;
				glm::vec3 normal = SafeNormalise(c->position - c->position);//relative velocity
				glm::vec3 relativeVelocity = r->velocity - r->velocity;
				float velocityAlongNormal = glm::dot(relativeVelocity, normal);
				if (velocityAlongNormal < 0)
				{
					// Coefficient of restitution (bounciness) and calculating impulse
					float restitution = 0.2f;
					float impulse = (1 + restitution) * velocityAlongNormal;

					if (!r->isKinematic)
					{
						glm::vec3 impulseVector = impulse * normal;
						r->velocity += impulseVector;
					}

					if (!r->isKinematic)
					{
						glm::vec3 impulseVector = impulse * normal;
						r->velocity -= impulseVector;
					}
				}







				// < 0 means they are moving towards each other

			}
		}
	}
	
}

void Physics::HandleDynamicDynamic(std::vector<Collision> collisions)
{
	for (auto* r : Rigidbody::rbEntities)
	{
		for (Collision c : collisions)
		{
			//std::cout << "handle dynamic dynamic";
			glm::vec3 normal = c.normal1; // might need to change that to just normal without the 1

			glm::vec3 relativeVelocity = r->velocity - r->velocity;
			float velocityAlongNormal = glm::dot(relativeVelocity, normal);

			if (velocityAlongNormal > 0) continue;

			float impulse = (1 + Restitution) * velocityAlongNormal;

			glm::vec3 impulseVector = impulse * normal;

			r->velocity += impulseVector;
			r->velocity += impulseVector;

			glm::vec3 r1 = c.point - c.col1->position;
			glm::vec3 r2 = c.point - c.col2->position;

			glm::vec3 torque1 = glm::cross(r1, impulseVector);
			glm::vec3 torque2 = glm::cross(r2, impulseVector);

			r->angularVelocity += r->inverseMomentOfInertia * torque1 * 100000000.0f;
			r->angularVelocity += r->inverseMomentOfInertia * torque2 * 100000000.0f;

		}
	}
	
}

void Physics::HandleStaticDynamic(std::vector<Collision> collisions, std::vector<Motion> motions)
{
	const float SlidingFriction = 0.5f;
	for (Motion rb : motions)
	{
		for (Collision c : collisions)
		{
			//std::cout << "handle static dynamic";
			Collider* A = c.col1;
			Collider* B = c.col2;

			Rigidbody* RigA = rb.rig1;
			Rigidbody* RigB = rb.rig2;

			bool A_isDynamic = !RigA->isKinematic;
			bool B_isDynamic = !RigB->isKinematic;

			if (!A_isDynamic && !B_isDynamic) continue;

			Collider* dynamicCollider = A_isDynamic ? A : B;
			Collider* staticCollider = A_isDynamic ? B : A;

			Rigidbody* dynamicRigidbody = A_isDynamic ? RigA : RigB;
			Rigidbody* staticRigidbody = A_isDynamic ? RigB : RigA;

			glm::vec3 n = glm::normalize(c.normal1);
			glm::vec3 r = c.point - dynamicCollider->position;

			glm::vec3 v = dynamicRigidbody->velocity + glm::cross(dynamicRigidbody->angularVelocity, r);
			float vRelDotN = glm::dot(v, n);

			if (vRelDotN > 0) continue;

			float invMass = (dynamicRigidbody->mass > 0) ? 1.0f / dynamicRigidbody->mass : 0;
			glm::vec3 r_cross_n = glm::cross(r, n);
			float angularEffect = glm::dot(r_cross_n, dynamicRigidbody->inverseMomentOfInertia * r_cross_n);

			float impulseMagnitude = -(1 + Restitution) * vRelDotN / (invMass * angularEffect);
			glm::vec3 impulse = impulseMagnitude * n;

			//apply impulse to linear velocity
			dynamicRigidbody->velocity += impulse * invMass;

			//angular velocity (considering moment of inertia 
			dynamicRigidbody->angularVelocity += dynamicRigidbody->inverseMomentOfInertia * glm::cross(r, impulse);

			glm::vec3 tangentVelocity = v - (n * glm::dot(v, n));
			if (glm::length(tangentVelocity) > 0.0001f)
			{
				glm::vec3 frictionDirection = -glm::normalize(tangentVelocity);
				glm::vec3 frictionImpulse = frictionDirection * SlidingFriction * glm::length(tangentVelocity);

				dynamicRigidbody->velocity += frictionImpulse * invMass;
				dynamicRigidbody->angularVelocity += dynamicRigidbody->inverseMomentOfInertia * glm::cross(r, frictionImpulse);
			}

		}
	}
	
}


bool Physics::BoolCheckIntersect(Collider* c1, Collider* c2)
{

	//CheckIntersect(c1, c2);
	if (c1->isOf<SphereCollider>() && c2->isOf<SphereCollider>())
	{
		std::cout << "check with spheres intersect ";
		SphereCollider* sphere1 = dynamic_cast<SphereCollider*>(c1);
		SphereCollider* sphere2 = dynamic_cast<SphereCollider*>(c2);
		return SphereSphereIntersect(*sphere1, *sphere2);
		
	}

	else if (c1->isOf<CubeCollider>() && c2->isOf<SphereCollider>())
	{
		std::cout << "check with cubes & spheres intersect";
		CubeCollider* cube1 = dynamic_cast<CubeCollider*>(c1);
		SphereCollider* sphere1 = dynamic_cast<SphereCollider*>(c2);

		return CubeSphereIntersect(*cube1, *sphere1);
		
		
	}

	else if (c1->isOf<CubeCollider>() && c2->isOf<CubeCollider>())
	{
		std::cout << "check with cubes intersect";
		CubeCollider* cube1 = dynamic_cast<CubeCollider*>(c1);
		CubeCollider* cube2 = dynamic_cast<CubeCollider*>(c2);
		return CubeCubeIntersect(*cube1, *cube2);
		
	}

	
}

std::vector<Collider*> Physics::UpdatePhysicsScene()
{
	std::vector<Collider*> returnColliders;
	for (auto& o : Object::Entities)
	{
		//std::cout << "apply velocity";
		returnColliders.push_back(o->myCollider);

	}
	return returnColliders;
}

std::vector<Collision> Physics::CheckIntersections(std::vector<Collider*> colliders)
{
	
	

	int count = colliders.size();

	for (auto* c1 : Collider::CollEntities)
	{
		for (auto* c2 : Collider::CollEntities)
		{
			if (c1 != c2)
			{
				if (BoolCheckIntersect(c1, c2))
				{
					
					Collision collision;
					collision.col1 = c1;
					collision.col2 = c2;
					collisions.push_back(collision);
					std::cout << "check Intersections";

				}
			}
		}
	}
	return collisions;
}

glm::mat3 Physics::ComputeMomentOfInertiaSPhere(float mass, float radius) // omw to return a float that is a glm
{
	float inertiaScalar = (2.0f / 3.0f) * mass * (radius * radius);
	return glm::mat3(inertiaScalar);
}

bool Physics::SphereSphereIntersect(const SphereCollider& c1, const SphereCollider& c2)
{
	
			float dist = glm::distance(c1.position, c2.position);

			if (dist < c1.radius + c2.radius)
			{
				//std::cout << "Spheres are intersecting!" << std::endl;
				return true;
			}
			else
			{
				return false;
			}
	
	
}

bool Physics::CubeSphereIntersect(const CubeCollider& aCube1, const SphereCollider& aSphere2)
{
	/*for (int i = 0; aCube1.transform.length() > i; i++)
	{
		if (aCube1.transform[i].x <= -100000)
		{
			std::cout << "is less then -100000";
			break;*/

			glm::vec3 sphereCenter = glm::vec3(aSphere2.transform[3]);
			glm::vec3 localSphereCenter = glm::inverse(aCube1.transform) * glm::vec4(sphereCenter, 1.0f); // problems arise here
			glm::vec3 closestPoint = glm::clamp(localSphereCenter, -aCube1.extents, aCube1.extents);
			float dist2 = glm::length(localSphereCenter - closestPoint); // -nan(ind) error
			if (dist2 >= aSphere2.radius * aSphere2.radius)
			{
				//std::cout << "cubes & spheres intersect" << std::endl;
				return true;
			}
			else {
				return false;
			}

	//	}
	//}
	
	
}

bool Physics::CubeCubeIntersect(const CubeCollider& aCube1, const CubeCollider& aCube2)
{
	// static_assert failed: ''abs' only accept floating-point and integer scalar or vector inputs'

	glm::mat3 rotation1 = glm::mat3(aCube1.transform);
	glm::mat3 rotation2 = glm::mat3(aCube2.transform);
	glm::vec3 translation = glm::vec3(aCube2.transform[3]) - glm::vec3(aCube1.transform[3]);
	translation = glm::transpose(rotation1) * translation;

	glm::mat3 rotation = glm::transpose(rotation1) * rotation2;
	glm::mat3 absRotation; /* glm::abs(rotation) + glm::mat3(0.0001f);*/

	for (int i = 0; i < 3; i++)
	{
		absRotation[i] = glm::abs(rotation[i]) + 0.00001f;
	} 
	glm::vec3 halfSize1 = aCube1.extents * 0.5f;
	glm::vec3 halfSize2 = aCube2.extents * 0.5f;

	// SAT (seperating axis theorem
	for (int i = 0; i < 3; ++i)
	{
		float ra = halfSize1[i];
		float rb = glm::dot(absRotation[i], halfSize2);
		if (glm::abs(translation[i]) > ra + rb) return false;
	}

	for (int i = 0; i < 3; ++i)
	{
		float ra = glm::dot(absRotation[i], halfSize1);
		float rb = halfSize2[i];
		if (glm::abs(glm::dot(rotation[i], translation)) > ra + rb) return false;
	}

	return true;
	std::cout << "cubes are intersecting" << std::endl;

}

bool Physics::RayCast(const Ray& aRay, RayHit& aHit)
{
	
	for (auto* c : Collider::CollEntities)
	{
		/*if (r->mass > 0)
		{
			r->velocity *= glm::pow(1.0f, Lineardrag)
		}*/
		if (CheckRayIntersect(aRay, c))
		{
			aHit.collider = c;
			aHit.point = glm::vec3(0, 0, 0);
			aHit.distance = 10;
			return true;
		}
	}
	return false;
}

bool Physics::CheckRayIntersect(const Ray& aRay, Collider* aCollider)
{
	if (aCollider->isOf<SphereCollider>())
	{
		SphereCollider* sphere = dynamic_cast<SphereCollider*>(aCollider);
		return RaySphereIntersect(aRay, *sphere);
	}
	else if (aCollider->isOf<CubeCollider>())
	{
		CubeCollider* cube = dynamic_cast<CubeCollider*>(aCollider);
		return RayCubeIntersect(aRay, *cube);
	}
}

bool Physics::RayCubeIntersect(const Ray& aRay, CubeCollider aCube)
{
	glm::vec3 min = glm::vec3(aCube.transform[3]) - aCube.extents;
	glm::vec3 max = glm::vec3(aCube.transform[3]) + aCube.extents;

	glm::vec3 invDir = 1.0f / aRay.direction;

	float t1 = (min.x - aRay.origin.x) * invDir.x;
	float t2 = (max.x - aRay.origin.x) * invDir.x;
	float t3 = (min.y - aRay.origin.y) * invDir.y;
	float t4 = (max.y - aRay.origin.y) * invDir.y;
	float t5 = (min.z - aRay.origin.z) * invDir.z;
	float t6 = (max.z - aRay.origin.z) * invDir.z;

	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::min(t5, t6));

	return tmax >= std::max(0.0f, tmin);
}

bool Physics::RaySphereIntersect(const Ray& aRay, SphereCollider aSphere)
{
	// Look at glm intersectRaySphere

	// vector from ray origin to sphere center
	glm::vec3 diff = aSphere.center - aRay.origin;

	// project diff onto ray direction
	float t0 = glm::dot(diff, aRay.direction);

	//perpendicular distance! .....? also dot on itself makse sense since diff is not normalized
	float dSquared = glm::dot(diff, diff) - t0 * t0;

	// distance is greater than the sphere's radius squared, no intersection
	float radiusSquared = aSphere.radius * aSphere.radius;
	if (dSquared > radiusSquared)
	{
		return false;
	}

	// distance from closest to intersection point 
	float t1 = glm::sqrt(radiusSquared - dSquared);

	float Epsilon = 0.000001f; // just a small number to help with tiny floating point errors
	float outIntersectionDistance = (t0 > t1 + Epsilon) ? t0 - t1 : t0 + t1; // could actually return this as the2 distance

	//return true if the intersection distance is positive
	return outIntersectionDistance > Epsilon;
}

bool Physics::RayOBBIntersect(const Ray& aRay, const CubeCollider& aCube)
{
	glm::vec3 center = glm::vec3(aCube.transform[3]);
	glm::mat3 rotation = glm::mat3(aCube.transform);

	glm::vec3 localOrigin = glm::transpose(rotation) * (aRay.origin - center);
	glm::vec3 localDirection = glm::transpose(rotation) * aRay.direction;

	CubeCollider localCube = CubeCollider(glm::vec3(0, 0, 0), aCube.extents, aCube.position);
	localCube.extents = aCube.extents;

	Ray localRay(localOrigin, localDirection);
	return RayCubeIntersect(localRay, localCube);
}
