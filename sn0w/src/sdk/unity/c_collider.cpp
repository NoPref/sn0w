#include "c_collider.h"
#include "../globals.hpp"
#include "../includes/il2cpp/il2cpp-api.h"

bounds_t C_Collider::getBounds() const noexcept {
    static bounds_t(*func)(const C_Collider*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Collider"), oxorany("UnityEngine"), oxorany("UnityEngine.PhysicsModule.dll")), oxorany("get_bounds"), 0)->methodPointer);
    return func(this);
}