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

## Week 6 Summary (10/13/2025)
### This week I worked on:

During class, I created a sample dummy AI class that only drops checkers into random columns. The purpose of this class is not to demonstrate the AI's capabilities as a Q-Learning algorithm would, but to show how a game against a machine opponent would play out in the software.
Throughout Fall Break, I got to work on the main menu and its graphical components. Each menu within the application is encapsulated into its own function. User input is handled through a while getline() loop, in which the program will stop prompting the user for any more input once a valid character is typed in. The graphical aspects of the menu use ANSI Escape Codes to format the text, as well as calling system("clear") commands to switch between different menus. The downside of using the latter is that it restricts my program to being able to work most effectively on Linux Operating Systems, such as Ubuntu. Windows PowerShell has its own clear command in the form of "cls", which is different compared to "clear" in Linux.

### This week I learned:

I refreshed my knowledge on Object-Oriented Programming when constructing the dummy AI class. By adding a reference to the Player Superclass in the AI's class name, all of the player's data properties are inherited into the AI class. I also incorporated polymorphism by overriding the Base Player's dropChecker() method to do something different for the AI class.

### My successes this week were:

By adding ANSI codes into my program, I have implemented a simple and intuitive menu navigation system that works in the console terminal. The success of adding the dummy AI class to the program also made me confident in my ability to add the Reinforcement Q-Learning aspect to the program in the future.

### The challenges I faced this week were:

I did not come across any major roadblocks this week, although making the dummy AI class body did left me thinking for a while. I was concerned with how I could change some inherited variables by default when initializing an instance of the dummy AI. I ended up having the constructor call the Player class's constructor to change the default name from "Arthur" to "Lily," just so I can tell the two classes apart.

---

## Week 7 Summary (10/20/2025)
### This week I worked on:

Because my sprint presentation has been pushed to the following week, I made sure that I spent as much time as I could practicing. I also started development on the Q-Learning AI, where right now I am creating a training function. This function is supposed to update the table of Q-Values to be the most optimal for every thousand epochs.

### This week I learned:

Brushing up on Q-Learning made me realize three main things. The first one is that decisions are made based on selecting the most-rewarding (or highest) value in the Q-Table. The dimensions of a Q-Table correspond to the number of available actions and the amount of possible states in the game. These values are influenced by the algorithm's decision-making equation and whether the chosen state has led to a win or a loss. If it is a win, then the AI is rewarded with points added to their table. This ultimately makes the table the most vital component of a Q-Learning algorithm. The second thing I have noticed is that the Q-Learning algorithm only switches between two main states, making it simple to implement. Exploration is where the AI instinctively selects columns to place its checker just to see what happens. While Exploitation has the algorithm sift through the Q-Table to find the largest Q-Value and, therefore, the best decision to make. The final main idea I have learned is that Q-Learning algorithms, as powerful as they are, are not equipped to handle Q-Tables of large actions and states. Considering that the game of Connect Four has over 4.5 trillion possible board states, I was afraid that my thesis work might take far longer than I anticipated. But then it turned out that my Q-Table of three states (Win, Loss, and Incomplete) and seven actions (Seven columns to drop checkers) is just right for the Q-Learning algorithm to handle, as long as I do not resort to constructing a decision tree like I have done in building previous AI algorithms.

### My successes this week were:

I surprisingly got a significant amount of the Q-Learning part of the software coded up. As I indicated before, all that I need to do is put all my helper methods together into a training function. I do hope that the Q-Learning AI works well, as it is the final and most important main element I have to put in my program. If I get the program finished early, I can choose to upgrade my Q-Learning AI further by incorporating elements of Deep Learning.

### The challenges I faced this week were:

Like with my Elevator Pitch, it was tough trying to find time throughout the day to practice for my first sprint presentation. This week has been arguably busier than almost a month ago, because on top of my senior thesis progress, I have another ambitious project to work on from another class, as well as a midterm that I needed to study for. I do believe, however, that I will come to class next Monday as prepared as ever for my first demonstration of my thesis project.

---

## Week 8 Summary (10/27/2025)
### This week I worked on:

I spent the entire past week creating a training function for the Q-Learning AI, since it is necessary for it to make the correct moves. This training method has the computer player choosing to either explore or exploit existing Q-Data to find the right column. Once it has the column index, it then drops a checker on their chosen spot and determines the immediate reward of making that move. The AI ultimately wants to win the game to retrieve a maximum reward value of 1.0. This training is repeated thousands of times until a Q-table full of diverse values is supposedly formed. The Q_Table in the Connect 4 Program is an Unordered Map, with the key being the board string states and the value contained being a vector of double Q-values. Because of this, I also created a script for a Decision tree that helps in generating an unordered set of board states for the Q-table.

