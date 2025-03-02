#pragma once
#include "../singleton.hpp"
#include "../unity/c_transform.h"
#include "../so2/c_playercontroller.h"
#include "../config.hpp"

class CLegitbot : public CSingleton<CLegitbot> {
private:
    legitbot_config_t* m_currentConfig{};
    const CPlayerController* m_target{};
    const CTransform* m_targetBone{};
public:
    CLegitbot() = default;
    ~CLegitbot() = default;

    static void createMove() noexcept;

    bool isTargetValid() const noexcept;
    void destroyTarget() noexcept;
    bool processConfig() noexcept;
    bool processTarget() noexcept;
    bool updateTarget() noexcept;
    void aimbot() noexcept;
};