-- this premake file is quite bad, because I just start with premake and lua.
-- This file is written to build on archlinux and windows8 (with codeblocks).
-- I use static linking on windows.

solution "Color-Project"
  configurations {"Release"}

  -- engine --
  project "engine"
    kind "StaticLib"
    language "c++"
    files {"src/Engine/**.hpp", "src/Engine/**.cpp"}

    configuration "Release"
      flags { "Optimize" }
      buildoptions "-std=c++11"
      if os.get() == "windows" then
        defines { "SFML_STATIC" }
      end

  -- game --
  project "game"
    kind "WindowedApp"
    language "c++"
    files {"src/Game/**.hpp", "src/Game/**.cpp"}

    configuration "Release"
      flags { "Optimize" }
      buildoptions "-std=c++11"
      links { "engine", "jsoncpp" }
      if os.get() == "windows" then
        defines { "SFML_STATIC" }
        links { "sfml-graphics-s", "sfml-window-s", "sfml-system-s", "sfml-audio-s" }
      else
        links { "sfml-graphics", "sfml-window", "sfml-system", "sfml-audio" }
      end
      
  -- editor --
  project "editor"
    kind "WindowedApp"
    language "c++"
    files {"src/Editor/**.hpp", "src/Editor/**.cpp"}
    
    configuration "Release"
      flags { "Optimize" }
      buildoptions "-std=c++11"
