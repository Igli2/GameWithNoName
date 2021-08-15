#include "empty_menu.h"

EmptyMenu::EmptyMenu() : visible{false} {

}

bool EmptyMenu::isVisible() {
    return this->visible;
}

void EmptyMenu::setVisible(bool state) {
    this->visible = state;
}

void EmptyMenu::set_shader_registry(utils::registry<rendering::shader_program>* shader_registry) {
    this->shader_registry = shader_registry;
}

utils::registry<rendering::shader_program>* EmptyMenu::get_shader_registry() {
    return this->shader_registry;
}

void EmptyMenu::set_font_registry(utils::registry<rendering::font>* font_registry) {
    this->font_registry = font_registry;
}

utils::registry<rendering::font>* EmptyMenu::get_font_registry() {
    return this->font_registry;
}

void EmptyMenu::render() {}