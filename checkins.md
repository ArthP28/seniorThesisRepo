## Week 1 Summary (09/08/2025)

### This week I worked on:

I first presented my proposal to Professors Mahoney and Zak. My proposal was to write a paper about the applications of Machine Learning in video games and other virtual environments. Afterwards, I cloned the base Senior Thesis Repository onto my computer, and added a blank thesis document to get started. Meanwhile, outside of class, I took annotated notes on some research articles I found that are relevant to my paper.

### This week I learned:

I have learned about the requirements and expectations of the Senior Thesis Project and how they apply to my paper proposal.

### My successes this week were:

I was able to get my own copy of the Senior Thesis Repo and insert my own sources into it.

### The challenges I faced this week were:

Because I chose to work on a paper in a project-heavy course, my biggest challenge this week was trying to convince the instructors of my proposal. I wanted to write a paper for my Senior Project because it was the most effective way for me to explore new and exciting technologies.

---

## Week 2 Summary (09/15/2025)
### This week I worked on:

I was not able to commit much work on my Project Repo this week, because I spent most of my time communicating with instructors. I was talking with them about my project proposal and the progress I have made on it prior to the beginning of the academic year. Towards the tail end of the week, I came up with a fresh new idea to share with my instructors.

### This week I learned:

As I talked with professors about my initial proposal, it began to dawn on me how better it would be to convey my thesis idea through a project rather than a paper. Making a project around machine learning would be a more direct and rewarding method to demonstrate the revolutionary prospects machine learning has on the mediums of both physical and virtual games.

### My successes this week were:

Even though I had to sacrifice my paper proposal, choosing to work on a Machine Learning Connect Four algorithm will hopefully give me a stronger base to work on my thesis idea.

### The challenges I faced this week were:

The decision to give up my proposal to write a thesis paper was the most difficult I had to make. It essentially reduced the amount of resource-gathering and note-taking I put in over the past two months to nothing. However, considering the direction I have been taking over the past three years, as a student software developer with an interest in AI, it would be more difficult to connect my future prospects through a paper than through a project.

---

## Week 3 Summary (09/22/2025)
### This week I worked on:

After I got my proposal approved and locked in, I spent the whole week designing a basic Connect 4 program as well as writing the specifications for my whole Senior Project.

### This week I learned:

While designing the graphical elements of the software, I took some time to review what ANSI Escape Code do, and how they modify the command terminal's output. I used it to bold text, color in text a specific color, and to erase individual lines of printed strings. By incorporating system() commands as well, I formatted my software to appear clean and professional.

### My successes this week were:

Getting the overall Player vs. Player Connect Four program working is the biggest success I have had in my Senior Project so far. It felt like I had already completed half the entire project.

### The challenges I faced this week were:

Trying to mentally picture the overall structure of my Connect Four Program was pretty challenging. I ended up having the whole game be in one function within main(), where, within a while loop, players take turns choosing a column to drop their own checker into. The program then checks if the player has won right before the end of the primary while loop. I based the nested logic of the player's actions on my existing experience working with graphical applications, such as a Geography Comparer program I worked on last summer. I am not sure whether using an alternate structure would make the program's code simpler to understand.

---

## Week 4 Summary (09/29/2025)
### This week I worked on:

This Monday, I met with professors Zak and Mahoney to discuss my project progress as well as to schedule my elevator pitch for next week. I then spent the rest of the week preparing for the pitch, by first typing out an outline and then finding time every day to practice speaking.

### This week I learned:

During the discussion I had with both professors, I was first made aware of a more sophisticated form of Q-Learning called "Deep Q-Learning." Rather than using Reinforcement Learning, Deep Q-Learning utilizes Deep Learning for environments with a high number of possible future states, such as robotics and video games. If I successfully implement Q-Learning early, I might consider upgrading the current algorithm to run on Deep Learning.

### My successes this week were:

Both professors were excited about the project idea. Professor Zak especially could not wait to see where the concept of an adaptive ML algorithm playing board games can go. Because I already have a working prototype of the Connect Four game engine implemented, that left me with a lot of time to focus on pitch practice and other homework.

### The challenges I faced this week were:

Because of the workload I have received over the week, I struggled to find a lot of time to work on my elevator pitch. But I was still able to dedicate a good amount of time over the last few days practicing and revising my pitch to a point where I can reasonably be confident in presenting my thesis idea well.

---

## Week 5 Summary (10/06/2025)
### This week I worked on:

Throughout this week, I added a new player class to my project. Besides being able to drop in their own checkers, the player class also has data regarding wins and losses for all games. They will be displayed in an options menu. The AI models, including the Q-Learning one, will be derived from this class, with the only major change being a distinct dropChecker() method that overrides the base one. I revamped the main file to be compatible with these new player classes, and within the board file, I reworked a couple of methods and added some new ones.

### This week I learned:

Upon completing my first assignment for the AI class, I noticed that the board class for a Tic-Tac-Toe algorithm utilizes enums to determine the player turn and the status of each new board state. Considering that my Q-Learning algorithm will function similarly to the uninformed search algorithms of the assignment, I decided to implement these enums into my project.

### My successes this week were:

My player class remained an important highlight of this week because I am getting one step closer to integrating Artificial Intelligence within my project. This player class will serve as a base for a dummy AI algorithm that I will work on next week. It will just randomly select columns to drop checkers.

### The challenges I faced this week were:

I was having trouble figuring out the relationship between the board and the player. I wanted the board to reference the player for scorekeeping and win-checking, while I wanted the player to reference the board for the actions that happen within the game. So, I initially have two variables within two classes that reference their opposite class, which threw me into a circular inclusion error that I could not solve on my own. I resorted to having the playGame() function in main.cpp keep track of the current state of the game, while I only let the player class use the board class for dropping checkers.

---

## Week 6 Summary (MM/DD/YYYY)
### This week I worked on:

[Your answer here]

### This week I learned:

[Your answer here]

### My successes this week were:

[Your answer here]

### The challenges I faced this week were:

[Your answer here]

---

## Week 7 Summary (MM/DD/YYYY)
### This week I worked on:

[Your answer here]

### This week I learned:

[Your answer here]

### My successes this week were:

[Your answer here]

### The challenges I faced this week were:

[Your answer here]

---

## Week 8 Summary (MM/DD/YYYY)
### This week I worked on:

[Your answer here]

### This week I learned:

[Your answer here]

### My successes this week were:

[Your answer here]

### The challenges I faced this week were:

[Your answer here]

---

## Week 9 Summary (MM/DD/YYYY)
### This week I worked on:

[Your answer here]

### This week I learned:

[Your answer here]

### My successes this week were:

[Your answer here]

### The challenges I faced this week were:

[Your answer here]

---

## Week 10 Summary (MM/DD/YYYY)
### This week I worked on:

[Your answer here]

### This week I learned:

[Your answer here]

### My successes this week were:

[Your answer here]

### The challenges I faced this week were:

[Your answer here]

---

## Week 11 Summary (MM/DD/YYYY)
### This week I worked on:

[Your answer here]

### This week I learned:

[Your answer here]

### My successes this week were:

[Your answer here]

### The challenges I faced this week were:

[Your answer here]

---

## Week 12 Summary (MM/DD/YYYY)
### This week I worked on:

[Your answer here]

### This week I learned:

[Your answer here]

### My successes this week were:

[Your answer here]

### The challenges I faced this week were:

[Your answer here]

---

## Week 13 Summary (MM/DD/YYYY)
### This week I worked on:

[Your answer here]

### This week I learned:

[Your answer here]

### My successes this week were:

[Your answer here]

### The challenges I faced this week were:

[Your answer here]

---
