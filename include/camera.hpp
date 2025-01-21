#include "raylib.h"
#include <settings.hpp>

namespace conway {

    Camera camera = { 0 };

    // angle between camera position and the positive x-axis
    float theta = 45.0f;
    // angle between camera position and the positive y-axis
    float phi = 45.0f;

    // straight line distance between camera and origin
    float r = sqrt( std::pow( settings::camera_x, 2 ) + std::pow( settings::camera_y, 2 ) + std::pow( settings::camera_z, 2 ) );

    void set_up_camera() {
        camera.position = Vector3{ settings::camera_x, settings::camera_y, settings::camera_z };
        camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
        camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
        // field of view
        camera.fovy = 20.0f;
        camera.projection = CAMERA_PERSPECTIVE;
    }

    void modify_camera_position() {
        // update camera position in three dimensions
        camera.position.x = r * sin( phi * DEG2RAD ) * cos( theta * DEG2RAD );
        camera.position.y = r * cos( phi * DEG2RAD );
        camera.position.z = r * sin( phi * DEG2RAD ) * sin( theta * DEG2RAD );
    }

    void move_camera_left() {
        // moving the camera left increases the size of theta
        theta = fmod( theta + 1.0f, 360.0f );
        modify_camera_position();
    }

    void move_camera_right() {
        // moving the camera right decreases the size of theta
        theta = fmod( theta - 1.0f, 360.0f );
        modify_camera_position();
    }

    void move_camera_up() {
        // moving the camera up decreases the size of phi
        phi = fmod( phi - 1.0f, 360.0f );
        modify_camera_position();
    }

    void move_camera_down() {
        // moving the camera down decrease the size of phi
        phi = fmod( phi + 1.0f, 360.0f );
        modify_camera_position();
    }

}
