#pragma once

#include <string>
#include "state.h"

class InputField
    {
    public:
        InputField(std::string title, int posY, int posX, bool isSelectable = true, int inputLenght = 5);
        void setInputText(std::string);
        std::string getInputText();
        void popBackInputText();
        void print(WINDOW*);
        bool getSelected();
        void setSelected(bool);

    private:
        int posX, posY;
        int inputLen;
        int extend = 0;
        std::string title;
        std::string inputText = "";
        bool selected = false;
        bool selectable = true;
    };