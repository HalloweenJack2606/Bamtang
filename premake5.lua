workspace "Laberinto3D"
    architecture "x64"
    startproject "Laberinto3D"
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

group "Dependencies"
    include "Laberinto3D/vendor/GLFW"
group ""

include "Laberinto3D"