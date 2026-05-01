#pragma once
#include <Collider.h>
class Rigidbody
{
public:
	Rigidbody();
	
	std::string name;

	glm::vec3 velocity;
	glm::vec3 position;
	float friction;
	float mass;
	float gravity;
	static std::vector<Rigidbody*> rbEntities;
	//static std::vector<Motion*> motions;
	glm::mat3 momentOfInertia;
	glm::mat3 inverseMomentOfInertia;
	glm::vec3 angularVelocity;

	bool hasGravity;
	bool isKinematic;
	glm::mat4 transform;

	
};

//struct MotionCollision
//{
//	MotionCollision();
//	
//	
//	glm::vec3 origin;
//	glm::vec3 direction;
//	float restitution; 
//	float LinearDrag; 
//};
//
