#include "model_loader.h"

#include <stdexcept>
#include <cstddef>
#include <vector>

using namespace rendering;

//helper functions
void advance_line(std::istream& stream, std::string& line, std::istream::pos_type& last_line);
std::vector<std::string> split(const std::string& to_split, const std::string& delimiter);
size_t get_index(const std::string& index_str, const size_t max);
void parse_float_array(const std::vector<std::string>& components, std::vector<float>& out_arr, const size_t start, const size_t count);
bool parse_face(const std::vector<std::string>& components, const std::vector<float>& vertices, const std::vector<float>& texture_coords_in,
                std::vector<unsigned int>& indices, std::vector<float>& texture_coords);

void advance_line(std::istream& stream, std::string& line, std::istream::pos_type& last_line) {
    last_line = stream.tellg();
    std::getline(stream, line);
}

size_t get_index(const std::string& index_str, const size_t max) {
    ssize_t index = std::stoll(index_str);
    if(index == 0) throw std::runtime_error("Invalid index!");

    if(index < 0) return max - index;

    return index - 1;
}

std::vector<std::string> split(const std::string& to_split, const std::string& delimiter) {
    std::vector<std::string> components;
    
    size_t last_split_pos = 0;
    size_t split_pos = to_split.find(delimiter, last_split_pos);

    while(split_pos != std::string::npos) {
        components.push_back(to_split.substr(last_split_pos, split_pos - last_split_pos));

        last_split_pos = split_pos + delimiter.size();
        split_pos = to_split.find(delimiter, last_split_pos);
    }

    components.push_back(to_split.substr(last_split_pos, split_pos - last_split_pos));

    return components;
}

void parse_float_array(const std::vector<std::string>& components, std::vector<float>& out_arr, const size_t start, const size_t count) {
    for(size_t component = start; component < start + count; component++) {
        out_arr.push_back(std::stof(components[component]));
    }
}

bool parse_face(const std::vector<std::string>& components, const std::vector<float>& vertices, const std::vector<float>& texture_coords_in,
                std::vector<unsigned int>& indices, std::vector<float>& texture_coords) {
    for(size_t face_vertex = 0; face_vertex < 3; face_vertex++) {
        std::vector<std::string> vertex_info = split(components[face_vertex + 1], "/");
        if(vertex_info.size() > 3) return false;

        indices.push_back(get_index(vertex_info[0], vertices.size() / 3));

        if(vertex_info.size() > 1 && !vertex_info[1].empty()) {
            size_t texture_index = get_index(vertex_info[1], texture_coords_in.size() / 2);
            for(size_t texture_coord = 0; texture_coord < 2; texture_coord++) {
                texture_coords.push_back(texture_coords_in[texture_index * 2 + texture_coord]);
            }
        }
    }

    return true;
}



mesh rendering::load_mesh_from_file(const std::string& filepath) {
    std::ifstream file{filepath};

    if(!file.is_open()) throw std::runtime_error("Unable to open the file '" + filepath + "'!");

    mesh loaded_mesh = load_mesh_from_stream(file);
    file.close();

    return loaded_mesh;
}

mesh rendering::load_mesh_from_stream(std::istream& stream) {
    std::string line;
    std::istream::pos_type last_line_pos;

    advance_line(stream, line, last_line_pos);

    std::vector<float> texture_coordinates_in;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> texture_coordinates;

    while(stream.good()) {
        std::vector<std::string> components = split(line, " ");

        if(!components.empty()) {
            if(components[0] == "v") {
                if(components.size() != 4) throw std::runtime_error("Invalid vertex coordinate '" + line  + "'!"); 

                parse_float_array(components, vertices, 1, 3); 
            } else if(components[0] == "vt") {
                if(components.size() != 3) throw std::runtime_error("Invalid vertex texture coordinate '" + line  + "'!");

                parse_float_array(components, texture_coordinates_in, 1, 2); 
            } else if(components[0] == "f") {
                if(components.size() != 4 || !parse_face(components, vertices, texture_coordinates_in, indices, texture_coordinates))
                    throw std::runtime_error("Invalid face coordinate '" + line  + "'(only triangular faces are supported)!");
            }
        }

        advance_line(stream, line, last_line_pos);
    }

    if(texture_coordinates.empty()) {
        return mesh::create(GL_STATIC_DRAW, 3, vertices, indices);
    } else {
        return mesh::create_with_texture(GL_STATIC_DRAW, 3, vertices, indices, texture_coordinates);
    }
}