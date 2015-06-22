It's safe to unzip Box2D_v2.1.2 here.

liquidfun-1.1.0.zip should be unzipped inside liquidfun-1.1.0/
Then, edit liquidfun-1.1.0/liquidfun/Box2D/CMakeLists.txt by adding 
`FindPackage(Threads)` beneath `project(Box2D)` so it will build properly.
Alternatively, use the original Box2D library in the root CMakeLists.txt.
By doing this, the project will build faster, but you will lose functionality.

SDL2_gfx-1.0.1.zip should be unzipped inside SDL2_gfx/

tinyxml_2_6_2.zip should be unzipped inside tinyxml/

