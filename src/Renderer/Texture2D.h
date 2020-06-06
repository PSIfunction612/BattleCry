//
// Created by shala on 06.06.2020.
//

#ifndef BATTLECRY_TEXTURE2D_H
#define BATTLECRY_TEXTURE2D_H

#include "glad/glad.h"
#include <string>

namespace Renderer{
    class Texture2D {
    public:
        Texture2D(GLuint width, GLuint heigth, const unsigned char* data,
                const unsigned int channels, const GLenum filter,
                const GLenum wrapMode);

        Texture2D() = delete;
        Texture2D(const Texture2D& ) = delete;
        Texture2D& operator=(const Texture2D& ) = delete;
        Texture2D& operator=(Texture2D &&texture2D);
        Texture2D(Texture2D&& texture2D);
        ~Texture2D();

        void bind() const;

    private:
        GLuint m_ID;
        GLenum m_mode;
        GLuint m_width;
        GLuint m_heigth;

    };

}


#endif //BATTLECRY_TEXTURE2D_H
