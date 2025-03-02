#pragma once
#include <stdint.h>
#include "../unity/common/include.h"
#include "../unity/c_object.h"
#include "../unity/c_component.h"
#include "../includes/il2cpp/il2cpp-api.h"

enum view_synchronization : uint8_t {
	view_synchronization_off = 0,
	view_synchronization_reliable_delta_compressed = 1,
	view_synchronization_unreliable = 2,
	view_synchronization_unreliable_on_change = 3,
};

enum on_serialize_transform : uint8_t {
	on_serialize_transform_only_position = 0,
	on_serialize_transform_only_rotation = 1,
	on_serialize_transform_only_scale = 2,
	on_serialize_transform_position_and_rotation = 3,
	on_serialize_transform_all = 4,
};

enum on_serialize_rigid_body : uint8_t {
	on_serialize_rigid_body_only_velocity = 0,
	on_serialize_rigid_body_only_angularVelocity = 1,
	on_serialize_rigid_body_all = 2,
};

enum ownership_option : uint8_t {
	ownership_optionn_fixed = 0,
	ownership_option_takeover = 1,
	ownership_option_request = 2,
};

class CPhotonPlayer;

#pragma pack(1)
class CPhotonView : public C_Component {
char pad2[sizeof(void*)*2];

public:
    int32_t m_iOwnerId;
    int8_t m_iGroup;
    bool m_bMixedModeIsReliable;
    bool m_bOwnerShipWasTransfered;
    char pad3[0x1];
    int32_t m_iPrefixBackup;
    array_t<Il2CppObject*>* m_aInstantiationDataField;
    array_t<Il2CppObject*>* m_aLastOnSerializeDataSent;
    array_t<Il2CppObject*>* m_aLastOnSerializeDataReceived;
    view_synchronization m_synchronization;
    char pad4[0x3];
    on_serialize_transform m_onSerializeTransformOption;
    char pad5[0x3];
    on_serialize_rigid_body m_onSerializeRigidBodyOption; 
    char pad6[0x3];
    ownership_option m_ownershipTransfer;
    char pad7[0x3];
    list_t<C_Component*>* m_lObservedComponents;
    dictionary_t<C_Component*, MethodInfo*>* m_dOnSerializeMethodInfos;
    void* m_iViewIdSafe;
    int32_t m_iInstantiationID;
    int32_t m_iCurrentMasterID;
    bool m_bDidAwake;
    bool m_bIsRuntimeInstantiated;
    bool m_bRemovedFromLocalViewList;
    char pad8[0x5];
    array_t<void*>* m_aRpcMonoBehaviours;
    MethodInfo* m_onSerializeMethodInfo;
    bool m_bFailedToFindOnSerialize;

    CPhotonPlayer* getOwner() const noexcept;

};
#pragma pack()