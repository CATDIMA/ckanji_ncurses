#include "input_field.h"

InputField::InputField(std::string title, int posY, int posX, bool isSelectable, int inputLenght)
{
    this->title = title;
    this->posX = posX;
    this->posY = posY;
    selectable = isSelectable;
    inputLen = inputLenght;
}

void InputField::setInputText(std::string str)
{
    inputText = str;
}

std::string InputField::getInputText()
{
    return inputText;
}

void InputField::popBackInputText()
{
    if(!inputText.empty())
        inputText.pop_back();
}

void InputField::print(WINDOW* win)
{
    wclrtoeol(win);
    mvwprintw(win, posY, posX, title.c_str());

    if(selected)
        wattron(win, COLOR_PAIR(static_cast<int>(COLOR_PAIR::CURSOR)));
    else
        wattron(win, COLOR_PAIR(static_cast<int>(COLOR_PAIR::SECONDARY_WIN_BACKGROUND)));

    if(inputText.empty())
    {
        mvwprintw(win, posY, posX + utf8Length(title), std::string(inputLen, ' ').c_str());
    }
    else if(utf8Length(inputText) < inputLen)
    {
        mvwprintw(win, posY, posX + utf8Length(title), inputText.c_str());
        mvwprintw(win, posY, posX + utf8Length(title) + utf8Length(inputText), std::string(inputLen - utf8Length(inputText), ' ').c_str());
    }
    else
    {
        mvwprintw(win, posY, posX + utf8Length(title), inputText.c_str());
    }
        
    if(selected)
        wattroff(win, COLOR_PAIR(static_cast<int>(COLOR_PAIR::CURSOR)));
    else    
        wattroff(win, COLOR_PAIR(static_cast<int>(COLOR_PAIR::SECONDARY_WIN_BACKGROUND)));
}

bool InputField::getSelected()
{
    return selected;
}

void InputField::setSelected(bool isSelected)
{
    selected = isSelected;
}