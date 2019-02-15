## Kingdom Rush

A knock-off of the actual game "Kingdom Rush".
The genuine "Kingdom Rush" is a realtime tower defense game with a fantasy-medieval theme, produced by Ironhide and distributed by Armor Games.

---
### Table of Contents
* [General info](#general-info)
* [Setup](#setup)
* [Game rules](#game-rules)

---
### General info
This is the first out of four assignments for my "Advanced Programming" course. Project had to be completed individually in a week.
The code is messy but it gets better in each assignment.
This is all coded in C++.

---
### Setup
To run this project, install a custom SDL2 wrapper, RSDL, found on the [UT AP github page](https://github.com/UTAP/RSDL). All credit goes to Professor Ramtin Khosravi.
To run the game, use the makefile and input any level:

```
$ make
$ ./all <level1.txt
```
---
### Game rules
You are given 15 lives and 220 points to begin with. You lose lives if any enemy passes through the finish line. You win if all the enemy wave have finished, there are no more enemies on the path and you still have atleast one life left.

#### Towers
You can add a tower by clicking on a tower spot on the map and typing the letter representing the tower.
Towers you can add are as follows:

**1. Archer**

<img src="https://github.com/hodaaab/KingdomRush/blob/master/assets/towers/archer.png" width="70">

This tower has quick, physical attacks. Each bullet causes **50 units damage**. Each bullet is thrown once every 700 milliseconds. Costs **70 points**. Press key **A** to add.

**2. Cannon**

<img src="https://github.com/hodaaab/KingdomRush/blob/master/assets/towers/canon.png" width="70">

This tower has slow, physical attacks. Causes **140 units damage**. Attacks once every 2000 milliseconds. Bullets thrown don't affect just the one enemy hit but all enemies in a 50 pixel radius of the enemy hit. Costs **125 points**. Press key **C** to add.

**3. Mage**

<img src="https://github.com/hodaaab/KingdomRush/blob/master/assets/towers/mage.png" width="70">

This tower has magical attacks. Causes **140 units damage**. Attackes once every 1500 milliseconds. Costs **90 points**. Press key **M** to add.

**4. Icy**

<img src="https://github.com/hodaaab/KingdomRush/blob/master/assets/towers/icy.png" width="70">

This tower has magical attacks. When an enemy is hit, its speed decreases to half. Causes **30 units damage**. Attacks once every 2000 milliseconds. Costs **80 points**. Press key **I** to add.

#### Enemies
Enemies enter the map at specific times, based on the level, in waves. 

**1. Orc**

<img src="https://github.com/hodaaab/KingdomRush/blob/master/assets/enemies/orc/right.png" width="50">

Simplest enemy. Has **200 lives**, moves 42 pixels/sec, no armor. Destroying it has **5 points**. If it reaches the endpoint, you lose **1 life**.

**2. Wolf**

<img src="https://github.com/hodaaab/KingdomRush/blob/master/assets/enemies/wolf/right.png" width="50">

Fast but easy to destroy. Has **100 lives**, moves 85 pixels/sec, no armor. Destroying it has **4 points**. If it reaches the endpoint, you lose **1 life**.

**3. Armored**

<img src="https://github.com/hodaaab/KingdomRush/blob/master/assets/enemies/armored/right.png" width="50">

Slow but powerful. Has **450 lives**, moves 21 pixels/sec, has physical armor. Destroying it has **8 points**. If it reaches the endpoint, you lose **3 lives**.

**4. Demon**

<img src="https://github.com/hodaaab/KingdomRush/blob/master/assets/enemies/demon/right.png" width="50">

Slow but powerful. Has **400 lives**, moves 28 pixels/sec, has magical armor. Destroying it has **8 points**. If it reaches the endpoint, you lose **3 lives**.
