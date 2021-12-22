#include "dirwrapper.h"

DirWrapper::DirWrapper(const QString &dir) : QDir(dir, "*.xml")
{}
