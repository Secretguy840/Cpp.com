#include <vector>
#include <memory>

class PhysicsEngine {
    struct RigidBody {
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 force;
        float mass;
        // Collider, etc...
    };

    std::vector<std::unique_ptr<RigidBody>> bodies;
    glm::vec3 gravity{0.0f, -9.81f, 0.0f};

public:
    void addBody(std::unique_ptr<RigidBody> body) {
        bodies.push_back(std::move(body));
    }

    void update(float dt) {
        // Apply forces
        for (auto& body : bodies) {
            body->force += gravity * body->mass;
        }

        // Integrate
        for (auto& body : bodies) {
            body->velocity += body->force / body->mass * dt;
            body->position += body->velocity * dt;
            body->force = glm::vec3(0.0f);
        }

        // Collision detection
        detectCollisions();
    }

private:
    void detectCollisions() {
        // Broad phase
        // Narrow phase
        // Resolution
    }
};
