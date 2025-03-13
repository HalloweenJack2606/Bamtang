project "Laberinto3D"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")
    files
    {
        "src/**.h",
        "src/**.cpp"
    }
    includedirs
    {
        "src",
	"vendor/GLFW/include",
        "vendor/glew/include",
        "vendor/glm",
	"vendor/stb_image"
    }
    libdirs
    {
        "vendor/glew/lib"
    }
    links
    {
        "GLFW",
        "opengl32.lib",
        "glew32s.lib"
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