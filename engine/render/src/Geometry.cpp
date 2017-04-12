#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Geometry.h"
#include <iostream>
#include <cstring>
#include <vector>

#include "WSLog.h"
#include "Matrix.h"
#include "ShaderProgram.h"

namespace engine
{
    using WsTools::Log;

    Chartlet * Geometry::DefaultCharlet(void)
    {
        static Chartlet * result = nullptr;
        if(!result)
        {
            result = &Chartlet::Create();
            result->retain();
        }

        return result;
    }

    const bool Geometry::bindChartlet(Chartlet & c)
    {
        if(m_chartlet) { m_chartlet->release(); }

        m_chartlet = &c;
        c.retain();

        //更新着色器
        if(!updateShaderProgram()){ return false; }

        return true;
    }

    Geometry::Geometry(void)
    {
        m_vertexs = nullptr;
        m_indies = nullptr;
        m_normals = nullptr;
        m_uvs = nullptr;
        m_chartlet = nullptr;

        m_shaderProgram = nullptr;

        m_vertexArrayObject = m_vertexBufferObject = m_indiesBufferObject = 0;
        m_vertexsCount = m_indiesCount = 0;
    }

    const bool Geometry::init(void)
    {
        if(!Node::init()){ return false; }

        m_chartlet = DefaultCharlet();
        updateShaderProgram();
        return true;
    }

    void Geometry::vertexsCount(const unsigned short count)
    {
        m_vertexsCount = 0;
        if(m_vertexs) { delete[] m_vertexs; }
        if(m_normals) { delete[] m_normals; }
        if(m_uvs) { delete[] m_uvs; }

        if(!count)
        {
            m_vertexs = nullptr;
            m_normals = nullptr;
            m_uvs = nullptr;
            return;
        }

        m_vertexs = new Vec3[count];
        m_normals = new Vec3[count];
        m_uvs = new Vec2[count];
        if(!m_vertexs || !m_normals || !m_uvs)
        {
            Log.error("System Error: malloc memory fail!");
            return;
        }
        

        //申请顶点数组对象
        while(!m_vertexArrayObject)
        {
            glGenVertexArrays(1, &m_vertexArrayObject);
        }

        //申请缓存对象
        while(!m_vertexBufferObject)
        {
            glGenBuffers(1, &m_vertexBufferObject);
        }

        m_vertexsCount = count;
    }

    void Geometry::indiesCount(const unsigned short count)
    {
        m_indiesCount = 0;

        if(m_indies){ delete[] m_indies; }

        if(!count){ m_indies = nullptr; }

        m_indies = new unsigned short[count];
        if(!m_indies) return;

        //申请缓存对象
        while(!m_indiesBufferObject)
        {
            glGenBuffers(1, &m_indiesBufferObject);
        }

        m_indiesCount = count;
        memset(m_indies, 0, sizeof(unsigned short) * m_indiesCount);
    }

    const GLuint Geometry::vertexArrayObject(void) const
    {
        return m_vertexArrayObject;
    }
    const GLuint Geometry::vertexBufferObject(void) const
    {
        return m_vertexBufferObject;
    }
    const GLuint Geometry::indiesBufferObject(void) const
    {
        return m_indiesBufferObject;
    }

    void Geometry::vertex(const unsigned short index, const Vec3 & data)
    {
        if(index >= m_vertexsCount)
        {
            Log.critical("Set vertex out!");
            return;
        }
        *(m_vertexs + index) = data;
    }

    void Geometry::vertex(const unsigned short index, const Vec3 & p_vertex, const Vec3 & p_normal, const Vec2 & p_uv)
    {
        if(index >= m_vertexsCount)
        {
            Log.critical("Set vertex, normal and uv out!");
            return;
        }
        *(m_vertexs + index) = p_vertex;
        *(m_normals + index) = p_normal;
        *(m_uvs + index) = p_uv;
    }

    void Geometry::indie(const unsigned short index, const unsigned short data)
    {
        if(index >= m_indiesCount)
        {
            Log.critical("Set india out!");
            return;
        }
        *(m_indies + index) = data;
    }

