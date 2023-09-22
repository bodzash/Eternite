# Requirements for the game and the engine

## 3D Tech and Art

Art style is "cartoony" like LoL, WoW, Owerwatch

Handpainted textures with AO and other detail already painted into them

So there is no need for a more complicated Renderer

Character should have a 6k - 10k polygon budget in total

Optimal texture sizes should be 1024x or 512x

No need for in game lighting

Animation system

- Anim playback (no shit)
- Skinning (no shit)
- Joint attachement
- Blending between two animations
- Partial blending (seperate upperbody and lowerbody)

## VFX / Particles

Need for animated textures

Also regular textures

Transparent textures

- Cards (quads)
- Camera facing cards
- Ribbons
- Meshes
- Skinned meshes
- Decals

All these with animated textures wrapped unto them

Some above/bellow character meshes

Instanced rendering of quads

And of course need to create a Particle System

Well architected shader system >:(

3D VFX / Particle editor tool

## Asset loading

Load PNG textures and generate mipmaps with bgfx

The only material meshes need is the diffuse

One mesh can reference multiple textures

Assimp library is bloated and slow to compile so focus on one file format:

- FBX
- GLTF

Loading skeleton and animations

Need to set up Blender as a level editor :D

Loading level model and metadata

Prebake shadows in Blender

## Gameplay / Code

2D Physics engine should be good enough

Optimized Actor - Component System (not ECS)

## UI and HUD

## Networking and Netcode

Optional compile Engine in Headless mode

Server with debug draw

Config server with steam_api bullshit mode

Fuck me...

## Back-end services

Steam, PlayFab integration

Achievements

Fake and real money In-game Shop

Storing currency, characters, skins

## Packaging / Serialization

Need to convert asset files into binary

Maybe we need to put files into one big file :D

Optimize asset files for runtime

## CI/CD

More like fuck you

## Deployment of product

Distribute on Steam