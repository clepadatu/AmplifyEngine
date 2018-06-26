
OpenGL Shootemup game prototype

AmplifyEngine is a learning ground project for C++&OpenGL game programming. This is nowhere nearly to be a complete experience and should be considered a WIP. More will come as time permits and updates will pushed at least on a weekly basis.

My goal two goals with this project are: - Dig and learn as much possible about OpenGL and game architecture. - Implement everything learned and eventually reach a release version of a game. Steam may be the go-to place then.

In the next few updates, the immediate possibilities for improvement and systems that I am thinking about implementing are : - Revamp the engine to allow a component based approach and LUA scripting - Improved GUI Layer system - Save/Load Game options - Graphic options - Level Data (external data,loader,generator) - Improved AI, score and control system - Hot-seat multiplayer support - Animations (very low priority)

Running: Precompiled binaries are available in the bin folder which should provide a quick sneak peek on the progress of this project.

Setup: If you need to compile the sources, you will most probably have to correct the TYPE_PTR header file - go to textobject header and edit: #include </whatever_folder_name/Amplify-2D/Dependencies/GLM/include/gtc/type_ptr.hpp> to your actual path to the project, excluding any disk drive letters

Current version:1.0.0.1

Note: Amplify-2D is discontinued, and has been revampede into this current shape. Part of the things mentioned for the future are here, part of them are not. Still a WIP. Cheers!