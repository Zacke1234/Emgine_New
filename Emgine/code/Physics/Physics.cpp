
#include <Object.h>
#include "Collider.h"
#include "Physics.h"
#include <Time/Time.h>

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


Physics::Physics()
{
	
}

void Physics::GatherAllPhysicObjects()
{
	//
}

void Physics::Simulate(const float& aDeltaTime, Time* physicsTime)
{
	
	


	if (physicsTime->IsPaused == false)
	{
		
		colliders = UpdateCollidersScene();
		rigidbodies = UpdateRigidbodiesScene();
		std::vector<Collision*> collisions = CheckIntersections(colliders);

		//std::vector<Rigidbody> rigidbodies = 
		ApplyGravity(rigidbodies, aDeltaTime);

		HandleCollisions(collisions, rigidbodies);

		ApplyVelocity(rigidbodies, aDeltaTime);

		UpdateVisuals(physicsTime);
	


	}

}

void Physics::UpdateColliderProperties(std::vector<Collider*> colliders)
{
	for (auto& o : Object::Entities) // Have to make it so an Entity MUST have a sphere or cube collider to be considered being a "Collider"
	{
		if (o->myCollider != NULL)
		{
			o->myCollider->position = o->Position;
			if (o->myCollider->autoColliderSize)
			{
				o->myCollider->extents = o->Scale;
				o->myCollider->transform = o->trans;
				o->myCollider->center = glm::vec3(0.5f * o->Scale.x, 0.5f * o->Scale.y, 0.5f * o->Scale.z);
				std::cout << "";
			}
			
		}
		
		//o->myCollider->extents



	}
}

void Physics::UpdateRigidbodyProperties(std::vector<Rigidbody*> rigidbodies)
{
	for (auto& o : Object::Entities)
	{
		if (o->myRigidbody != NULL)
		{
			o->myRigidbody->position = o->Position;
			o->myRigidbody->transform = o->trans;
			
			
		}
	}
	
}

