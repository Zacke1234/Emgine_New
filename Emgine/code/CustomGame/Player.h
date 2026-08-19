
#include <Managers/ObjectManager.h>
#include <Managers/TextureManager.h>
#include <Managers/ColliderManager.h>
#include <Managers/RigidbodyManager.h>
#include <Managers/CameraManager.h>
#include <Time/Time.h>
#include <Managers/ShaderManager.h>
#include <Physics.h>

class Player 
{
public:
	Player(GLFWwindow* getWindow, ObjectManager* myObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime, Physics* aPhysics);
	ShaderManager* aShaderManager;
	void InputMovement();
	bool CheckCollision();


	
	bool CheckIntersect = false;
	float movementSpeed;
	float jumpStrength;
	float dashStrength;

	bool moveButtons;
	
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
	bool atWall;
	Physics* playerPhysics;

private:
	GLFWwindow* window;
	
};

