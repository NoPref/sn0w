#pragma once

//due to llvm obfuscator strings are not encrypted and can be visibile in decompiler (i dont want it)
//this header is optional and is only needed for obfuscated cpps
namespace consts {
    const char* libil2cpp_so() noexcept;
    const char* libunity_so() noexcept;
    const char* gettouch() noexcept;
    const char* raycast() noexcept;
    const char* inputfield() noexcept;
    const char* inputfield_type() noexcept;
    const char* axleboltchat() noexcept;
    const char* assembly_csharp() noexcept;
    const char* lateupdate() noexcept;
    const char* gameobject() noexcept;
    const char* unityengine() noexcept;
    const char* unitycoremodule() noexcept;
    const char* server_ip() noexcept;
    const char* encrypt_key() noexcept;
    const char* getinternet() noexcept;
    const char* keypath() noexcept;
    const char* regex() noexcept;
    const char* getmodel() noexcept;
    const char* getname() noexcept;
    const char* getuid() noexcept;
    const char* key() noexcept;
    const char* hwid() noexcept;
};