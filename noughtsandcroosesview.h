#ifndef NOUGHTSANDCROOSESVIEW_H
#define NOUGHTSANDCROOSESVIEW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>
#include "noughtsandcrossesmodel.h"

class NoughtsAndCroosesView : public QObject
{
    Q_OBJECT
public:
    explicit NoughtsAndCroosesView(QObject *parent = 0);
    void updateGameboardView(QQuickItem* field);
    void greyGameboard();
    void emptyGameboard();
    void greyField(int row,int column);
    void emptyField(int row,int column);
    void switchPlayer();
    void updateScore();
    void clearGameboard();
signals:

public slots:
    void fieldClicked();
    void win();
    void nextRound();

private:
    QQmlApplicationEngine engine;
    NoughtsAndCrossesModel model;

    //fields is a pointer to QML's Rectangle that contain 9 playable fields
    QQuickItem* fields;
    //scores is a pointer to QML's nextPlayer/nextRound button
    QObject* nextPlayer;
    //scores is a pointer to QML's score rectangle
    QObject* score;

};

#endif // NOUGHTSANDCROOSESVIEW_H
