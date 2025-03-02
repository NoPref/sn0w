#pragma once
#include <stdint.h>

struct delegate_t {
char pad[sizeof(void*)*2];
public:
    void* m_pMethod;
	void* m_pInvokeImpl;
	void* m_target; 
	void* m_method;
	void* m_delegateTrampoline;
	void* m_extraArg;
	void* m_methodCode; 
	void* m_interpMethod; 
	void* m_interpInvokeImpl;
	void* m_methodInfo;
	void* m_originalMethodInfo;
	void* m_data;
	bool m_bMethodIsVirtual;

    void hook(void* hk, void** origin) noexcept;
};