#ifndef HIGH_SCORE_MANAGER_H
#define HIGH_SCORE_MANAGER_H

#include <string>
#include <vector>
#include <utility>

namespace sfSnake
{
struct ScoreEntry
{
    std::string playerName;
    std::size_t score;
    
    ScoreEntry() : playerName(""), score(0) {}
    ScoreEntry(const std::string& name, std::size_t s) : playerName(name), score(s) {}
    
    bool operator<(const ScoreEntry& other) const
    {
        return score > other.score; // Higher scores first
    }
};

class HighScoreManager
{
public:
    static const size_t MAX_SCORES = 10;
    static HighScoreManager& getInstance();
    
    void loadScores();
    void saveScores();
    bool isHighScore(std::size_t score) const;
    bool isHighestScore(std::size_t score) const;
    void addScore(const std::string& playerName, std::size_t score);
    const std::vector<ScoreEntry>& getTopScores() const;
    
private:
    HighScoreManager();
    ~HighScoreManager() = default;
    HighScoreManager(const HighScoreManager&) = delete;
    HighScoreManager& operator=(const HighScoreManager&) = delete;
    
    static const std::string SCORE_FILE;
    
    std::vector<ScoreEntry> scores_;
    bool scoresLoaded_ = false;
};

}

#endif 