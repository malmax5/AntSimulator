#pragma once

#include <QSettings>

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

signals:
    void settingsChanged();

private:
    explicit AppSettings(QObject* parent = nullptr);

    QSettings settings;
};
