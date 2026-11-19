#include "sensortablemodel.h"

SensorTableModel::SensorTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    Sensor s1;
    s1.date = "2026-11-19";
    s1.time = "10:30:00";
    s1.elapsedTime = "00:00:00";
    s1.elapsedHours = 0.0001;
    s1.lcps = 120;
    s1.mrPerHour = 1.5;
    s1.hcps = 15;
    s1.rPerHour = 0.2;
    s1.totalDose = 66;
    sensors.append(s1);

    Sensor s2;
    s2.date = "2026-11-19";
    s2.time = "10:31:00";
    s2.elapsedTime = "00:01:00";
    s2.elapsedHours = 0.0167;
    s2.lcps = 135;
    s2.mrPerHour = 1.7;
    s2.hcps = 18;
    s2.rPerHour = 0.25;
    s2.totalDose = 68;
    sensors.append(s2);

    Sensor s3;
    s3.date = "2026-11-19";
    s3.time = "10:32:00";
    s3.elapsedTime = "00:02:00";
    s3.elapsedHours = 0.0333;
    s3.lcps = 142;
    s3.mrPerHour = 1.9;
    s3.hcps = 20;
    s3.rPerHour = 0.28;
    s3.totalDose = 70;
    sensors.append(s3);

    Sensor s4;
    s4.date = "2026-11-19";
    s4.time = "10:33:00";
    s4.elapsedTime = "00:03:00";
    s4.elapsedHours = 0.05;
    s4.lcps = 128;
    s4.mrPerHour = 1.6;
    s4.hcps = 17;
    s4.rPerHour = 0.23;
    s4.totalDose = 72;
    sensors.append(s4);
}

int SensorTableModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return sensors.size();
}

int SensorTableModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return 9;
}

QVariant SensorTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};

    if(role != Qt::DisplayRole)
        return {};

    if(index.row() < 0 || index.row() >= sensors.size())
        return {};

    const Sensor &sensor = sensors.at(index.row());

    switch(index.column())
    {
        case 0: return sensor.date;
        case 1: return sensor.time;
        case 2: return sensor.elapsedTime;
        case 3: return sensor.elapsedHours;
        case 4: return sensor.lcps;
        case 5: return sensor.mrPerHour;
        case 6: return sensor.hcps;
        case 7: return sensor.rPerHour;
        case 8: return sensor.totalDose;

        default: return {};
    }
}
