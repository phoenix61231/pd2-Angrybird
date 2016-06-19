#ifndef BLOCK_H
#define BLOCK_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BLOCK_DENSITY 8.0f
#define BLOCK_FRICTION 0.2f
#define BLOCK_RESTITUTION 0.5f

class block : public GameItem
{
public:
    block(float x, float y, float w,float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
};

#endif // BLOCK_H
