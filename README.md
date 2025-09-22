# Senior Thesis Repo: CONNECT 4 SOFTWARE WITH A Q-LEARNING ML-POWERED ALGORITHM
This repository is provided to help you build your senior thesis project. You will edit it to store your specification documents, code, and weekly checkins.

## Software Requirements Specification

## Introduction

### Purpose
This document provides all the functional and non-functional requirements of the Machine Learning Connect Four Software. The primary purpose of this software is to train an Artificially Intelligent algorithm on the popular MB game, Connect Four, so that it can go up against and masterfully beat human players of the game.

The key goals of the software are:
- To create a Q-Learning-based algorithm capable of mastering Connect Four
- To discover possible new and unexpected strategies for winning the game
- To showcase the potential of Machine Learning AI in games both physical and virtual.

### Scope
Although it is an option for two human players to play Connect Four, this software is supposed to pit human players against an AI. The AI decides the best possible move based on the current state of the board, and is either rewarded or punished based on the ultimate outcome of the game.
The software will handle:
- Connect Four Board setup
- Checking for win
- Player vs. Player functionality
- Player vs. AI functionality
- AI vs. AI functionality (If possible)

### Definitions, Acronyms, and Abbreviations
- **Machine Learning (ML)**: A form of Artificial Intelligence where computers utilize recorded data to make its own decisions
- **Q-Learning**: A specific type of ML in which the AI determines the best possible course of action based on the current state of the game.
- **State (s)**: The list of all moves played by both agents throughout the game.
- **Agent**: Anything that acts to achieve a goal.
- **Learning Rate (α)**: How much new information should be acquired versus old info.
- **Discount Factor (γ)**: How important is the future reward over the immediate reward.
- **Board**: The 7x6 Game Space in which agents drop their checkers into the seven spots on top of the board.
- **Hole**: The place inside the board where a checker lands into. Marked as follows:
  - R for Player 1 (Red)
  - B for Player 2 (Black)
  - O for Empty

## Overview
Machine Learning Connect Four is a software designed to train an AI algorithm. The algorithm is based on Q-Learning, a type of machine learning where decisions are made based on what is happening right now and which one is the most valuable.
The primary functionality for the algorithm is based on the following equation: **Q(s, a) = Q(s, a) + α * [R(s, a) + γ * maxQ(s', a') - Q(s, a)]**
Q(s, a) is the current state of the game based on the action taken
α is the Learning Rate. See the Definitions page for the full definition.
R(s, a) determines whether the AI should be rewarded or punished at the end of the game. Points are added if the AI wins, points are docked if it loses, and half a point is added if the game ends in a draw.
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

### Use Case 1.1: Place checker
- **Actors**: Agent
- **Overview**: Agent selects spot on the top of the Board to drop the checker into

**Typical Course of Events**:
1. Software prompts agent to select a spot.
2. Agent types in numeric value to select a specific spot.
3. Checker is dropped and either lands on the bottom of the board or on top of another checker.
4. Checks entire board if agent has connected four checkers.

**Alternative Courses**:
- **Step 3**: Spot number is not valid.
  1. Displays error.
  2. Go back to step 1.

### Use Case 1.2: Determine Win
- **Actors**: Student
- **Overview**: Student finds a desired class.

**Typical Course of Events**:
1. Run Use Case 1.1, *Secure Login*.
2. Displays list of current and upcoming semesters.
3. Student selects a semester.
4. Displays departments actively offering courses in that semester.
5. Student selects a department.
6. Displays courses of that department from that semester that are currently offered.
7. Student selects a course.
8. Displays course details.

**Alternative Courses**:
- Any step: Student can start a new search at any time
  1. Student clicks "start new search."
  2. Go back to step 2.

### Use Case 1.3: Register for a Course
- **Actors**: Student
- **Overview**: Student registers for a course.

**Typical Course of Events**:
1. Run Use Case 1.2, *Find a Course*.
2. Student clicks on "register for course" button.
3. Verify that student can take the course.
4. Display "You have successfully registered for 'insert course name here'."

**Alternative Courses**:
- **Step 4**: Student can't take course
  1. Displays "You cannot take this course, please contact the registrar for further information."

### Use Case 1.4: Check Grades
- **Actors**: Student
- **Overview**: Student checks grades.

**Typical Course of Events**:
1. Run Use Case 1.1, *Secure Login*.
2. Display previous semesters in which the student took course(s).
3. Student selects semester.
4. Displays courses and grades.

### Use Case 1.5: Registrar Creates Sections
- **Actors**: Registrar
- **Overview**: Registrar creates section.

**Typical Course of Events**:
1. Run Use Case 1.1, *Secure Login*.
2. Registrar selects "Create Section."
3. Display "Create Section" form.
4. Registrar submits form.
5. System verifies valid entry (no overlapping schedules/times).
6. Displays section details and successfully added.

**Alternative Courses**:
- **Step 6**: Entry invalid
  1. Display error.
  2. Go back to step 3.

### Use Case 1.6: Registrar Modifies Section
- **Actors**: Registrar
- **Overview**: Registrar modifies existing sections.

**Typical Course of Events**:
1. Run Use Case 1.1, *Secure Login*.
2. Registrar selects "Modify section."
3. Displays all sections (with order options).
4. Choose section.
5. Display "Edit Form" with filled-in data.
6. Submit/verify data.
7. Display "Section successfully edited."

**Alternative Courses**:
- **Step 7**: Invalid Data
  1. Display Error.
  2. Go back to step 5.
