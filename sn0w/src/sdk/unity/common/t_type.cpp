#include "t_type.h"
#include "../globals.hpp"

type_t* type_t::find(const char* const& szType) noexcept {
    static type_t*(*func)(string_t*, bool);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Type"), oxorany("System"), oxorany("mscorlib.dll")), oxorany("GetType"), 2)->methodPointer;
    return func(string_t::create(szType), false);
}