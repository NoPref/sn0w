#pragma once
#include "c_object.h"

class CShader : public CObject {
public:
    static CShader* find(const char* const& szName) noexcept;
    static int propertyToID(const char* const& szProperty) noexcept;
};