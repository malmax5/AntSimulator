#pragma once

#include <QSettings>

#include "../model/AntColonyModel.hpp"
#include "../AntSimulator.hpp"

class AppSettings : public QObject
{
    Q_OBJECT
public:
    static AppSettings& instance()
    {
        static AppSettings instance;
        return instance;
    }

    void setWindowSize(const QSize& size);
    QSize windowSize();

    void saveModelData(const AntColonyModel* model);
    bool loadModelData(AntColonyModel* model);

    void saveSimulationState(const AntSimulator* simulator);
    bool loadSimulationState(AntSimulator* simulator); 

signals:
    void settingsChanged();

private:
    explicit AppSettings(QObject* parent = nullptr);

    QSettings settings;
};
