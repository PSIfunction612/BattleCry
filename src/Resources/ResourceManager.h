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
    class Texture2D;
}

class ResourceManager {
public:
    ResourceManager(const std::string &executable);

    ~ResourceManager() = default;

    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager &operator=(const ResourceManager &&) = delete;

    ResourceManager(const ResourceManager &) = delete;

    ResourceManager(const ResourceManager &&) = delete;

    std::shared_ptr<Renderer::ShaderProgram> loadShaderProgram(const std::string &shaderName,
                                                                const std::string &vertexPath,
                                                                const std::string &fragmentPath);
    std::shared_ptr<Renderer::ShaderProgram> getShader(const std::string &shaderName);

    std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string & textureName, const std::string& texturePath);
    std::shared_ptr<Renderer::Texture2D> getTexture(const std::string &textureName);

private:
    std::string getFileString(const std::string& relativeFilePath) const;

    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderPrograms;

    typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
    TexturesMap m_textures;

    std::string m_path;
};

#endif //BATTLECRY_RESOURCEMANAGER_H
