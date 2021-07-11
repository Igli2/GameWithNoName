#pragma once

#include <map>

#include "resource.h"

#include "../rendering/mesh.h"
#include "../rendering/texture.h"
#include "../rendering/shader.h"
#include "../rendering/font.h"

#include "../utils/registry.h"


class ResourceEntry {
    public:
        float x;
        float y;
        float width;
        float height;
        int resource_count;
        Resource resource;
        std::string resource_name;

        ResourceEntry(float x, float y, float width, float height, Resource resource);
        void render(utils::registry<rendering::shader_program>* shader_registry, utils::registry<rendering::font>* font_registry, int scroll_offset);
};

class ResourceMenu {
    private:
        const float MARGIN_LEFT_RIGHT = 100;

        bool visible;
        int scroll;
        std::vector<ResourceEntry> resource_entries;
        rendering::mesh background;
        rendering::mesh entry_background;
		utils::registry<rendering::shader_program>* shader_registry;
		utils::registry<rendering::font>* font_registry;

        void createBackground(const int width, const int height);
    public:
        ResourceMenu(const int width, const int height);
        void addResources(Resource resource, unsigned int amount);
        // remove resources, returns false if you don't have enough, returns true on success
        bool removeResources(Resource resource, unsigned int amount);
        bool hasResource(Resource resource, unsigned int amount);
        void setVisible(bool state);
        bool isVisible();
		void set_shader_registry(utils::registry<rendering::shader_program>* shader_registry);
		void set_font_registry(utils::registry<rendering::font>* font_registry);
        void render();
        void on_scroll(double offset);
};