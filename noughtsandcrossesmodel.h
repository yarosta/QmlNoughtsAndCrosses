#ifndef NOUGHTSANDCROSSESMODEL_H
#define NOUGHTSANDCROSSESMODEL_H

#include <QObject>
#include <QDebug>


class NoughtsAndCrossesModel : public QObject
{
    Q_OBJECT
public:
    explicit NoughtsAndCrossesModel(QObject *parent = 0);
    bool markField(int row, int column);

    QString getGameboardField(int row, int column);
    void setGameboardField(int row, int column);
    void markWinnerGameboardField(int row, int column);
    void markEmptyGameboardField(int row, int column);
    void markEmptyGameboard();
    void clearGameboard();
    void clearGameboardField(int row, int column);

    QString getActualPlayer();
    void switchPlayer();
    void checkWin(int row, int column);
    void updateScore();
    void nextRound();

    void addNoughtPoint();
    void addCrossPoint();
    int getNoughtScore();
    int getCrossScore();

signals:
    void winner();
public slots:

private:
    QString actualPlayer;
    QString gameboardFields[9];

    int noughtScore;
    int crossScore;
};

#endif // NOUGHTSANDCROSSESMODEL_H
