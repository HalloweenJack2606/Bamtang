workspace "Fisica"
    architecture "x64"
    startproject "Fisica"
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
    include "Fisica/vendor/GLFW"
group ""

include "Fisica"