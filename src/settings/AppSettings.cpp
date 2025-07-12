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

void AppSettings::saveSimulationState(AntColonyModel* model, AntSimulator* simulator)
{
    settings.beginGroup("Simulation");

    //Parameters
    settings.setValue("isRunning", simulator->isSimulationRunning());
    settings.setValue("isPaused", simulator->isSimulationPaused());
    settings.setValue("collectedFood", simulator->collectedFood());
    settings.setValue("simulationSpeed", simulator->getSimulationSpeed());
    settings.setValue("antCount", simulator->getAntCount());

    // Ants
    QByteArray antData;
    QDataStream antStream(&antData, QIODevice::WriteOnly);
    antStream << model->getAnts();
    
    settings.setValue("ants", antData);

    //Food
    QByteArray foodData;
    QDataStream foodStream(&foodData, QIODevice::WriteOnly);
    foodStream << model->getFoodStorage().getFoods();

    settings.setValue("food", foodData);

    //Pheromones
    QByteArray pheromonesData;
    QDataStream pheromonesStream(&pheromonesData, QIODevice::WriteOnly);
    pheromonesStream << model->getPheromoneMap().getPheromonePoints();

    settings.setValue("pheromones", pheromonesData);

    settings.endGroup();
    settings.sync();
}

bool AppSettings::loadSimulationState(AntColonyModel* model, AntSimulator* simulator)
{
    if (!model || !simulator)
    {
        return false;
    }

    settings.beginGroup("Simulation");

    //Parameters
    simulator->setSimulationRunning(settings.value("isRunning", false).toBool());
    simulator->setSimulationPaused(settings.value("isPaused", false).toBool());
    simulator->setCollectedFood(settings.value("collectedFood", 0).toInt());
    simulator->setSimulationSpeed(settings.value("simulationSpeed", 1.0).toReal());
    simulator->setAntCount(settings.value("antCount", 10).toInt());

    //Ants
    QByteArray antData = settings.value("ants").toByteArray();
    QDataStream antStream(&antData, QIODevice::ReadOnly);
    antStream >> model->getAnts();

    //Food
    QByteArray foodData = settings.value("food").toByteArray();
    QDataStream foodStream(&foodData, QIODevice::ReadOnly);
    foodStream >> model->getFoodStorage().getFoods();

    //Pheromones
    QByteArray pheromonesData = settings.value("pheromones").toByteArray();
    QDataStream pheromonesStream(&pheromonesData, QIODevice::ReadOnly);
    pheromonesStream >> model->getPheromoneMap().getPheromonePoints();

    settings.endGroup();

    emit settingsChanged();

    return true;
}
