import os
import sys
import subprocess

# TODO: implement unix timestamping of shit FOR TEXTURE lol :D
# TODO: from bgfx_shader.sh remove the predefined uniforms at the bottom

"""
    Argument list
    -dxlevel | 9, 11, 12  | DirectX version.                   | Defaults to 9
    -oplevel | 0, 1, 2, 3 | Optimization level. (DX9 and DX11) | Defaults to 0
"""

# Arguments
argc = len(sys.argv)
argv = sys.argv[1:]
opt_dxlevel = ""
opt_oplevel = ""

# Path definitions
in_folder: str = "../Content/Shaders/"
out_folder: str = "../Content/Shaders/DirectX9/" # TODO: remove hard coded
compiler_path: str = "../Binaries/Win32/shaderc" # TODO: only use Win64
varying_path: str = "../Content/Shaders/Varying.def"
include_path: str = "../External/bgfx.cmake/bgfx/src"

# Sanitize arguments

# Apply arguments
opt_dxlevel = argv[argv.index("-dxlevel") + 1]
# out_folder = "../Data/Shaders/D3D" + argv[argv.index("-dxlevel") + 1]
profile_model = ""
if opt_dxlevel == "9":
    profile_model = "s_3_0"
else:
    profile_model = "s_5_0"

opt_oplevel = argv[argv.index("-oplevel") + 1]

# Functions
def sanitize_args():
    pass

def apply_args():
    pass

def compile_vertex(shader: str):
    in_path: str = f"-f {in_folder}{shader}"
    out_path: str = f"-o {out_folder}{shader}".replace(".vert", ".bvs")
    type: str = "--type vertex"
    include: str = f"-i {include_path}"
    platform: str = "--platform windows"
    varying: str = f"--varyingdef {varying_path}"
    profile: str = f"-p {profile_model}"
    optlevel: str = f"-O {opt_oplevel}"

    command = [compiler_path, in_path, out_path, type, include, platform, varying, profile, optlevel]
    exitcode = subprocess.run(" ".join(command).split(" ")).returncode

    exitcode or print(f"Compiled {shader}")
    exitcode and print(f"Failed {shader}")

def compile_fragment(shader: str):   
    in_path: str = f"-f {in_folder}{shader}"
    out_path: str = f"-o {out_folder}{shader}".replace(".frag", ".bfs")
    type: str = "--type fragment"
    include: str = f"-i {include_path}"
    platform: str = "--platform windows"
    varying: str = f"--varyingdef {varying_path}"
    profile: str = f"-p {profile_model}"
    optlevel: str = f"-O {opt_oplevel}"

    command = [compiler_path, in_path, out_path, type, include, platform, varying, profile, optlevel]
    exitcode = subprocess.run(" ".join(command).split(" ")).returncode

    exitcode or print(f"Compiled {shader}")
    exitcode and print(f"Failed {shader}")

# Main
print("\n--- Shader Compiler Script ---")
print(f"DirectX: {opt_dxlevel} | Optimization: {opt_oplevel}\n")

for f in os.listdir(in_folder):
    if f.endswith(".frag"):
        compile_fragment(f)
        continue

    if f.endswith(".vert"):
        compile_vertex(f)