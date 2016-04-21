#include "noughtsandcrossesmodel.h"

NoughtsAndCrossesModel::NoughtsAndCrossesModel(QObject *parent) : QObject(parent)
{
    actualPlayer = "Nought";
    for (int i=0; i<9; i++)
    {
        gameboardFields[i]="";
    }
    noughtScore = 0;
    crossScore = 0;
}

bool NoughtsAndCrossesModel::markField(int row, int column)
{
    if (getGameboardField(row,column) == "")
    {
        setGameboardField(row,column);

        return true;
    } else return false;
}

QString NoughtsAndCrossesModel::getGameboardField(int row, int column)
{
    int position;
    position = (row-1)*3+column-1;
    return gameboardFields[position];
}

void NoughtsAndCrossesModel::setGameboardField(int row, int column)
{
    int position;
    position = (row-1)*3+column-1;
    gameboardFields[position] = actualPlayer;
}

void NoughtsAndCrossesModel::markWinnerGameboardField(int row, int column)
{
    //marking fields that won
    int position;
    position = (row-1)*3+column-1;
    gameboardFields[position] = "Winner";
}

void NoughtsAndCrossesModel::markEmptyGameboardField(int row, int column)
{
    //marking fields that still empty after the won
    int position;
    position = (row-1)*3+column-1;
    gameboardFields[position] = "Empty";
}

QString NoughtsAndCrossesModel::getActualPlayer()
{
    return actualPlayer;
}

void NoughtsAndCrossesModel::switchPlayer()
{
    if (actualPlayer=="Nought")
    {
        actualPlayer="Cross";
    } else actualPlayer="Nought";
}

void NoughtsAndCrossesModel::checkWin(int row, int column)
{
    bool win;
    win = false;
    int winningFields;
    winningFields=0;
    //checking horizontal line that content last marked field
    for (int i=1; i<=3; i++)
    {
        if(getGameboardField(row,i)==getActualPlayer())
        {
            winningFields++;
        }
    }
    if (winningFields == 3)
    {
        win = true;
        //marking winning's fields
        for (int i=1; i<=3; i++)
        {
            markWinnerGameboardField(row,i);
        }       
    }
    winningFields = 0;
    if (win == false)
    {
        //checking vertical line that content last marked field
        for (int i=1; i<=3; i++)
        {
            if(getGameboardField(i,column)==getActualPlayer())
            {
                winningFields++;
            }
        }
        if (winningFields == 3)
        {
            win = true;
            //marking winning's fields
            for (int i=1; i<=3; i++)
            {
                markWinnerGameboardField(i,column);
            }            
        }
        winningFields = 0;
    }
    if (win == false)
    {
        if ((row+column)%2 == 0)
        {
            //checking diagonal line that content last marked field
            if (row == column)
            {
                for (int i=1; i<=3; i++)
                {
                    if(getGameboardField(i,i) == getActualPlayer())
                    {
                        winningFields++;
                    }
                }
                if (winningFields == 3)
                {
                    win = true;
                    //marking winning's fields
                    for (int i=1; i<=3; i++)
                    {
                        markWinnerGameboardField(i,i);
                    }
                }
                winningFields = 0;
            }
            //checking diagonal line that content last marked field
            if ((row+column) == 4)
            {
                for (int i=1; i<=3; i++)
                {
                    if(getGameboardField(i,4-i) == getActualPlayer())
                    {
                        winningFields++;
                    }
                }
                if (winningFields == 3)
                {
                    win = true;
                    //marking winning's fields
                    for (int i=1; i<=3; i++)
                    {
                        markWinnerGameboardField(i,4-i);
                    }
                }
                winningFields = 0;
            }
        }
    }

    if(win == true)
    {
        //marking "Empty" at fields thats're still empty to it wasn't available for scaling
        markEmptyGameboard();
        emit winner();
    }
}

void NoughtsAndCrossesModel::markEmptyGameboard()
{
    for (int row=1; row<=3; row++)
    {
        for (int column=1; column<=3; column++)
        {
            if (getGameboardField(row, column) == "")
            {
                markEmptyGameboardField(row, column);
            }
        }
    }
}

void NoughtsAndCrossesModel::nextRound()
{
    clearGameboard();
}

void NoughtsAndCrossesModel::clearGameboard()
{
    for (int row=1; row<=3; row++)
    {
        for (int column=1; column<=3; column++)
        {
            clearGameboardField(row,column);
        }
    }
}

void NoughtsAndCrossesModel::clearGameboardField(int row, int column)
{
    int position;
    position = (row-1)*3+column-1;
    gameboardFields[position] = "";
}

void NoughtsAndCrossesModel::updateScore()
{
    if (getActualPlayer() == "Nought")
    {
        addNoughtPoint();
    }
    if (getActualPlayer() == "Cross")
    {
        addCrossPoint();
    }
}

void NoughtsAndCrossesModel::addNoughtPoint()
{
    noughtScore++;
}

void NoughtsAndCrossesModel::addCrossPoint()
{
    crossScore++;
}

int NoughtsAndCrossesModel::getNoughtScore()
{
    return noughtScore;
}

int NoughtsAndCrossesModel::getCrossScore()
{
    return crossScore;
}
