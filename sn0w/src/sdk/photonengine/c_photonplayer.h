#pragma once
#include <stdint.h>
#include "../unity/common/include.h"
#include "../includes/il2cpp/il2cpp-api.h"
#include "../so2/common/enums.h"
#include "../includes/oxorany/include.h"

#pragma pack(1)
class CPhotonPlayer {
char pad[sizeof(void*)*3];
public:
    int32_t m_iActorID;
    char pad2[0x4];
    string_t* m_sNameField;
    string_t* m_sUserID;
    bool m_bIsLocal;
    bool m_bIsInactive;
    char pad3[0x6];
    dictionary_t<string_t*, void*>* m_dCustomProperties;

    template<typename T>
    T getProperty(const char* const& szProp) const noexcept {
        if(this->m_dCustomProperties != NULL) {
            if(this->m_dCustomProperties->isValid()) {
                for(uint32_t i=0;i<this->m_dCustomProperties->getSize();++i) {
                    const string_t* key   = this->m_dCustomProperties->get(i).m_key;
                    const void*     value = this->m_dCustomProperties->get(i).m_value;
                    if(key != NULL && value != NULL) {
                        if(!strcmp(szProp, key->toUTF8().c_str())) {
                            return *(T*)((unsigned long long)value + oxorany(0x10));
                        }
                    }
                }
            }
        }
        return (T)0;
    }

    template<typename T>
    T setProperty(const char* const& szProp, T value) const noexcept {
        if(this->m_dCustomProperties != NULL) {
            if(this->m_dCustomProperties->isValid()) {
                for(uint16_t i=0;i<this->m_dCustomProperties->getSize();++i) {
                    const string_t* key   = this->m_dCustomProperties->get(i).m_key;
                    const void*     value = this->m_dCustomProperties->get(i).m_value;
                    if(key != NULL && value != NULL) {
                        if(!strcmp(szProp, key->toUTF8().c_str())) {
                            *(T*)((unsigned long long)value + oxorany(0x10)) = value;
                        }
                    }
                }
            }
        }
        return (T)0;
    }

    int getHealth() const noexcept;
    int getArmor() const noexcept;
    team getTeam() const noexcept;
    bool getHasHelmet() const noexcept;
    bool getIsUntouchable() const noexcept;
};
#pragma pack()