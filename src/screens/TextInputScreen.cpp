/*---------------------------------[INCLUDES]---------------------------------*/
#include "TextInputScreen.h"
#include <vector>
#include <utility>

/*---------------------------------[PRIVATE]----------------------------------*/

class RowString
{
public:
    RowString(int row, char * str, int strLen) : _row(row), _str(str), _strLen(strLen) {};
    ~RowString() {};

    int getRow() { return _row; }
    char * getStr() { return _str; }
    int getStrLen() { return _strLen; }

private:
    int _row;
    char * _str;
    int _strLen;
};

class Cursor {
public:
    Cursor(int minCol, int maxCol, int minRow, int maxRow) : 
        _col(minCol), _row(minRow), 
        _minCol(minCol), _maxCol(maxCol), 
        _minRow(minRow), _maxRow(maxRow) {};
    ~Cursor(){};

    void incrementCursor()
    {
        _col++;

        if (_col > _maxCol) 
        {
            _col = _minCol;
            _row++;

            if (_row > _maxRow)
            {
                _row = _minRow;
            }
        }

        while(isForbiddenPosition(_col, _row))
        {
            incrementCursor();
        };
    }

    void decrementCursor()
    {
        _col--;

        if (_col < _minCol) 
        {
            _col = _maxCol;
            _row--;
            if (_row < _minRow)
            {
                _row = _maxRow;
            }
        }

        while(isForbiddenPosition(_col, _row))
        {
            decrementCursor();
        };
    }

    void setCursor(int col, int row) 
    { 
        if(col >= _minCol && col <= _maxCol && row >= _minRow && row <= _maxRow)
        {
            _col = col; 
            _row = row;
        }
    }     

    void addForbiddenPosition(int col, int row)
    {
        if(col >= _minCol && col <= _maxCol && row >= _minRow && row <= _maxRow)
        {
            _forbiddenPositions.push_back(std::make_pair(col, row));
        }
    }

    bool isForbiddenPosition(int col, int row)
    {
        for(auto &pos : _forbiddenPositions)
        {
            if(pos.first == col && pos.second == row)
            {
                return true;
            }
        }
        return false;
    }

    uint8_t getCol() { return _col; }
    uint8_t getRow() { return _row; }

    void addString(int row, char * str, int strLen)
    {
        _rowStrings.push_back(RowString(row, str, strLen));
    }

    char getCharAtPosition(int col, int row)
    {
        for(auto &rowString : _rowStrings)
        {
            if(rowString.getRow() == row)
            {
                return rowString.getStr()[col];
            }
        }
        return 0;
    }

private:
    int _col;
    int _row;
    int _minCol;
    int _maxCol;
    int _minRow; 
    int _maxRow;
    std::vector<std::pair<int, int>> _forbiddenPositions;
    std::vector<RowString> _rowStrings;
};

bool TextInputScreen::ev_cw_step() {
    _cursor->incrementCursor();
    m_controller.GetServices()->pLcd->setCursor(_cursor->getCol(), _cursor->getRow());
    return true;
}

bool TextInputScreen::ev_ccw_step() {
    _cursor->decrementCursor();
    m_controller.GetServices()->pLcd->setCursor(_cursor->getCol(), _cursor->getRow());
    return true;
}

bool TextInputScreen::ev_confirm_pressed() {
    char c = _cursor->getCharAtPosition(_cursor->getCol(), _cursor->getRow());
    if(c != 0)
    {
        Serial.println(c);

        if(c == '<')
        {
            model.clear();
            model.concat("                   ");
            model.clear();
        }
        else
        {
            model.concat(c);
            _inputLine[_inputLineIndex] = c;
            _inputLineIndex++;                        
        }
        
        update();
    }
    else
    {
        Serial.println("Invalid character");
        return false;
    }
    return true;
}

bool TextInputScreen::ev_cancel_pressed() {
    m_controller.Back();
    return true;
}

bool TextInputScreen::ev_update() {
    if(!_initCursor)
    {
        m_controller.GetServices()->pLcd->setCursor(_cursor->getCol(), _cursor->getRow());
        m_controller.GetServices()->pLcd->cursor();
        _initCursor = true;
    }
    return true;
}

/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/

TextInputScreen::TextInputScreen(MenuController &c, String &m) : Screen(c), model(m)
{
    static char KeyboardStringLine1[] = "ABCDEFGHIJKLMNOPQRST";
    static char KeyboardStringLine2[] = "UVWXYZ0123456789<";
    
    LiquidLine *pInputLine      = new LiquidLine(0, 0, ">", DYN_LINE(model.c_str()));
    LiquidLine *pKeyboardLine1  = new LiquidLine(0, 1, KeyboardStringLine1);
    LiquidLine *pKeyboardLine2  = new LiquidLine(0, 2, KeyboardStringLine2);

    addLine(pInputLine);
    addLine(pKeyboardLine1);
    addLine(pKeyboardLine2);

    _cursor = new Cursor(0, 19, 1, 2);
    _cursor->addString(1, KeyboardStringLine1, 20);
    _cursor->addString(2, KeyboardStringLine2, 15);

    // empty spaces
    _cursor->addForbiddenPosition(17, 2);
    _cursor->addForbiddenPosition(18, 2);
    _cursor->addForbiddenPosition(19, 2);

    update();
}

TextInputScreen::~TextInputScreen() 
{
    delete(_cursor);
    _cursor = nullptr;
    m_controller.GetServices()->pLcd->noCursor();
}

bool TextInputScreen::onEvent(Event event) {
    // Implementation to handle events
    switch (event) {
        case Event::EV_CW_STEP:
            return ev_cw_step();
        case Event::EV_CCW_STEP:
            return ev_ccw_step();
        case Event::EV_CONFIRM_PRESSED:
            return ev_confirm_pressed();
        case Event::EV_CANCEL_PRESSED:
            return ev_cancel_pressed();
        case Event::EV_UPDATE_LOOP:
            return ev_update();
        default:
            return false;
    }
}