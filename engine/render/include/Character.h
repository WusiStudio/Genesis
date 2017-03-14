#pragma once
#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Rectangle.h"
#include "Font.h"

namespace engine
{
    class Character: public Rectangle
    {
        PROPERTY(Size2, size);
    public:
        static Character & Create(const CharacterInfo & characterInfo);
        const bool characterInfo(const CharacterInfo & characterInfo);
        void position(const Vec3 & v) override;
    protected:
        CREATEFUNC(Character);
        virtual const bool init(void) override;
        virtual const bool initWithCharacterInfo(const CharacterInfo & characterInfo);

        const int bearingX(void) const;
        const int bearingY(void) const;


        ShaderProgram & customShaderProgram(void) override;
        const bool customVaoData(void) override;

        virtual const bool tick(const float dp) override;
        virtual const bool draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override;

        Character(void);
        virtual ~Character(void){ };
    private:
        CharacterInfo * m_characterInfo;
    };
}

#endif //__CHARACTER_H__