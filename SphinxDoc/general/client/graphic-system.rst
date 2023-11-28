.. _graphic-system:

Graphic System
==============

|

Introduction
------------

The graphic system is the code which will translate the data between the :ref:`ecs` and the graphic library.
It will initialize whatever is needed by the graphic library (window, textures...) and draw them.

|

.. _graphic-components:

Graphic components
------------------

To be the most generic possible, the ecs should not have any knowledge of the graphic library.
To do this we have created some components which represent graphic elements :

.. code-block:: c++

    struct Position {
        int x;
        int y;
    };

    struct Velocity {
        int x;
        int y;
    };

    struct ColorRGBA {
        int r;
        int g;
        int b;
        float a;
    };

    struct SpriteData {
        std::string path;
        std::pair<int, int> sheetSize;
        std::pair<int, int> rectPos;
        std::pair<int, int> rectDim;
    };

    struct ShapeData {
        std::vector<std::pair<int, int>> points;
    };

    struct TextData {
        std::string text;
        std::string fontPath;
        int fontSize;
    };

    struct Drawable {
        bool isVisible;
        std::pair<int, int> scale;
        float rotation;
        ColorRGBA color;
        std::variant<SpriteData, ShapeData, TextData> data;
    };

    struct SpriteRectMovement {
        int x;
        int y;
        float delay;
        float lastRefresh;
    };

    struct KeysPressed {
        std::unordered_map<KeysCode, bool> data;
        bool windowClosed;

        KeysPressed() {
            for (int i = 0; i < KeyCount; ++i) {
                data[static_cast<KeysCode>(i)] = false;
            }
            windowClosed = false;
        }
    };

    struct Background {};

    struct Middleground {};

    struct Foreground {};


The Graphic System abstract class
---------------------------------

We have a folder 'Client/GraphicSystem' which contains all needed files for the graphic system.

Here are the abstract class :

.. code-block:: c++

    class AGraphicSystem : IGraphicSystem {
        public:
            AGraphicSystem() = default;
            AGraphicSystem(std::shared_ptr<Clock> clock);
            //draw systems
            void drawBackground(Position &pos, Drawable &drawable, Background &layer) override;
            void drawMiddleground(Position &pos, Drawable &drawable, Middleground &layer) override;
            void drawForeground(Position &pos, Drawable &drawable, Foreground &layer) override;
            // draw sub systems
            void draw(Position &pos, Drawable &drawable) override;
            // key detection system
            void detectKeys(KeysPressed &keysPressed) override;
            // update systems
            void updateSprites(Drawable &drawable, SpriteRectMovement &movement) override;
            //other
            void updatePositions(Position &pos, Velocity &vel) override;
            void clear() override;
            void display() override;
            std::unordered_map<int, SpriteData> getSpritesProperties() override;
        protected:
            std::shared_ptr<Clock> _clock;
    };

Let's start with the three **draw{layer}** methods.
**{layer}** is one of the three class which define the layer where will the entity be drawn.
Each will draw entities which have **Postion**, **Drawable** and **{layer}** components, by calling the **draw** method.

**detectKeys** method will detect the keys pressed by the user and fill the **KeysPressed** component (see :ref:`keys-inputs`).

**updateSprites** method will update the sprite of entities having Drawable and SpriteRectMovement components. This allows to animate the sprite.

**updatePositions** method will update the position of entities having Position and Velocity components. This allow to make entites move.

**clear** method will clear the window.

**display** method will display the window.

**getSpritesProperties** method will return a map of SpriteData component.

|

Create your own graphic system
------------------------------

To create your own graphic system, you have to create a class which inherits from AGraphicSystem.
You have to override some method, cause all aren't defined by the abstract class. This allow to have a generic graphic system and keep code using the graphic lib in the tiniest file possible.
Here are those methods you have to override :

``draw``

``detectKeys``

``clear``

``display``

``getSpritesProperties``

|

Example with SFML
-----------------

The constructor
^^^^^^^^^^^^^^^

.. code-block:: c++

    SfmlSystem::SfmlSystem(std::shared_ptr<Clock> clock)
    {
        _clock = clock;
        _shape = sf::ConvexShape(4);
        _text = Text("[Default text]", FONT_PATH, sf::Vector2f(100, 100), 50, TOPLEFT);
        _windowSize = sf::Vector2i(WINDOW_SIZE_X, WINDOW_SIZE_Y);
        _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(_windowSize.x, _windowSize.y), "R-Type");

        _spritesData[PLAYER] = (SpriteData) {PLAYER_PATH, std::make_pair(PLAYER_SHEET_WIDTH * PLAYER_SIZE_X, PLAYER_SHEET_HEIGHT * PLAYER_SIZE_Y), {0, 0}, std::make_pair(PLAYER_SIZE_X, PLAYER_SIZE_Y)};
        _spritesData[PROJECTILE] = (SpriteData) {PROJECTILE_PATH, std::make_pair(PROJECTILE_SHEET_WIDTH * PROJECTILE_SIZE_X, PROJECTILE_SHEET_HEIGHT * PROJECTILE_SIZE_Y), {0, 0}, std::make_pair(PROJECTILE_SIZE_X, PROJECTILE_SIZE_Y)};
        _spritesData[ENEMY] = (SpriteData) {ENEMY_PATH, std::make_pair(ENEMY_SHEET_WIDTH * ENEMY_SIZE_X, ENEMY_SHEET_HEIGHT * ENEMY_SIZE_Y), {0, 0}, std::make_pair(ENEMY_SIZE_X, ENEMY_SIZE_Y)};
        _spritesData[CAVE_0] = (SpriteData) {CAVE_0_PATH, std::make_pair(CAVE_SHEET_WIDTH * CAVE_SIZE_X, CAVE_SHEET_HEIGHT * CAVE_SIZE_Y), {0, 0}, std::make_pair(CAVE_SIZE_X, CAVE_SIZE_Y)};
        _spritesData[CAVE_1] = (SpriteData) {CAVE_1_PATH, std::make_pair(CAVE_SHEET_WIDTH * CAVE_SIZE_X, CAVE_SHEET_HEIGHT * CAVE_SIZE_Y), {0, 0}, std::make_pair(CAVE_SIZE_X, CAVE_SIZE_Y)};
        _spritesData[CAVE_2] = (SpriteData) {CAVE_2_PATH, std::make_pair(CAVE_SHEET_WIDTH * CAVE_SIZE_X, CAVE_SHEET_HEIGHT * CAVE_SIZE_Y), {0, 0}, std::make_pair(CAVE_SIZE_X, CAVE_SIZE_Y)};
        _spritesData[CAVE_3] = (SpriteData) {CAVE_3_PATH, std::make_pair(CAVE_SHEET_WIDTH * CAVE_SIZE_X, CAVE_SHEET_HEIGHT * CAVE_SIZE_Y), {0, 0}, std::make_pair(CAVE_SIZE_X, CAVE_SIZE_Y)};
        initSpritePalette();
    }

    void SfmlSystem::initSprite(std::string path, sf::Vector2i rectDim)
    {
        std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(path, rectDim);
        if (sprite->isLoaded() == true)
            _spritePalette[path] = sprite;
    }

    void SfmlSystem::initSpritePalette()
    {
        for (auto &spriteData : _spritesData)
            initSprite(spriteData.second.path, sf::Vector2i(spriteData.second.rectDim.first, spriteData.second.rectDim.second));
    }