void Physics::UpdateVisuals(Time* physicsTime)
{

	for (auto& o : Object::Entities)
	{
		//o->UpdateTransform();
		if (!o->myRigidbody == NULL)
		{
			o->Position = o->myRigidbody->position;
		}
		
	}

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

void Physics::ApplyVelocity(std::vector<Rigidbody*> rbs, float dt)
{
	// std::vector<Collider*> colliders
	for (Rigidbody* r : rbs)
	{
		if (!r->isKinematic)
		{
			glm::vec3 pos = glm::vec3(r->transform[3]);
			pos += r->velocity * dt;
			r->position = pos;
			r->transform[3] = glm::vec4(pos, 1.0f);
		}
	}


}

void Physics::ApplyGravity(	std::vector<Rigidbody*> rbs, float dt)
{
	
	for (Rigidbody* r : rbs)
	{
		if (r->hasGravity && !r->isKinematic)
		{
			r->velocity += glm::vec3(0, -1.8, 0) * dt;
			int b = 1;

		}
	}
}

void Physics::HandleCollisions(std::vector<Collision*> collisions, std::vector<Rigidbody*> rbs)
{
	for (Rigidbody* r : rbs)
	{
		if (!r->isKinematic)
		{
			for (Collision* c : collisions)
			{
				if (c->col1)
				{
					r->velocity *= 0;
				}

				if (c->col2)
				{
					r->velocity *= 0;
				}

				//c.col1->transform 

			}
			
		}

	}
	
}


bool Physics::BoolCheckIntersect(Collider* c1, Collider* c2)
{	
	//CheckIntersect(c1, c2);
	if (c1->isOf<SphereCollider>() && c2->isOf<SphereCollider>())
	{
		//std::cout << "check with spheres intersect ";
		SphereCollider* sphere1 = dynamic_cast<SphereCollider*>(c1);
		SphereCollider* sphere2 = dynamic_cast<SphereCollider*>(c2);
		return SphereSphereIntersect(*sphere1, *sphere2);
		
	}

	if (c1->isOf<CubeCollider>() && c2->isOf<SphereCollider>())
	{
		//std::cout << "check with cubes & spheres intersect";
		CubeCollider* cube1 = dynamic_cast<CubeCollider*>(c1);
		SphereCollider* sphere1 = dynamic_cast<SphereCollider*>(c2);

		return CubeSphereIntersect(*cube1, *sphere1);
		
		
	}

	if (c1->isOf<SphereCollider>() && c2->isOf<CubeCollider>())
	{
		//std::cout << "check with cubes & spheres intersect";
		SphereCollider* sphere1 = dynamic_cast<SphereCollider*>(c1);
		CubeCollider* cube1 = dynamic_cast<CubeCollider*>(c2);

		return CubeSphereIntersect(*cube1, *sphere1);


	}

	if (c1->isOf<CubeCollider>() && c2->isOf<CubeCollider>()) // cube colliding is hard to get to work
	{
		//std::cout << "check with cubes intersect";
		CubeCollider* cube1 = dynamic_cast<CubeCollider*>(c1);
		CubeCollider* cube2 = dynamic_cast<CubeCollider*>(c2);
		return CubeCubeIntersect(*cube1, *cube2);
		
	}

	
}

std::vector<Collider*> Physics::UpdateCollidersScene()
{
	std::vector<Collider*> returnColliders;
	for (auto& o : Object::Entities)
	{
		if (!o->myCollider == NULL)
		{
			UpdateColliderProperties(returnColliders);
			returnColliders.push_back(o->myCollider);
		}
		

	}
	return returnColliders;
}

std::vector<Rigidbody*> Physics::UpdateRigidbodiesScene()
{
	std::vector<Rigidbody*> returnrbs;
	for (auto& o : Object::Entities)
	{
		if (!o->myRigidbody == NULL)
		{
			UpdateRigidbodyProperties(returnrbs);
			returnrbs.push_back(o->myRigidbody);
		}


	}
	return returnrbs;
}

std::vector<Collision*> Physics::CheckIntersections(std::vector<Collider*> colliders)
{
	
	std::vector<Collision*> collisions;

	for (Collider* c1 : colliders)
	{
		for (Collider* c2 : colliders)
		{
			if (c1 != c2)
			{
				if (BoolCheckIntersect(c1, c2))
				{
					Collision* collision = new Collision;
					
					collision->col1 = c1;
					collision->col2 = c2;
					collisions.push_back(collision);
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

bool Physics::SphereSphereIntersect(SphereCollider& sphere1, SphereCollider& sphere2)
{
	
			float dist = glm::distance(sphere1.position, sphere2.position);

			if (dist < sphere1.radius + sphere2.radius)
			{
				std::cout << "Spheres are intersecting!" << std::endl;
				return true;
			}
			else
			{
				return false;
			}
	
	
}

bool Physics::CubeSphereIntersect(CubeCollider& aCube1, SphereCollider& aSphere2)
{	
	glm::vec3 sphereCenter = glm::vec3(aSphere2.transform[3]);
	glm::vec3 localSphereCenter = glm::inverse(aCube1.transform) * glm::vec4(sphereCenter, 1.0f);
	glm::vec3 closestPoint = glm::clamp(localSphereCenter, -aCube1.extents, aCube1.extents);
	float dist2 = glm::length(localSphereCenter - closestPoint); 
	
	return dist2 < aSphere2.radius * aSphere2.radius;
}

bool Physics::CubeCubeIntersect(CubeCollider& aCube1, CubeCollider& aCube2)
{
	// static_assert failed: ''abs' only accept floating-point and integer scalar or vector inputs'

	glm::mat3 rotation1 = glm::mat3(aCube1.transform);
	glm::mat3 rotation2 = glm::mat3(aCube2.transform);
	glm::vec3 translation = glm::vec3(aCube2.transform[3]) - glm::vec3(aCube1.transform[3]);
	translation = glm::transpose(rotation1) * translation;

	glm::mat3 rotation = glm::transpose(rotation1) * rotation2;
	glm::mat3 absRotation;// = glm::abs(rotation) + glm::mat3(0.0001f); // this just won't compile! 
	//glm::vec3 absRotation2 = glm::abs(translation) + glm::vec3(0.0001f);
 	glm::vec3 halfSize1 = aCube1.extents * 0.5f;
	glm::vec3 halfSize2 = aCube2.extents * 0.5f;

	// SAT (seperating axis theorem
	for (int i = 0; i < 3; ++i)
	{
		float ra = aCube1.extents[i];
		float rb  = glm::dot(absRotation[i], aCube2.extents);
		if (glm::abs(translation[i]) > ra + rb) return false;
	}

	for (int i = 0; i < 3; ++i)
	{
		float ra = glm::dot(absRotation[i], aCube1.extents);
		float rb = aCube2.extents[i];
		if (glm::abs(glm::dot(rotation[i], translation)) > ra + rb) return false;
	}

	return true;
	std::cout << "cubes are intersecting" << std::endl;

}

bool Physics::RayCast(Ray& aRay, RayHit& aHit)
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

bool Physics::CheckRayIntersect(Ray& aRay, Collider* aCollider)
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

bool Physics::RayCubeIntersect(Ray& aRay, CubeCollider aCube)
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

bool Physics::RaySphereIntersect(Ray& aRay, SphereCollider aSphere)
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

bool Physics::RayOBBIntersect(Ray& aRay, CubeCollider& aCube)
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
