# GameEngine
A 3D Game Engine made by students of CITM for the assigment of Videogame Engine Development. 


### Our GitHubs:
- [David Benages](https://github.com/Divangus)
- [Marina Albalà](https://github.com/Vizalt)

Click [here](https://github.com/Vizalt/MistEngine) to see our project:

## How Mist Engine works?
- Download the [here](https://github.com/Vizalt/MistEngine/releases) last release.
- Extract files from the .zip
- Execute .exe

### Camera
- **W** - Move forward
- **A** - Move Left
- **S** - Move backwards
- **D** - Move Right
- **Q** - Move Up
- **E** - Move Down
- **Mouse Wheel** - Zoom in/Zoom out
- **Right Click** - Free rotation
- **Holding Shift + 'WASD'** - Duplicates movement speed
- **LALT + Left Click** - Orbit around Selected Object.
- **F** - Focus object selected

### Inspector
Displays all different components of the selected GameObjects and allows the user to edit them.

### Components
- Component Transform - Rotate, position and scale.
- Component Mesh - Show all info about differents meshes vertex of selected object
- Component Textures - Allow viewing textures.
- Component Camera - Edit camera of gameobjects (FOV, Near Distance and Far Distance) and shows number of render objects.

### GameObject Camera
Create different cameras that can be configured as Game Camera.

### Mouse Picking
Enables the user to select an object by clicking on them in the scene that will be marked in the hierarchy.

### Frustum Culling
The engine only prints the objects that are visibles by the camera.

### Drag&Drop
The engine allows the user to Drag&Drop FBX files from anywhere in the hard drive and later, drag and drop files to put textures for the GameObjects.

## Move between windows
### Viewports
Scene Window and Game Window.

### Play/Stop/Pause Buttons
Play/Stop/Pause buttons change the viewports and the states of the engine.

### Configuration
- Application
  -  Frame Information.
  -  Slider to limitate FPS.
- Window
  - Window Options:
    - Full Screen, resizable, full desk and borderless.
    - Change brightness, width and height.
- Camera
  - Configuration about Scene Camera.
  - Change frustum configuration and shows number of render objects.
- File System
  - Shows base path.
- Input
  -  Mouse Information (Position and Motion).
- Hardware Information
  - SDL Version.
  - Memory consumption.
### Hierarchy
Shows a list of all GameObjects. The user can create, move and change the parent of the selected GameObject. Also create cameras.
### Primitives
The user can create Cubes, Spheres, Cilinders and Lines.
### Console
Shows the user geometry loading process from ASSIMP and the external libraries initialization process.

### External libraries
Externals libraries used in our engine:
- SDL
- ImGui
- Assimp
- Glew
- MathGeoLib
- DevIL
- PhysFS

