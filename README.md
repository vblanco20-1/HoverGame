# HoverGame
Hovercraft game example in UE4. Acts as a game framework for a hybrid C++/Blueprint project. Some parts of it are easily reusable and can be used in other projects.

If you want to try it, its free to download on: https://vblanco20-1.itch.io/hover-game-prototype

Video: https://youtu.be/bx0LBRroAiw


This example was written for a lesson, and it comes with detailed explanation of all the systems. All the code and blueprints is well commented and clear.


# GENERAL

Controls: WASD to move, mouse to aim. Left click to fire, Right click to fire shotgun, press shift to target enemies, release shift to throw missiles. Spacebar to jump, Escape to pause.

The game is a 3rd person shooter where the player controls a hovercraft in the moon, and needs to disable an orbital cannon that is threatening the earth. To disable the cannon, the player needs to disable the shield that protects it, by breaking energy crystals around the map.

Hovergame is developed using unreal engine in a couple days in a gamejam style workflow but with an extra care on code design to allow easy extension into a real project. 
The code is mostly in blueprint, with some helper components and hierarchies defined in C++. The reason for that, is that blueprint is many times faster to use than C++, making it very useful for prototyping. Once it reaches a certain level of complexity, it should be translated to C++, as C++ is far better at mantainability and allows proper source control. On a late stage project,  nearly all the code should be C++ except the “highest level” gameplay layer and some mission/level related logic.


# TERRAIN
The Terrain was done in 10 minutes by using Houdini with a few noise filters and a couple procedural steps for the craters. 

# HOVERCRAFT:

The player hovercraft is a hybrid of pure physics simulation with some basic movement. The basic movement is done by the FlyingMovementComponent, wich is an unreal engine component that adds velocity from input and can do some correction. The physics are done by the physics engine, and by the 4 thrusters wich control the suspension of the hovercraft. 
Each of the 4 thrusters performs a downwards trace, and adds a force upwards depending on how close the ground is. To avoid high springiness, if 2 or more thrusters are touching the ground, the hovercraft gets extra physical dampening.

The hovercraft also performs torque to align itself with the player view direction. 

To avoid flipping over, the physical center of mass of the physics body is in an impossible position, far below the physics object. Also, there is a correction force that adds a force in the opposite direction of the turning to help the cases where the center of mass offset isnt enough. 

For shooting, the hovercraft has 2 turrets attached. These turrets aim at the point the player is looking.

When the hovercraft receives enough damage, it respawns at the starter location.

The hovercraft also has a missile system, with aim-lock. The aimlock is coded in C++ under the TargettingComponent, wich finds all the TargetComponents in a cone from the view, and creates the correct UI effects for them. When shooting, its list is cleared and missiles are launched towards those targets. To speed this up, every TargetComponent registers itself to a singleton TargettingSystem, which then allows the programmer to do queries, such as (get targets in cone), efficiently.


# DAMAGE:

The damage system is taken from the damage system in DWVR and other personal projects. It consists on a Damage Component that holds the damage and health logic, and emits events for death or damage. This allows the code to centralize the damage logic, thus avoiding repetition.
To have ANY actor have damage/health logic, just attach a DamageComponent to it.

All bullets are extremely basic actors with a ProjectileMovement component. I'm creating and destroying them constantly, which is not a good thing to do. Given this is a prototype, that doesn't matter. But in a real project creating a projectile pool and making sure all bullets are pooled is very important.

# ENEMY ARCHITECTURE:

From the experience with other games, there is a EnemyInterface, empty right now, which will be used for shared enemy logic. 
The game has 2 C++ enemy classes, one that inherits from Pawn, and other that inherits from Character. Both of them have no logic other than attaching the TakeDamage interface to the DamageComponent. 

ENEMY- Robot:
This is the most common enemy. It is a robot that patrols an area, and if the player gets close enough, he will fight the player. The robot has a turret very similar to the ones the player has, and shoots the player constantly. ACharacter based, with ground movement and physics

ENEMY-Flying:
Placeholder flying enemy, just flies around randomly. If the player gets close, it flies randomly near him. APawn based, with simple flying movement.

ENEMY- Laser Turret:
Static turret, AActor based. Can't move. When the player gets into range, it will start to charge up a laser blast, and then shoot the blast at full energy. Right before launching the blast, the turret has to stop aiming, wich gives the player time to avoid. 

ENEMY- Orbital Cannon:
Once the player has destroyed enough crystals, the orbital cannon is activated.
The orbital cannon will keep shooting the player anywhere in the map, and launches an explosion on a position that it predicts the player will go. If the player does not change course, he will get hit by the explosion. The player needs to perform evasive movement to avoid the explosions. Can't be destroyed directly, the player needs to destroy the 2 crystals that keep it powered. 

# GLOBAL EVENTS:
The GameInstance is used as a global event manager. It holds some delegates for damage, death, and player messages. This keeps things like the hit marker decoupled from the actual enemies, and allows the level to easily do logic when things die. 


# LEVEL LOGIC:
The level is done with multiple maps, to be able to have 2 “missions” on the same map. The landscape and lighting is in a separate map than the enemies and logic.
The mission logic is done in the Level Blueprint. The level blueprint has extra features that allows to connect things together effectively, but on a full game, a “mission” class would be better on the long run.
For the game, the player needs to destroy 3 crystals, and then destroy the 2 crystals that power the orbital cannon. On the way, he has to fight the different enemies.
To detect the destruction of the 5 total crystals, the LevelBlueprint attaches an event to the GameInstance “OnDeath” event. It also connects directly to the specific crystals OnDeath event from the DamageComponent, to remove the quest marker of that specific crystal.

# INTERFACE:
The game has a main menu which is a very simple map selection, with buttons to start a normal game, a peaceful game, or to exit. The menus go into UI input mode which shows the mouse pointer, so that the player can click the buttons.

In-game, the hovercraft pawn creates a game widget and adds it to the view. This widget holds the health bar ,the target reticle, and the message list. The target reticle is a hitmarker widget with the hitmarker logic related. The main in-game widget is connected to events in the GameInstance, and uses the Damage event to trigger the hitmarker animation. Its also connected to the Message event in the GameInstance, and it shows the message on the screen when that happens.
If the player presses ESC or Backspace while in-game, it enters a pause. The pause pauses the game and shows a pause UI with buttons for continue or exit.

