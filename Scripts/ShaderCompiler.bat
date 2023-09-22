@ECHO OFF
ECHO [INFO]: Compiling shaders...

REM Static mesh
@ECHO OFF
START ../Bin/shaderc -f ../Resources/Shaders/StaticMesh/StaticMesh.vert^
 -o ../Resources/Shaders/DirectX9/StaticMesh.bvs^
 --type vertex -i ../External/bgfx.cmake/bgfx/src --platform windows^
 --varyingdef ../Resources/Shaders/StaticMesh/StaticMesh.def -p s_3_0
@ECHO ON

@ECHO OFF
START ../Bin/shaderc -f ../Resources/Shaders/StaticMesh/StaticMesh.frag^
 -o ../Resources/Shaders/DirectX9/StaticMesh.bfs^
 --type fragment -i ../External/bgfx.cmake/bgfx/src --platform windows^
 --varyingdef ../Resources/Shaders/StaticMesh/StaticMesh.def -p s_3_0
@ECHO ON

@ECHO OFF
REM Skybox

@ECHO OFF
START ../Bin/shaderc -f ../Resources/Shaders/Skybox/Skybox.vert^
 -o ../Resources/Shaders/DirectX9/Skybox.bvs^
 --type vertex -i ../External/bgfx.cmake/bgfx/src --platform windows^
 --varyingdef ../Resources/Shaders/Skybox/Skybox.def -p s_3_0
@ECHO ON

@ECHO OFF
START ../Bin/shaderc -f ../Resources/Shaders/Skybox/Skybox.frag^
 -o ../Resources/Shaders/DirectX9/Skybox.bfs^
 --type fragment -i ../External/bgfx.cmake/bgfx/src --platform windows^
 --varyingdef ../Resources/Shaders/Skybox/Skybox.def -p s_3_0
@ECHO ON

@ECHO OFF
REM ScreenQuad

@ECHO OFF
START ../Bin/shaderc -f ../Resources/Shaders/ScreenQuad/ScreenQuad.vert^
 -o ../Resources/Shaders/DirectX9/ScreenQuad.bvs^
 --type vertex -i ../External/bgfx.cmake/bgfx/src --platform windows^
 --varyingdef ../Resources/Shaders/ScreenQuad/ScreenQuad.def -p s_3_0
@ECHO ON

@ECHO OFF
START ../Bin/shaderc -f ../Resources/Shaders/ScreenQuad/ScreenQuad.frag^
 -o ../Resources/Shaders/DirectX9/ScreenQuad.bfs^
 --type fragment -i ../External/bgfx.cmake/bgfx/src --platform windows^
 --varyingdef ../Resources/Shaders/ScreenQuad/ScreenQuad.def -p s_3_0
@ECHO ON

@ECHO OFF
REM TransQuad

@ECHO OFF
START ../Bin/shaderc -f ../Resources/Shaders/TransQuad/TransQuad.vert^
 -o ../Resources/Shaders/DirectX9/TransQuad.bvs^
 --type vertex -i ../External/bgfx.cmake/bgfx/src --platform windows^
 --varyingdef ../Resources/Shaders/TransQuad/TransQuad.def -p s_3_0
@ECHO ON

@ECHO OFF
START ../Bin/shaderc -f ../Resources/Shaders/TransQuad/TransQuad.frag^
 -o ../Resources/Shaders/DirectX9/TransQuad.bfs^
 --type fragment -i ../External/bgfx.cmake/bgfx/src --platform windows^
 --varyingdef ../Resources/Shaders/TransQuad/TransQuad.def -p s_3_0
@ECHO ON

@ECHO OFF
REM GBuffer

@ECHO OFF
START ../Bin/shaderc -f ../Resources/Shaders/Deferred/GBuffer.vert^
 -o ../Resources/Shaders/DirectX9/GBuffer.bvs^
 --type vertex -i ../External/bgfx.cmake/bgfx/src --platform windows^
 --varyingdef ../Resources/Shaders/Deferred/GBuffer.def -p s_3_0
@ECHO ON

@ECHO OFF
START ../Bin/shaderc -f ../Resources/Shaders/Deferred/GBuffer.frag^
 -o ../Resources/Shaders/DirectX9/GBuffer.bfs^
 --type fragment -i ../External/bgfx.cmake/bgfx/src --platform windows^
 --varyingdef ../Resources/Shaders/Deferred/GBuffer.def -p s_3_0
@ECHO ON

@ECHO OFF
REM LightingPass

@ECHO OFF
START ../Bin/shaderc -f ../Resources/Shaders/Deferred/LightingPass.vert^
 -o ../Resources/Shaders/DirectX9/LightingPass.bvs^
 --type vertex -i ../External/bgfx.cmake/bgfx/src --platform windows^
 --varyingdef ../Resources/Shaders/Deferred/LightingPass.def -p s_3_0
@ECHO ON

@ECHO OFF
START ../Bin/shaderc -f ../Resources/Shaders/Deferred/LightingPass.frag^
 -o ../Resources/Shaders/DirectX9/LightingPass.bfs^
 --type fragment -i ../External/bgfx.cmake/bgfx/src --platform windows^
 --varyingdef ../Resources/Shaders/Deferred/LightingPass.def -p s_3_0
@ECHO ON

@ECHO OFF
REM shaderc std out will be displayed here
PAUSE