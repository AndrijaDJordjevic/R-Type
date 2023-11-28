.. _keys-inputs:

Keys Inputs
===========

|

Introduction
------------

Keys detection is a part of the :ref:`graphic-system`.
To manage keys inputs out of the graphic library, we use a :ref:`keys-code` which list all keys available.

|

.. _keys-detection:

Example with SFML
-----------------

First, we define a struct wich will be a component which store the keys pressed.
Here's it's an unordered_map storing a boolean and using the :ref:`keys-code` as index.

.. code-block:: c++

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

Then we create a system which will detect keys pressed and store them in the component.

.. code-block:: c++

    void SfmlSystem::detectKeys(KeysPressed &keysPressed)
    {
        sf::Event event;

        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window->close();
                keysPressed.windowClosed = true;
                return;
            }
            if (event.type == sf::Event::KeyPressed) {
                sf::Keyboard::Key key = event.key.code;
                KeysCode keyCode = static_cast<KeysCode>(key);
                if (keyCode >= KeysCode::A && keyCode < KeysCode::KeyCount) {
                    keysPressed.data[keyCode] = true;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                sf::Keyboard::Key key = event.key.code;
                KeysCode keyCode = static_cast<KeysCode>(key);
                if (keyCode >= KeysCode::A && keyCode < KeysCode::KeyCount) {
                    keysPressed.data[keyCode] = false;
                }
            }
        }
    }

Finally, we put the system in a variable and call it :

.. code-block:: c++

    _DetectKeysFunc = [this](KeysPressed &keysPressed) -> void {_graphicSystem->detectKeys(keysPressed);};

.. code-block:: c++

    registry.Exec(_DetectKeysFunc);

|

Return Inputs to send it to the server
--------------------------------------

In our :ref:`protocol`, we send keys inputs with a Inputs struct :

.. code-block:: c++

    struct Inputs {
        bool left;
        bool right;
        bool up;
        bool down;
    };

To fill it from our KeysPressed component, we use this function :

.. code-block:: c++

    bool Game::fillInputs(Inputs &inputs, KeysPressed &keysPressed)
    {
        if (keysPressed.windowClosed) return false;
        inputs.left = keysPressed.data[LEFT];
        inputs.right = keysPressed.data[RIGHT];
        inputs.up = keysPressed.data[UP];
        inputs.down = keysPressed.data[DOWN];
        return true;
    }

LEFT, RIGHT, UP, and DOWN are macros which associate a :ref:`keys-code` to a name. So you can easily change the key mapping.

|

.. _keys-code:

KeysCode
--------

.. code-block:: c++

    enum KeysCode {
        Unknown = -1 , A = 0 , B , C ,
        D , E , F , G ,
        H , I , J , K ,
        L , M , N , O ,
        P , Q , R , S ,
        T , U , V , W ,
        X , Y , Z , Num0 ,
        Num1 , Num2 , Num3 , Num4 ,
        Num5 , Num6 , Num7 , Num8 ,
        Num9 , Escape , LControl , LShift ,
        LAlt , LSystem , RControl , RShift ,
        RAlt , RSystem , Menu , LBracket ,
        RBracket , Semicolon , Comma , Period ,
        Apostrophe , Slash , Backslash , Grave ,
        Equal , Hyphen , Space , Enter ,
        Backspace , Tab , PageUp , PageDown ,
        End , Home , Insert , Delete ,
        Add , Subtract , Multiply , Divide ,
        Left , Right , Up , Down ,
        Numpad0 , Numpad1 , Numpad2 , Numpad3 ,
        Numpad4 , Numpad5 , Numpad6 , Numpad7 ,
        Numpad8 , Numpad9 , F1 , F2 ,
        F3 , F4 , F5 , F6 ,
        F7 , F8 , F9 , F10 ,
        F11 , F12 , F13 , F14 ,
        F15 , Pause , KeyCount , Tilde = Grave ,
        Dash = Hyphen , BackSpace = Backspace , BackSlash = Backslash , SemiColon = Semicolon ,
        Return = Enter , Quote = Apostrophe
    };

Use KeyCount to get the number of keys available.
Use Unknown when the key is not available.

|

*All the code above can be found in the 'Client' folder*

|

Related
-------

:ref:`ecs`
:ref:`graphic-system`
