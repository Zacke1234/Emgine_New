#pragma once
#include <Collider.h>
class Rigidbody
{
public:
	Rigidbody(float gravity);
	
	glm::vec3 velocity;
	float friction;
	float mass;
	static std::vector<Rigidbody*> rbEntities;

	glm::mat3 momentOfInertia;
	glm::mat3 inverseMomentOfInertia;
	glm::vec3 angularVelocity;

	bool hasGravity;
	bool isKinematic;
	glm::mat4 transform;

	
};

struct Motion
{
	Rigidbody* rig1;
	Rigidbody* rig2;
	glm::vec3 origin;
	glm::vec3 direction;
	float restitution; 
	glm::mat3 LinearDrag; 
};

