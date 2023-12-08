# Simple Render
Real time 3D objects visualisation tool using OpenGL  
![preview](readme_imgs/preview.png)  
Model by [Francesco Coldesina](https://sketchfab.com/3d-models/gibson-from-rickgreeve-cee58deadaa44425bbb4bf8f0ec46b44)


## List of Classes

### External Libraries
* OpenGL (GLFW & GLAD): Drawing API
* GLM: OpenGL compatible maths library
* stb_image: Image loader
* Assimp: 3D models importing library
* ImGUI:: UI interface
* WinAPI: File Dialog

Classes are prefixed with 'Render' (e.g RenderCamera, RenderScene) to indicate that they belong to Simple Render.   
Concrete UI classes are a exception since their parent class is named RenderUI.  

To avoid circular dependency and share objects across multiple classes, Render objects are created using the new keyword. Exceptions exist where maintaining a single reference is insignificant.


### Classes that must be instiatiated on the heap:  

* RenderTexture
* RenderShader
* RenderShaderProgram
* RenderObject
* RenderScene
* RenderCamera
* All UI classes

### Classes that can be instantiated on the stack:
* RenderVertex
* RenderMesh

### Class Info:
* RenderVertex: Container for position, normal and texture coordinate for a vertex
* RenderMesh: A face in RenderObject
* RenderObject: A whole renderable object. Contains textures, shaders etc to draw the object.
* RenderTexture: 2D Texture.
* RenderShader: GLSL shader. Can be a vertex, fragment or geometry shader.
* RenderShaderProgram: shader program. Must have a vertex and a fragment shader to operate. Geometry shader is optional
* RenderCamera: Camera.
* RenderScene: Contains multiple RenderObjects, cameras, shaders etc.
* FileReader: Helper class to read files



## To do
* Consider using a different data structure for Render elements in RenderScene. Deletion is inconvenient and costly
* Find a place to shove in stbi_set_flip_vertically_on_load in RenderTexture
* Understand and how OpenFileName works and customise it
* Fix a bug where the program crashes when minimised
* Update UI objects so that they can communicate to one another.
