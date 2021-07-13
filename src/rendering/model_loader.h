#pragma once

#include <fstream>
#include <string>

#include "mesh.h"

namespace rendering {
    mesh load_mesh_from_file(const std::string& filepath);
    mesh load_mesh_from_stream(std::istream& stream);
}