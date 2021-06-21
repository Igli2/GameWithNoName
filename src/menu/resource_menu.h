#pragma once

#include <map>

enum Resource {
    BEECH_LOG,
    ANDESITE_ROCK,
    BEECH_PLANK
};

class Menu {
    private:
        std::map<Resource, unsigned int> resources;
    public:
        Menu();
        // add resources
        void addResources(Resource resource, unsigned int amount);
        // remove resources, returns false if you don't have enough, returns true on success
        bool removeResources(Resource resource, unsigned int amount);
};