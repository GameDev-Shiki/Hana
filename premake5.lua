workspace "Hana"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hana/vendor/GLFW/include"
IncludeDir["Glad"] = "Hana/vendor/Glad/include"
IncludeDir["ImGui"] = "Hana/vendor/imgui"
IncludeDir["glm"] = "Hana/vendor/glm"
IncludeDir["stb_image"] = "Hana/vendor/stb_image"

group "Dependencies"
	include "Hana/vendor/GLFW"
	include "Hana/vendor/Glad"
	include "Hana/vendor/imgui"

group ""

project "Hana"
	location "Hana"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hnpch.h"
	pchsource "Hana/src/hnpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HN_PLATFORM_WINDOWS",
			"HN_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

	filter "configurations:Debug"
		defines "HN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HN_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
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
		"Hana/vendor/spdlog/include",
		"Hana/src",
		"Hana/vendor",
		"%{IncludeDir.glm}",
	}

	links
	{
		"Hana"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HN_DIST"
		runtime "Release"
		optimize "on"
