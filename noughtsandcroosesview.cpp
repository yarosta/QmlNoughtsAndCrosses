#include "noughtsandcroosesview.h"

NoughtsAndCroosesView::NoughtsAndCroosesView(QObject *parent) : QObject(parent)
{
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QWindow* window = qobject_cast<QWindow*> (engine.rootObjects().at(0));
    window->setIcon(QIcon(":grey.png"));

    //fields is a pointer to QML's Rectangle that contain 9 playable fields
    fields = qobject_cast<QQuickItem*>(window->children().at(0));

    //scores is a pointer to QML's Rectangle that contain nextPlayer/nextRound button and score rectangle
    QObject* scores;
    scores = window->children().at(1);
    nextPlayer = scores->children().at(1);
    score = scores->children().at(2);

    QObject* grid;
    grid = fields->children().at(0);
    QObject* field;
    for (int i=0; i<9; i++)
    {
        field = grid->children().at(i);
        //field is a pointer to QML's playable field
        QObject::connect(field,SIGNAL(fieldClicked()),this,SLOT(fieldClicked()));
    }

    QObject::connect(&model,SIGNAL(winner()),this,SLOT(win()));

    QObject::connect(nextPlayer, SIGNAL(nextRound()), this, SLOT(nextRound()));
}

void NoughtsAndCroosesView::fieldClicked()
{
    QQuickItem* field;
    field = qobject_cast<QQuickItem*> (QObject::sender());

    //calculate which field sends signal fieldClicked()
    float fieldX;
    fieldX = field->x();
    float fieldsWidth;
    fieldsWidth = fields->width();
    int column;
    column = int((3*fieldX+1)/fieldsWidth)+1;

    float fieldY;
    fieldY = field->y();
    float fieldsHeight;
    fieldsHeight = fields->height();
    int row;
    row = int((3*fieldY+1)/fieldsHeight)+1;

    qDebug() << row;
    qDebug() << column;

    //if field was able to marked, game's updating view in QML
    //and checking if it actualPlayer won
    //and switching player in the view and in the model
    if(model.markField(row,column)==true)
    {
        updateGameboardView(field);
        model.checkWin(row,column);
        switchPlayer();
        model.switchPlayer();
    }
}

void NoughtsAndCroosesView::switchPlayer()
{
    QMetaObject::invokeMethod(nextPlayer, "switchPlayer");
}

void NoughtsAndCroosesView::updateGameboardView(QQuickItem* field)
{
    if(model.getActualPlayer() == "Nought")
    {      
        QMetaObject::invokeMethod(field, "setNought");
    }
    if(model.getActualPlayer() == "Cross")
    {        
        QMetaObject::invokeMethod(field, "setCross");
    }
}

void NoughtsAndCroosesView::win()
{
    qDebug() << "win";
    //when somebody won, game is greying all marked fields besides winning fields
    greyGameboard();
    //empty are no longer available fo scaling
    emptyGameboard();
    updateScore();
}

void NoughtsAndCroosesView::updateScore()
{
    model.updateScore();
    QVariant noughtScore;
    noughtScore = model.getNoughtScore();
    QVariant crossScore;
    crossScore = model.getCrossScore();
    QMetaObject::invokeMethod(score, "updateScore", Q_ARG(QVariant, noughtScore), Q_ARG(QVariant, crossScore));
}

void NoughtsAndCroosesView::greyGameboard()
{
    for (int row=1; row<=3; row++)
    {
        for (int column=1; column<=3; column++)
        {
            QString markedField;
            markedField = model.getGameboardField(row,column);
            if (markedField == "Nought" || markedField == "Cross")
            {
                greyField(row,column);
            }
        }
    }
}

void NoughtsAndCroosesView::emptyGameboard()
{
    for (int row=1; row<=3; row++)
    {
        for (int column=1; column<=3; column++)
        {
            QString noneField;
            noneField = model.getGameboardField(row,column);
            if (noneField == "Empty")
            {
                emptyField(row,column);
            }
        }
    }
}

void NoughtsAndCroosesView::greyField(int row,int column)
{
    int position;
    position = (row-1)*3+column-1;
    QObject* grid = fields->children().at(0);
    QObject* field = grid->children().at(position);
    QMetaObject::invokeMethod(field,"setGrey");
}

void NoughtsAndCroosesView::emptyField(int row,int column)
{
    int position;
    position = (row-1)*3+column-1;
    QObject* grid = fields->children().at(0);
    QObject* field = grid->children().at(position);
    QMetaObject::invokeMethod(field,"setEmpty");
}

void NoughtsAndCroosesView::nextRound()
{
    //clearing all fields in the view and in the model
    model.clearGameboard();
    clearGameboard();
}

void NoughtsAndCroosesView::clearGameboard()
{
    QObject* grid;
    grid = fields->children().at(0);

    for (int position=0; position<9; position++)
    {
        QObject* field;
        field = grid->children().at(position);
        QMetaObject::invokeMethod(field, "clearField");
    }
}
