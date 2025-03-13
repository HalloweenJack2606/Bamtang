workspace "Laberinto"
    architecture "x64"
    startproject "Laberinto"
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
    include "Laberinto/vendor/GLFW"
group ""

include "Laberinto"