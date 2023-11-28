# ECS
An ECS (Entity Component System) is a software architectural pattern mostly used in video game development for the representation of game world objects. An ECS comprises entities composed from components of data, with systems which operate on entities's components.

## Usage

### Create an ECS :
```Registry registry = Registry();```

### Create an entity :
In an ECS, an entity is juste an index (size_t).<br />
```int entity = registry.spawnEntity();```<br />
This method will create a new entity in the registry, and return the entity's index.

### Kill an entity :
```registry.killEntity(entity);```

### Add a component :
A registry can't have multiples component with the same type, so you should use structures.<br />
```registry.registerComponent<ComponentType>();```<br />
This method will add a new component who store "ComponentType" datas.<br />
If this component already exist, it will juste throw an error.

### Set data to an entity :
```registry.emplaceComponent<ComponentType>(entity, data);```

### Remove data to an entity :
```registry.removeComponent<ComponentType(entity)```

### Get a component value from an entity :
```ComponentType data = registry.getComponents<ComponentType>()[entity];```
