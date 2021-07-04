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

        this->background = std::move(rendering::mesh::create(GL_STATIC_DRAW, 2, vertices, indices));
}

void ResourceEntry::render() {
    this->background.draw();
}



ResourceMenu::ResourceMenu(const int width, const int height): resource_entries{}, scroll{0} {
    int index = 0;
    for (int resource_int = Resource::BEECH_LOG; resource_int != Resource::MAX; resource_int++) {
        Resource resource = static_cast<Resource>(resource_int);

        ResourceEntry entry{120, 100 * (float)index + 20, (float)width - 240, 80};
        entry.resource = resource;
        this->resource_entries.push_back(std::move(entry));

        index += 1;
    }

    this->background_texture = rendering::texture::load_from_file("../res/textures/menu_background.png", GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT, GL_RGBA);
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

    std::vector<float> tex_coords{{
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	}};

   this->background = std::move(rendering::mesh::create_with_texture(GL_STATIC_DRAW, 2, vertices, indices, tex_coords));
}

void ResourceMenu::render() {
    this->background_texture.use();
    this->background.draw();

    for (ResourceEntry& r_entry : this->resource_entries) {
        r_entry.render();
    }
}