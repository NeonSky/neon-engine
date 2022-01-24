engine
  game loop
  scene manager
    scene(s)
      ecs
      root node
      scripts
  renderer
    window manager&
  window manager
    opengl application?
    vulkan application?
    window(s)
      render_context

We want to render stuff to windows
Thus, a window should be a central unit

opengl and vulkan are only relevant for rendering stuff

Specifically, we want to render scenes to windows



> "There is no global state in Vulkan and all per-application state is stored in a VkInstance object."
In vulkan we need an instance and a device (Application)
We also need a surface per window (Context)

To create a vulkan Application, we need nothing
To create a vulkan Context, we need a surface (glfw could ask the vulkan application for access to the instance)


> "OpenGL is a global state machine, but things are separated with contexts."
In opengl we potentially want global settings (Application)
We also need VAOs (and other state stuff) per window (Context)

To create an opengl Application, we need nothing
To create an opengl context, we need nothing


Restriction: only opengl or only vulkan, not both at the same time

Ok, so the window manager needs a single graphics/api application

Maybe a window interface in OS, but individual classes in graphics? VulkanWindow and OpenGLWindow


example.cpp in each folder that demonstrates the package
