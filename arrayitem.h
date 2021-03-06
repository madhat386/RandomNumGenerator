#ifndef ARRAYITEM_H
#define ARRAYITEM_H
#include "item.h"


class ArrayItem: public Item {
public:
    explicit ArrayItem(QObject* parent = nullptr);
    int minLen;
    int maxLen;
    bool showAmount;
};

#endif // ARRAYITEM_H
