cmake_minimum_required( VERSION 3.6 )

set(CMAKE_CXX_STANDARD 17)

project( HDK_Project )

# CMAKE_PREFIX_PATH must contain the path to the toolkit/cmake subdirectory of
# the Houdini installation. See the "Compiling with CMake" section of the HDK
# documentation for more details, which describes several options for
# specifying this path.
list( APPEND CMAKE_PREFIX_PATH "$ENV{HFS}/toolkit/cmake" )

# Locate Houdini's libraries and header files.
# Registers an imported library target named 'Houdini'.
find_package( Houdini REQUIRED )

set( library_name SOP_Star )

#set(CMAKE_CXX_STANDARD 11)

# Code generation for the embedded DS file in SOP_Star.C.
houdini_generate_proto_headers( FILES SOP_Terrain.cpp )

# Add a library and its source files.
add_library( ${library_name} SHARED
    SOP_Terrain.cpp
    SOP_Terrain.hpp
)

add_library( TerrainModel
    TerrainModel/Nutrients.hpp
    TerrainModel/Nutrients.cpp
    TerrainModel/TerrainAgent.hpp
    TerrainModel/TerrainFormation.hpp
    TerrainModel/TerrainMessage.hpp
    TerrainModel/TerrainSimulation.hpp
    TerrainModel/Water.cpp
    TerrainModel/Water.hpp
    TerrainModel/TerrainFormation.cpp
    TerrainModel/TerrainSimulation.cpp
    TerrainModel/TerrainAgent.cpp
    TerrainModel/TerrainMessage.cpp
    TerrainModel/Lookup.hpp
    TerrainModel/TerrainFormationConstructors.cpp
    TerrainModel/TerrainFormationProcess.cpp
    TerrainModel/Utility/Vector.hpp
    TerrainModel/Utility/Vector.cpp
        )


# Link against the Houdini libraries, and add required include directories and
# compile definitions.
target_link_libraries( ${library_name} Houdini TerrainModel)

# Include ${CMAKE_CURRENT_BINARY_DIR} for the generated header.
target_include_directories( ${library_name} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)


# Sets several common target properties, such as the library's output directory.
houdini_configure_target( ${library_name} )
