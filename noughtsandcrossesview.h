#ifndef NOUGHTSANDCROSSESVIEW_H
#define NOUGHTSANDCROSSESVIEW_H

#include <QObject>
#include <QQmlApplicationEngine>

class NoughtsAndCrossesView : public QObject
{
    Q_OBJECT
public:
    explicit NoughtsAndCrossesView(QObject *parent = 0);

signals:

public slots:

private:
    QQmlApplicationEngine engine;

};

#endif // NOUGHTSANDCROSSESVIEW_H
