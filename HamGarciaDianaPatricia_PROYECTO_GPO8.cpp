#include <iostream>
#include <cmath>

// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

//For Keyboard
float	movX = 0.0f;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );
void animacion();

// Camera
Camera camera( glm::vec3( 0.0f, 2.0f, 32.0f ));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;
//GLfloat lastX = 400, lastY = 300;

// Animación
glm::vec3 PosIni(0.0f, 0.0f, 0.0f);
float movKitZ = 0.0;
float movKitZ2 = 0.0;
float movKitZ3 = 0.0;

bool cajon = false;
bool silla = false;
bool pastel = false;

bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = true;
bool recorrido4 = false;
bool recorrido5 = true;
bool recorrido6 = false;

// Delta time
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );

    // Load models

    //Modelos para el escenario e interior
    Model ourModel1((char*)"Models/proyecto/mitadprimera.obj");
    Model ourModel2((char*)"Models/proyecto/mitadsegunda.obj");
    Model ourModel3((char*)"Models/proyecto/cuarto.obj");
    Model ourModel4((char*)"Models/proyecto/detallitos.obj");
    
    //Modelos para objetos y muebles
    Model ourModel5((char*)"Models/proyecto/muebles.obj");
    Model ourModel6((char*)"Models/proyecto/armario.obj");
    Model ourModel7((char*)"Models/proyecto/piedra.obj");
    Model ourModel8((char*)"Models/proyecto/silla.obj");
    Model ourModel9((char*)"Models/proyecto/cajon.obj");
    Model ourModel10((char*)"Models/proyecto/pastel.obj");
    Model ourModel11((char*)"Models/proyecto/llave.obj");


    // Draw in wireframe
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
    // Game loop
    while( !glfwWindowShouldClose( window ) )
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime( );
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Check and call events
        glfwPollEvents( );
        DoMovement( );
        animacion();
        
        // Clear the colorbuffer
        glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        shader.Use( );
        
        glm::mat4 view = camera.GetViewMatrix();

        glUniformMatrix4fv( glGetUniformLocation( shader.Program, "projection" ), 1, GL_FALSE, glm::value_ptr( projection ) );
        glUniformMatrix4fv( glGetUniformLocation( shader.Program, "view" ), 1, GL_FALSE, glm::value_ptr( view ) );
        
        // Draw the loaded models

        glm::mat4 model1(1);
        model1 = glm::scale(model1, glm::vec3(4.0f, 4.0f, 4.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model1));
        ourModel1.Draw(shader);

        glm::mat4 model2(1);
        model2 = glm::scale(model2, glm::vec3(4.0f, 4.0f, 4.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model2));
        ourModel2.Draw(shader);

        glm::mat4 model3(1); 
        model3 = glm::scale(model3, glm::vec3(4.0f, 4.0f, 4.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model3));
        ourModel3.Draw(shader);

        glm::mat4 model4(1);
        model4 = glm::scale(model4, glm::vec3(4.0f, 4.0f, 4.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model4));
        ourModel4.Draw(shader);

        glm::mat4 model5(1);
        model5 = glm::scale(model5, glm::vec3(4.0f, 4.0f, 4.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model5));
        ourModel5.Draw(shader); 

        glm::mat4 model6(1);
        model6 = glm::scale(model6, glm::vec3(4.0f, 4.0f, 4.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model6));
        ourModel6.Draw(shader);

        glm::mat4 model7(1);
        model7 = glm::scale(model7, glm::vec3(4.0f, 4.0f, 4.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model7));
        ourModel7.Draw(shader);

        //Silla
        glm::mat4 model8(1);
        model8 = glm::scale(model8, glm::vec3(4.0f, 4.0f, 4.0f));
        model8 = glm::translate( model8, glm::vec3(0.0f, 0.0f, movKitZ2) );
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model8));
        ourModel8.Draw(shader);

        //Cajon
        glm::mat4 model9(1);
        model9 = glm::scale(model9, glm::vec3(4.0f, 4.0f, 4.0f));
        model9 = glm::translate( model9, glm::vec3(0.0f, 0.0f, movKitZ ) );
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model9));
        ourModel9.Draw(shader);

        //Pastel
        glm::mat4 model10(1);
        model10 = glm::scale(model10, glm::vec3(4.0f, 4.0f, 4.0f));
        model10 = glm::translate( model10, glm::vec3(0.0f, 0.0f, movKitZ3) );
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model10));
        ourModel10.Draw(shader);

        glm::mat4 model11(1);
        model11 = glm::scale(model11, glm::vec3(4.0f, 4.0f, 4.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model11));
        ourModel11.Draw(shader);


        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement( )
{

    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
    if (keys[GLFW_KEY_1])
    {
        cajon = true;
    }
    if (keys[GLFW_KEY_2])
    {
        cajon = false;
    }
    if (keys[GLFW_KEY_3])
    {
        silla = true;
    }
    if (keys[GLFW_KEY_4])
    {
        silla = false;
    }
    if (keys[GLFW_KEY_5])
    {
        pastel = true;
    }
    if (keys[GLFW_KEY_6])
    {
        pastel = false;
    }

}

void animacion()
{

    //Movimiento del cajón
    if (cajon)
    {
        movKitZ = 0;
        if (recorrido1)
        {
            movKitZ -= 0.4f;
            if (movKitZ > -5.0f)
            {
                recorrido1 = false;
                recorrido2 = true;
            }
        }
        if (recorrido2)
        {
            movKitZ += 0.35f;
            if (movKitZ > 0.0f)
            {
                recorrido2 = false;
                recorrido1 = true;

            }
        }
    }

    //Movimiento de silla
    if (silla)
    {
        movKitZ2 = 0;
        if (recorrido3)
        {
            movKitZ2 -= 0.4f;
            if (movKitZ2 > -5.0f)
            {
                recorrido3 = false;
                recorrido4 = true;
            }
        }
        if (recorrido4)
        {
            movKitZ2 += 0.35f;
            if (movKitZ2 > 0.0f)
            {
                recorrido4 = false;
                recorrido3 = true;

            }
        }

    }

    //Movimiento de pastel
    if (pastel)
    {
        movKitZ = 0;
        if (recorrido5)
        {
            movKitZ3 -= 0.4f;
            if (movKitZ3 > -3.0f)
            {
                recorrido5 = false;
                recorrido6 = true;
            }
        }
        if (recorrido6)
        {
            movKitZ3 += 0.3f;
            if (movKitZ3 > -0.0f)
            {
                recorrido6 = false;
                recorrido5 = true;

            }
        }

    }

        
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }

    if (keys[GLFW_KEY_Y])
    {
        movX -= 5.0f;
        if (movX == -20.0f) {
            movX = 0.0f;
        }
    }

    if (keys[GLFW_KEY_T])
    {
        movX += 5.0f;
        if (movX == 5.0f) {
            movX = -15.0f;
        }
    }
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

