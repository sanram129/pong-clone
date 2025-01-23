# Sanjay's Pong Clone
This is a simple pong clone made using SDL2 in the summer of 2022, as a side project. It was originally a local project, and was pushed to GitHub in January of 2025. 

# How do I play?
1. Download the file in "Releases"
2. Unzip and open the "Pong.exe" file within the folder
3. Have fun!

## Controls
- Use up/down/enter keys to select a mode
- Use W and S keys to move player 1's paddle
- Use up and down arrow keys to move player 2's paddle

# How is the code designed?
From a high level, the game is designed to use a state machine, with an instance of it created in the Main.cpp file. The objects rendered to the screen, including the ball, paddle, and AI, are all classes instantiated within the code depending on the state. Most of the game's logic is handled within the GameStates.cpp file, with the GameTimer.cpp and RenderTools.cpp files providing helper functions for keeping ball speed consistent and displaying fonts, respectively. 

# Screenshots
The game's splash screen
![Splash screen of game](screenshots/splash-screen.png?raw=true)

Example of gameplay
![Gameplay example](screenshots/middle-game.png?raw=true)

Winner screen
![Completed game; winner displayed](screenshots/finished-game.png?raw=true)