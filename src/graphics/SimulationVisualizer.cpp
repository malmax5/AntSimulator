    #include "../../include/graphics/SimulationVisualizer.hpp"

    SimulationVisualizer::SimulationVisualizer(QGraphicsScene* scene, AntColonyModel* model, QObject* parent)
        : QObject(parent), scene(scene), model(model)
    {
        createNest();
        setPheromoneMap();
    }

    void SimulationVisualizer::createNest()
    {
        if (!scene) return;
        constexpr qreal nestSize = 0.04;
        QPointF nestPos = model->getNestPosition();

        nestItem = new QGraphicsEllipseItem(
            nestPos.x() - nestSize / 2,
            nestPos.y() - nestSize / 2,
            nestSize, nestSize
        );

        nestItem->setBrush(QColor(150, 75, 0));
        nestItem->setPen(Qt::NoPen);
        nestItem->setZValue(1);
        scene->addItem(nestItem);
    }

    void SimulationVisualizer::updateAnts()
    {
        if (!scene) return;
        const auto& ants = model->getAnts();

        for (const auto& ant : ants)
        {
            if (antItems.find(ant.id) == antItems.end())
            {
                AntItem* newAnt = new AntItem(ant);
                antItems[ant.id] = newAnt;
                scene->addItem(newAnt);
            }
            else
            {
                antItems[ant.id]->updatePosition(ant.logicalPosition, ant.hasFood, ant.target);
            }
        }

        std::vector<int> toRemove;
        toRemove.reserve(antItems.size());
        for (auto it = antItems.begin(); it != antItems.end(); it++)
        {
            int id = it.key();
            AntItem* item = it.value();

            bool exist = std::any_of(ants.begin(), ants.end(), 
                [id](const Ant& a){ return a.id == id; });
            
            if (!exist)
            {
                scene->removeItem(item);
                delete item;
                toRemove.push_back(id);
            }
        }

        for (int id : toRemove)
        {
            antItems.remove(id);
        }
    }

    void SimulationVisualizer::updateFood()
    {
        if (!scene) return;
        const auto& foods = model->getFoodStorage().getFoods();
        QSet<QPair<qreal, qreal>> currentFood;

        for (const auto& food : foods)
        {
            currentFood.insert({food.x(), food.y()});

            if (!foodItems.contains({food.x(), food.y()}))
            {
                auto* foodItem = new QGraphicsRectItem(
                    food.x() - 0.005,
                    food.y() - 0.005,
                    0.01, 0.01
                );

                foodItem->setBrush(Qt::green);
                foodItem->setPen(Qt::NoPen);
                foodItem->setZValue(2);
                scene->addItem(foodItem);
                foodItems.insert({food.x(), food.y()}, foodItem);
            }
        }

        auto it = foodItems.begin();
        while (it != foodItems.end())
        {
            if (currentFood.find(it.key()) == currentFood.end())
            {
                scene->removeItem(it.value());
                delete it.value();
                it = foodItems.erase(it);
            }
            else
            {
                it++;
            }
        }
    }

    void SimulationVisualizer::setPheromoneMap()
    {
        if (!scene) return;
        if (pheromoneLayer)
        {
            return;
            scene->removeItem(pheromoneLayer);
            delete pheromoneLayer;
        }

        pheromoneLayer = new PheromoneLayer(model->getPheromoneMap());
        pheromoneLayer->setZValue(1);
        scene->addItem(pheromoneLayer);
    }

    void SimulationVisualizer::updateVisualization()
    {
        if (!scene) return;
        QMutexLocker locker(&updateMutex);
        updateAnts();
        updateFood();
    }
