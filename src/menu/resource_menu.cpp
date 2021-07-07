#include "resource_menu.h"

ResourceEntry::ResourceEntry(float x, float y, float width, float height)
    : x{x}, y{y}, width{width}, height{height}, resource_count{0}, resource{Resource::BEECH_LOG} {
        std::vector<float> vertices{{
            x, y,
            x + width, y,
            x, y + height,
            x + width, y + height
        }};

        std::vector<unsigned int> indices{{
            0, 1, 2,
            1, 2, 3
        }};

        std::vector<float> color{{
            0.7, 0.7, 0.7, 0.4,
            0.7, 0.7, 0.7, 0.4,
            0.7, 0.7, 0.7, 0.4,
            0.7, 0.7, 0.7, 0.4
        }};

        this->background = std::move(rendering::mesh::create_with_color(GL_STATIC_DRAW, 2, vertices, indices, color));
}

void ResourceEntry::render(utils::registry<rendering::shader_program>* shader_registry, utils::registry<rendering::font>* font_registry) {
    shader_registry->get("overlay_shader").use();
    this->background.draw();

    shader_registry->get("font_shader").use();
    vec2<float> text_dimensions = font_registry->get("example_font").get_string_render_bounds("Resource name here " + std::to_string(this->resource_count), 0.5f);
    font_registry->get("example_font").draw_string("Resource name here " + std::to_string(this->resource_count), 0.5f, vec4<float>{0.78f, 0.29f, 0.44f, 1.0f}, vec3<float>{this->x + (this->width - text_dimensions.x) / 2, this->y + (this->height + text_dimensions.y) / 2});
}



ResourceMenu::ResourceMenu(const int width, const int height): resource_entries{}, scroll{0}, visible{false} {
    int index = 0;
    for (int resource_int = Resource::BEECH_LOG; resource_int != Resource::MAX; resource_int++) {
        Resource resource = static_cast<Resource>(resource_int);

        ResourceEntry entry{120, 100 * (float)index + 20, (float)width - 240, 80};
        entry.resource = resource;
        this->resource_entries.push_back(std::move(entry));

        index += 1;
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
        this->MARGIN_LEFT_RIGHT, 0,
        w - this->MARGIN_LEFT_RIGHT, 0,
        this->MARGIN_LEFT_RIGHT, h,
        w - this->MARGIN_LEFT_RIGHT, h
    }};

    std::vector<unsigned int> indices{{
        0, 1, 2,
        1, 2, 3
    }};

        std::vector<float> color{{
            0.7, 0.7, 0.7, 0.4,
            0.7, 0.7, 0.7, 0.4,
            0.7, 0.7, 0.7, 0.4,
            0.7, 0.7, 0.7, 0.4
        }};

   this->background = std::move(rendering::mesh::create_with_color(GL_STATIC_DRAW, 2, vertices, indices, color));
}

void ResourceMenu::render() {
    if (this->visible) {
        this->background.draw();

        for (ResourceEntry& r_entry : this->resource_entries) {
            r_entry.render(this->shader_registry, this->font_registry);
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