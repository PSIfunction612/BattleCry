//
// Created by shala on 28.05.2020.
//

#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include <sstream>
#include <fstream>
#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

ResourceManager::ResourceManager(const std::string &executable) {
    size_t found = executable.find_last_of("/\\");
    m_path = executable.substr(0, found);

}

std::shared_ptr<Renderer::ShaderProgram>
ResourceManager::loadShaderProgram(const std::string &shaderName, const std::string &vertexPath,
                            const std::string &fragmentPath) {
    std::string vertex_string = getFileString(vertexPath);
    if (vertex_string.empty()) {
        std::cerr << "No vertex shader!" << std::endl;
        return nullptr;
    }

    std::string fragment_string = getFileString(fragmentPath);
    if (fragment_string.empty()) {
        std::cerr << "no fragment shader!" << std::endl;
        return nullptr;
    }

    std::shared_ptr<Renderer::ShaderProgram> &newShared = m_shaderPrograms.emplace(shaderName,
                                                                                   std::make_shared<Renderer::ShaderProgram>(
                                                                                           vertex_string,
                                                                                           fragment_string)).first->second;
    if (newShared->isCompiled()) {
        return newShared;
    }
    return nullptr;
}


std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShader(const std::string &shaderName) {
    ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
    if (it!=m_shaderPrograms.end()){
        return it->second;
    }
    std::cerr << "Can't find shader program " <<  shaderName << std::endl;
    return nullptr;
}

void ResourceManager::loadTexture(const std::string &textureName, const std::string &texturePath) {
    int channels = 0;
    int width = 0;
    int heigth = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(std::string(m_path + "\\" + texturePath).c_str(), &width, &heigth, &channels, 0);
    if (!pixels){
        std::cerr << "Can't load image " + texturePath << std::endl;
        return;
    }
    stbi_image_free(pixels);
}

std::string ResourceManager::getFileString(const std::string &relativeFilePath) const {
    std::ifstream f;
    f.open(m_path + "\\" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cerr << "Can't open file in such directory: " << m_path + "\\" + relativeFilePath << std::endl;
        return std::string{};
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}