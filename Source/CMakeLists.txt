# Name the Project and give files
set(GAME_NAME Ripple_Effects)

# I could use this to get all files, but then it wouldn't include headers in the file tree
# or automatically find new files
# file(GLOB CPP_HEADER_SOURCES
	# "*.cpp"
	# ".h"
# )

set(Actor_Files
	Actor.cpp
	Actor.h
	BarrelBehavior.cpp
	BarrelBehavior.h
	CarrierBehavior.cpp
	CarrierBehavior.h
	Component.cpp
	Component.h
	PlayerBehavior.cpp
	PlayerBehavior.h
	RigidBody.cpp
	RigidBody.h
	RippleGFX.cpp
	RippleGFX.h
	RipplePhysics.cpp
	RipplePhysics.h
	Sprite.cpp
	Sprite.h
)
set(Devices_Files
	CircleRGBA.cpp
	CircleRGBA.h
	GraphicsDevice.cpp
	GraphicsDevice.h
	InputDevice.cpp
	InputDevice.h
	Texture.cpp
	Texture.h
	Timer.cpp
	Timer.h
)

set(Libraries_Files
	ArtAssetLibrary.cpp
	ArtAssetLibrary.h
	MusicAssetLibrary.cpp
	MusicAssetLibrary.h
	PhysicsAssetLibrary.cpp
	PhysicsAssetLibrary.h
)

add_executable(${GAME_NAME}
	${Actor_Files}
	${Devices_Files}
	${Libraries_Files}
	Box2DDebugDraw.cpp
	Box2DDebugDraw.h
	Definitions.h
	Game.cpp
	Game.h
	MyContactListener.cpp
	MyContactListener.h
	ResourceManager.cpp
	ResourceManager.h
	Source.cpp
	View.cpp
	View.h
)

# Make VS filters
source_group(Actor_Files FILES ${Actor_Files})
source_group(Devices_Files FILES ${Devices_Files})
source_group(Libraries_Files FILES ${Libraries_Files})

# Includes..
include_directories(
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	${SDL2_MIXER_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
	${Box2D_SOURCE_DIR}
	${tinyxml_SOURCE_DIR}
	${SDL2_gfx_SOURCE_DIR}
)

# What it should link against
target_link_libraries(${GAME_NAME}
	${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2_MIXER_LIBRARY}
	${SDL2_TTF_LIBRARY}
	Box2D
	tinyxml
	SDL2_gfx
)

if(MSVC)
	# Tell VS where to build the executable for both debug and release versions
	set_target_properties(${GAME_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Game")
	set_target_properties(${GAME_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Game")
	
	# Copy Assets where both VS can find them (it doesn't look in the Game folder) and the Game folder
	file(COPY "${CMAKE_SOURCE_DIR}/Assets" DESTINATION ${PROJECT_BINARY_DIR}/Source)
	file(COPY "${CMAKE_SOURCE_DIR}/Assets" DESTINATION ${CMAKE_SOURCE_DIR}/Game)
	
	# Copy Config where both VS can find them (it doesn't look in the Game folder) and the Game folder
	file(COPY "${CMAKE_SOURCE_DIR}/Config" DESTINATION ${PROJECT_BINARY_DIR}/Source)
	file(COPY "${CMAKE_SOURCE_DIR}/Config" DESTINATION ${CMAKE_SOURCE_DIR}/Game)
	
	# Find and copy 32-bit DLLs to Game folder
	file(GLOB X86_DLL_FILES 
			${SDL2_HOME}/lib/x86/*.dll
			${SDL2_IMAGE_HOME}/lib/x86/*.dll
			${SDL2_MIXER_HOME}/lib/x86/*.dll
			${SDL2_TTF_HOME}/lib/x86/*.dll
	)
	file(COPY ${X86_DLL_FILES} DESTINATION ${CMAKE_SOURCE_DIR}/Game)
endif()
