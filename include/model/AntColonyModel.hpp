#pragma once

#include <QSize>
#include <QMutex>

#include "Ant.hpp"
#include "FoodStorage.hpp"
#include "PheromoneMap.hpp"

class AntColonyModel
{
public:
    AntColonyModel();
    explicit AntColonyModel(int heigth, int weigth);
    explicit AntColonyModel(int size);

public:
    void setAnts(const QVector<Ant*>& ants);
    const QVector<Ant*>& getAnts() const;
    void clearAnts();
    void addAnt(Ant* ant);
    void removeAnt(int index);
    Ant* getAnt(int index);

    void setFoods(const FoodStorage& foods);
    void addFood(const QPointF& pos);
    void removeFood(const QPointF& pos);
    FoodStorage& getFoodStorage();

    void setPheromones(PheromoneMap& pheromones);
    void addPheromone(const QPointF& pos, qreal strength);
    void evaporatePheromones();
    QPointF getDiractionByPheromones(const QPointF& pos, qreal detectionRadius) const;
    PheromoneMap& getPheromoneMap();

    QPointF getNestPosition() const;
    void setNestPosition(const QPointF newPos);

    void reset();

    friend QDataStream& operator<<(QDataStream& out, const AntColonyModel& model)
    {
        out << model.nestPosition;
        
        int antSize = model.ants.size();
        out << antSize;
        for (const Ant* ant : model.ants)
        {
            out << ant->id();
            out << *ant;
        }

        out << model.foods
            << model.pheromoneMap;
        
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, AntColonyModel& model)
    {
        in >> model.nestPosition;

        int antCount;
        in >> antCount;
        for (int i = 0; i < antCount; i++)
        {
            int antId;
            in >> antId;
            Ant* ant = new Ant(antId);
            in >> *ant;
            model.ants.append(ant);
        }

        in >> model.foods
           >> model.pheromoneMap;
        
        return in;
    }

public:
    mutable QMutex dataMutex;
    
private:
    QPointF nestPosition;
    QVector<Ant*> ants;
    FoodStorage foods;
    PheromoneMap pheromoneMap;
};
