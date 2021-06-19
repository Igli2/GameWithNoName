#include "event_handler.h"

#include <algorithm>

using namespace::event;

event_handler::event_handler() {
}

void event_handler::add_key_event(const key_event event) {
    this->key_events.push_back(event);
}

bool event_handler::remove_key_event(const key_event event) {
    std::vector<key_event>::iterator pos = std::find(this->key_events.begin(), this->key_events.end(), event);

    if(pos == this->key_events.end()) return false;

    this->key_events.erase(pos);

    return true;
}

void event_handler::add_mouse_event(const mouse_event event) {
    this->mouse_events.push_back(event);
}

bool event_handler::remove_mouse_event(const mouse_event event) {
    std::vector<mouse_event>::iterator pos = std::find(this->mouse_events.begin(), this->mouse_events.end(), event);

    if(pos == this->mouse_events.end()) return false;

    this->mouse_events.erase(pos);

    return true;
}

void event_handler::key_press_callback(rendering::render_window* window, int key, int scancode, int action, int mods) {
    for(const key_event& event : this->key_events) {
        event(window, key, scancode, action, mods);
    }
}

void event_handler::mouse_move_callback(rendering::render_window* window, double xpos, double ypos) {
    for(const mouse_event& event : this->mouse_events) {
        event(window, xpos, ypos);
    }
}


event_handler::~event_handler() {
}