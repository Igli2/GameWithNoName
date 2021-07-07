#pragma once

#include <map>

#include "../rendering/mesh.h"
#include "../rendering/texture.h"
#include "../rendering/shader.h"
#include "../rendering/font.h"

#include "../utils/registry.h"

enum Resource {
    BEECH_LOG,
    ANDESITE_ROCK,
    BEECH_PLANK,
    MAX
};

class ResourceEntry {
    public:
        float x;
        float y;
        float width;
        float height;
        int resource_count;
        Resource resource;
        rendering::mesh background;

        ResourceEntry(float x, float y, float width, float height);
        void render(utils::registry<rendering::shader_program>* shader_registry, utils::registry<rendering::font>* font_registry);
};

class ResourceMenu {
    private:
        const float MARGIN_LEFT_RIGHT = 100;

        bool visible;
        int scroll;
        std::vector<ResourceEntry> resource_entries;
        rendering::mesh background;
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
};