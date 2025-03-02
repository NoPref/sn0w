#pragma once
#include "c_object.h"
#include "c_shader.h"
#include "c_texture.h"
#include "common/t_color.h"
#include "../includes/oxorany/include.h"

class CMaterial : public CObject {
public:
    static void create(CMaterial* thiz, CShader* shader) noexcept;
    static void create(CMaterial* thiz, CMaterial* material) noexcept;
    
    CShader* getShader() const noexcept;
    void setShader(CShader* pShader) noexcept;

    void* getMainTexture() const noexcept;
    void setMainTexture(void* texture) noexcept;

    color_t getColor(const char* szProperty = oxorany("_Color")) const noexcept;
    void setColor(const color_t& color, const char* szProperty = oxorany("_Color")) noexcept;

    float getFloat(const char* const& szProperty) const noexcept;
    void setFloat(const float& fValue, const char* const& szProperty) noexcept;
    
    CTexture* getTexture(const char* const& szTexture) const noexcept;
    void setTexture(CTexture* texture, const char* const& szTexture) noexcept;
};