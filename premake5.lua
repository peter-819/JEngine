workspace "JEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "JEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "JEngine/vendor/Glad/include"
IncludeDir["JEimgui"] = "JEngine/vendor/JEimgui"
IncludeDir["glm"] = "JEngine/vendor/glm"

include "JEngine/vendor/GLFW"
include "JEngine/vendor/Glad"
include "JEngine/vendor/JEimgui"

project "JEngine"
	location "JEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "JEpch.h"
	pchsource "JEngine/src/JEpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		
		"%{prj.name}/platform/**.h",
		"%{prj.name}/platform/**.cpp",

		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.inl"
	}

	includedirs
	{
		"JEngine/vendor/spdlog-1.x/include",
		"JEngine/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.JEimgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"JEimgui"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"JE_PLATFORM_WINDOWS",
			"JE_BUILD_DLL",
			"JE_ENABLE_ASSERTS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "JE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "JE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "JE_DIST"
		runtime "Release"
		optimize "on"


project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"JEngine/vendor/spdlog-1.x/include",
		"JEngine/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.JEimgui}"
	}

	links
	{
		"JEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"JE_PLATFORM_WINDOWS",
			"JE_BUILD_EXE",
			"JE_ENABLE_ASSERTS"
		}

	filter "configurations:Debug"
		defines "JE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "JE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "JE_DIST"
		runtime "Release"
		optimize "on"	
