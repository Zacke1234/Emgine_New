#pragma once
#include <glm.hpp>
#include <iostream>
#include <vector>




glm::mat3 ComputeMomentOfInertiaCube(float mass, glm::vec3 extents);
glm::mat3 ComputeMomentOfInertiaSphere(float mass, float radius);

class Collider
{
public: 
	Collider();
	virtual void test();
	//virtual ~Collider() {};

	template<typename T>
	bool isOf() { return (dynamic_cast<T*>(this) != NULL); }; // do i need multiple of these in the structs?

	// Determines if the collider will automatically scale with the object
	bool autoColliderSize = true;
	
	std::string name;
	//void UpdateCollider(SphereCollider* sphere, CubeCollider* cube);
	
	glm::vec3 extents;
	
	glm::vec3 center;
	// move to dynamic body
	glm::mat4 transform;
	
	glm::vec3 position;

	float radius;

	enum ColliderType {
		Null = 0 , Sphere, Cube, Raycast
	};

	ColliderType CollType; // = ColliderType::Null;
	
	//glm::vec3 extents;

	// auto* r : Rigidbody::rbEntities
	// Rigidbody r : rigidbodies

	void SetTheCollision();
	
	static std::vector<Collider*> CollEntities;
	
	//SphereCollider* mySphereColl;
	//CubeCollider* myCubeColl;

};

struct Collision {
	Collider* col1;
	Collider* col2;
	glm::vec3 point;
	glm::vec3 normal1;
	glm::vec3 normal2;
	
};



class SphereCollider : public Collider{

public:

	SphereCollider(const glm::vec3& aCenter, const float& aRadius, glm::vec3 Apos);

};

class CubeCollider : public Collider
{
public:
	// glm::vec3 aScale
	CubeCollider(const glm::vec3& aCenter, const glm::vec3& someExtents, glm::vec3 Apos);
	
};

class Ray {
public:
	Ray(const glm::vec3& anOrigin, const glm::vec3& aDirection)
	{
		origin = anOrigin;
		direction = aDirection;
	}
	glm::vec3 origin;
	glm::vec3 direction;
};

class RayHit {
public:
	RayHit(glm::vec3 aPoint, Collider* aCollider, float aDistance) {
		point = aPoint;
		collider = aCollider;
		distance = aDistance;
	};

	glm::vec3 point;
	Collider* collider;
	float distance;
};