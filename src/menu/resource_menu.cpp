#include "resource_menu.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <json.h>
#include <json_reader.h>

#include <fstream>
#include <iostream>

ResourceEntry::ResourceEntry(float x, float y, float width, float height, Resource resource)
    : x{x}, y{y}, width{width}, height{height}, resource_count{0}, resource{resource} {
        // load resource properties
        std::string filename = resource_files[resource];
        std::ifstream file;
        file.open("../res/data/" + filename);

        if (!file.is_open()) {std::cout << "File not found." << std::endl; return;}

        json::json_object obj = json::json_reader::next_object_from_stream(file);
        this->resource_name = obj.get_map()["name"].get_string();
        std::string icon_file = obj.get_map()["icon_file"].get_string();

        // load icon texture & mesh
        std::vector<float> vertices{{
            0, 0,
            40, 0,
            0, 40,
            40, 40
        }};

        std::vector<unsigned int> indices{{
            0, 1, 2,
            1, 2, 3
        }};

        std::vector<float> tex_coords{{
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f
        }};

        this->icon_mesh = std::move(rendering::mesh::create_with_texture(GL_STATIC_DRAW, 2, vertices, indices, tex_coords));
        this->icon = std::move(rendering::texture::load_from_file("../res/textures/" + icon_file, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT, GL_RGBA));

        file.close();
}

void ResourceEntry::render(utils::registry<rendering::shader_program>* shader_registry, utils::registry<rendering::font>* font_registry, int scroll_offset) {
    shader_registry->get("font_shader").use();

    vec2<float> text_dimensions = font_registry->get("example_font").get_string_render_bounds(this->resource_name, 0.5f);
    glm::mat4 text_pos{1.0f};
    text_pos = glm::translate(text_pos, glm::vec3{this->x + (this->width - text_dimensions.x) / 2, this->y + (this->height - text_dimensions.y) / 2 - scroll_offset, 0.0f});
    font_registry->get("example_font").draw_string(this->resource_name, 0.5f, vec4<float>{0.78f, 0.29f, 0.44f, 1.0f}, text_pos);

    vec2<float> count_dimensions = font_registry->get("example_font").get_string_render_bounds(std::to_string(this->resource_count), 0.5f);
    glm::mat4 count_pos{1.0f};
    count_pos = glm::translate(count_pos, glm::vec3{this->x + this->width - count_dimensions.x - 20, this->y + (this->height - count_dimensions.y) / 2 - scroll_offset, 0.0f});
    font_registry->get("example_font").draw_string(std::to_string(this->resource_count), 0.5f, vec4<float>{0.78f, 0.29f, 0.44f, 1.0f}, count_pos);

    shader_registry->get("overlay_shader").use();
    this->icon.use();
    glm::mat4 icon_pos{1.0f};
    icon_pos = glm::translate(icon_pos, glm::vec3{this->x + 20, this->y + 20 - scroll_offset, 0.0f});
    this->icon_mesh.draw(icon_pos);
}



ResourceMenu::ResourceMenu(const int width, const int height, std::map<std::string, int>* settings): resource_entries{}, scroll{0}, visible{false}, settings{settings} {
    unsigned int i = 0;
    for (int resource_int = Resource::BEECH_LOG; resource_int != Resource::MAX; resource_int++) {
        Resource resource = static_cast<Resource>(resource_int);

        ResourceEntry entry{120, height - 100 * (float)i - 100, (float)width - 240, 80, resource};
        this->resource_entries.push_back(std::move(entry));

        i += 1;
    }

    this->createBackground(width, height);
}

void ResourceMenu::addResources(Resource resource, unsigned int amount) {
    for (ResourceEntry& r_entry : this->resource_entries) {
        if (r_entry.resource == resource) {
            r_entry.resource_count += amount;
            return;
        }
    }
}

bool ResourceMenu::removeResources(Resource resource, unsigned int amount) {
    for (ResourceEntry& r_entry : this->resource_entries) {
        if (r_entry.resource == resource) {
            if (r_entry.resource_count >= amount) {
                r_entry.resource_count -= amount;
                return true;
            }
            break;
        }
    }
    return false;
}

bool ResourceMenu::hasResource(Resource resource, unsigned int amount) {
    for (ResourceEntry& r_entry : this->resource_entries) {
        if (r_entry.resource == resource) {
            if (r_entry.resource_count >= amount) {
                return true;
            }
            break;
        }
    }
    return false;
}

void ResourceMenu::createBackground(const int width, const int height) {
    float w = static_cast<float>(width);
    float h = static_cast<float>(height);

    std::vector<float> vertices{{
        ResourceMenu::MARGIN_LEFT_RIGHT, 0,
        w - ResourceMenu::MARGIN_LEFT_RIGHT, 0,
        ResourceMenu::MARGIN_LEFT_RIGHT, h,
        w - ResourceMenu::MARGIN_LEFT_RIGHT, h
    }};

    std::vector<float> entry_vertices{{
        0.0f, 0.0f,
        width - 240.0f, 0.0f,
        0.0f, 80.0f,
        width - 240.0f, 80.0f
    }};

    std::vector<unsigned int> indices{{
        0, 1, 2,
        1, 2, 3
    }};

    std::vector<float> color{{
        0.85, 0.7, 0.7, 0.4,
        0.7, 0.85, 0.7, 0.4,
        0.7, 0.7, 0.85, 0.4,
        0.85, 0.85, 0.7, 0.4
    }};

   this->background = std::move(rendering::mesh::create_with_color(GL_STATIC_DRAW, 2, vertices, indices, color));
   this->entry_background = std::move(rendering::mesh::create_with_color(GL_STATIC_DRAW, 2, entry_vertices, indices, color));
}

void ResourceMenu::render() {
    if (this->visible) {
        this->background.draw();

        for (ResourceEntry& r_entry : this->resource_entries) {
            shader_registry->get("overlay_shader").use();

            glm::mat4 offset{1.0f};
            offset = glm::translate(offset, glm::vec3{r_entry.x, r_entry.y - this->scroll, 0.0f});
            this->entry_background.draw(offset);

            r_entry.render(this->shader_registry, this->font_registry, this->scroll);
        }
    }
}

void ResourceMenu::setVisible(bool state) {
    this->visible = state;
}

bool ResourceMenu::isVisible() {
    return this->visible;
}

void ResourceMenu::set_shader_registry(utils::registry<rendering::shader_program>* shader_registry) {
    this->shader_registry = shader_registry;
}

void ResourceMenu::set_font_registry(utils::registry<rendering::font>* font_registry) {
    this->font_registry = font_registry;
}

void ResourceMenu::on_scroll(double offset) {
    this->scroll += offset * this->settings->at("scroll_speed");
}