//
// Created by shala on 06.06.2020.
//

#include "Texture2D.h"
namespace Renderer{
    Texture2D::Texture2D(GLuint width, GLuint heigth,
                        const unsigned char *data,
                        const unsigned int channels,
                        const GLenum filter, const GLenum wrapMode)
            :m_width(width), m_heigth(heigth){
        switch (channels) {
            case 3:
                m_mode = GL_RGB;
                break;
            case 4:
                m_mode = GL_RGBA;
                break;
            default:
                m_mode = GL_RGBA;
                break;
        }
        glGenTextures(1, &m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ID);
        glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_heigth, 0, m_mode, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture2D::Texture2D(Texture2D &&texture2D) {
        m_ID = texture2D.m_ID;
        texture2D.m_ID = 0;
        m_mode = texture2D.m_mode;
        m_width=texture2D.m_width;
        m_heigth=texture2D.m_heigth;
    }

    Texture2D & Texture2D::operator=(Texture2D && texture2D) {
        glDeleteTextures(1, &m_ID);
        m_ID = texture2D.m_ID;
        texture2D.m_ID = 0;
        m_mode = texture2D.m_mode;
        m_width=texture2D.m_width;
        m_heigth=texture2D.m_heigth;
        return *this;
    }

    void Texture2D::bind() const {
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }

    Texture2D::~Texture2D() {
        glDeleteTextures(1, &m_ID);
    }

}
