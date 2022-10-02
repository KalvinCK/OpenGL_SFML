#include <iostream>
using namespace std;

// Include GLFW
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace sf;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "Camera.hpp"

void Camera::MovingUpdate(Vector2i sizeWindow, sf::Event & event)
{
    float deltaTime = time.restart().asSeconds();

	// Get mouse position
	Vector2i MousePosicao(Mouse::getPosition().x, Mouse::getPosition().y);

	// Reset mouse position for next frame
	Mouse::setPosition(Vector2i(sizeWindow.x/2, sizeWindow.y/2));

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(sizeWindow.x / 2 - MousePosicao.x );
	verticalAngle   += mouseSpeed * float(sizeWindow.y / 2 - MousePosicao.y );

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle),cos(verticalAngle) * cos(horizontalAngle));
	
	// Right vector
	right = glm::vec3( sin(horizontalAngle - 3.14f/2.0f),  0, cos(horizontalAngle - 3.14f/2.0f) );
	
	// Up vector
	up = glm::cross( right, direction );


	// Move forward
	if(Keyboard::isKeyPressed(Keyboard::W)) position += direction * deltaTime * speed;
	if(Keyboard::isKeyPressed(Keyboard::S)) position -= direction * deltaTime * speed;
	if(Keyboard::isKeyPressed(Keyboard::A)) position -= right * deltaTime * speed;
	if(Keyboard::isKeyPressed(Keyboard::D)) position += right * deltaTime * speed;

	if(Keyboard::isKeyPressed(Keyboard::Space)) position += up * deltaTime * speed;
	if(Keyboard::isKeyPressed(Keyboard::C)) 	position -= up * deltaTime * speed;

	if(Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::LShift)) position += direction * deltaTime * (speed * 7);
	if(Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::LShift)) position -= direction * deltaTime * (speed * 7);
	
	if(event.type == sf::Event::MouseWheelScrolled)
	{	
		if(event.mouseWheelScroll.delta ==  1 && FoV >= 11) 
			FoV -= 1.0;
		if(event.mouseWheelScroll.delta == -1 && FoV <= 59) 
			FoV += 1.0;
	}
	

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), sizeWindow.x / (float)sizeWindow.y , 0.1f, 600.0f);

	// Camera matrix
	ViewMatrix = glm::lookAt( position, position+direction, up );
}