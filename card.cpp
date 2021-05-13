#include <iostream>

#include "card.h"

Color Card::getColor() const{
    return color;
}
    
int Card::getNumber() const{
    return number;
}

void Card::setColor(Color c){
    color = c;
}

void Card::setNumber(int n){
    number = n;
}

// TODO: We need to add colors here
string Card::render(int line, int pos) {
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: 
            switch(color){
            case RED:
                // Change color + (MSG) + change back
                return "|\033[01;44;41m    RED    \x1B[0m|";
                break;
            case BLUE:
                return "|\033[01;44;44m    BLUE   \x1B[0m|";
                break;
            case GREEN:
                return "|\033[01;44;42m   GREEN   \x1B[0m|";
                break;
            case YELLOW:
                return "|\033[01;44;43m  YELLOW   \x1B[0m|";
                break;
            case WILD:
                return "|   \033[01;44;41mW\x1B[0m\033[01;44;44mI\x1B[0m\033[01;44;43mL\x1B[0m\033[01;44;42mD\x1B[0m    |";
            default:
                return "|           |";
                break;
            break;
            }
        case 3: return "|           |";
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        case 8: {
            ss << " Card: " <<  pos << "     ";
            return ss.str();
        };
        default:
            return " ";
    }
}

NumberCard::NumberCard(Color c, int n) {
    setColor(c);
    setNumber(n);
}

string NumberCard::render(int line, int pos) {
    stringstream ss;
    if (line == 3) {
        ss << "|     " <<  number << "     |";
        return ss.str();
    } else {
        return Card::render(line, pos);
    }
}

bool NumberCard::play(Card* discard, GameState &gameState) {
    if(color == discard->getColor() || number == discard->getNumber()){
        return true;
    } else {
        return false;
    }
}

//////////////////////////////////
// Reverse card
// Card Number: 10

ReverseCard::ReverseCard(Color c) {
    setColor(c);
    setNumber(10);
}

string ReverseCard::render(int line, int pos) {
    if (line == 3) {
        return "|  REVERSE  |";
    } else {
        return Card::render(line, pos);
    }
}

bool ReverseCard::play(Card *discard, GameState &gameState) {
    if (color == discard->getColor() || number == discard->getNumber()){
        if (gameState.turnDirection == RIGHT) gameState.turnDirection = LEFT;
        else gameState.turnDirection = RIGHT;
        return true;
    } else {
        return false;
    }
}

//////////////////////////////////
// Skip card
// Card Number: 11

SkipCard::SkipCard(Color c) {
    setColor(c);
    setNumber(11);
}

string SkipCard::render(int line, int pos) {
    if (line == 3) {
        return "|   SKIP    |";
    } else {
        return Card::render(line, pos);
    }
}

bool SkipCard::play(Card *discard, GameState &gameState) {
    if (color == discard->getColor() || number == discard->getNumber()){
        gameState.nextTurn();
        return true;
    } else {
        return false;
    }
}

//////////////////////////////////
// Draw-2
// Card Number: 12

Draw2Card::Draw2Card(Color c) {
    setColor(c);
    setNumber(12);
}

string Draw2Card::render(int line, int pos) {
    if (line == 3) {
        return "|   DRAW 2  |";
    } else {
        return Card::render(line, pos);
    }
}

bool Draw2Card::play(Card *discard, GameState &gameState) {
    if (color == discard->getColor() || number == discard->getNumber()){
        gameState.numCardsToDraw = 2;
        gameState.nextTurn();
        return true;
    } else {
        return false;
    }
}

//////////////////////////////////
// Wild
// Card Number: 13

WildCard::WildCard() {
    setColor(WILD);
    setNumber(13);
}

string WildCard::render(int line, int pos) {
    if (line == 3) {
        return "|   WILD    |";
    } else {
        return Card::render(line, pos);
    }
}

bool WildCard::play(Card *discard, GameState &gameState) {
    int input;
    std::cout << "Choose color:" << std::endl;
    std::cout << "1: RED" << std::endl;
    std::cout << "2: BLUE" << std::endl;
    std::cout << "3: GREEN" << std::endl;
    std::cout << "4: YELLOW" << std::endl;
    std::cin >> input;
    
    switch (input) {
        case 1: setColor(RED); break;
        case 2: setColor(BLUE); break;
        case 3: setColor(GREEN); break;
        case 4: setColor(YELLOW); break;
        default: return false;
    }
    
    return true;
}

