-- this premake file is quite bad, because I just start with premake.

solution "Color-Project"

   configurations {"Release"}
 
   project "game"
      kind "WindowedApp"
      language "C++"
      files {"src/**.h", "src/**.cpp"}
 
      configuration "Release"
         flags { "Optimize" }
         buildoptions "-std=c++11"  
         links { "sfml-graphics", "sfml-window", "sfml-system", "sfml-audio", "jsoncpp" }
