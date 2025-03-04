﻿#include "Map.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

Map::Map(int rows,int cols): m_rows(rows), m_cols(cols){
    m_grid.resize(rows, std::vector<CellType>(cols, FREE_SPACE));
}

void Map::createRandomMap() {
    srand(time(NULL));
    std::vector<int> CellChance = {40, 45, 15};
    int total = 0;
    
    for (int weight : CellChance)
        total += weight;

    for (int x = 0; x < m_rows; ++x) {
        for (int y = 0; y < m_cols; ++y) {
            int randValue = rand() % total + 1;
            
            int choice = 0;
            for (int i = 0; i < CellChance.size(); ++i) {
                choice += CellChance[i];
                if (choice >= randValue) {
                    if (i == 1 && rand() % 60 == 0) {
                        m_grid[x][y] = static_cast<CellType>(3);
                        
                    }
                    else {
                        m_grid[x][y] = static_cast<CellType>(i);
                    }
                    break;
                }
            }
        }
    }

    createPath({ m_rows / 2, m_cols / 2 }, { 0, 0 });
    createPath({ m_rows / 2, m_cols / 2 }, { 0, m_cols - 1 });
    createPath({ m_rows / 2, m_cols / 2 }, { m_rows - 1, 0 });
    createPath({ m_rows / 2, m_cols / 2 }, { m_rows - 1, m_cols - 1 });
}

void Map::createPath(std::pair<int, int> start, std::pair<int, int> finish)
{
    std::pair<int, int> currentPosition = start;

    while (currentPosition != finish)
    {
        m_grid[currentPosition.first][currentPosition.second] = static_cast<CellType>(0);

        if (rand() % 2 == 0)
        {
            if (currentPosition.first != finish.first)
                currentPosition.first += static_cast<int>(currentPosition.first < finish.first) * 2 - 1;
            else
                currentPosition.second += static_cast<int>(currentPosition.second < finish.second) * 2 - 1;
        }
        else
        {
            if (currentPosition.second != finish.second)
                currentPosition.second += static_cast<int>(currentPosition.second < finish.second) * 2 - 1;
            else
                currentPosition.first += static_cast<int>(currentPosition.first < finish.first) * 2 - 1;
        }
    }

    m_grid[currentPosition.first][currentPosition.second] = FREE_SPACE;
}

std::vector<CellType> Map::getNeighboursVal(int X, int Y)
{
    std::vector<CellType> neighbours;
    if (X + 1 < m_grid.size()) //RIGHT
        neighbours.push_back(m_grid[X + 1][Y]); //emplace_back(X + 1, Y);
    if (X - 1 >= 0) //LEFT
        neighbours.push_back(m_grid[X - 1][Y]); //.emplace_back(X - 1, Y);
    if (Y + 1 < m_grid[X].size()) //DOWN
        neighbours.push_back(m_grid[X][Y + 1]); //.emplace_back(X, Y + 1);
    if (Y - 1 >= 0) //UP
        neighbours.push_back(m_grid[X][Y - 1]); //.emplace_back(X, Y - 1);
    return neighbours;
}

const std::vector<std::vector<CellType>>& Map::getMap() {
    return m_grid;
}

void Map::setPositionValue(int X, int Y, CellType value)
{
    if (X >= 0 && X < m_grid.size())
        if (Y >= 0 && Y < m_grid[X].size())
            m_grid[X][Y] = value;
}

CellType Map::getPositionValue(int X, int Y)
{
    if (X >= 0 && X < m_grid.size())
        if (Y >= 0 && Y < m_grid[X].size())
            return m_grid[X][Y];
    return CellType::EMPTY_SPACE;
}

std::pair<int, int> Map::getSize()
{
    return { m_rows, m_cols };
}

void Map::placeRandomSpecialItem() {
    std::srand(std::time(nullptr)); 

    while (true) {
        int randomX = std::rand() % getSize().first;
        int randomY = std::rand() % getSize().second;

        
        if (getPositionValue(randomX, randomY) == FREE_SPACE) {
            setPositionValue(randomX, randomY, CellType::SPECIAL_ITEM);
            break;
        }
    }
}