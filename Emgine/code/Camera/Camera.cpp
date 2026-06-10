#include "Camera.h"

glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
float lastX = 400, lastY = 300;
Camera* Camera::Instance;
int Entered;

std::vector<Camera*> Camera::cameras;

Camera::Camera(GLFWwindow* getWindow, std::string aName)
{
	name = aName;
	window = getWindow;
	myTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	direction = glm::vec3(0, 0, 0);
	myDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	myPosition = glm::vec3(0.0f, 0.0f, 10.0f);
	myFront = glm::vec3(1.0f, 0.0f, 0.0f);
	myUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	myWidth = 800.0f;
	myHeight = 600.0f;
	
	myView = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	curx = 0;
	cury = 0;
	cameraViewRange = 300.0f;

	if (name == "SceneCamera")
	{
		CameraController = new Controller();
	}
	
}

Camera::~Camera()
{
	delete this;
}

void Camera::CameraSendToShader(Shader* myShader)
{
	myShader->SetMatrix("projection", projection);
	myShader->SetMatrix("view", myView);
	myShader->SetVec3("viewPos", myPosition);
}

void Camera::CameraUpdate() // the mouse cursor is still not good, when you tab in, it will just snap to another position again, need to fix
{
	myUp = glm::cross(myDirection, myRight);
	
	projection = glm::perspective(glm::radians(fieldOfView), myWidth / myHeight, 0.1f, cameraViewRange);

	myRight = glm::normalize(glm::cross(WorldUp, myDirection));
	
	myView = glm::lookAt(myPosition, myPosition + myDirection, myUp);

	mouse_callback(lastX, lastY);

}

void Camera::ProcessInput(float& deltatime)
{
	
	if (CameraController->W_KEY(window))
	{
		myPosition += cameraSpeed * myDirection;
	}

	if (CameraController->S_KEY(window))
	{
		myPosition -= cameraSpeed * myDirection;
	}

	if (CameraController->A_KEY(window))
	{
		myPosition -= glm::normalize(glm::cross(myDirection, myUp)) * cameraSpeed;
	}

	if (CameraController->D_KEY(window))
	{
		myPosition += glm::normalize(glm::cross(myDirection, myUp)) * cameraSpeed;
	}

	if (CameraController->ESCAPE_KEY(window))
	{
		CameraController->glfwSetInputMode_normal(window);
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		TabbedIn = false;
	}

	if (CameraController->TAB_KEY(window))
	{
		CameraController->glfwSetInputMode_cursor(window);
		CameraController->glfwSetInputMode_disabled(window);
		CameraController->glfwSetInputMode_unavailable(window);
		TabbedIn = true;
	}

	if (CameraController->SHIFT_KEY(window))
	{
		//std::cout << "shift" << "\n";
		cameraSpeed = 9.0f * 0.5;
	}

	if (CameraController->SHIFT_KEY_RELEASE(window))
	{
			//std::cout << "let go of shift" << "\n";
			cameraSpeed = 3.0f * 0.5f;
	}

}

void Camera::Mouse_Callback(GLFWwindow* window, double xpos, double ypos)
{
	lastX = xpos;
	lastY = ypos;
}

void Camera::mouse_callback(double xpos, double ypos)
{
	myDirection = glm::normalize(direction);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (!TabbedIn )
	{
		
		return;
		
	}
	
	bool firstMouse = true;
	
	if (firstMouse)
	{
		
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - curx;
	float yoffset = cury - ypos;
	curx = xpos;
	cury = ypos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset; 
	pitch += yoffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0)
	{
		pitch = -89.0f;
	}

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

}


