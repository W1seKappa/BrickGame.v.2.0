#ifndef BRICKGAME_TETRIS_CONTROLLER_H_
#define BRICKGAME_TETRIS_CONTROLLER_H_



#include "../brick_game/tetris/TetrisModel.h"

namespace s21 {
class TetrisContoller {
    public:

    explicit TetrisContoller(TetrisModel *model = nullptr) : model_(model) {}
    ~TetrisContoller() = default;


    void updateModelData(UserAction act = UserAction::noSig) {
        model_->UpdateModelData(act);
    }

    void SetModelDataDefault() { model_->SetGameDataDefault();}

    TetrisGameData &GetModelData() { return model_->GetTetrisGameData(); }

    private:
    TetrisModel *model_;
};


} // namespace s21

#endif //  BRICKGAME_TETRIS_CONTROLLER_H_