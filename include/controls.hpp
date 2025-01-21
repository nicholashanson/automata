#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <camera.hpp>
#include <map>
#include <functional>

namespace conway {

    std::map<int, std::function<void()>> controls = {
        { KEY_LEFT, move_camera_left },
        { KEY_RIGHT, move_camera_right },
        { KEY_DOWN, move_camera_down },
        { KEY_UP, move_camera_up }
    };

    void handle_controls() {
        for ( const auto& [ key, action ] : controls ) {
            if ( IsKeyDown( key ) ) {
                action();
            }
        }
    }

}

#endif
