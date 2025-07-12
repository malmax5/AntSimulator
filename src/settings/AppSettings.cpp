#include "../../include/settings/AppSettings.hpp"

#include <QSize>

AppSettings::AppSettings(QObject* parent)
    : QObject(parent), settings("MyCompany", "AntSimulator")
{
    
}

void AppSettings::setWindowSize(const QSize& size)
{
    settings.setValue("window/size", size);
    emit settingsChanged();
}

QSize AppSettings::windowSize()
{
    return settings.value("window/size", QSize(800, 600)).toSize();
}
