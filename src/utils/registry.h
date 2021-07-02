#pragma once

#include <map>
#include <string>
#include <type_traits>

namespace utils {
    template<class type>
    class registry {
        static_assert(!std::is_pointer<type>::value, "A registry of pointers isn't allowed!");
        static_assert(!std::is_reference<type>::value, "A registry of references isn't allowed!");

        private:
            std::map<std::string, type> elements;
        public:
            registry();
            bool insert(const std::string& identifier, type&& element);
            bool has(const std::string& identifier);
            type& get(const std::string& identifier);
            bool remove(const std::string& identifier);
            ~registry();
    };    
}

#include "registry.ipp"