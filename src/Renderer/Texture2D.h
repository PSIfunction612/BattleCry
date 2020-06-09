//
// Created by shala on 06.06.2020.
//

#ifndef BATTLECRY_TEXTURE2D_H
#define BATTLECRY_TEXTURE2D_H

#include "glad/glad.h"
#include <string>
#include <map>
#include <glm/vec2.hpp>


namespace Renderer{
    class Texture2D {
    public:

        struct SubTexture2D {
            glm::vec2 leftBottomUV;
            glm::vec2 rightTopUV;

            SubTexture2D(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV)
            :leftBottomUV(_leftBottomUV), rightTopUV(_rightTopUV)
            {            }

            SubTexture2D()
            :leftBottomUV(0.f),
            rightTopUV(1.f)
            {            }
        };

        Texture2D(GLuint width, GLuint height, const unsigned char* data,
                const unsigned int channels, const GLenum filter,
                const GLenum wrapMode);

        Texture2D() = delete;
        Texture2D(const Texture2D& ) = delete;
        Texture2D& operator=(const Texture2D& ) = delete;
        Texture2D& operator=(Texture2D &&texture2D);
        Texture2D(Texture2D&& texture2D);
        ~Texture2D();

        void addSubTexture(const std::string& name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV);
        const SubTexture2D& getSubTexture2D(const std::string& name) const;

        unsigned int width(){return m_width;}
        unsigned int height(){return m_heigth;}

        void bind() const;

    private:
        GLuint m_ID;
        GLenum m_mode;
        GLuint m_width;
        GLuint m_heigth;

        std::map<std::string, SubTexture2D> m_subTextures;
    };

}


#endif //BATTLECRY_TEXTURE2D_H
