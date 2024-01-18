#include "components/simple_scene.h"


class Inima{
    public:
    float radius = 3.7;
    int segments = 50;

Mesh* create(
    const std::string &name,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;    

    for (int i = 0; i < segments; ++i) {
        float theta = glm::radians(static_cast<float>(i) / static_cast<float>(segments) * 360.0f);

        float x = radius * (16 * glm::sin(theta) * glm::sin(theta) * glm::sin(theta));
        float y = radius * (13 * glm::cos(theta) - 5 * glm::cos(2 * theta) - 2 * glm::cos(3 * theta) - glm::cos(4 * theta));

        vertices.push_back(VertexFormat(glm::vec3(x, y, 0.0f), color));
    }

    if (fill) {
        for (int i = 1; i < segments - 1; ++i) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
    }

    Mesh* heart = new Mesh(name);
    heart->SetDrawMode(fill ? GL_TRIANGLES : GL_LINE_LOOP);
    heart->InitFromData(vertices, indices);

    return heart;
}
};
