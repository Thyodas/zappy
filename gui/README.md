# Zappy GUI

The Zappy GUI is a graphical interface in charge of receiving commands from the Zappy Server and display the data accordingly.
The GUI protocol is defined in [Gui Protocol](#gui-protocol).

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
    - [How to use](#how-to-use)
    - [Keys](#keys)
- [Contribute](#contribute)
    - [Configuration file](#configuration-file)
        - [Add a new model](#add-a-new-model)
    - [Add a graphical library](#add-a-graphical-library)
- [Credits](#credits)
- [License](#license)

## Installation

___

Depending on your OS (Operating System), you will need to install the following packages / libraries on order to run the program.

- [CMake](https://cmake.org/download/)
- [C++ Compiler](https://gcc.gnu.org/install/)
- [LibConfig](https://github.com/hyperrealm/libconfig)
- [RayLib](https://github.com/raysan5/raylib)


## Usage
___

### How to use

In order to run the program, compile the project with the following commands:
```bash
$ git git@github.com:EpitechPromo2026/B-YEP-400-STG-4-1-zappy-remi.mergen.git
$ cd B-YEP-400-STG-4-1-zappy-remi.mergen/gui
$ cmake . && make -j
$ ./zappy_gui [-h host] -p port
```

Parameters:
- -h: ip adress of the server (by default localhost)
- -p: port of the server

___

### Keys

The available keys are:
- Z: Zoom in
- S: Zoom out
- Arrow left: Rotate to the left and left block in selection mode
- Arrow Right: Rotate to the right and right block in selection mode
- Arrow up: Upside zoom and up block in selection mode
- Arrow down: Downside zoom and down block in selection mode
- H: Hide objects
- R: Selection mode (Shows the content of a cell / player)
- Left Mouse Click: Selection mode for a player

## Contribute
___

### Configuration file

In order to load the models, a config.cfg file is available at the root of the gui folder and contains the following a models field which is a list of model.
A model is described by the following fields which are all required:

Name            | Type              | Description |
| :---:         | :---:             | :---: |
| name          | string            | Name of the model |
| modelPath     | string            | Path of the model |
| texturePath   | string            | Path of the model's texture |
| scale         | float             | Displayed scale of the model |
| rotation      | list of floats    | Displayed rotation of the model |
| animation     | boolean           | Animation in the model or not |

___

### Add a new model

In order to add a new model, follow these steps:

1. Add a new model in the config.cfg file with the fields described above (models are located in ./assets/models/).

2. In the `enum` data structure located in `./include/Model.hpp`, add a new element with the name of the new model.

3. Finaly,in the Parser class constructor (default parser), add a new element inside the variable `std::map<GUI::ModelEntity, std::string> _models;`. (I.e. `{GUI::ModelEntity::EGG, "egg"}`).

___

### Add a Graphical Library

By default, the zappy gui uses the RayLib library, but any 3D library can be used (not tested on 2D libraries).

The IGraphicalModule interface describes the required methods. (`./include/interface/IGraphicalModule.hpp`). It should be located in `./include/libs/`.

```c++
    class IGraphicalModule {
        public:
            virtual ~IGraphicalModule() = default;
            virtual void loadModels(std::unordered_map<ModelEntity, modelConfig> models) = 0;
            virtual void drawModel(ModelEntity model, Vector3f position, float scale, Vector3f rotation) = 0;
            virtual void clear(C_Color color) = 0;
            virtual void init(GUI::Vector2i size) = 0;
            virtual void close() = 0;
            virtual void display() = 0;
            virtual void handleEvents() = 0;
            virtual bool isKeyPressed(GUI::Key key) = 0;
            virtual bool isKeyReleased(GUI::Key key) = 0;
            virtual GUI::Vector2f getMousePosition() = 0;
            virtual void preDraw() = 0;
            virtual void postDraw() = 0;
            virtual GUI::Vector3f getModelSize(ModelEntity model) = 0;
            virtual void drawGrid(Vector2i size, float spacing, GUI::C_Color color) = 0;
            virtual bool isMouseButtonPressed(GUI::Mouse button) = 0;
            virtual GUI::Vector3f mousePosFromGrid(GUI::Vector2i position, int cellSize, GUI::Vector2i numberOfCells) = 0;
            virtual void drawText(std::string text, GUI::Vector2f position, int size, C_Color color) = 0;
            virtual void drawRectangle(GUI::Vector2f position, GUI::Vector2f size, C_Color color) = 0;
            virtual void enable3DMode(std::shared_ptr<ICamera> camera) = 0;
            virtual void disable3DMode() = 0;
            virtual bool isInteraction() = 0;
            virtual void animateModel(ModelEntity model, AnimationType type, int frame) = 0;
            virtual int getMaxFrame(ModelEntity model, AnimationType type) = 0;
            virtual void rotateModel(ModelEntity model, Direction direction) = 0;
            virtual bool isModelSelected(ModelEntity model, Vector3f position, float scale, std::shared_ptr<ICamera> camera) = 0;
    };
```

Also, in order to change the library, a camera inheriting from the ICamera interface must be implemented. (`./include/interface/ICamera.hpp`). It should be located in `./include/`.

```c++
    class ICamera {
        public:
            virtual ~ICamera() = default;
            virtual void setPosition(Vector3f pos) = 0;
            virtual void setTarget(Vector3f target) = 0;
            virtual void rotateX(float angle) = 0;
            virtual void rotateY(float angle) = 0;
            virtual Vector3f getPosition() const = 0;
            virtual Vector3f getTarget() const = 0;
            virtual void zoom(float value) = 0;
    };
```
___

## Credits

List of contributors:

- [**Nathan de Balthasar de Gacheo**](https://github.com/nathandebalthasar)
- [**Rémi Mergen**](https://github.com/Remi-Mergen)
- [**Jean Cardonne**](https://github.com/jcardonne)
- [**Mehdy Morvan**](https://github.com/iMeaNz)
- [**Guillaume Hein**](https://github.com/Thyodas)

___

## License

MIT License

Copyright (c) 2023 Strayder Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
