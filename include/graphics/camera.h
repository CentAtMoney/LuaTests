#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class camera
{
public:

    /**
     * @param pos    position of camera
     * @param front  normalized direction the camera is looking
     * @param up     what direction is "up" to the camera
     */
    camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up);

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
     * @brief Get what direction the camera is looking
     * @return glm::vec3 normalized direction
     */
    glm::vec3 get_front() const;

    /**
     * @brief Get what direction is up for the camera
     * @return glm::vec3 normalized direction
     */
    glm::vec3 get_up() const;

    /**
     * @brief get what the camera is looking at
     * @return glm::vec3 
     */
    glm::vec3 get_target() const;

    /**
     * @brief get the direction to the right of the camera
     * @return glm::vec3 
     */
    glm::vec3 get_right() const;

    /**
     * @brief Update the camera's position
     * @param pos glm::vec3 position relative to world
     */
    void set_pos(glm::vec3 pos);

    /**
     * @brief update what is front to the camera
     * @param front normalized direction
     */
    void set_front(glm::vec3 front);

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

    /**
     * @brief move the camera by a specified amount
     * 
     * @param dx change in pos
     */
    void move(glm::vec3 dx);


protected:

    glm::vec3 pos_;
    glm::vec3 up_;
    glm::vec3 front_;

};

#endif