#include <string.h>
#include "consts.hpp"
#include "../includes/oxorany/include.h"

const char* consts::libil2cpp_so() noexcept {
    static char buff[13]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("libil2cpp.so"));
    return buff;
} 
const char* consts::libunity_so() noexcept {
    static char buff[12]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("libunity.so"));
    return buff;
} 
const char* consts::gettouch() noexcept {
    static char buff[36]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("UnityEngine.Input::get_touchCount()"));
    return buff;
}
const char* consts::raycast() noexcept {
    static char buff[183]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("UnityEngine.PhysicsScene::Internal_Raycast_Injected(UnityEngine.PhysicsScene&,UnityEngine.Ray&,System.Single,UnityEngine.RaycastHit&,System.Int32,UnityEngine.QueryTriggerInteraction"));
    return buff;
} 
const char* consts::inputfield() noexcept { 
    static char buff[19]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("InputFieldNoInsert"));
    return buff;
}
const char* consts::inputfield_type() noexcept {
    static char buff[71]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("Axlebolt.Standoff.Game.UI.Chat.InputFieldNoInsert, Assembly-CSharp.dll"));
    return buff;
} 
const char* consts::axleboltchat() noexcept { 
    static char buff[31]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("Axlebolt.Standoff.Game.UI.Chat"));
    return buff;
}
const char* consts::assembly_csharp() noexcept {
    static char buff[20]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("Assembly-CSharp.dll"));
    return buff;
}
const char* consts::lateupdate() noexcept { 
    static char buff[11]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("LateUpdate"));
    return buff;
}
const char* consts::gameobject() noexcept { 
    static char buff[11]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("GameObject"));
    return buff;
}
const char* consts::unityengine() noexcept { 
    static char buff[12]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("UnityEngine"));
    return buff;
}
const char* consts::unitycoremodule() noexcept { 
    static char buff[27]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("UnityEngine.CoreModule.dll"));
    return buff;
}
const char* consts::server_ip() noexcept { 
    static char buff[21]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("91.200.150.173:50008"));
    return buff;
}
const char* consts::encrypt_key() noexcept { 
    static char buff[32]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("0gbpdnf6az2z8uzvru8q3h34flcjv33"));
    return buff;
}
const char* consts::getinternet() noexcept { 
    static char buff[52]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("UnityEngine.Application::get_internetReachability()"));
    return buff;
}
const char* consts::keypath() noexcept { 
    static char buff[71]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("/storage/emulated/0/Android/data/com.axlebolt.standoff2/cache/sn0w.key"));
    return buff;
}
const char* consts::regex() noexcept { 
    static char buff[19]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("^[a-zA-Z0-9_]{19}$"));
    return buff;
}
const char* consts::getmodel() noexcept { 
    static char buff[41]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("UnityEngine.SystemInfo::GetDeviceModel()"));
    return buff;
}
const char* consts::getname() noexcept { 
    static char buff[40]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("UnityEngine.SystemInfo::GetDeviceName()"));
    return buff;
}
const char* consts::getuid() noexcept { 
    static char buff[52]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("UnityEngine.SystemInfo::GetDeviceUniqueIdentifier()"));
    return buff;
}
const char* consts::key() noexcept { 
    static char buff[4]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("key"));
    return buff;
}
const char* consts::hwid() noexcept { 
    static char buff[5]{};
    if(buff[0] == NULL)
        strcpy(buff, oxorany("hwid"));
    return buff;
}