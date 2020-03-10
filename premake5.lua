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
IncludeDir["imgui"] = "JEngine/vendor/imgui"

include "JEngine/vendor/GLFW"
include "JEngine/vendor/Glad"
include "JEngine/vendor/imgui"

project "JEngine"
	location "JEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "JEpch.h"
	pchsource "JEngine/src/JEpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/platform/**.h",
		"%{prj.name}/platform/**.cpp"
	}

	includedirs
	{
		"JEngine/vendor/spdlog-1.x/include",
		"JEngine/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"imgui"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"JE_PLATFORM_WINDOWS",
			"JE_BUILD_DLL",
			"JE_ENABLE_ASSERTS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox")
		}
	filter "configurations:Debug"
		defines "JE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "JE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "JE_DIST"
		runtime "Release"
		optimize "On"


project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"JEngine/src"
	}

	links
	{
		"JEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
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
		symbols "On"

	filter "configurations:Release"
		defines "JE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "JE_DIST"
		runtime "Release"
		optimize "On"	
