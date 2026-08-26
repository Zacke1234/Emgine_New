#pragma once
#include <glm.hpp>
#include <iostream>
#include <vector>
#include <Rigidbody.h>




glm::mat3 ComputeMomentOfInertiaCube(float mass, glm::vec3 extents);
glm::mat3 ComputeMomentOfInertiaSphere(float mass, float radius);
class Rigidbody;

class Collider
{
public: 
	~Collider();
	Collider();
	virtual void test(); // polymorphic
	//virtual ~Collider() {};

	std::string name;

	template<typename T>
	bool isOf() { return (dynamic_cast<T*>(this) != NULL); };

	enum ColliderType {
		Null = 0, Sphere, Cube, Ray, RayHit
	};

	// Determines if the collider will automatically scale with the object
	bool autoColliderSize = false;
	bool isKinematic;

	float friction;
	glm::vec3 extents;
	
	glm::vec3 center;
	// move to dynamic body
	glm::mat4 transform;
	
	glm::vec3 position;

	float radius;

	std::string tag;

	ColliderType CollType; // = ColliderType::Null;
	
	void SetTheCollision();
	
	std::vector<glm::vec3> points;

	glm::vec3 point;

	static std::vector<Collider*> CollEntities;
	
	
	
};

struct Collision {
	Collision();
	Collider* col1;
	Collider* col2;

	Rigidbody* rig1;
	Rigidbody* rig2;

	glm::vec3 point;
	glm::vec3 normal1;
	glm::vec3 normal2;
	
};



class SphereCollider : public Collider{

public:
	glm::vec3 aCenter;
	SphereCollider(const float& aRadius, glm::vec3 Apos);

};

class CubeCollider : public Collider
{
public:
	glm::vec3 aCenter;
	// glm::vec3 aScale
	CubeCollider(const glm::vec3& someExtents, glm::vec3 Apos);
	
};

class MeshCollider : public Collider
{
public:
	std::vector<glm::vec3> points;
	MeshCollider(const std::vector<glm::vec3> aPoints);
	
};

class Ray : public Collider {
public:
	Ray(const glm::vec3& anOrigin, const glm::vec3& aDirection)
	{
		origin = anOrigin;
		direction = aDirection;
	}
	glm::vec3 origin;
	glm::vec3 direction;
};

class RayHit : public Collider {
public:
	RayHit(glm::vec3 aPoint, Collider* aCollider, float aDistance) {
		point = aPoint;
		collider = aCollider;
		distance = aDistance;
	};

	
	Collider* collider;
	float distance;
};