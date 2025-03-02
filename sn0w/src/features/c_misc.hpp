#pragma once
#include "../singleton.hpp"

class CMisc : public CSingleton<CMisc> {
public:
    CMisc() = default;
    ~CMisc() = default;

    void clampAngles() noexcept;
    void disableOccludee() noexcept;
    
    void cameraFOV() noexcept;
    void removals() noexcept;
    void removalsR() noexcept;
    void hitsound() noexcept;
    void thirdperson() noexcept;
    void airStrafes() noexcept;
    void fastStop() noexcept;
    void viewmodel() noexcept;
    void aspectRatio() noexcept;
    void test() noexcept;

    static void update() noexcept;
    static void lateUpdate() noexcept;
    static void render() noexcept;
};