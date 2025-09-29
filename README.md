# Senior Thesis Repo: CONNECT 4 SOFTWARE WITH A Q-LEARNING ML-POWERED ALGORITHM
This repository is provided to help you build your senior thesis project. You will edit it to store your specification documents, code, and weekly checkins.

## Software Requirements Specification

## Introduction

### Purpose
This document provides all the functional and non-functional requirements of the Machine Learning Connect Four Software. The primary purpose of this software is to train an Artificially Intelligent algorithm on the popular MB board game, Connect Four, so that it can capably go up against human players.

The key goals of the software are:
- To create a Q-Learning-based algorithm that is able to learn and master Connect Four
- To discover possible new and unexpected strategies for winning the game
- To demonstrate the potential of Machine Learning AI in games, both physical and virtual.

### Scope
Although it is an option for two human players to play Connect Four, this software is supposed to pit human players against a Machine Learning-based AI. The AI decides the best possible move based on the current state of the board, and is either rewarded or punished based on the ultimate outcome of the game.
The overall scope of the software will consist of:
- Connect Four Grid setup
- Checking win conditions
- Player vs. Player mode
- Player vs. AI mode
- AI vs. AI mode (If possible)

### Definitions, Acronyms, and Abbreviations
- **Machine Learning (ML)**: A form of Artificial Intelligence where computers utilize recorded data to make its own decisions
- **Q-Learning**: A specific type of Reinforcement Learning in which the AI learns to select the best possible choice based on the values of future states.
- **State (s)**: The list of all moves played by both agents throughout the game.
- **Agent**: Anything that acts to achieve a goal.
- **Learning Rate (α)**: How much new information should be acquired versus old info.
- **Discount Factor (γ)**: How important is the future reward over the immediate reward.
- **Grid**: The 7x6 Game Space in which agents drop their checkers into the seven spots on top of the board.
- **Hole**: The place inside the board where a checker lands into. Marked as follows:
  - R for Player 1 (Red)
  - B for Player 2 (Black)
  - O for Empty

## Overview
Machine Learning Connect Four is a software designed to train an AI algorithm. The algorithm is based on Q-Learning, a type of machine learning where decisions are made based on selecting the most valuable choice.
The primary functionality for the algorithm is based on the following equation: **Q(s, a) = Q(s, a) + α * [R(s, a) + γ * maxQ(s', a') - Q(s, a)]**
Q(s, a) is the current state of the game based on the action taken
α is the Learning Rate. See the Definitions page for the full definition.
R(s, a) determines whether the AI should be rewarded or punished at the end of the game for their decision. Points are added if the AI wins, and points are docked if it loses.
γ is the Discount Rate. See the Definitions page for the full definition.
maxQ(s', a') lists all future states for the AI to pick the best possible state-action pair.

### System Features:
1. **Main Menu** A selection screen where the user can select from different game modes
2. **Player vs. Player** A game mode that plays like traditional Connect Four
3. **Player vs. AI** A game mode in which the player plays against the Machine Learning computer
4. **AI vs. AI** The computer is trained against another identical model to generate more learning data
5. **Options** User can set their checker color and erase AI data.

The following sections detail the specific use cases that the software will support

## Use Cases

### Use Case 1.1: Drop checker
- **Actors**: Agent (User or AI)
- **Overview**: Agent selects a column in the grid to place their checker into

**Typical Course of Events**:
1. Case begins at the beginning of the agent's turn and when the game is not yet won.
2. Agent is prompted to select one column out of seven in the grid.
3. Agent types in a numeric value from 1 - 7 to select the column.
4. The checker is dropped and either lands at the bottom of the grid or on top of another checker.

**Alternative Courses**:
- **Step 3**: Agent types in value <= 0 or > 7.
  1. Displays error ("Invalid column number!").
  2. Go back to step 1.

### Use Case 1.2: Determine Win Condition
- **Actors**:
- **Overview**: The algorithm checks if the agent has made a four-in-a-row.

**Typical Course of Events**:
1. This case starts after the end of the current agent's turn.
2. The algorithm executes a linear search of the whole grid, beginning with the upper-most row of the left-most column.
3. If it detects a checker of the current agent, it checks if there is an identical checker east, south, southeast, and southwest of it.
4. If there are two checkers horizontally, search to the right for a horizontal four-in-a-row.
5. If there are two checkers vertically, search down for a vertical four-in-a-row.
6. If there are two checkers diagonally down to the right, search southeast for a diagonal four-in-a-row.
7. If there are two checkers diagonally down to the left, search southwest for a diagonal four-in-a-row.
8. If any one of these four above conditions is fulfilled, then the agent who made the Connect Four is declared the winner, and there is no need to search the grid any more.

**Alternative Courses**:
- **Step 3**: If the algorithm encounters either the opponent's checker or an empty space adjacent to the current agent's checker.
  1. Go back to step 2 and keep searching.
- **Step 4 - 7**: If the algorithm does not find a Connect Four horizontally, vertically, or horizontally.
  1. Go back to step 2 and keep searching.

### Use Case 1.3: Choose to start another game
- **Actors**: User
- **Overview**: User is offered the choice to either play another Connect Four game or quit to the main menu.

**Typical Course of Events**:
1. Case starts after 1.2 when either the user or the agent wins.
2. Software asks user if they would like to play another game with the same opponent or quit.
3. User types in a numerical value. "1" means that the user wants to replay the game and "2" means to go back to the main menu.
4. If the user types in "1," execute Case 1.1 for the user if he lost, or for the opponent if the user won.

**Alternative Courses**:
- **Step 3**: User types in invalid number
  1. Display "Invalid Number" and repeat Step 2.

### Use Case 1.4: Main Menu
- **Actors**: User
- **Overview**: A Menu where the user can select from different game modes.

**Typical Course of Events**:
1. Case occurs either upon first starting the program or after the user quits playing a Connect Four game.
2. User is presented with five choices, each designated by a numeric value: Player vs. Player, Player vs. AI, AI vs. AI, Options, and Quit
3. Selecting the first three will start a new game and execute Case 1.1 (Whoever deals with that case first is randomly selected by the algorithm)
4. Selecting "4" for "Options" will execute Case 1.5 and take the user to the Options page.
5. Selecting "5" for "Quit" will end the application.

**Alternative Courses**:
- **Step 3 - 5**: User types in invalid number
  1. Display "Invalid Number" and repeat Step 2.

### Use Case 1.5: Options Menu
- **Actors**: User
- **Overview**: Allows the user to view player and AI records, as well as the ability to start the AI training over from scratch.

**Typical Course of Events**:
1. Case occurs after the user selects "Options" in the main menu.
2. User is given four choices to choose from, each designated by a numeric value: View Player Records, View AI Records, Erase AI Data, and Quit
3. Typing "1" brings up the game data for the player, listing how many games it played, its wins, its losses, and a win-loss ratio.
4. Typing "2" brings up the game data for the ML AI algorithm, listing how many games it played, its wins, its losses, and a win-loss ratio.
5. Typing "3" asks the user if the training data the AI has learned while playing will be erased. Typing "Y" will do so and "N" takes the user back to step 2 (The Options Menu).
6. Typing "4" brings the user to the Main Menu (Case 1.4).

**Alternative Courses**:
- **Step 3 - 5**: User types in invalid number
  1. Display "Invalid Number" and repeat Step 2.
