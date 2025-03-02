#include "c_shader.h"
#include "../globals.hpp"
#include "../includes/il2cpp/il2cpp-api.h"

CShader* CShader::find(const char* const& szName) noexcept {
    static CShader*(*func)(Il2CppString*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Shader"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("Find"), 1)->methodPointer);
    return func(g.il2cpp.string_new(szName));
}

int CShader::propertyToID(const char* const& szProperty) noexcept {
    static int(*func)(Il2CppString*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Shader"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("PropertyToID"), 1)->methodPointer);
    return func(g.il2cpp.string_new(szProperty));
}