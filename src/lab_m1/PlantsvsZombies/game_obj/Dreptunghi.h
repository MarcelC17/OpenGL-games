#include "components/simple_scene.h"

class Dreptunghi
{ 
    public: 
    float width = 60, height=470;
    glm::vec3 corner = glm::vec3(20,20,0);

    Mesh* create(
    const std::string &name,
    glm::vec3 color,
    bool fill)
    {
    
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(width, 0, 0), color),
            VertexFormat(corner + glm::vec3(width, height, 0), color),
            VertexFormat(corner + glm::vec3(0, height, 0), color)
        };

        Mesh* square = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2, 3 };

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
        } else {
            // Draw 2 triangles. Add the remaining 2 indices
            indices.push_back(0);
            indices.push_back(2);
        }

        square->InitFromData(vertices, indices);
        return square;
    }

    void set_default(){
        width = 60;
        height = 470;
    }

}; 