#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<random>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Error.h"
#include"Shader.h"
#include"Primitives.h"
#include"Camera.h"

GLFWwindow* window;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const unsigned int TOTAL_CUBES = 4;
const unsigned int TOTAL_PYRAMIDS = 4;
const unsigned int TOTAL_RECTANGLES = 4;
const unsigned int TOTAL_DIAMONDS = 6;

Camera camera;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

float randomFloat()
{
    // Use a random device to seed the random number generator
    std::random_device rd;

    // Use the random device to generate a random seed for the engine
    std::default_random_engine engine(rd());

    // Define the distribution for float values between 0 and 10
    std::uniform_real_distribution<float> distribution(-20.0f, 20.0f);

    // Generate a random float
    float randomFloat = distribution(engine);

    return randomFloat;
}


void initOpenGL()
{

    glfwInit();
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "3D Cube", NULL, NULL);
    if (!window)
    {
        fatalError("GLFW Window could not be created!");
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}


int main()
{

    initOpenGL();

    //Model Matrix  with Frequent Changes
    Shader mainShader("Main.vert", "Main.frag");
    mainShader.CreateShaders();

    //Model Matrix  with Minor Changes
    Shader minorShader("Minor.vert", "Main.frag");
    minorShader.CreateShaders();

    Cube cube(TOTAL_CUBES);
    cube.Create();

    Pyramid pyramid(TOTAL_PYRAMIDS);
    pyramid.Create();

    Rectangle rectangle(TOTAL_RECTANGLES);
    rectangle.Create();

    Terrain terrain;
    terrain.Create();

    float aspectRatio = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;
    glm::mat4 projection = glm::perspective(glm::radians(45.f), aspectRatio, 0.1f, 500.f);
    //glm::mat4 minorModel = glm::mat4(1.f);

    mainShader.Bind();
    mainShader.SendUniformData("projection", projection);
    mainShader.Unbind();

    minorShader.Bind();
    minorShader.SendUniformData("projection", projection);
    minorShader.SendUniformData("model", glm::mat4(1.f));
    minorShader.Unbind();

    Diamond diamond(TOTAL_DIAMONDS);
    diamond.Create();

    glm::mat4 cubeModels[TOTAL_CUBES] = {};
    glm::mat4 pyramidModels[TOTAL_PYRAMIDS] = {};

    glm::mat4 rectangleModels[TOTAL_RECTANGLES] = {};
    glm::mat4 diamondModels[TOTAL_DIAMONDS] = {};


    // Position Matrix
    glm::mat4 cubesPosMatrix[TOTAL_CUBES] =
    {
      glm::translate(glm::vec3(2.0f, 3.f, -15.f)),
      glm::translate(glm::vec3(4.0f, 0.5f, -15.f)),
      glm::translate(glm::vec3(6.0f, 5.f, -20.f)),
      glm::translate(glm::vec3(8.0f, 6.f, -20.f))
    };

    glm::mat4 pyramidsPosMatrix[TOTAL_PYRAMIDS] =
    {
      glm::translate(glm::vec3(-4.5f, 2.5f, -25.f)),
      glm::translate(glm::vec3(-2.5f, 3.5f, -25.f)),
      glm::translate(glm::vec3(-4.5f, 1.f, -10.f)),
      glm::translate(glm::vec3(-3.5f, 4.f, -15.f))
    };

    //OS RETANGULOS ESTAO ATRAS DA CAMERA, PRECISA GIRAR COM O MOUSE PRA ENXERGAR

    glm::mat4 rectanglesPosMatrix[TOTAL_RECTANGLES] =
    {
      glm::translate(glm::vec3(3.f + randomFloat(), 4.f, 15.f)),
      glm::translate(glm::vec3(6.f + randomFloat(), 3.5f, 15.f)),
      glm::translate(glm::vec3(-6.f + randomFloat(), 3.f, 15.f)),
      glm::translate(glm::vec3(-3.f + randomFloat(), 5.2f, 15.f))
    };

    glm::mat4 diamondPosMatrix[TOTAL_DIAMONDS] =
    {
      glm::translate(glm::vec3(10.0f, 0.f, 5.f)),
      glm::translate(glm::vec3(randomFloat(), randomFloat(), randomFloat())),
      glm::translate(glm::vec3(randomFloat(), randomFloat(), randomFloat())),
      glm::translate(glm::vec3(randomFloat(), randomFloat(), randomFloat())),
      glm::translate(glm::vec3(randomFloat(), randomFloat(), randomFloat())),
      glm::translate(glm::vec3(randomFloat(), randomFloat(), randomFloat())),
    };



    //Angular Speed - Axis X, Y and Z
    glm::vec3 cubeAngSpeed[TOTAL_CUBES] =
    {
        glm::vec3(-1.75f, +0.75f, -2.75f),
        glm::vec3(+0.75f, -3.75f, +1.75f),
        glm::vec3(+1.50f, +0.50f, +2.35f),
        glm::vec3(-1.75f, +0.75f, -3.75f)
    };

    glm::vec3 pyramidAngSpeed[TOTAL_PYRAMIDS] =
    {
        glm::vec3(-0.55f, -2.60f, +0.40f),
        glm::vec3(+0.50f, +1.75f, -0.42f),
        glm::vec3(+0.70f, +2.30f, -0.80f),
        glm::vec3(+0.80f, -3.52f, +0.52f)
    };

    glm::vec3 rectangleAngSpeed[TOTAL_RECTANGLES] =
    {
        glm::vec3(-0.55f, -2.60f, +0.40f),
        glm::vec3(+0.50f, +1.75f, -0.42f),
        glm::vec3(+0.70f, +2.30f, -0.80f),
        glm::vec3(+0.80f, -3.52f, +0.52f)
    };

    glm::vec3 diamondAngSpeed[TOTAL_DIAMONDS] =
    {
        glm::vec3(-0.55f, -2.60f, +0.40f),
        glm::vec3(+0.50f, +1.75f, -0.42f),
        glm::vec3(+0.70f, +2.30f, -0.80f),
        glm::vec3(+0.80f, -3.52f, +0.52f),
        glm::vec3(+0.70f, +2.30f, -0.80f),
        glm::vec3(+0.80f, -3.52f, +0.52f)
    };


    unsigned int cubeModelVBO = cube.GetModelVBO();
    unsigned int pyramidModelVBO = pyramid.GetModelVBO();
    unsigned int rectangleModelVBO = rectangle.GetModelVBO();
    unsigned int diamondModelVBO = diamond.GetModelVBO();

    float startTime = (float)glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {

        float currentTime = (float)glfwGetTime();
        float dt = currentTime - startTime;

        glm::mat4 viewMatrix = camera.ativar();



        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Terrain Render
        {

            minorShader.Bind();
            minorShader.SendUniformData("view", viewMatrix);
            terrain.Draw();
            minorShader.Unbind();
        }

        mainShader.Bind();
        {
            mainShader.SendUniformData("view", viewMatrix);
            //Cube 
            {
                for (unsigned int i = 0; i < TOTAL_CUBES; i++)
                {
                    cubeModels[i] = glm::rotate(cubeAngSpeed[i].x * dt, glm::vec3(1.f, 0.f, 0.f));
                    cubeModels[i] = glm::rotate(cubeModels[i], cubeAngSpeed[i].y * dt, glm::vec3(0.f, 1.f, 0.f));
                    cubeModels[i] = cubesPosMatrix[i] * glm::rotate(cubeModels[i], cubeAngSpeed[i].z * dt, glm::vec3(0.f, 0.f, 1.f));
                }

                // Update Matrix Buffer
                glBindBuffer(GL_ARRAY_BUFFER, cubeModelVBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubeModels), cubeModels);


                cube.Draw();

            }

            //Pyramid 
            {
                for (unsigned int i = 0; i < TOTAL_PYRAMIDS; i++)
                {
                    pyramidModels[i] = glm::rotate(pyramidAngSpeed[i].x * dt, glm::vec3(1.f, 0.f, 0.f));
                    pyramidModels[i] = glm::rotate(pyramidModels[i], pyramidAngSpeed[i].y * dt, glm::vec3(0.f, 1.f, 0.f));
                    pyramidModels[i] = pyramidsPosMatrix[i] * glm::rotate(pyramidModels[i], pyramidAngSpeed[i].z * dt, glm::vec3(0.f, 0.f, 1.f));
                }

                // Update Matrix Buffer
                glBindBuffer(GL_ARRAY_BUFFER, pyramidModelVBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pyramidModels), pyramidModels);

                pyramid.Draw();
            }

            //Rectangle 
            {
                for (unsigned int i = 0; i < TOTAL_RECTANGLES; i++)
                {
                    rectangleModels[i] = glm::rotate(rectangleAngSpeed[i].x * dt, glm::vec3(1.f, 0.f, 0.f));
                    rectangleModels[i] = glm::rotate(rectangleModels[i], rectangleAngSpeed[i].y * dt, glm::vec3(0.f, 1.f, 0.f));
                    rectangleModels[i] = rectanglesPosMatrix[i] * glm::rotate(rectangleModels[i], rectangleAngSpeed[i].z * dt, glm::vec3(0.f, 0.f, 1.f));
                }

                // Update Matrix Buffer
                glBindBuffer(GL_ARRAY_BUFFER, rectangleModelVBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rectangleModels), rectangleModels);

                rectangle.Draw();
            }

            //Pentahedron 
            {
                for (unsigned int i = 0; i < TOTAL_DIAMONDS; i++)
                {
                    diamondModels[i] = glm::rotate(diamondAngSpeed[i].x * dt, glm::vec3(1.f, 0.f, 0.f));
                    diamondModels[i] = glm::rotate(diamondModels[i], diamondAngSpeed[i].y * dt, glm::vec3(0.f, 1.f, 0.f));
                    diamondModels[i] = diamondPosMatrix[i] * glm::rotate(diamondModels[i], diamondAngSpeed[i].z * dt, glm::vec3(0.f, 0.f, 1.f));
                }

                // Update Matrix Buffer
                glBindBuffer(GL_ARRAY_BUFFER, diamondModelVBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(diamondModels), diamondModels);

                diamond.Draw();
            }

        }

        mainShader.Unbind();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        // Forward
        camera.moveForward();
    }
    else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        // Back
        camera.moveBack();

    }
    else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        // Left
        camera.moveLeft();

    }
    else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        // Right
        camera.moveRight();
    }

}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    camera.mouseUpdate(glm::vec2(xpos, ypos));
}