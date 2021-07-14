#include "custom_window.h"

// Constructor with initializer list
custom_window::custom_window(const std::string& title, const size_t width, const size_t height, const bool resizable, event::event_handler& ev_handler)
    : render_window{title, width, height, resizable, ev_handler}, custom_attribute{0} {
}

void custom_window::custom_method() {
    // Custom stuff here
}



// Main loop
int main() {
	// Create the event handler
    event::event_handler ev_handler{};

	// Create the window
    custom_window window{"Example", 600, 800, true, ev_handler};

	// Set the background color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Event loop
	while(window.is_open()) {
		// Clear buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update buffer
    	window.update();
	}

	// Properly destroy window
	glfwTerminate();

	return 0;
}