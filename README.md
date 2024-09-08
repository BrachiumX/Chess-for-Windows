# Chess for Windows


## Introduction
This is a chess app for Windows. The only non system/standard library is SDL which is used for rendering and interactions with the window. Everything else is self implemented.

## Keys

Pressing Esc gets the game out of fullscreen.
Pressing R restarts the game.

## Customization

Using config.txt the default resolution and the textures can be adjusted.

To change the textures change the name of the folder in the config.txt and put the new folder in the same folder as the default folder.

## Issues

When the resolution of the game is not divisible by 8, the textures are rendered at incorrect positions by a few pixels. To fix this the program always resizes itself to be divisible by 8. However Windows does not allow resizing when the game is maximized and usually the game resolution is not divisible by 8 when maximized. To fix this partially the game goes into fullscreen mode when maximized. This should mostly fix the issue as most screen resolutions are divisible by 8.

The promote texture and pieces are rendered independently which means changing the piece textures does not affect the promote texture.
