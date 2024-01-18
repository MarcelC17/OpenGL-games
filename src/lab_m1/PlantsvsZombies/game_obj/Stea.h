#include "components/simple_scene.h"

class Stea
{ 
    public:
    float scaled = 7, radius =17 * scaled;

    Mesh* create(
    const std::string &name,
    float scale,
    glm::vec3 color)
    {
    
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(glm::vec3(0, scale * 3.3, 0), color),
            VertexFormat(glm::vec3(scale * 2.6f,scale * 1.8f, 0), color),
            VertexFormat(glm::vec3(scale * 2, scale * -0.6, 0), color),
            VertexFormat(glm::vec3(scale * -2, scale * -0.6, 0), color),
            VertexFormat(glm::vec3(scale * -2.6f, scale * 1.8f, 0), color),
            VertexFormat(glm::vec3(scale * -1, scale * 0.5f, 0), color),
            VertexFormat(glm::vec3(scale * 1, scale * 0.5f, 0), color),
            VertexFormat(glm::vec3(0, scale * 0.35f, 0), color),
        };

        Mesh* star = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 2, 5, 0, 3, 6, 1, 4, 7};

        star->InitFromData(vertices, indices);
        return star;
    }

};