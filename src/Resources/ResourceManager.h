//
// Created by shala on 28.05.2020.
//

#ifndef BATTLECRY_RESOURCEMANAGER_H
#define BATTLECRY_RESOURCEMANAGER_H

#include <string>
#include <memory>
#include <map>

namespace Renderer {
    class ShaderProgram;
}

class ResourceManager {
public:
    ResourceManager(const std::string &executable);

    ~ResourceManager() = default;

    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager &operator=(const ResourceManager &&) = delete;

    ResourceManager(const ResourceManager &) = delete;

    ResourceManager(const ResourceManager &&) = delete;

    std::shared_ptr<Renderer::ShaderProgram>
    loadShaderProgram(const std::string &shaderName, const std::string &vertexPath, const std::string &fragmentPath);


    std::shared_ptr<Renderer::ShaderProgram>
    getShader(const std::string &shaderName);


    void loadTexture(const std::string & textureName, const std::string& texturePath);

private:
    std::string getFileString(const std::string& relativeFilePath) const;

    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderPrograms;

    std::string m_path;
};

#endif //BATTLECRY_RESOURCEMANAGER_H
