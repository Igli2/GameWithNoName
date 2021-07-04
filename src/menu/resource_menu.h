#pragma once

#include <map>

#include "../rendering/mesh.h"
#include "../rendering/texture.h"

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
        void render();
};

class ResourceMenu {
    private:
        const float MARGIN_LEFT_RIGHT = 100;

        int scroll;
        std::vector<ResourceEntry> resource_entries;
        rendering::mesh background;
        rendering::texture background_texture;

        void createBackground(const int width, const int height);
    public:
        ResourceMenu(const int width, const int height);
        // add resources
        void addResources(Resource resource, unsigned int amount);
        // remove resources, returns false if you don't have enough, returns true on success
        bool removeResources(Resource resource, unsigned int amount);
        // called when window is resized, needed to draw dynamic menu
        void render();
};