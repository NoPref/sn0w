#pragma once
#include "common/include.h"
#include "c_component.h"

class CTransform : public C_Component {
public:

    vec3_t getPosition() const noexcept;
    void setPosition(const vec3_t& vecOrigin) noexcept;

    vec3_t getLocalPosition() const noexcept;
    void setLocalPosition(const vec3_t& vecOrigin) noexcept;

    euler_angles_t getEulerAngles() const noexcept;
    void setEulerAngles(const euler_angles_t& ang) noexcept;

    euler_angles_t getLocalEulerAngles() const noexcept;
    void setLocalEulerAngles(const euler_angles_t& ang) noexcept;

    vec3_t getRight() const noexcept;
    vec3_t getUp() const noexcept;
    vec3_t getForward() const noexcept;

    quaternion_t getRotation() const noexcept;
    void setRotation(const quaternion_t& qRotation) noexcept;

    quaternion_t getLocalRotation() const noexcept;
    void setLocalRotation(const quaternion_t& qRotation) noexcept;

    vec3_t getLocalScale() const noexcept;
    void setLocalScale(const vec3_t& vecScale) noexcept;

    vec3_t getLossyScale() const noexcept;

    CTransform* getParent() const noexcept;
    void setParent(CTransform* parent) noexcept;
    void setParent(CTransform* parent, bool bWorldPosStays) noexcept;
};
