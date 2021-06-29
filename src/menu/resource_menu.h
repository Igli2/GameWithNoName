#pragma once

#include <map>

#include "../rendering/mesh.h"

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

        ResourceEntry(float x, float y, float width, float height);
        void render();
};

class ResourceMenu {
    private:
        int scroll;
        std::vector<ResourceEntry> resource_entries;
        rendering::mesh background;
    public:
        ResourceMenu();
        // add resources
        void addResources(Resource resource, unsigned int amount);
        // remove resources, returns false if you don't have enough, returns true on success
        bool removeResources(Resource resource, unsigned int amount);
        // called when window is resized, needed to draw dynamic menu
        void updateWindowSize(const int width, const int height);
        void render();
};