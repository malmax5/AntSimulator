#pragma once

#include <QWidget>
#include <QPointF>

class SettingsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPanel(QWidget* parent = nullptr);

signals:
    void startSimulation();
    void pauseSimulation();
    void resetSimulation();

    void antCountChanged(int count);
    void simulationSpeedChanged(qreal speed);

    void addFood(QPointF positin);

public slots:
    void updateAntCount(int count);
    void updateSimulationSpeed(qreal speed);

private slots:
    void onAddFoodButtonClicked();

private:
    QSlider* antCountSlider;
    QSlider* speedSlider;
    QPushButton* startButton;
    QPushButton* pauseButton;
    QPushButton* resetButton;
    
};
