#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Primitives.h"

Diamond::Diamond(unsigned int totalHexahedrons)
{
    _total = totalHexahedrons;
}

void Diamond::FillBuffers()
{
    glm::vec3 points[] =
        {
            glm::vec3(-0.5f, +0.0f, +0.5f), // 1
            glm::vec3(-0.5f, +0.0f, -0.5f), // 2
            glm::vec3(+0.5f, +0.0f, -0.5f), // 3
            glm::vec3(+0.5f, +0.0f, +0.5f), // 4
            glm::vec3(+0.0f, +1.0f, +0.0f), // 5 pico superior
            glm::vec3(+0.0f, -1.0f, +0.0f), // 6 pico inferior

        };

    glm::vec3 vertices[] =
        {
            // piramide superior
            // lado 1
            points[4],
            points[0],
            points[1],

            // lado 2
            points[4],
            points[3],
            points[0],

            // lado3
            points[4],
            points[3],
            points[2],

            // lado 4,
            points[4],
            points[2],
            points[1],

            // base
            points[0],
            points[1],
            points[2],
            points[3],

            // piramide inferior
            // lado 1
            points[5],
            points[0],
            points[1],

            // lado 2
            points[5],
            points[3],
            points[0],

            // lado3
            points[5],
            points[3],
            points[2],

            // lado 4,
            points[5],
            points[1],
            points[2],

        };

    GLubyte colors[] =
    {
        //Front Red
       255, 0, 0,
       255, 0, 0,
       255, 0, 0,
       
       //Right Green
       0, 255, 0,
       0, 255, 0,
       0, 255, 0,
       
       //Left Blue
       0, 0, 255,
       0, 0, 255,
       0, 0, 255,

       //Back Yellow
       255, 255, 0,
       255, 255, 0,
       255, 255, 0,

       //Bottom Cyan
        0, 255, 255,
        0, 255, 255,
        0, 255, 255, 
        0, 255, 255,

        //Front Red
       255, 0, 0,
       255, 0, 0,
       255, 0, 0,
       
       //Right Green
       0, 255, 0,
       0, 255, 0,
       0, 255, 0,
       
       //Left Blue
       0, 0, 255,
       0, 0, 255,
       0, 0, 255,

       //Back Yellow
       255, 255, 0,
       255, 255, 0,
       255, 255, 0,
    };

    unsigned int indices[] =
        {
            // l1
            0, 1, 2,

            // l2
            3, 4, 5,

            // l3
            6, 7, 8,

            // l4
            9, 10, 11,

            // base
            // 12, 13, 14,
            // 12, 14, 15,

            // -l1
            16, 17, 18,

            // -l2
            19, 20, 21,

            // -l3
            22, 23, 24,

            // -l4
            25, 26, 27,

        };

    // Fill with indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Fill with vertices
    glBindBuffer(GL_ARRAY_BUFFER, _positionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Fill with colors
    glBindBuffer(GL_ARRAY_BUFFER, _colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // Create empty model Buffer
    glBindBuffer(GL_ARRAY_BUFFER, _modelVBO);
    glBufferData(GL_ARRAY_BUFFER, _total * sizeof(glm::mat4), 0, GL_DYNAMIC_DRAW);
}

void Diamond::LinkBuffers()
{
    glBindVertexArray(_VAO);
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

        glBindBuffer(GL_ARRAY_BUFFER, _positionVBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

        glBindBuffer(GL_ARRAY_BUFFER, _colorVBO);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 3 * sizeof(GLubyte), 0);

        glBindBuffer(GL_ARRAY_BUFFER, _modelVBO);
        {
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4) * 0));

            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4) * 1));

            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4) * 2));

            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4) * 3));

            glVertexAttribDivisor(2, 1);
            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
        }
    }
    glBindVertexArray(0);
}

void Diamond::Draw()
{
    glBindVertexArray(_VAO);
    {
        glDrawElementsInstanced(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0, _total);
    }
    glBindVertexArray(0);
}
