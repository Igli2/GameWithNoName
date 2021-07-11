#pragma once

#include <glm/glm.hpp>

namespace rendering {
    enum render_mode {
        RENDER_2D,
        RENDER_3D
    };

    class camera {
    private:
        glm::mat4 view_mat;
        glm::mat4 projection_2D;
        glm::mat4 projection_3D;

        render_mode mode;

        void update_3D_perspective();
        void update_2D_perspective();
    public:
        camera(const render_mode initial_mode);
        render_mode get_current_render_mode();
        void set_render_mode(const render_mode mode);
        void set_view_matrix(const glm::mat4& view_mat);
        void set_2D_projection_matrix(const glm::mat4& proj_mat);
        void set_3D_projection_matrix(const glm::mat4& proj_mat);
        void update_render_perspective();
        ~camera();
    };
}