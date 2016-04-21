#include "noughtsandcrossesview.h"

NoughtsAndCrossesView::NoughtsAndCrossesView(QObject *parent) : QObject(parent)
{
   engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

}