    void Geometry::normal(const unsigned short index, const Vec3 & data)
    {
        if(index >= m_vertexsCount)
        {
            Log.critical("Set normal out!");
            return;
        }
        *(m_normals + index) = data;
    }

    void Geometry::uv(const unsigned short index, const Vec2 & data)
    {
        if(index >= m_vertexsCount)
        {
            Log.critical("Set uv out!");
            return;
        }
        *(m_uvs + index) = data;
    }

    void Geometry::vertexs(const Vec3 * data)
    {
        vertexs(data, m_vertexsCount);
    }

    void Geometry::vertexs(const Vec3 * p_vertexs, const Vec3 * p_normals, const Vec2 * p_uvs)
    {
        vertexs(p_vertexs, p_normals, p_uvs, m_vertexsCount);
    }
    
    void Geometry::vertexs(const Vec3 * data, const unsigned short count, const unsigned short start_index)
    {
        if(start_index + count > m_vertexsCount)
        {
            Log.critical("Set vertexs out!");
            return;
        }
        memcpy(m_vertexs + start_index, data, count * sizeof(Vec3));
    }

    void Geometry::vertexs(const Vec3 * p_vertexs, const Vec3 * p_normals, const Vec2 * p_uvs, const unsigned short count, const unsigned short start_index)
    {
        if(start_index + count > m_vertexsCount)
        {
            Log.critical("Set vertexs,normals and uvs out!");
            return;
        }

        vertexs(p_vertexs, count, start_index);
        normals(p_normals, count, start_index);
        uvs(p_uvs, count, start_index);
    }

    void Geometry::normals(const Vec3 * data)
    {
        normals(data, m_vertexsCount);
    }

    void Geometry::normals(const Vec3 * data, const unsigned short count, const unsigned short start_index)
    {
        if(start_index + count > m_vertexsCount)
        {
            Log.critical("Set normals out!");
            return;
        }
        memcpy(m_normals + start_index, data, count * sizeof(Vec3));
    }

    void Geometry::uvs(const Vec2 * data)
    {
        uvs(data, m_vertexsCount);
    }

    void Geometry::uvs(const Vec2 * data, const unsigned short count, const unsigned short start_index)
    {
        if(start_index + count > m_vertexsCount)
        {
            Log.critical("Set uvs out!");
            return;
        }
        memcpy(m_uvs + start_index, data, count * sizeof(Vec2));
    }

    void Geometry::indies(const unsigned short * data, const unsigned short count, const unsigned short start_index)
    {
        memcpy(m_indies + start_index, data, (m_indiesCount - start_index) * sizeof(unsigned short));
    }

    void Geometry::indies(const unsigned short * data)
    {
        indies(data, m_indiesCount, 0);
    }

    const Vec3 * Geometry::vertexs(void) const 
    {
        return m_vertexs;
    }

    const Vec3 * Geometry::normals(void) const
    {
        return m_normals;
    }

    const unsigned short * Geometry::indies(void) const 
    {
        return m_indies;
    }

