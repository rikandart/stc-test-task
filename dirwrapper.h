#ifndef DIRWRAPPER_H
#define DIRWRAPPER_H

#include <QDir>

class DirWrapper : public QDir
{
public:
    DirWrapper(const QString& dir);
};

#endif // DIRWRAPPER_H
