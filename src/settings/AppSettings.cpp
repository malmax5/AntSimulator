#include "../../include/settings/AppSettings.hpp"

#include <QSize>
#include <QIODevice>

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

void AppSettings::saveModelData(const AntColonyModel* model)
{
    if (!model)
    {
        return;
    }

    settings.beginGroup("Simulation model");
    QByteArray modelData;
    QDataStream modelStream(&modelData, QIODevice::WriteOnly);
    modelStream << *model;
    settings.setValue("modelData", modelData);
    settings.endGroup();
    settings.sync();
}

bool AppSettings::loadModelData(AntColonyModel* model)
{
    if (!model)
    {
        return false;
    }

    settings.beginGroup("Simulation model");
    QByteArray modelData = settings.value("modelData").toByteArray();
    QDataStream modelStream(&modelData, QIODevice::ReadOnly);
    modelStream >> *model;
    settings.endGroup();

    emit settingsChanged();

    return true;
}

void AppSettings::saveSimulationState(const AntSimulator* simulator)
{
    if (!simulator)
    {
        return;
    }

    settings.beginGroup("Simulation state");

    settings.setValue("isRunning", simulator->isSimulationRunning());
    settings.setValue("isPaused", simulator->isSimulationPaused());
    settings.setValue("collectedFood", simulator->collectedFood());
    settings.setValue("simulationSpeed", simulator->getSimulationSpeed());
    settings.setValue("antCount", simulator->getAntCount());

    settings.endGroup();
    settings.sync();
}

bool AppSettings::loadSimulationState(AntSimulator* simulator)
{
    if (!simulator)
    {
        return false;
    }

    settings.beginGroup("Simulation");

    simulator->setSimulationRunning(settings.value("isRunning", false).toBool());
    simulator->setSimulationPaused(settings.value("isPaused", false).toBool());
    simulator->setCollectedFood(settings.value("collectedFood", 0).toInt());
    simulator->setSimulationSpeed(settings.value("simulationSpeed", 1.0).toReal());
    simulator->setAntCount(settings.value("antCount", 10).toInt());

    settings.endGroup();

    emit settingsChanged();

    return true;
}