### This week I learned:

This week, I gained a deeper understanding of Q-Training's inner workings by analyzing the order of operations in common implementations. Most of these implementations are written in Python, so I tried my best to paraphrase and translate the code into C++. This is also the first time I utilized unordered sets and maps in my project, and they are really useful to have.

### My successes this week were:

Despite numerous challenges, I got the training method to develop a Q_Table with a relatively large amount of nonzero state-action pairs (That is, a list ofactions that are not entirely comprised of zeroes for a particular board state). Working on the functions that convert boards into strings and vice versa was also one of my biggest successes this past week, because having these functions made developing and visualizing the Q-Table so much more efficient and convenient.

### The challenges I faced this week were:

Throughout the first few days of the week, I tried designing my training function around a 7x7 Q-Table (7 Max Actions, 7 Possible future states for each action taken), because I knew there was no way I would design a Q-Table with 4.5 trillion possible states for a 7x6 game grid. However, as I struggled trying to design the right training algorithm to accommodate a Q-Table and board grid of such a size, I turned to my professors for help. That was when I learned that, considering the millions of possible states that exist in Connect Four, and the very slow amount of time it would take to process all of them, it would be impossible for me to create a Q-Table of that size, even if I prune out all the duplicates and illegal moves. Because having a Q-Learning AI is crucial for my project, I reduced the size of the game board considerably so that the computer has a better chance of processing all the possible states. The Q-Learning AI can now only work on game boards in the absolute minimum dimensions (4x4). 5x5 and 4x5 boards are also compatible; however, they require significantly more time for the compiler to process. For processing regular-sized boards, my professors encouraged me to search for a more efficient AI algorithm capable of handling a ginormous amount of states, which I have quickly found and plan to implement at the end of my second sprint.

---

## Week 9 Summary (11/03/2025)
### This week I worked on:

Throughout this week, I made the final tunings to my Connect Four Q-Learning Algorithm. My primary goal was to strike a balance between efficiency and effectiveness by adjusting certain significant values until they were just right. These included the hyperparameters needed for updating the Q-Table, such as the alpha, discount factor, and gamma values, as well as the number of episodes (games) on which the algorithm is trained.

### This week I learned:

The numerous rounds of testing and debugging led me to reevaluate the structure of my C++ Implementation of the Q-Learning algorithm, which I translated from others' Python versions. I ended up rewriting various chunks of my training algorithm to ensure that the AI algorithm gathers a substantial amount of Q-Information within a realistic timeframe. So if there was one thing that I can take away from this week, it was to think outside the box.

### My successes this week were:

This week marks the final time I have worked on the Q-Learning Algorithm in my project. Since reorganizing my training method, the AI has been able to accurately gather Q-Data and take full advantage of it to make intelligent decisions. Despite its capabilities being limited to small 4x4 and 4x5 game grids, it was powerful enough to win against me in a majority of the games it played. Because the Q-Learning Algorithm accomplished its purpose of capably competing against human Connect Four players and triumphing, I consider a significant part of the project complete and am ready to start my work on a second Artificial Intelligence, which makes decisions on a proper 7x6 board more efficiently through Deep Learning.

### The challenges I faced this week were:

While adjusting all the necessary values for the Q-Algorithm took lots of trial and error, one hidden irregularity within the Q-Learning intelligence has perplexed me. Despite all the changes to the values I have done, the AI would appear to select the highest Q-Value on its first turn as expected. However, as the game progresses, it eventually resorts to dropping checkers into the first available column. I knew this strange behavior was due to the Q-Value propagation not penetrating those possible future states in the game, yet I was stumped as to where this bug originated. With guidance from my professor, I was surprised to discover that this sudden regression in Q-Thinking came from both the Q-Learning AI itself (B) as well as the training algorithm (R) using the same Q-Table for their decision making. The AI was not exploring enough Q-States to affect its values because the decision to set those values comes from the current data of the Q-Table at that turn and not from the other player's actions. I since changed R's behavior to randomly selecting columns to drop its checkers and change the Q-Values afterwards. Now the training function works wonders, and I can finally rest knowing that I have spent a lot of time learning and developing an effective Q-Learning Algorithm.

---

## Week 10 Summary (11/10/2025)
### This week I worked on:

