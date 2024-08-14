#include "BaseView.h"

namespace s21 {
    void BaseView::GameFieldRendering(Choose currGame, int level, int score, int record) {
        DrawBox(0, 0, GameSizes::windowHeight, GameSizes::windowWidth);

        DrawBox(0, 0, GameSizes::fieldHeight + 1, GameSizes::fieldWidth + 1);

        mvaddch(0, GameSizes::fieldWidth + 1, ACS_TTEE);

        
    }


}// namespace s21