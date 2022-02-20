#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

class camera
{
public:

    /**
     * @param pos    position of camera
     * @param target normalized direction the camera is looking
     * @param up     what direction is "up" to the camera
     */
    camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up);

    /**
     * @brief Get the view matrix
     * @return glm::mat4 
     */
    glm::mat4 get_view() const;

    /**
     * @brief Get the camera's position
     * @return glm::vec3 position relative to world
     */
    glm::vec3 get_pos() const;

    /**
     * @brief Get the direction the camera is looking
     * @return glm::vec3 normalized direction
     */
    glm::vec3 get_target() const;

    /**
     * @brief Get what direction is up for the camera
     * @return glm::vec3 normalized direction
     */
    glm::vec3 get_up() const;

    /**
     * @brief Update the camera's position
     * @param pos glm::vec3 position relative to world
     */
    void set_pos(glm::vec3 pos);

    /**
     * @brief Update what direction the camera is looking
     * @param target normalized direction
     */
    void set_target(glm::vec3 target);

    /**
     * @brief set what direction is up for the camera
     * @param up normalized direction
    */
    void set_up(glm::vec3 up);

    /**
     * @brief rotate the camera using euler angles
     * 
     * @param pitch angle (radians)
     * @param yaw   angle (radians)
     * @param roll  angle (radians)
     */
    void rotate(float pitch, float yaw, float roll);

protected:

    glm::vec3 pos_;
    glm::vec3 target_;
    glm::vec3 up_;


};

#endif