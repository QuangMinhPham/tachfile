#ifndef _HIGHSCORE__H
#define _HIGHSCORE__H


    void loadHighScore(int& highScore) {
        std::ifstream file("highscore.txt");
        if (file.is_open()) {
            file >> highScore;
            file.close();
        }
    }

    void saveHighScore(int& highScore) {
        std::ofstream file("highscore.txt");
        if (file.is_open()) {
            file << highScore;
            file.close();
        }
    }

    void updateHighScore(int& highScore ) {
        if (HIGHEST_SCORE > highScore) {
            highScore = HIGHEST_SCORE;
            saveHighScore(highScore);
        }
    }

#endif // _HIGHSCORE__H
