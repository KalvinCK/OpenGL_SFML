#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera
{
private:
    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;

    float speed = 10.0f;
    float mouseSpeed = 0.002f;

    float FoV = 60.0f;
    
    Clock time;
    
public:

    vec3 position = vec3( 0, 0, 5 );

    mat4 ViewMatrix;
    mat4 ProjectionMatrix;

    // Right vector
	vec3 right;
    // Up vector
    vec3 up;

    void MovingUpdate(Vector2i sizeWindow, sf::Event & event);

};

#endif