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
}

QSize AppSettings::windowSize()
{
    return settings.value("window/size", QSize(800, 600)).toSize();
}

void AppSettings::loadSettingsState(SettingsPanel* settingsPanel)
{
    if (!settingsPanel)
    {
        return;
    }

    settings.beginGroup("SettingsState");

    settingsPanel->updateAntCount(settings.value("AntCount", 10).toInt());
    settingsPanel->updateSimulationSpeed(settings.value("SimulationSpeed", 1).toReal());

    settings.endGroup();
}

void AppSettings::saveSettingsState(const SettingsPanel* settingsPanel)
{
    if (!settingsPanel)
    {
        return;
    }

    settings.beginGroup("SettingsState");

    settings.setValue("AntCount", settingsPanel->getAntCount());
    settings.setValue("SimulationSpeed", settingsPanel->getSimulationSpeed());

    settings.endGroup();
    settings.sync();
}

void AppSettings::saveSplitterState(const QString& splitterName, const QSplitter* splitter)
{
    if (!splitter)
    {
        return;
    }

    settings.beginGroup("SplitterStates");
    settings.setValue(splitterName, splitter->saveState());
    settings.endGroup();
}

void AppSettings::loadSplitterState(const QString& splitterName, QSplitter* splitter)
{
    if (!splitter)
    {
        return;
    }

    settings.beginGroup("SplitterStates");
    splitter->restoreState(settings.value(splitterName, QByteArray()).toByteArray());
    settings.endGroup();
}

void AppSettings::saveModelData(const AntColonyModel* model)
{
    if (!model)
    {
        return;
    }

    settings.beginGroup("SimulationModel");
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

    settings.beginGroup("SimulationModel");
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

    settings.beginGroup("SimulationState");

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

    settings.beginGroup("SimulationState");

    simulator->setSimulationRunning(settings.value("isRunning", false).toBool());
    simulator->setSimulationPaused(settings.value("isPaused", false).toBool());
    simulator->setCollectedFood(settings.value("collectedFood", 0).toInt());
    simulator->setSimulationSpeed(settings.value("simulationSpeed", 1.0).toReal());
    simulator->setAntCount(settings.value("antCount", 10).toInt());

    settings.endGroup();

    emit settingsChanged();

    return true;
}
