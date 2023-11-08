# Mobile requirements for the Engine and Game

A collection of libraries to change to later.

## Interop (Objective C, Switft, Java, Kotlin)

AdMob: Java library for showing ads. (Naughty shit, probably won't do this.)

Android NDK - Native Development Kit

JNI - Java Native Interface

TODO: do more research about this.

## Windowing / Multimedia / Foundation (C++)

[SDL3](https://github.com/libsdl-org/SDL) is the GOAT.

No question about it, supports mobile, desktop and consoles.

## Renderer (C++)

Raylib is not supported on iOS, so it's not an option.

### [BGFX](https://github.com/bkaradzic/bgfx)

It's a crossplatform graphics middleware, need to make a renderer with it.

Allows for optimisation, although OGRE is already optimized.

Could make a simple, lean and mean one, also with skeletal animation support. (Copy how Raylib does animations)

Need to use [TinyGLTF]() for model loading.

### [OGRE](https://github.com/OGRECave/ogre)

A fully featured renderer, with shadowmapping, lighting and all that shit already implemented.

Includes a lot of VERY useful things, it's also modular, so the useless modules can be omitted.

## Audio (C++)

[FMOD Core](https://www.fmod.com/core) is the GOAT.

No question about it, unfortunately need to pay licensing.

Very powerful features like banking, cross platform, mixing.

## Networking (C++)

Easy to switch to from SteamworksSDK.

Valve's GNS library can be used both on iOS and Android.

Although there is no official CMake support for them.

Valve shipped Dote Underlords with it, so it's also proven.

[GameNetworkingSockets](https://github.com/ValveSoftware/GameNetworkingSockets) is the only option, also the GOAT, so that settles it.

## Back-End Services (C++)

[Playfab](https://playfab.com/) is the GOAT.

It provides a lot of control over a lot of things.

Use the "Legacy" C++ SDK until the new one gets full Mobile support.