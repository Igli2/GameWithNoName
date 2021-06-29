#include <iostream>

#include "resource_menu.h"

ResourceEntry::ResourceEntry(float x, float y, float width, float height)
    : x{x}, y{y}, width{width}, height{height}, resource_count{0}, resource{Resource::BEECH_LOG} {
        
}

void ResourceEntry::render() {
    // TODO
}



ResourceMenu::ResourceMenu(): resource_entries{}, scroll{0} {
    for (int resource_int = Resource::BEECH_LOG; resource_int != Resource::MAX; resource_int++) {
        Resource resource = static_cast<Resource>(resource_int);

        ResourceEntry entry{0, 0, 100, 100};
        entry.resource = resource;
        this->resource_entries.push_back(std::move(entry));
    }
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

void ResourceMenu::updateWindowSize(const int width, const int height) {
    float w = static_cast<float>(width);
    float h = static_cast<float>(height);
    std::vector<float> vertices{{
        100, 50, 0.0f,
        w - 100, 50, 0.0f,
        100, h - 50, 0.0f,
        w - 100, h - 50, 0.0f
    }};

    std::vector<unsigned int> indices{{
        0, 1, 2,
        1, 2, 3
    }};

    this->background = std::move(rendering::mesh::create(GL_STATIC_DRAW, 2, vertices, indices));
}

void ResourceMenu::render() {
    this->background.draw();
    for (ResourceEntry r_entry : this->resource_entries) {
        r_entry.render();
    }
}