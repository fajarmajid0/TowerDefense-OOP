# TowerDefense-OOP

This is 2D Tower Defense game developed in C++ using oop concepts and the SFML GUI library.
The features are as follows:
- Multiple enemy types:
  - Basic Enemy
  - Fast Enemy
  - Tank Enemy
  - Flying Enemy
  - Healer Enemy
- Multiple tower types:
  - Cannon Tower
  - Sniper Tower
  - Slow Tower
- Wave-based enemy spawning
- Path-following enemies
- Real-time gameplay using SFML
- 

How to compile the project and run it:
1. Install SFML
Download SFML from the following website:
https://www.sfml-dev.org/download.php
and extract the sfml folder after downloading it.

3. Include SFML in Visual Studio
Include Directories
Add:
SFML/include
# Library Directories
Add:
SFML/lib
# Additional Dependencies
For Debug mode:
- sfml-graphics-d.lib
- sfml-window-d.lib
- sfml-system-d.lib
For Release mode:
- sfml-graphics.lib
- sfml-window.lib
- sfml-system.lib
# Copy DLL Files
Copy the required SFML DLL files from:
SFML/bin
into your project executable folder.

 4. Run the Project
Open the `.sln` file in Visual Studio and run the project.


# Known Issues / Limitations
- Enemy animations are limited.
- Towers currently have basic targeting logic.
- UI system is still under development.
- Path is hardcoded and not dynamically generated.
- Some textures may need manual scaling depending on screen resolution.




