#include "components/simple_scene.h"

class Cerc
{ 
    public: 
    float radius = 40, vCount=50;
    

    Mesh* create(
    const std::string &name,
    glm::vec3 color,
    bool fill)
    {
        
        std::vector<VertexFormat> vertices;
        float angle = 360.0f / vCount;

        int triangleCount = vCount - 2;
        for (int i = 0; i < vCount; i++)
        {
            float currentAngle = angle * i;
            float x = radius * cos(glm::radians(currentAngle));
            float y = radius * sin(glm::radians(currentAngle));
            float z = 0.0f;

           vertices.push_back(VertexFormat(glm::vec3(x, y, z), color));
        }

        Mesh* circle = new Mesh(name);
        std::vector<unsigned int> indices;
        for (int i = 0; i < triangleCount; i++)
            {
                indices.push_back(0);
                indices.push_back(i + 1);
                indices.push_back(i + 2);
            }

       

        if (!fill) {
            circle->SetDrawMode(GL_LINE_LOOP);
        }
        
        circle->InitFromData(vertices, indices);
        return circle;
    }

}; 