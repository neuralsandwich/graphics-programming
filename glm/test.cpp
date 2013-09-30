#include <iostream>
#include <glm/glm.hpp>

int main(void) {
        // Create a 3D vector by adding two vectors together
        glm::vec3 v = glm::vec3(10.0, 20.0f, 30.0f)
                                + glm::vec3(10.0f, 15.0f, 20.0f);
        // Output the result
        std::cout << "X: " << v.x
                          << " Y: " << v.y
                          << " Z: " << v.z << std::endl;
}
