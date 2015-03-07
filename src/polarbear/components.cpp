#include <polarbear/components.hpp>

#include <algorithm>
#include <sstream>
#include <fstream>
#include <stdexcept>

template <typename T> const unsigned int BaseComponent<T>::type(nextType++);

SpriteComponent::SpriteComponent(std::string filename): transparent_char(0x20), attr(0) // Spaces are transparent
{
    // Read from file, assuming square
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        std::getline(file, line);
        width = line.size();
        file.seekg(0);

        std::stringstream buffer;
        buffer << file.rdbuf();
        auto data = std::string(buffer.str());
        std::remove_if(data.begin(), data.end(), [](char x){return std::iscntrl(x);});

        sprite_chars = std::vector<int>(data.begin(), data.end());

        height = sprite_chars.size() / width;

    } else {
        throw std::runtime_error("Sprite file not found.");
    }
}