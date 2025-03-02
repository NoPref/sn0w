#pragma once
#include "../singleton.hpp"
#include "../sdk/so2/c_playercontroller.h"
#include "../sdk/unity/common/include.h"
#include "../sdk/unity/c_transform.h"

namespace ragebot {
    struct target_t {
    public:
        const CPlayerController* m_pPlayer{};
        const CTransform* m_pBone{};
        bool m_bVisible{};
        bool m_bCanWallbang{};
        bool m_bPredicted{};
        bool m_bCanBAim{};

        target_t() = default;
        ~target_t() = default;

        void destroy() noexcept {
            this->m_pPlayer = NULL;
            this->m_pBone = NULL;
            this->m_bVisible = false;
            this->m_bCanWallbang = false;
            this->m_bPredicted = false;
            this->m_bCanBAim = false;
        }

        bool isValid() const noexcept {
            if(this->m_pPlayer == NULL || this->m_pBone == NULL)
                return false;
            return this->m_pPlayer->isAlive();
        }
    };
    
    //так лучше т.к если много хуйни в рейкасте вызывать то лаги пздц
    struct psilent_info_t {
    public:
        bool m_bValid{};
        vec3_t m_vecDst{};
        vec3_t m_vecDirection{};
    };
};

class CRagebot : public CSingleton<CRagebot> {
private:
    CTransform* m_currentCamera;
public:
    ragebot::psilent_info_t m_psInfo{};
    ragebot::target_t m_target;
    euler_angles_t m_cameraAngles;
    bool m_bFiring;
    float m_fDoubletapRecharge;
    
    CRagebot() = default;
    ~CRagebot() = default;

    static void createMove() noexcept;
    static void lateUpdate() noexcept;
    static void update() noexcept;

    static void movementFix(const float& cameraYaw, const float& realYaw);

    bool isTargetValid() const noexcept;
    void destroyTarget() noexcept;

    bool getCamera() noexcept;
    void rotateCamera() noexcept;
    void rotateCameraCM() noexcept;
    
    bool processTarget() noexcept;
    bool updateTarget() noexcept;
    void checkTarget() noexcept;

    void autoStop() noexcept;
    void autoScope() noexcept;
    void autoWall() noexcept;
    void autoFire() noexcept;

    void autos() noexcept; //IDK HOW NAME THIS )))))9990080812340

    void doubletap() noexcept;
    
    void aimbot() noexcept;
};