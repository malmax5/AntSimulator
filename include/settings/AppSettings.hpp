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

    void saveSimulationState(AntColonyModel* model, AntSimulator* simulator);
    bool loadSimulationState(AntColonyModel* model, AntSimulator* simulator); 

signals:
    void settingsChanged();

private:
    explicit AppSettings(QObject* parent = nullptr);

    QSettings settings;
};
