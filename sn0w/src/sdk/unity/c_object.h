#pragma once
#include <stdint.h>
#include "common/include.h"

class CTransform;

#pragma pack(1)
class CObject {
char pad[sizeof(void*)*2];
public:
    void* m_pCached;
    
    int getInstanceID() const noexcept;
    static CObject* findObjectFromID(const int32_t& id) noexcept;
    static array_t<CObject*>* findObjectsOfType(type_t* type) noexcept;
    static array_t<CObject*>* findObjectsByType(type_t* type) noexcept;
    static CObject* findObjectOfType(type_t* type) noexcept;
    static CObject* instantiate(CObject* orig, const vec3_t& vecOrigin, const quaternion_t& qRot) noexcept;
    static CObject* instantiate(CObject* orig, const vec3_t& vecOrigin, const quaternion_t& qRot, CTransform* parent) noexcept;
    void destroy() noexcept;
    void dontDestroyOnLoad() noexcept;
    string_t* getName() const noexcept;
    void setName(string_t* u16str) noexcept;
    void setName(const char* const& u8str) noexcept;

};
#pragma pack()