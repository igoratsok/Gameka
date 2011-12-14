#ifndef UPDATEFILEPAIR_H
#define UPDATEFILEPAIR_H

#include <QString>

class UpdateFilePair
{
public:
    UpdateFilePair(QString source, QString destination);

    void updatePair();

    QString source;
    QString destination;
};

#endif // UPDATEFILEPAIR_H
