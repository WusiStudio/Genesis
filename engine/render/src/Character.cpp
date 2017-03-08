#include "Character.h"


namespace engine
{
    Character & Character::Create(const CharacterInfo & characterInfo)
    {
        Character & result = Create();

        bool characterInit = result.initWithCharacterInfo(characterInfo);

        assert(characterInit);

        if(!characterInit) { result.initializeError(1); }

        return result;
    }

    void Character::position(const Vec3 & v)
    {
        Node::position(Vec3(v.x + bearingX() + m_size.width / 2, v.y + bearingY() + m_size.height / 2));
    }

    const bool Character::init(void)
    {
        if(!Rectangle::init()){ return false; }
        
        return true;
    }

    const bool Character::initWithCharacterInfo(const CharacterInfo & characterInfo)
    {
        m_size = characterInfo.size();
        m_characterInfo = (CharacterInfo *)&characterInfo;

        if(!Rectangle::init(m_size)){ return false; }
        
        return true;
    }
    const int Character::bearingX(void) const
    {
        return (int)(m_characterInfo->bearing().x);
    }

    const int Character::bearingY(void) const
    {
        return (int)(m_characterInfo->bearing().y - m_characterInfo->size().height + m_characterInfo->fontSize() / 4);
    }

    ShaderProgram & Character::customShaderProgram(void)
    {
        vector<string> v_shader_files, f_shader_files;

        switch(materia().materiaType())
        {
            case MateriaType::Purity:
                v_shader_files.push_back("FontMPurity.vert");
                f_shader_files.push_back("FontMPurity.frag");
            break;
            case MateriaType::Multicolor:
                v_shader_files.push_back("Multicolor.vert");
                f_shader_files.push_back("Multicolor.frag");
            break;
            case MateriaType::Chartlet2D:
                v_shader_files.push_back("Chartlet2D.vert");
                f_shader_files.push_back("Chartlet2D.frag");
            break;
        }

        //创建新的着色器
        ShaderProgram & newShaderProgram = ShaderProgram::Create(v_shader_files, f_shader_files);

        return newShaderProgram;
    }

    const bool Character::customVaoData(void)
    {
        Vec2 * fontTexCoords = new Vec2[vertexsCount()];
        if(!texCoords(fontTexCoords)) { return false; }

        shaderProgram().uniformSet("fColor", materia().color().rgba());

        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vec3) * vertexsCount() + sizeof(Vec2) * vertexsCount()), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)(sizeof(Vec3) * vertexsCount()), vertexs());
        glBufferSubData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vec3) * vertexsCount()), (GLsizeiptr)(sizeof(Vec2) * vertexsCount()), fontTexCoords);


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (const void *)(sizeof(Vec3) * vertexsCount()));
        glEnableVertexAttribArray(1);

        delete[] fontTexCoords;

        return true;
    }

    const bool Character::tick(const float dp)
    {
        return Rectangle::tick(dp);
    }

    const bool Character::draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const
    {
        if(!Geometry::draw(eye_matrix, screen_matrix)) return false;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, (GLuint)m_characterInfo->textrue2D()->textrueId());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiesBufferObject());
        glDrawElements(GL_TRIANGLE_STRIP, indiesCount(), GL_UNSIGNED_SHORT, nullptr);
        return true;
    }
}