First we initialize the window.
Then we define default graphic elements : shape, text and sprite
For sprites, we initialize a map of SpriteData :ref:`graphic-components` using a enum reprenting sprites for index. This allow to quickly setup a sprite palette.
For exemple, here our enum:

.. code-block:: c++

    enum SpriteType {
        PLAYER = 1,
        PROJECTILE = 2,
        ENEMY = 3,
        CAVE_0 = 4,
        CAVE_1 = 5,
        CAVE_2 = 6,
        CAVE_3 = 7
    };

draw method
^^^^^^^^^^^

Has you saw in :ref:`graphic-components`, Drawable have a std::variant of SpriteData, ShapeData and TextData.
So we start by checking which one is used. Then we modify the graphic element with the data of the component.
Finally draw it.

.. code-block:: c++

    void SfmlSystem::draw(Position &pos, Drawable &drawable)
    {
        if (drawable.isVisible == false) return;

        if (std::holds_alternative<SpriteData>(drawable.data)) { // if drawable is a Sprite
            SpriteData &data = std::get<SpriteData>(drawable.data);
            if (_spritePalette.find(data.path) == _spritePalette.end()) return; // if sprite not known
            std::shared_ptr<Sprite> sprite = _spritePalette[data.path];
            sprite->setPosition(pos.x, pos.y);
            sprite->moveRectH(data.rectPos.first);
            sprite->moveRectV(data.rectPos.second);
            if (drawable.rotation != 0)
                sprite->setRotation(drawable.rotation);
            if (drawable.scale.first != 1 && drawable.scale.second != 1)
                sprite->setScale(drawable.scale.first, drawable.scale.second);
            if (drawable.color.a != 255)
                sprite->setColor(sf::Color(drawable.color.r, drawable.color.g, drawable.color.b, drawable.color.a));
            _window->draw(*sprite);
        } else if (std::holds_alternative<ShapeData>(drawable.data)) { // if drawable is a Shape
            ShapeData &data = std::get<ShapeData>(drawable.data);
            _shape.setPointCount(data.points.size());
            for (int i = 0; i < (int) data.points.size(); i++)
                _shape.setPoint(i, sf::Vector2f(data.points[i].first, data.points[i].second));
            _shape.setRotation(drawable.rotation);
            _shape.setScale(drawable.scale.first, drawable.scale.second);
            _shape.setFillColor(sf::Color(drawable.color.r, drawable.color.g, drawable.color.b, drawable.color.a));
            _window->draw(_shape);
        } else if (std::holds_alternative<TextData>(drawable.data)) { // if drawable is a Text
            TextData &data = std::get<TextData>(drawable.data);
            _text.setString(data.text);
            if (_text.getFontPath() != data.fontPath)
                _text.setFontFromPath(data.fontPath);
            _text.setCharacterSize(data.fontSize);
            _text.setPosition(pos.x, pos.y);
            _text.setRotation(drawable.rotation);
            _text.setScale(drawable.scale.first, drawable.scale.second);
            _text.setFillColor(sf::Color(drawable.color.r, drawable.color.g, drawable.color.b, drawable.color.a));
            _window->draw(_text);
        }
    }

detectKeys method
^^^^^^^^^^^^^^^^^

See :ref:`keys-detection`.

clear and display methods
^^^^^^^^^^^^^^^^^^^^^^^^^

Used to clear and display the window.

.. code-block:: c++

    void SfmlSystem::clear()
    {
        _window->clear(sf::Color::Black);
    }

    void SfmlSystem::display()
    {
        _window->display();
    }

getSpritesProperties method
^^^^^^^^^^^^^^^^^^^^^^^^^^^

We use it in the updateData method from Game class to update datas in the :ref:`ecs`. See :ref:`update-data`

.. code-block:: c++

    std::unordered_map<int, SpriteData> SfmlSystem::getSpritesProperties()
    {
        return _spritesData;
    }

|

*All the code above can be found in the 'Client' folder*

|

Related
-------

:ref:`ecs`
:ref:`keys-inputs`
