#include "HighScoreManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>

namespace sfSnake
{

const std::string HighScoreManager::SCORE_FILE = "score.txt";

HighScoreManager::HighScoreManager()
{
    loadScores();
}

HighScoreManager& HighScoreManager::getInstance()
{
    static HighScoreManager instance;
    return instance;
}

void HighScoreManager::loadScores()
{
    if (scoresLoaded_) return;
    
    scores_.clear();
    std::ifstream file(SCORE_FILE);
    
    if (file.is_open())
    {
        std::string name;
        std::size_t score;
        
        while (file >> name >> score && scores_.size() < MAX_SCORES)
        {
            scores_.emplace_back(name, score);
        }
        
        file.close();
    }
    
    // Sort scores in descending order
    std::sort(scores_.begin(), scores_.end());
    scoresLoaded_ = true;
}

void HighScoreManager::saveScores()
{
    std::ofstream file(SCORE_FILE);
    
    if (file.is_open())
    {
        for (const auto& entry : scores_)
        {
            file << entry.playerName << " " << entry.score << std::endl;
        }
        file.close();
    }
}

bool HighScoreManager::isHighScore(std::size_t score) const
{
    if (scores_.size() < MAX_SCORES) return true;
    return score > scores_.back().score;
}

bool HighScoreManager::isHighestScore(std::size_t score) const
{
    if (scores_.empty()) return true;
    return score > scores_.front().score;
}

void HighScoreManager::addScore(const std::string& playerName, std::size_t score)
{
    scores_.emplace_back(playerName, score);
    std::sort(scores_.begin(), scores_.end());
    
    // Keep only top MAX_SCORES
    if (scores_.size() > MAX_SCORES)
    {
        scores_.resize(MAX_SCORES);
    }
    
    saveScores();
}

const std::vector<ScoreEntry>& HighScoreManager::getTopScores() const
{
    return scores_;
}

} 