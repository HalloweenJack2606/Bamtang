workspace "Cipher"
    architecture "x64"
    startproject "Cipher"
    configurations
    {
        "Debug",
        "Release"
    }
    flags
    {
        "MultiProcessorCompile"
    }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Cipher"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files
    {
        "src/**.h",
        "src/**.cpp"
    }
    includedirs
    {
        "src",
    }
    defines "_CRT_SECURE_NO_WARNINGS"
    filter "system:windows"
        systemversion "latest"
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    filter "configurations:Release"
        runtime "Release"
        optimize "on"