workspace "vegan"
  configurations { "debug", "release" }

project "veganc++"
  kind "StaticLib"
  language "C++"
  cppdialect "C++20"
  targetdir "lib/"
  symbols "On"

  files { "include/vegan/*.h",
          "include/vegan/*/*.h",
          "src/*.cpp" }
  includedirs { "include" }

project "sort"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"
  symbols "On"

  files { "examples/sort.cpp" }
  includedirs { "include" }
  links { "veganc++" }

project "wc"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"
  symbols "On"

  files { "examples/wc.cpp" }
  includedirs { "include" }
  links { "veganc++" }
