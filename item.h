#ifndef ITEM_H
#define ITEM_H

#include <QObject>

class Item : public QObject {
    Q_OBJECT
public:
    explicit Item(QObject* parent = nullptr);
    double max;
    double min;
    char endOfVal;
    bool isInt;
    bool isArray;
    int numOfDecimal;

signals:

public slots:

};



#endif // ITEM_H
