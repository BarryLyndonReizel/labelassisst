#ifndef PUBLIC_HH
#define PUBLIC_HH

#include <QIcon>

QIcon* newIcon(QString icon){
    return new QIcon(":/icons/" + icon + ".png");
}

#endif // PUBLIC_HH
