#include <stdexcept>

template<class type>
utils::registry<type>::registry() {
}

template<class type>
bool utils::registry<type>::insert(const std::string& identifier, type&& element) {
    if(this->has(identifier)) return false;

    this->elements.insert(std::make_pair(identifier, std::move(element)));
    return true;
}

template<class type>
bool utils::registry<type>::has(const std::string& identifier) {
    try {
        this->elements.at(identifier);
        return true;
    } catch(...) {
        return false;
    }
}

template<class type>
type& utils::registry<type>::get(const std::string& identifier) {
    if(!this->has(identifier)) throw std::runtime_error("Tried to access non-existent registry object '" + identifier + "'!");
    return this->elements.at(identifier);
}

template<class type>
bool utils::registry<type>::remove(const std::string& identifier) {
    if(!this->has(identifier)) return false;

    this->elements.erase(identifier);
    return true;
}

template<class type>
utils::registry<type>::~registry() {
}