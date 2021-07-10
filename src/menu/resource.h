#pragma once

#include <map>
#include <string>


enum Resource {
    BEECH_LOG,
    ANDESITE_ROCK,
    BEECH_PLANK,
    MAX
};

static std::map<Resource, std::string> resource_files = {
    {Resource::BEECH_LOG, "items/beech_log.json"},
    {Resource::ANDESITE_ROCK, "items/andesite_rock.json"},
    {Resource::BEECH_PLANK, "items/beech_plank.json"}
};