This week, I spent most of my time preparing for my second sprint presentation. I made sure to reserve more time throughout the week to review my slides and program demonstration. I even had my older sister listen to my presentation, and she offered me some mindful tips. Because of the extra training I did, I felt more confident about my presentation than I was before. In addition to the speech, I created a helper tree class for the upcoming Connect 4 Neural Network. Unlike the Q-Learning Tree class, the Neural Network Tree Class gathers labeled movement data of the computer, utilizing it as a guide to plot a path to the finish.

### This week I learned:

I have developed a foundational understanding of Neural Networks in the course on Artificial Intelligence. So I envisioned my theoretical Neural Network model to take in 42 neurons in the input layer, each one corresponding to a space on the 7x6 board, and illuminate one of the seven neurons in the output layer. The neurons here represent columns that are available to choose, and as more columns get filled, more neurons are prohibited from ever lighting up.

### My successes this week were:

As stated before, I was able to spend more time practicing for my presentation and therefore felt more mentally prepared to present. I have also already created a Tree Helper class for the Neural Network, which is a crucial component of the new AI Model that I am about to build.

### The challenges I faced this week were:

I made several design choices while conjuring up the methods for the tree helper class. For instance, a movement path for the computer is built by backpropagating through the nodes of the tree, from the winning move to the beginning of the game. Each label recording the AI's deciding move is retrieved from the action value of the current node's child. A risky strategy I chose to implement is the inclusion of duplicate board states, because even though both states look exactly identical, the way they came to be is unique. This means that the default state-generation method with no parameters does not work. Therefore, I included an overloaded variant in which only a specific number of games are played to gather the labeled input data.

---

## Week 11 Summary (11/17/2025)
### This week I worked on:

This week, I worked on creating the Neural Network Class. Using the Neural Network Code kindly provided by Professor Mahoney, the algorithm should go through all its trained label data to process all 42 input nodes from the current board and return the best possible move to make.

### This week I learned:

Through integrating the Professor's Neural Network code into my Machine Learning algorithm, I have gained a deeper understanding of how Neural Networks function. I have learned more about how these networks process tons of training data into an input vector of double-type arrays. Each double represents the current value that each neuron holds. 

### My successes this week were:

The Neural Network was able to predict the testing data very accurately. The success rate would typically be around 85 - 95% based on my learning rate and layer configurations.

### The challenges I faced this week were:

There were quite a few bugs that I have discovered while testing the logic of my neural network. The algorithm would sometimes select columns that are already full, putting itself in an infinite loop. To mitigate this, I have the prediction method return the next illuminated neuron, which does break some of the logic behind how a Neural Network is supposed to work, but it does discourage the AI from choosing full columns. More fundamentally, the Network is not making the decisions that I expected it would make, as it fails to recognize how to achieve a four-in-a-row. I will have to spend all of Thanksgiving Break trying to find ways to make this better.

---

## Week 12 Summary (11/24/2025)
### This week I worked on:

For almost all of Thanksgiving Break I tried finding numerous ways to improve the intelligence of my Neural Network algorithm. These included adjusting the learning rate, adding more layers, adding more neurons to each hidden layer, and even trying the Mixture of Experts approach. However, all of my attempts either greatly increased the training time to an unbearably slow rate, or confused the logic of the network itself. Towards the end of my break, I was out of ideas and time, so I moved onto creating a save system for the Player and Neural Network data, which would be my last major change in the Thesis Project.

### This week I learned:

This Thanksgiving week was when I truly learned the importance of managing my time and expectations. As much as I wanted to keep pursuing a solution for my Neural Network, I realized that this would only waste more time that could have been spent on implementing other functions of the project. I always intended to have my project finished by the beginning of December, so that I have the rest of the time left for practicing for my final presentation. I made the difficult decision to halt further development of the Neural Network, as it became obvious that it had grown too ambitious to be fully completed by the end of the semester. I redirected my focus to my last initial proposed function, the save system, and was able to finish development of the program by December 1st.

### My successes this week were:

The silver lining of this week was the fact that I got a working save system implemented for all players. Each player has scoring data that is saved automatically to its own .txt file for preservation. In order to load an existing player, it must be done manually by typing the name of the txt file containing the data of a particular player.

### The challenges I faced this week were:

As stated before, the constant tweaking of the Neural Network code was perhaps the hardest challenge I have ever faced in the entire development process. The algorithm grew too ambitious for me to reasonably finish in the amount of time that I had left, so I left it on the side to work on later after this semester is over.

---

## Week 13 Summary (12/01/2025)
### This week I worked on:

[Your answer here]

### This week I learned:

[Your answer here]

### My successes this week were:

[Your answer here]

### The challenges I faced this week were:

[Your answer here]

---
