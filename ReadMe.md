# DeckBuilder Game 
> Project Created by Lucy Mills and Ramon Fernandez-Garcia

A deckbuilder game inspired by the popular game Hearthstone. This is a custom, two player expierence all viewed in a terminal window. There are emoticon graphics to represent the different cards you possess and that are the field against your foe. 

This was our final project for our class CSCI-2270 - Data Structures. 

## How to run the game
1. Download the folder
2. Open a new terminal
3. type 'run [DeckFile.csv]' Where Deckfile can be any .csv with the proper format 

## Game info
There is a DeckFile already provided (Deck_01.csv) but you may add cards in this format
> Health,Mana_Cost,Attack,Name

- Once game is running you will need to type in Player1's name and Player2's name then hit ENTER After that the players will have to type numbers 1-6 to place cards on the battle field, Then hit 6 to pass on the turn

Game will end when either one of these 3 things happens:
- Player1 dies
- Player2 dies
- Turns surpass the max amount of turns (*Set at 20*)
