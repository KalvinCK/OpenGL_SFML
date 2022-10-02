#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
using namespace std;

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace sf;

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include <SOIL/SOIL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// inclui os modulos
#include "common/ShaderProgram.hpp"
#include "common/ImageProgram.hpp"
#include "common/Camera.hpp"
#include "common/LoadModel.hpp"
#include "common/Texto.hpp"

#include "Game/Movement.hpp"
#include "Game/BuffersRegistro.hpp"
#include "Game/CreateObject.hpp"
#include "Game/Outdoor.hpp"
#include "Game/RenderBuffer.hpp"
#include "Game/RenderSprite.hpp"
#include "Game/HUD.hpp"
#include "Game/SkyBox.hpp"
#include "Game/RenderBuffer.hpp"


void activeContextSettigs(ContextSettings & settings);
void InitGlew();

#define WIDTH 1600
#define HEIGHT 900

int main() {
    ContextSettings settings;
    activeContextSettigs(settings);

    Window window(VideoMode(WIDTH, HEIGHT), "OpenGL/SFML", Style::Default, settings);
    Image icon;
    icon.loadFromFile("resources/Icon_OpenGL.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    // window.setVerticalSyncEnabled(true);
    //...
    window.setActive(true);

    InitGlew();

    Mouse::setPosition(Vector2i(window.getSize().x / 2, window.getSize().y /2));
    window.setMouseCursorVisible(false);

    glEnable(GL_DEPTH_TEST);
    
    // ativa a opacidade nos shaders
    // glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ativa a correção de gama
    // glEnable(GL_FRAMEBUFFER_SRGB);

    glClearColor(0.16f, 0.16f, 0.18f, 1.0f);

    Camera camera;
    
    
    float Frames;
    Clock clock;

    while(window.isOpen())
    {
        Frames = 1.0 / clock.restart().asSeconds();
        
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(Keyboard::isKeyPressed(Keyboard::Escape)) 
                window.close();
            if(event.type == sf::Event::Closed) 
                window.close();
            if (event.type == sf::Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);

        }
        // draw...

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        window.display();
    }
    
    return EXIT_SUCCESS;
}
void InitGlew()
{
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
        cout << "Falha na inicialização" << endl;
        exit(1);
    }
}
void activeContextSettigs(ContextSettings & settings)
{
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4;
    settings.minorVersion = 6;
    settings.Core;
}