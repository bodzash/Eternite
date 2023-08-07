@ECHO OFF
ECHO [INFO]: Compiling textures...

REM Regular model textures shold use ETC1 or the other one
REM texturec -f ./Assets/Jack/HandsomeJack_Diff.png -o ./build/Debug/Jack/HandsomeJack_Diff.dds --mips -t ETC1
REM texturec -f ./Assets/Jack/HandsomeJackMask_Diff.png -o ./build/Debug/Jack/HandsomeJackMask_Diff.dds --mips -t ETC1

REM texturec -f ./Assets/Angel/Vog_Dif.png -o ./build/Debug/Angel/Vog_Dif.dds --mips -t ETC1
REM texturec -f ./Assets/Angel/Vog_Dif_s.png -o ./build/Debug/Angel/Vog_Dif_s.dds --mips -t ETC1

REM texturec -f ./Assets/Vampire/textures/Vampire_diffuse.png -o ./build/Debug/Vampire/textures/Vampire_diffuse.dds --mips -t ETC1
REM texturec -f ./Assets/Vampire/textures/Vampire_specular.png -o ./build/Debug/Vampire/textures/Vampire_specular.dds --mips -t ETC1

REM Transparent textures should use RGBA8 or BGRA8
REM texturec -f ./Assets/Grass.png -o ./build/Debug/Grass.dds --mips -t RGBA8

REM Skybox textures should use NO mipmaps and RGB8 or another losless format
REM texturec -f ./Assets/Skybox.png -o ./build/Debug/Skybox.dds --strip -t RGB8
REM texturec -f ./Assets/SkyboxDay.png -o ./build/Debug/SkyboxDay.dds --strip -t RGB8

START ../Bin/texturec -f ../Resources/Models/Jack/HandsomeJack_Diff.png -o ../Resources/Models/Jack/HandsomeJack_Diff.dds --mips -t ETC1
START ../Bin/texturec -f ../Resources/Models/Jack/HandsomeJackMask_Diff.png -o ../Resources/Models/Jack/HandsomeJackMask_Diff.dds --mips -t ETC1

START ../Bin/texturec -f ../Resources/Models/Angel/Vog_Dif.png -o ../Resources/Models/Angel/Vog_Dif.dds --mips -t ETC1
START ../Bin/texturec -f ../Resources/Models/Angel/Vog_Dif_s.png -o ../Resources/Models/Angel/Vog_Dif_s.dds --mips -t ETC1

REM START ../Bin/texturec -f ../Resources/Textures/Skyboxes/SkyboxDay.png -o ../Resources/Textures/Skyboxes/SkyboxDay.dds --strip -t RGB8

@ECHO ON

@ECHO OFF
PAUSE