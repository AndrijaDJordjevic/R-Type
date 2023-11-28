Client
======

|

Introduction
------------

The client is the part of the game ran by the player.
It collect informations sent by the server according to the :ref:`protocol`.
Then, it store those informations in the :ref:`ecs` then call the :ref:`graphic-system` to display them.
Finaly, it gather :ref:`keys-inputs` from the player and send them to the server.

You shouldn't draw your entities at each frame. You should draw them at a fixed rate using a :ref:`clock`.

|

Example
-------

Here's an example of a class Game used by the client :

.. code-block:: c++

   class Game {
    public:
        Game() = default;
        Game(std::shared_ptr<Registry> registry);
        ~Game() = default;
        void updateData(int id, Entity entity);
        std::optional<Inputs> refresh();
        void display();
    private:
        bool fillInputs(Inputs &inputs, KeysPressed &keysPressed);
        std::shared_ptr<Registry> _registry;
        std::unique_ptr<AGraphicSystem> _graphicSystem;
        size_t _gameIndex;
        Clock _clock;
        std::unordered_map<int, int> _serverEntities; // id, registry index
        //graphic systems
        std::function<void(Position &pos, Velocity &vel)> _UpdatePositionsFunc;
        std::function<void(Drawable &drawable, SpriteRectMovement &movement)> _UpdateSpritesFunc;
        std::function<void(Position &pos, Drawable &drawable, Background &layer)> _DrawBackgroundFunc;
        std::function<void(Position &pos, Drawable &drawable, Middleground &layer)> _DrawMiddlegroundFunc;
        std::function<void(Position &pos, Drawable &drawable, Foreground &layer)> _DrawForegroundFunc;
        std::function<void(KeysPressed &keysPressed)> _DetectKeysFunc;
   };

Game constructor take the registry as parameter. It also initialize systems and the :ref:`clock`.

The updateData method is called by the client when it receive informations from the :ref:`server`. It update the :ref:`ecs` with the news informations.
refresh method is called by the client at each frame. It return the :ref:`keys-inputs` of the player or nullopt if the client closed the window. It also call display which draw entites by calling Exec method from registry.

The last lines are systems called by previous methods.

|

.. _update-data:

More details about updateData method
------------------------------------

Here's how we implemented this method

.. code-block:: c++

   void Game::updateData(int id, Entity entity)
   {
      int entityIndex = (_serverEntities.find(id) != _serverEntities.end() ? _serverEntities[id] : -1);

      SpriteData spriteProperties = _graphicSystem->getSpritesProperties()[entity.spriteType];
      if (entityIndex == -1) {
         entityIndex = createDefaultEntity((Position) {entity.x, entity.y}, (Drawable) {true, {5, 5}, 0, {0, 0, 0, 255}, spriteProperties}, LayerType::MIDDLEGROUND);
         _serverEntities[id] = entityIndex;
         _registry->emplaceComponent<Velocity>(entityIndex, (Velocity) {entity.velocityX, entity.velocityY});
      } else {
         _registry->getComponents<Velocity>()[entityIndex] = (Velocity) {entity.velocityX, entity.velocityY};
         _registry->getComponents<Position>()[entityIndex] = (Position) {entity.x, entity.y};
         _registry->getComponents<Drawable>()[entityIndex] = (Drawable) {true, {5, 5}, 0, {0, 0, 0, 255}, spriteProperties};
      }
   }

We fill the registry with the informations sent by the server. If the entity doesn't exist, we create it. If it already exist, we update it.
To fill the spriteData :ref:`graphic-components`, we use the spriteType sent by the server to get the spriteData from the :ref:`graphic-system`.

|

*All the code above can be found in the 'Client' folder*

|

Related
-------

:ref:`ecs`
:ref:`graphic-system`
:ref:`keys-inputs`
:ref:`clock`
:ref:`protocol`
