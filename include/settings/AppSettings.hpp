#pragma once

#include <QSettings>
#include <QSplitter>

#include "../model/AntColonyModel.hpp"
#include "../AntSimulator.hpp"
#include "../widgets/SettingsPanel.hpp"

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

    void loadSettingsState(SettingsPanel* settingsPanel);
    void saveSettingsState(const SettingsPanel* settingsPanel);

    void loadSplitterState(const QString& splitterName, QSplitter* splitter);
    void saveSplitterState(const QString& splitterName, const QSplitter* splitter);

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
