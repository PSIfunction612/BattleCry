//
// Created by shala on 07.06.2020.
//
#include <iostream>
#include "AnimatedSprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>


namespace Renderer {

    AnimatedSprite::AnimatedSprite(const std::shared_ptr<Texture2D> pTexture, const std::string& initialsubTexture,
            const std::shared_ptr<ShaderProgram> pShaderProgram,
            const glm::vec2 &position, const glm::vec2 &size, const float rotation) 
            
            :Sprite(std::move(pTexture), std::move(initialsubTexture),std::move(pShaderProgram), 
            position, size, rotation)
    {
        m_pCurrentAnimationDurations = m_statesMap.end();
    }

    void AnimatedSprite::update(uint64_t delta){
        if (m_pCurrentAnimationDurations != m_statesMap.end()){
            m_currentAnimationTime += delta;

            while (m_currentAnimationTime >= m_pCurrentAnimationDurations->second[m_currentFrame].second)
            {
                m_currentAnimationTime -= m_pCurrentAnimationDurations->second[m_currentFrame].second;
                ++m_currentFrame;
                m_dirty = true;
            }

            if (m_currentFrame == m_pCurrentAnimationDurations->second.size()){
                m_currentFrame = 0;
            }
            
        }
    }

    void AnimatedSprite::setState(std::string newState){
        auto it = m_statesMap.find(newState);
        if (it != m_statesMap.end()){
            std::cerr << "Can't find animation state " << newState << std::endl;
            return;
        }
        if (it !=m_pCurrentAnimationDurations){
            m_currentAnimationTime = 0;
            m_currentFrame = 0;
            m_pCurrentAnimationDurations = it;
            m_dirty = true;
        }
    }

    void AnimatedSprite::insertState(std::string name, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration) {
        m_statesMap.emplace(std::move(name), std::move(subTexturesDuration));
    }

    void AnimatedSprite::render() const {
        if (m_dirty)
        {
            auto subTexture = m_pTexture->getSubTexture2D(m_pCurrentAnimationDurations->second[m_currentFrame].first);

            const GLfloat textureCoords[] = {
                subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
                subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
                subTexture.rightTopUV.x, subTexture.rightTopUV.y,

                subTexture.rightTopUV.x, subTexture.rightTopUV.y,
                subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
                subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
            };

            glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof textureCoords, &textureCoords);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            m_dirty = false;
        }
        Sprite::render();
    }
}