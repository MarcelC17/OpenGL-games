#include "components/simple_scene.h"

class Tun
{ 
    public: 
    float scale = 12;
    float height;
    float width;

    Mesh* create(
    const std::string &name,
    glm::vec3 color)
    {
    
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(glm::vec3(0, 0, 0), color),
            VertexFormat(glm::vec3(scale*2, scale*4, 0), color),
            VertexFormat(glm::vec3(scale*4, 0, 0), color),
            VertexFormat(glm::vec3(scale*2, scale*-4, 0), color),
            VertexFormat(glm::vec3(scale*2, scale*1, 0), color),
            VertexFormat(glm::vec3(scale*2, scale*-1, 0), color),
            VertexFormat(glm::vec3(scale*6, scale*1, 0), color),
            VertexFormat(glm::vec3(scale*6, scale*-1, 0), color),
        };

        height = scale*8;
        width = scale*6;


        Mesh* canon = new Mesh(name);
        std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3, 4, 6, 7, 5, 4, 7};

        canon->InitFromData(vertices, indices);
        return canon;
    }

};