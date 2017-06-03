######  STAGE ONE  ######
The current assignment implements a space ship that moves right and left + shoots.

The first 3 lines of the config take the size, x position and instructions.
The instructions are seperated by ",".


The Config has been implemented with a signleton design pattern.
The Bullet has been implemented with a builder design pattern.



The extensions implemented were:

- According to the size of the ship, the game screen is adjusted and so is the starting y position.

- When a bullet is shot, there is a laser beam noise made (with QSound).

- The 4th additional line in the config file is the number of frames per second and can be modified for each individuals experience.

- I have attempted to align the bullet to project from the middle of the ship, regardless of what size the ship is or starting x.



######  STAGE TWO  ######
Cool dogs.
CONFIG FILE SHOWCASE:
 config - is the one used for demo demonstrating everything, however aliens shoot quite a bit so it may close.
		- 'incorrect' config input is used to show error handling
 confg dmo - same as above
 config simple - shows 1 swarm
 config friendly - shows friendly fire of aliens against aliens.
 config simple alien crash, crash 2 - shows that aliens colliding with player shuts the game safely

Fixes:
- Fixed the previous extension where bullets were NOT ACTUALLY shooting from the middle of the ship :( This was due to 1) incorrect maths with magic numbers 2) the images had transparent pixel borders which would inevitably stuff up the maths in the first place, so I cropped them out in Photoshop.
- Fixed some magic numbers
- Fixed deletion and config fixes e.g., one List loop where they deleted items while iterating, without backwards iteration (without using a foreach loop) PS Dogs are really cool.
- Made it so ships and aliens cannot go out of the canvas.
- Base class now has a collision(Base &item) function, since QRect / QGraphicsScene is not implemented

Information:
- Config fixed s.t., it can read other [headers] (and can still read the old config). A bit confusing due to the assignment requirement of needing backward compatibility, but basically its like recursive.
- Used composite structural design for swarms of aliens.
	Alien is a leaf, Swarm is a composite.
- Made the ship instructions loop so it moves forever until game close / lose (not necessary for Stage 3)
- Aliens use the same bullet builder class as Ship, just different parameters
- Aliens have a builder. If you want to make more aliens, please look at AlienBuilder
- Added 'friendliness' for bullets, used later for checking collision.
	- if you want aliens to shoot "Player" bullets for some reason (e.g., kill other aliens) try passing a special "type" of bullet to its builder. See Hunter class.

Other Notes FOR STAGE 3:
- For game scoreboard in part 3, take a look at the Menu class :)
- All dogs on earth wish that this was helpful for you.

