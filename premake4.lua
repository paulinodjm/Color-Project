-- this premake file is quite bad, because I just start with premake and lua.
-- This file is written to build on archlinux and windows8 (with codeblocks).

solution "Color-Project"
  configurations {"Release"}

  -- engine --
  project "engine"
    kind "StaticLib"
    language "c++"
    files {"src/Engine/**.hpp", "src/Engine/**.cpp"}

    configuration "Release"
      flags { "Optimize" }
      buildoptions "-std=gnu++11"

  -- game --
  project "game"
	kind "WindowedApp"
    language "c++"
	files {"src/Game/**.hpp", "src/Game/**.cpp"}

    configuration "Release"
      flags { "Optimize" }
      buildoptions "-std=gnu++11"
      links { "engine", "jsoncpp", "sfml-graphics", "sfml-window", "sfml-system", "sfml-audio" }
      
  -- editor --
  project "editor"
    kind "WindowedApp"
    language "c++"
    files {"src/Editor/**.hpp", "src/Editor/**.cpp", "src/Game/GameTypes.cpp"}
    
    configuration "Release"
      flags { "Optimize" }
      buildoptions "-std=gnu++11"
      links { "engine", "jsoncpp", "sfml-graphics", "sfml-window", "sfml-system", "sfml-audio" }
      
      -- wx windows flags --
      if os.get() == "windows" then
        files { "src/Editor/resources.rc" }
        buildoptions { "`wx-config.exe --cxxflags --prefix=c:/wxWidgets-2.8.12 --wxcfg=gcc_lib/msw`" }
        linkoptions { "`wx-config.exe --libs --prefix=c:/wxWidgets-2.8.12 --wxcfg=gcc_lib/msw`" }
        resincludedirs { "c:/wxWidgets-2.8.12/include" }
      
      -- wx linux flags --
      elseif os.get() == "linux" then
        buildoptions { "`wx-config --cxxflags`" }
        includedirs 
        { 
          "/usr/include/gtk-2.0/", 
          "/usr/include/glib-2.0",
          "/usr/lib/glib-2.0/include",
          "/usr/include/cairo",
          "/usr/include/pango-1.0",
          "/usr/lib/gtk-2.0/include", 
          "/usr/include/gdk-pixbuf-2.0", 
          "/usr/include/atk-1.0"
        }
        linkoptions { 
          "`wx-config --libs`",
          "/usr/lib/libgdk-x11-2.0.so.0", 
          "/usr/lib/libgtk-x11-2.0.so.0", 
          "/usr/lib/libgobject-2.0.so.0", 
          "/usr/lib/libX11.so.6" 
        }
      end
	
