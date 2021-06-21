#include <iostream>

#include "resource_menu.h"

Menu::Menu(): resources{} {}

void Menu::addResources(Resource resource, unsigned int amount) {
    this->resources[resource] += amount;
}

bool Menu::removeResources(Resource resource, unsigned int amount) {
    if (this->resources[resource] >= amount) {
        this->resources[resource] -= amount;
        return true;
    }
    return false;
}