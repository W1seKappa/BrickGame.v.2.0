#include "TetrisConsoleView.h"

namespace s21 {

    TetrisConsoleView::TetrisConsoleView(TetrisController *c) : controller_(c) {
        tData_ = &controller_->GetModelData();
        tAction_ = UserAction::NoSig;
    }

    void TetrisConsoleView::Start() {
        nodelay(stdscr, TRUE);
        controller_->setModelDataDefault();
        tData_ = &constroller_->GetModelData();

        TetrisMainLoop();

        if (tData_->tGameStatus == GameState::GameOver || 
            tData_->tGameStatus == GameState::Exit) {
                GameResultRendering(false, tData_->tLevel, tData->tScore);
        }
    }

    void TetrisConsoleView::TetrisMainLoop() {
        while (tData_->tGameStatus != GameState::GameOver && tData_->tGameStatus != GameState::Exit) {
            if (tData_->isModified) {
                Rendering();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            tAction_ = GetAction();
            ModelConnect();
        }
    }

    void TetrisConsoleView::Rendering() {
        if (tData_->tGameStatus == GameState::Start) {
            StartGameRendering();
        } else if (tData_->tGameStatus == GameState::Pause) {
            PauseRendering(tData_->tLevel, tData_->tScore);
        } else {
            GameRendering();
        }
    }

    void TetrisConsoleView::ModelConnect() {
        controller_->updateModelData(tAction_);
        TetrisGameData tmpData = controller_->GetModelData();
        tAction_ = UserAction::NoSig;
    }

    void TetrisConsoleView::GameRendering() {
        clear();
        GameFieldRendering(Choose::Tetris, tData_->tLevel, tData->tScore, tData_->tBestScore);

        for (const auto &item : tData_->tProjection.GetCoords()) {
            attron(COLOR_PAIR(8));
            mvprintw(item.y, item.x + 1, ".");
            attroff(COLOR_PAIR(8));
        }


        for (const auto &item : tData->tCurr.GetCoords()) {
            attron(COLOR_PAIR((short)tData_->tCurr.GetShape()));
            mvprintw(item.y, item.x + 1, ".");
            attroff(COLOR_PAIR((short)tData_->tCurr.GetShape()));
        }

        for (const auto &item : tData_->tNext.GetCoords()) {
            attron(COLOR_PAIR((short)tData->tNext.GetShape()));
            mvprintw(item.y + 1, item.x + 11, ".");
            attroff(COLOR_PAIR((short)tData_->tNext.GetShape()));
        }

        for (int i = 0; i < GameSizes::fieldHeight; ++i) {
            for (int j = 0; j < GameSizes::fieldWidth; ++j) {
                attron(COLOR_PAIR(tData_->tField_[i][j].second));
                if (tData_->tField_[i][j].first) mvprintw(i + 1, j + 1, ".");
                attroff(COLOR_PAIR(tData_->tField_[i][j].second));
            }
        }
    }

} // namespace s21