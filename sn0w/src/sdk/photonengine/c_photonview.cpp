#include "c_photonview.h"
#include "c_photonplayer.h"
#include "../includes/il2cpp/il2cpp-api.h"
#include "../globals.hpp"

CPhotonPlayer* CPhotonView::getOwner() const noexcept {
    static CPhotonPlayer*(*func)(const CPhotonView*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("PhotonView"), oxorany(""), oxorany("Assembly-CSharp.dll")), oxorany("get_owner"), 0)->methodPointer);
    return func(this);
}