# Pack files

Pack files are bundles of resources.

These files use the .pack extension and they are text format.

They are seperated by spaces and end with a new line character and they can only use ASCII characters.


They follow the following convention:

> TYPE NAME PATH

TYPE is an uint8_t - Type of asset

NAME is a std::string - Name in resource manager

PATH is a std::string - Path to file (starting from Data/)

Example of a .pack file:
```
# Fish.pack (this is a bundle of the Fish hero)
0 Fish0 Models/Champs/Fish/Fish0.gltf
1 Fish0 Models/Champs/Fish/FishAnimCommon.gltf
8 Fish Banks/Fish.fsb
6 FishVictory Audio/Champs/Fish/Speech.wav
```

List of valid TYPES: later replaced by uint8
```
MODEL           - .gltf file or engine specific
ANIMATION       - .gltf file or engine specific
TEXTURE         - Diffuse texture for Models
TEXTURE2D       - Used for particles, effects and ui
SHADER          - ...
MATERIAL        - ...
AUDIO           - .wav .ogg or some other file
AUDIOStream     - .wav .ogg or some other file
AUDIOBank       - .fsb export from FMOD
PACK            - This type of file
```