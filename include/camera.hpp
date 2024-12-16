#include "raylib.h"
#include <settings.hpp>

namespace conway {

    Camera camera = { 0 };

    float theta = 45.0f;
    float phi = 45.0f;

    float r = sqrt( std::pow( settings::camera_x, 2 ) + std::pow( settings::camera_y, 2 ) + std::pow( settings::camera_z, 2 ) );

    void set_up_camera() {
        camera.position = Vector3{ settings::camera_x, settings::camera_y, settings::camera_z };
        camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
        camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
        camera.fovy = 20.0f;
        camera.projection = CAMERA_PERSPECTIVE;
    }

    void modify_camera_position() {
        camera.position.x = r * sin( phi * DEG2RAD ) * cos( theta * DEG2RAD );
        camera.position.y = r * cos( phi * DEG2RAD );
        camera.position.z = r * sin( phi * DEG2RAD ) * sin( theta * DEG2RAD );
    }

    void move_camera_left() {
        theta = fmod( theta + 1.0f, 360.0f );
        modify_camera_position();
    }

    void move_camera_right() {
        theta = fmod( theta - 1.0f, 360.0f );
        modify_camera_position();
    }

    void move_camera_up() {
        phi = fmod( phi - 1.0f, 360.0f );
        modify_camera_position();
    }

    void move_camera_down() {
        phi = fmod( phi + 1.0f, 360.0f );
        modify_camera_position();
    }

}
