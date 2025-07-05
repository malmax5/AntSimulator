#pragma once

#include <QWidget>
#include <QPointF>
#include <QSlider>
#include <QPushButton>

class SettingsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPanel(QWidget* parent = nullptr);

signals:
    void startSimulation();
    void pauseSimulation();
    void resumeSimulation();
    void resetSimulation();

    void antCountChanged(int count);
    void simulationSpeedChanged(qreal speed);

    void addFood(const QPointF& positin);

public slots:
    void updateAntCount(int count);
    void updateSimulationSpeed(qreal speed);

private slots:
    void onAddFoodButtonClicked(int x, int y);

private:
    QSlider* antCountSlider;
    QSlider* speedSlider;

    QPushButton* addFoodButton;

    QPushButton* startButton;
    QPushButton* pauseButton;
    QPushButton* resumeButton;
    QPushButton* resetButton;
    
};
