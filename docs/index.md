# **Mist Engine**
![MistEngine](https://user-images.githubusercontent.com/70697960/212569055-4accfc6d-1d94-464d-a436-509cb50b2276.PNG)

# **About the Engine**
Mist Engine is a 3D Game Engine that provides a wide variety of tools and features for its users. This engine was conceived and developed as a project in the Videogame Engine Development assignment by students of the Videogame Design and Development degree at CITM.

# **About Team Members**
![TeamMembers](https://user-images.githubusercontent.com/70697960/212539542-bb666527-98be-4619-bb5e-16c2c3f60e6b.jpeg)

### **[David Benages](https://github.com/Divangus)**
#### David's contributions to the engine:
- Camera
- Game Objects & Components
- Frustrum Culling
- Drag&Drop
- Primitives
- Implemented External Libraries
- Inspector
- FBX Importer
- Texture Loader
- Particle Emitter
- Particle System

### **[Marina Albalà](https://github.com/Vizalt)**
#### Marina's contributions to the engine:
- Mouse Picking
- UI Interface
- Engine Menus
- Hierarchy
- Play/Stop/Pause
- Console
- Web Page
- Video
- Particle System


# **Core Sub-Systems**
### Editor Docking
ImGui's docking helped us to provide a cleaner workspace, allowing us to move the windows we created freely.
### Gameobject & Component System
The engine utilizes a Component system and Gameobjects. This allows us to create as many as desired and allows to adjust them to specific needs.
### Camera Culling
Camera Culling allows the scene to be rendered to give the program faster and more accurate rendering by not drawing meshes that are not on the screen.

### Camera Editor and Movement
Mist Engine includes a camera which can be controlled by the user, along with some parameters that allow customizing and moving the game's camera.

# **Particle Sub-System**
Mist Engine includes a particle system. It has been developed with the purpose of creating a particle emitter as desired by the user.

Within the software, is included an inspector that makes it possible to modify several parameters of the emitter which will affect the particles, such as speed, position and starting and ending color and scale, as well as being possible to place any desired texture.

Furthermore, another feature of the particle system is the use of the Billboard component. This allows the particles to always face the camera, both in the scene and in the game.

To illustrate what Mist Engine's particle system is capable of, upon starting the software, you can see how the initial scenario contains several emitters in the chimneys of the houses that produce smoke-simulating particulates, also you can press 1 to generate a firework effect.

![EngineGif2](https://user-images.githubusercontent.com/70697960/212568941-8ae00a3e-ff4c-4ba3-9901-db995e254da0.gif)

![EngineGif](https://user-images.githubusercontent.com/70697960/212568942-397a4f5b-861e-4892-8c17-e540db9732b2.gif)

# **WorkFlow Video**

<iframe width="560" height="315" src="https://www.youtube.com/embed/7fIiIfjpLBI" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

# **Last Release**
Click [here](https://github.com/Vizalt/MistEngine/releases) to see our last release!

# **License**

MIT License

Copyright (c) 2022 Marina Albalà and David Benages

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


