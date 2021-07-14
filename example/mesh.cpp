#include "events/event_handler.h"
#include "rendering/mesh.h"
#include "rendering/render_window.h"
#include "rendering/texture.h"

int main() {
    event::event_handler ev_handler{};

    rendering::render_window window{"Example", 600, 800, true, ev_handler};

    // These are the corners of your mesh
    std::vector<float> vertices{{
        0, 0,
        50, 0,
        0, 20,
        50, 20
    }};

    // The rectangle split into 2 triangles with following corners
	std::vector<unsigned int> indices{{
		0, 1, 2,
		1, 2, 3
	}};

    // The color for each vertex
    std::vector<float> color{{
        0, 1, 0, 1,
        0, 1, 0, 1,
        0, 1, 0, 1,
        0, 1, 0, 1
    }};

    // Creating a colored mesh
    rendering::mesh colored_mesh = std::move(rendering::mesh::create_with_color(GL_STATIC_DRAW, 2, vertices, indices, color));

    // The texture coords are simply the corners of your mesh
    std::vector<float> tex_coords{{
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
    }};

    // Load the texture
    rendering::texture texture = std::move(rendering::texture::load_from_file("texture.png", GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT, GL_RGBA));

    // Creating a textured mesh
    rendering::mesh textured_mesh = std::move(rendering::mesh::create_with_texture(GL_STATIC_DRAW, 2, vertices, indices, tex_coords));

    // Event loop
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	while(window.is_open()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // This method call draws the actual mesh
        colored_mesh.draw();

        // To draw a textured mesh you first have to tell the library to use a specific texture
        texture.use();
        textured_mesh.draw();

    	window.update();
	}

	glfwTerminate();

	return 0;
}