Extensions:
	Aliens: (AKA dog haters)
	- Angled bullets - rotates the bullet image in bullet builder.
		> When ship or alien makes a bullet,
		need to tell bulletbuilder if they want to shoot angled.
	- Randomised shooting times (with given range at config)
		> Also shoots a random type of bullet
		(BUT YOU MAY REMOVE THIS, It's just to showcase angles)
	- Aliens that hunt the Player.
		> And, aliens that are not so good at hunting. [hunter, dumb]
		> Normal, non hunting aliens are [red, blue]
	- REACTIONS: Aliens can react before they die.
		> Currently, Hunter aliens will shoot three bullets that can harm the player.
		> Dumb aliens will shoot three bullets that harm aliens.
	- Press 'P' to pause the game
	- Pausing displays the score button (it's a menu, but only 'score' menu is implemented)
		- score is opened with said button
	- Made so ships can't go out of the canvas area.
	- Player ship dies on contact with alien.


######  STAGE THREE  ######

Author: Oscar Lai
unikey: tlai4178

The main purpose of this stage is to polish the game into a more playable with game mechanics and functionality. The main implementations for
the game mechanics is adding the proper controls of the spaceships by using left/right for movements (or A/D), and using space for shooting
bullets. The game functions that were added also includes the game menu to controls the game settings, as well as different stages of the game
mechanics. Here this sections will includes notes that describes the implemented functionality and the techniques used in it.

Controlling of the space ship with cursor keys:
  - The space ship is controlable with the use of arrow keys (<- or ->), or the use of A/D for easier shooting with left hand
  - The use of [SPACE] bar to fire bullets
  - the additions of delays between each shoot to prevent spamming of bubllets

Controlling of the game with mouse:
  - There are a few functions that could be controlled with mouse, both in game setting management and game power ups.
  - The use of cursor to control game menu settings
  - The use of cursor to act as a GUI to construct game stages and adding aliens into the game
  - The use of cursor as a power ups that has the ability to act as power ups to defeat or protect the ship from bullets:
    - Using cursor to add barrier blocks which will act as a barrier to defend the ship from bullets (will be destroyed from one hit)
      - this will be activated when a "red feather" power up had been took by the space ship
      - this will be activated until the barrier energy bar had been completely drained
      - each added barrier blocks will drain a certain amount of plasma energy bar (Red bar)
      - when it has been drained, cursor will be switched back to the tie-fighter state
    - Using cursor to act as a plasma energy orb which has a energy bar and will destroy nearby bullets
      - for each second the left button is being pressed, it will continuously drain plasma energy (blue bar)
      - for each bullet being destroyed, it will drain a larger amount of plasma energy instantly
      - if the plasma energy bar has been completely drained, it will temporarily being disabled. It will re-enable again when it has been fully recharged

Game Stages:
  - Each stages had been implemented to be define within the same config.txt file from Stage 1/2. The generation or the config patterns are still
    the same as before, but each [swarms] tag will be concentrated into a signle stage if a [stage XX] tag is present within the config file
  - The [Stage] tag is needed for the game to be treated in the new version (instead of the legacy mode). The SwarmInfo in the original Stage 2 have been
    contained in a std::vector container and each index is representing each stage of the game. When all aliens have been destroyed, the next index in the
    vector container will be spawns to represent the next stage. A transition animation will also be played before the spawning of the next stage.
  - In short, when config.txt file contain the [stage] tag anywhere in the file, the new functionality will be triggered in the game. And every [swarm] tag
    between  here and next present of [stage] tag (or end of file) will be within the same stage. The same goes for the next [stage] tag.

Score board:
  - The score board functionality has been added to the game, where it has been added by a separate class that represent the score board of the game
  - The scores are saved after the ship has been destroyed or all stages have been finished. At that moment, a dialog box will be presented to ask player for
    their name. After that, the "name", "stage" up to, and "score" will be appended to the file "LEADERBOARD.sav" in the score file.
  - The score board will be sorted from the highest score to the lowest score. All past players will flow from the bottom to top.

Behavioural Design pattern:
  - Two behavioural pattern have been used in this game; State design pattern and command design pattern.
  - Command Design Pattern:
    - Used to implement each commands in the game menu, including the clearing of the stage, the changing of the mode to different mode, such as game mode,
      leader board mode, stage maker mode. This is appropriate as it enables one to concentrate the game functionality into a single interface.
  - State Design Pattern:
    - Used to implement different state of the cursor and using the same interface to process each mouse event. It decoupple the state from the sending of the
      Mouse Event

Changing Speed of the game:
  - It is achievable within the game menu with the use of a slider bar, and a visual representation of the "multiple coefficient" from x0.5 to x2.0

Debugger mode:
  - The use of [F1] will enable the debugger / cheat mode to allow user control the game functionality directly. For details check the instructions in the
    [F1] mode and the source code.

Extensions:
  - There are multiple extensions present in this implementations. Some of them has been mentioned in previous dot points.

  - Power ups
    - The main extension where it was the first thoughts of extensions. There are two sub-extensions, one for cannon type and one for cursor type. The cursor
      type is the first being implemented as it seems more "cool" than plain old cannon. But in the end both had been implemented.
    - Cursor power up
      - There are one normal state, and one power up. Normal state is a TIE-FIGHTER state (an aircraft from star war) where it is used to protect the ship
        from incoming bullets. The state will be activated upon a mouse click. When it is activated, it will destory nearby bullets. Energy will be drained
        every second.
      - The PEN state. It is used to add additional barrier block into the game. This idea comes from the orginal space invader game where the block will block
        incoming bullets.
    - Cannon power up
      - Machine Gun
        - The firing rate will be increased and two line of bullets will be fired (instead of one). It will be reverted to normal gun will all ammons are outs.
      - Laser Gun
        - There will be a beam of laser being fire, with no rate (always continuous). Everything touches it will be destroyed. It will be reverted to normal gun
          when all ammos are outs.

  - Stage Maker
    - This is another huge extension to allow player to be able to make their own stage and test it out. The hardest part is to create a GUI to allow player define
      the stage with ease. The idea comes from Mario Maker, where a drag and drown system is used to drag energy in place. In this mode, each aliens and barrier blocks
      are draggable into the main game screen. And to enable the use to define the movements of aliens, an instruction box is added into the game to able to link the
      instructions to aliens to control them like a swarms.
    - When the use click on the test stage button, each placed objects will be translated into the main game engine to build up a stage that looks exactly like what the
      user have been specified in the STAGE MAKER mode.
