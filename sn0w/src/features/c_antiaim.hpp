#pragma once
#include "../singleton.hpp"
#include "../sdk/so2/include.h"
#include "../sdk/unity/common/include.h"
#include "../sdk/unity/c_transform.h"

class CAntiAim : public CSingleton<CAntiAim> {
private:
    CTransform* m_currentCamera;
    euler_angles_t m_cameraAngles;
    
public:
    CAntiAim() = default;
    ~CAntiAim() = default;

    static void createMove() noexcept;
    static void lateUpdate() noexcept;

    void getCamera() noexcept;
    void getAngles() noexcept;
    void setAngles() noexcept;
    void rotateCamera() noexcept;
};