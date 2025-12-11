#include "Collider.h"
#include "Physics.h"
#include <Object.h>

std::vector<Collider*> Collider::CollEntities;

glm::mat3 ComputeMomentOfInertiaCube(float mass, glm::vec3 extents)
{
    //float inertiaScalar = (2.0f / 3.0f) * mass * (extents * extents);
    return glm::mat3(NULL);
}

glm::mat3 ComputeMomentOfInertiaSphere(float mass, float radius)
{
    float inertiaScalar = (2.0f / 3.0f) * mass * (radius * radius);
    return glm::mat3(inertiaScalar);
}

//void Collider::UpdateCollider(SphereCollider* sphere, CubeCollider* cube)
//{
//
//}

Collider::Collider() 
{
	
	center = glm::vec3(0, 0, 0);
	
	
	transform = Math::identity4;
	position = glm::vec3(0, 0, 0);
	extents = glm::vec3(0, 0, 0);
	
	std::cout << "test";
	//SetTheCollision();

}

void Collider::test()
{

}

SphereCollider::SphereCollider(const glm::vec3& aCenter, const float& aRadius, glm::vec3 Apos) : Collider()
{
	CollType = ColliderType::Sphere;

	center = aCenter;
	radius = aRadius;

	position = Apos;
	std::cout << "SphereCollider";
}

CubeCollider::CubeCollider(const glm::vec3& aCenter, const glm::vec3& someExtents, glm::vec3 Apos) : Collider()
{
	CollType = ColliderType::Cube;
	center = aCenter;
	extents = someExtents;
	position = Apos;
	//scale = aScale;
	std::cout << "CubeCollider";
}

void Collider::SetTheCollision()
{
	

	
	//CubeCollider* cubeColl = new CubeCollider(center, extents, pos);
 
	//std::cout << "set the collision" << std::endl;
}
