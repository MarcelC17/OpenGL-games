#include "components/simple_scene.h"

class Hexagon
{ 
    public: 
    float radius = 30;
    

    Mesh* create(
    const std::string &name,
    float scale1,
    glm::vec3 color1)
    {
    
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(glm::vec3(0, 0, 0), color1),
            VertexFormat(glm::vec3(scale1 * -0.5f, scale1*  1, 0), color1),
            VertexFormat(glm::vec3(scale1 *  0.5f, scale1*  1, 0), color1),
            VertexFormat(glm::vec3(scale1 * 1,  0, 0), color1),
            VertexFormat(glm::vec3(scale1 * 0.5f,  scale1* -1, 0), color1),
            VertexFormat(glm::vec3(scale1 * -0.5f, scale1* -1, 0), color1),
            VertexFormat(glm::vec3(scale1 * -1,0, 0), color1),

        };
 
        Mesh* Hexagon = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2, 0, 3, 4, 0, 5, 6, 0, 2, 3, 0, 4, 5, 0, 1,6};

        Hexagon->InitFromData(vertices, indices);
        return Hexagon;
    }

};