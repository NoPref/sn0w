cmake_minimum_required(VERSION 3.10)

set(ANDROID_NDK "/home/nopref/.androidStudioSDK/ndk/28.0.13004108")
set(CMAKE_SYSTEM_NAME ANDROID)
set(CMAKE_SYSTEM_VERSION 30) 
set(ANDROID_PLATFORM 30)
set(ANDROID_ABI arm64-v8a) 
set(CMAKE_TOOLCHAIN_FILE "${ANDROID_NDK}/build/cmake/android.toolchain.cmake")

project(sn0w)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_C_FLAGS "-ffixed-x18 -Wl,--hash-style=both -O2 -fvisibility=hidden -fvisibility-inlines-hidden -Wno-deprecated-volatile -Wno-tautological-undefined-compare -Wno-tautological-pointer-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -fno-rtti -static-libstdc++")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-exclude-libs,ALL -Wl,--gc-sections -Wl,--strip-all")
set(CMAKE_MODULE_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS})

include_directories(
	sn0w/
	sn0w/src/
	sn0w/src/render/engine
	sn0w/src/render/imgui
	sn0w/src/sdk
	sn0w/src/sdk/unity
	sn0w/src/sdk/unity/common
	sn0w/src/sdk/photonengine
	sn0w/src/sdk/so2
	sn0w/src/sdk/so2/common
	sn0w/src/sdk/sn0w
	sn0w/src/features
	sn0w/src/ui
	sn0w/src/authorization
	sn0w/includes/
	sn0w/includes/xdl
	sn0w/includes/xdl/include
	sn0w/includes/oxorany
	sn0w/includes/a64hook
	sn0w/includes/il2cpp
	sn0w/includes/imgui
	sn0w/includes/imgui/backends
	sn0w/includes/imgui/fonts
	sn0w/includes/http
	sn0w/includes/http/openssl
	sn0w/includes/http/curl
	sn0w/includes/utils
	sn0w/libs
)

file(GLOB includes
	sn0w/includes/xdl/*.c
	sn0w/includes/a64hook/And64InlineHook.cpp
	sn0w/includes/il2cpp/il2cpp-api.cpp
	sn0w/includes/utils/*.c
)

file(GLOB src
	#sn0w/src/*.cpp
	sn0w/src/config.cpp
)

file(GLOB render
	sn0w/src/render/*.cpp
	sn0w/src/render/engine/*.cpp
	sn0w/src/render/imgui/*.cpp
)

file(GLOB features
	sn0w/src/features/*.cpp
)

file(GLOB ui
	sn0w/src/ui/*.cpp
)

file(GLOB authorization
	sn0w/src/authorization/*.cpp
)

file(GLOB sdk
	sn0w/src/sdk/unity/*.cpp
	sn0w/src/sdk/unity/common/*.cpp
	sn0w/src/sdk/photonengine/*.cpp
	sn0w/src/sdk/so2/*.cpp
	sn0w/src/sdk/so2/common/*.cpp
	sn0w/src/sdk/sn0w/*.cpp
)

file(GLOB imgui
	sn0w/includes/imgui/*.cpp
	sn0w/includes/imgui/backends/*.cpp
)

file(GLOB protection
	sn0w/src/protection/*.cpp
)

add_library(obfuscated OBJECT 
	sn0w/src/main.cpp
	sn0w/src/globals.cpp
	sn0w/src/hooking.cpp
	#${authorization}
)

set_target_properties(obfuscated PROPERTIES
	#COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -mllvm -sub -mllvm -bcf -mllvm -fla -mllvm -split"
	COMPILE_FLAGS "${CMAKE_CXX_FLAGS}"
)

add_library(sn0w SHARED 
	${includes}
	${src}
	$<TARGET_OBJECTS:obfuscated>
	${render}
	${features}
	${ui}
	${sdk}
	${imgui}
	${protection}
)

set_target_properties(sn0w PROPERTIES
	PREFIX "lib" 
 	OUTPUT_NAME "sn0w" 
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out"
)

find_library(liblog log)
find_library(libandroid android)

target_link_libraries(sn0w
	${liblog}
	${libandroid}
	${CMAKE_SOURCE_DIR}/sn0w/libs/libcrypto.a
	${CMAKE_SOURCE_DIR}/sn0w/libs/libssl.a
	${CMAKE_SOURCE_DIR}/sn0w/libs/libcurl.a
)