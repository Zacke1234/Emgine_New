
#include <ObjectManager.h>
#include <TextureManager.h>
#include <ColliderManager.h>
#include <RigidbodyManager.h>
#include <CameraManager.h>
#include <Time/Time.h>
#include <ShaderManager.h>
#include <Physics.h>

class Player
{
public:
	Player(GLFWwindow* getWindow, ObjectManager* myObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime, Physics* aPhysics);
	ShaderManager* aShaderManager;
	void InputMovement();
	void CheckCollision();


	

	float movementSpeed;
	float jumpStrength;
	float dashStrength;
	GLFWwindow* window;
	Mesh* playerMesh;
	Texture* defaultTex;
	Collider* playerColl;
	Rigidbody* playerRB;
	Controller* playerController;
	Shader* getShader;
	Camera* playerCamera;
	Object* player;
	Time* getTime;
	bool onGround;
	Physics* playerPhysics;


	
	
};