    const bool Geometry::bindVaoData(void)
    {
        //如果没有顶点数据直接返回
        if(!m_vertexsCount) { return true; }

        //如果没有bind着色器程序
        if(!m_shaderProgram)
        { 
            Log.error("Not Bind ShaderProgram!");
            return false; 
        }

        m_shaderProgram->use();

        //材质
        if(!m_chartlet) 
        { 
            Log.error("Chartlet Is NULL!");
            return false; 
        }

        if(m_indiesCount)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indiesBufferObject);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(unsigned short) * m_indiesCount), m_indies, GL_STATIC_DRAW);
        }

        glBindVertexArray(m_vertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);

        if(!customVaoData()){ return false; }

        glBindVertexArray(0);

        return true;
    }

    const Chartlet & Geometry::chartlet(void) const
    {
        return * m_chartlet;
    }

    ShaderProgram & Geometry::shaderProgram(void) const
    {
        return *m_shaderProgram;
    }

    ShaderProgram & Geometry::customShaderProgram(void)
    {
        vector<string> v_shader_files, f_shader_files;

        if(m_chartlet)
        {
            switch(m_chartlet->chartletType())
            {
                case ChartletType::Purity:
                    v_shader_files.push_back("MPurity.vert");
                    f_shader_files.push_back("MPurity.frag");
                break;
                case ChartletType::Multicolor:
                    v_shader_files.push_back("Multicolor.vert");
                    f_shader_files.push_back("Multicolor.frag");
                break;
                case ChartletType::Chartlet2D:
                    v_shader_files.push_back("Chartlet2D.vert");
                    f_shader_files.push_back("Chartlet2D.frag");
                break;
            }
        }

        //创建新的着色器
        ShaderProgram & newShaderProgram = ShaderProgram::Create(v_shader_files, f_shader_files);

        return newShaderProgram;
    }

    const bool Geometry::customVaoData(void)
    {
         ChartletType chartletType = m_chartlet->chartletType();

         Vec2 * tempTexCoords = nullptr;

        switch(chartletType)
        {
            case ChartletType::Purity:
                glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount + sizeof(Vec3) * m_vertexsCount), nullptr, GL_STATIC_DRAW);
                glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount), m_vertexs);
                glBufferSubData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount), (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount), m_normals);
                m_shaderProgram->uniformSet("fColor", m_chartlet->color().rgba());

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const void *)(sizeof(Vec3) * m_vertexsCount));
                glEnableVertexAttribArray(1);
            break;
            case ChartletType::Multicolor:
                //材质的颜色数据数量不匹配时重新创建材质
                if(m_vertexsCount > m_chartlet->colorsCount())
                {
                    ColorRGBA * tempArray = new ColorRGBA[m_vertexsCount];
                    for(int i = 0; i < m_vertexsCount; ++i)
                    {
                        tempArray[i] = m_chartlet->colors()[i % m_chartlet->colorsCount()];
                    }
                    Chartlet & temp_charlet = Chartlet::Create();
                    temp_charlet.colors(tempArray, m_vertexsCount);
                    delete[] tempArray;

                    m_chartlet->release();
                    m_chartlet = &temp_charlet;
                    m_chartlet->retain();
                }

                glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount + sizeof(Vec3) * m_vertexsCount + sizeof(ColorRGBA) * m_chartlet->colorsCount()), nullptr, GL_STATIC_DRAW);
                glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount), m_vertexs);
                glBufferSubData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount), (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount), m_normals);
                glBufferSubData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount + sizeof(Vec3) * m_vertexsCount), (GLsizeiptr)(sizeof(ColorRGBA) * m_chartlet->colorsCount()), m_chartlet->colors());

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const void *)(sizeof(Vec3) * m_vertexsCount));
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (const void *)(sizeof(Vec3) * m_vertexsCount + sizeof(Vec3) * m_vertexsCount));
                glEnableVertexAttribArray(3);
            break;
            case ChartletType::Chartlet2D:

                glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount + sizeof(Vec3) * m_vertexsCount + sizeof(Vec2) * m_vertexsCount), nullptr, GL_STATIC_DRAW);
                glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount), m_vertexs);
                glBufferSubData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount), (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount), m_normals);
                glBufferSubData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vec3) * m_vertexsCount + sizeof(Vec3) * m_vertexsCount), (GLsizeiptr)(sizeof(Vec2) * m_vertexsCount), m_uvs);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const void *)(sizeof(Vec3) * m_vertexsCount));
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const void *)(sizeof(Vec3) * m_vertexsCount + sizeof(Vec3) * m_vertexsCount));
                glEnableVertexAttribArray(2);

                delete[] tempTexCoords;
            break;

            default:
                Log.error("chartletType({0}) is ndefine!", chartletType);
            return false;
        }

        return true;
    }

    const bool Geometry::updateShaderProgram(void)
    {
        ShaderProgram & newShaderProgram = customShaderProgram();
        if(!newShaderProgram.ready()){ return false; }
        
        //解除链接
        if(m_shaderProgram != nullptr)
        {
            m_shaderProgram->release();
            m_shaderProgram = nullptr;
        }

        //建立新的链接
        m_shaderProgram = &newShaderProgram;
        newShaderProgram.autoRelease();
        newShaderProgram.retain();

        //更新shader程序后重新绑定数据
        if(!bindVaoData()){ return false; }

        return true;
    }

    const bool Geometry::tick(const float dp)
    {
        if(!Node::tick(dp)){ return false; }
        return true;
    }

    const bool Geometry::draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const
    {
        //绘制子节点
        if(!Node::draw(eye_matrix, screen_matrix)){ return false; }

        m_shaderProgram->use();
        
        //平移
        Matrix4 translationMatrix = Matrix4::CreateTranslationMatrix(worldCoordinateOffset());
        // Log.info("translationMatrix: {0}", translationMatrix);
        //缩放
        Matrix4 scaleMatrix = Matrix4::CreateScaleMatrix(scale() * (Vec3(0) + accumulativeScaleOffset()));
        // Log.info("scaleMatrix: {0}", scaleMatrix);
        //创建旋转  缩放  平移到世界坐标 矩阵
        //旋转
        Matrix4 rotationMatrix = Matrix4::CreateRotationMatrix(rotate() + accumulativeRotateOffset());
        // Log.info("rotationMatrix: {0}", rotationMatrix);

        //m
        Matrix4 modelMatrix = rotationMatrix * scaleMatrix * translationMatrix;

        //v
        Matrix4 viewMatrix = eye_matrix;

        //p
        Matrix4 projectionMatrix = screen_matrix;

        m_shaderProgram->uniformSet("ambientStrength", Vec4(1.0f, 1.0f, 1.0f, .1f));
        m_shaderProgram->uniformSet("lightPos", Vec3(.0f, 1000.0f, 1000.0f));

        m_shaderProgram->uniformSet("modelMatrix", modelMatrix);
        m_shaderProgram->uniformSet("viewMatrix", viewMatrix);
        m_shaderProgram->uniformSet("projectionMatrix", projectionMatrix);

        glBindVertexArray(m_vertexArrayObject);
        if(m_chartlet->chartletType() == ChartletType::Chartlet2D)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, (GLuint)m_chartlet->chartlet2D()->textrueId());
        }

        return true;
    }

    const bool Geometry::texCoords(Vec2 * tex_coords) const
    {
        Vec3 * minMax[4];
        for(int i = 0; i < 4; i++)
        {
            minMax[i] = m_vertexs;
        }
        
        for(int i = 0; i < m_vertexsCount; ++i)
        {
            Vec3 * vertex = m_vertexs + i;
            if(vertex->x < minMax[0]->x)
            {
                minMax[0] = vertex;
            }

            if(vertex->y < minMax[1]->y)
            {
                minMax[1] = vertex;
            }

            if(vertex->x > minMax[2]->x)
            {
                minMax[2] = vertex;
            }

            if(vertex->y > minMax[3]->y)
            {
                minMax[3] = vertex;
            }
        }

        Size2 geometrySize(minMax[2]->x - minMax[0]->x, minMax[3]->y - minMax[1]->y);

        for(int i = 0; i < m_vertexsCount; ++i)
        {
            tex_coords[i].x = (m_vertexs[i].x - minMax[0]->x) / geometrySize.width;
            tex_coords[i].y = 1.0f - (m_vertexs[i].y - minMax[1]->y) / geometrySize.height;
        }

        return true;
    }

    Geometry::~Geometry(void)
    {
        if(m_vertexs){ delete[] m_vertexs; }
        if(m_normals){ delete[]m_normals; }
        if(m_uvs){ delete[] m_uvs; }
        if(m_indies){ delete[] m_indies; }

        if(m_vertexBufferObject){ glDeleteBuffers(1, &m_vertexBufferObject); }
        if(m_vertexBufferObject){ glDeleteBuffers(1, &m_indiesBufferObject); }
        if(m_vertexBufferObject){ glDeleteVertexArrays(1, &m_vertexArrayObject); }

        if(m_chartlet) { m_chartlet->release(); }
    }
}