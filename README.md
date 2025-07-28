# Pyroveil

Pyroveil is a Vulkan layer that can automatically replace shaders or roundtrip them via SPIRV-Cross -> glslang.
This can create SPIR-V that is more compatible with NVIDIA drivers in particular.

## Checkout and build

Make sure to install `git`, `cmake`, `ninja` and gcc toolchains first (often called `base-devel` or similar).

```
git clone https://github.com/HansKristian-Work/pyroveil.git
cd pyroveil
git submodule update --init
cmake . -Bbuild -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$HOME/.local
ninja -C build install
```

Alternative path if using Steam Flatpak. (I assume this is correct).

```
cmake . -Bbuild -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$HOME/.var/app/com.valvesoftware.Steam/.local
```

## To use

The layer needs a config file to operate. See the folders under `hacks/` for some ready to go config files.
Use `PYROVEIL_CONFIG=/path/to/pyroveil.json` to pick the config you want.
In Steam, run the game with `PYROVEIL=1 %command%`.

To know that it's active, run `grep "pyroveil:" ~/steam-$appid.txt` on the `PROTON_LOG` output. You should see, e.g.:

```
pyroveil: Found config in /tmp/pyroveil.json!
pyroveil: Adding match for spirvExecutionModel: 5365 (MeshEXT).
pyroveil: Adding GLSL roundtrip via SPIRV-Cross for match.
...
pyroveil: Found match for execution model in 55736cd1c3064f67.
...
```

Some config files use a roundtripCache to provide patched SPIR-V.
In this case, `cache/` folder next to pyroveil.json must also be copied.
It is likely easier to simply use the path that you checked out for the `pyroveil.json`. E.g.

`PYROVEIL=1 PYROVEIL_CONFIG=/path/to/pyroveil/checkout/hacks/monster-hunter-wilds-nv/pyroveil.json %command%`

## To use with Bottles (Flatpak)

Some manual workarounds will be required to make this work with a Bottles setup.

Assuming you have gone through the [checkout and build](#checkout-and-build) section, you will now have two files in the `CMAKE_INSTALL_PREFIX` directory:
* `$CMAKE_INSTALL_PREFIX/lib/libVkLayer_pyroveil_64.so`
* `$CMAKE_INSTALL_PREFIX/share/vulkan/implicit_layer.d/VkLayer_pyroveil_64.json`

By default Bottles will search several locations for Vulkan layer manifests, one of them is:
* `$HOME/.var/app/com.usebottles.bottles/config/vulkan/implicit_layer.d`

Copy over `VkLayer_pyroveil_64.json` into the location above. Open it and edit **ONLY** the `layer.library_path` field in the json like so (or any other path you like, as long as Bottles can access it):
```json
    "layer" : {
        "library_path": "/home/YOUR_USER/.var/app/com.usebottles.bottles/config/vulkan/lib/libVkLayer_pyroveil_64.so"
    }
```

For the final step it's suggested to copy the relevant hack to the `drive_c` folder of your game.

Finally, in the Bottles app, set the Launch options by clicking on the three dots next to your Program/Game, and clicking "Change Launch Options". Next add one of the hack locations:

`PYROVEIL=1 PYROVEIL_CONFIG=/home/YOUR_USER/.var/app/com.usebottles.bottles/data/bottles/bottles/YOUR_BOTTLE/drive_c/pyroveil.json %command%`

**NOTE:** If you are running an older version of a game, you might want to check the git history for that particular game's hack, and try an older version of the hack file.
