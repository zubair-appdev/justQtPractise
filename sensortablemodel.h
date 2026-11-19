#ifndef SENSORTABLEMODEL_H
#define SENSORTABLEMODEL_H

#include <QAbstractTableModel> //QObject is already present in this header
#include <QVector>
#include <QString>

struct Sensor
{
    QString date;
    QString time;
    QString elapsedTime;
    double elapsedHours;
    double lcps;
    double mrPerHour;
    double hcps;
    double rPerHour;
    double totalDose;
};

class SensorTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SensorTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


signals:


private:
    QVector<Sensor> sensors;
};

#endif // SENSORTABLEMODEL_H
