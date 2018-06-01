#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>
#include <QGraphicsRectItem>

#include "dotsignal.h"


//class QGraphicsSceneMouseEvent;

class Rectangle : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY( QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY
                previousPositionChanged )

public:
    explicit Rectangle( QObject* parent = 0 );
    ~Rectangle();

    enum ActionStates
    {
        ResizeState = 0x01,
        RotationState = 0x02
    };

    enum CornerFlags
    {
        Top = 0x01,
        Bottom = 0x02,
        Left = 0x04,
        Right = 0x08,
        TopLeft = Top | Left,
        TopRight = Top | Right,
        BottomLeft = Bottom | Left,
        BottomRight = Bottom | Right
    };

    enum CornerGrabbers
    {
        GrabberTop = 0,
        GrabberBottom,
        GrabberLeft,
        GrabberRight,
        GrabberTopLeft,
        GrabberTopRight,
        GrabberBottomLeft,
        GrabberBottomRight
    };

    QPointF previousPosition() const;
    void setPreviousPosition( const QPointF previousPosition );

    void setRect( qreal x, qreal y, qreal w, qreal h );
    void setRect( const QRectF& rect );

signals:
    void rectChanged( Rectangle* rect );
    void previousPositionChanged();
    void clicked( Rectangle* rect );
    void signalMove( QGraphicsItem* item, qreal dx, qreal dy );


protected:
    void mouseMoveEvent( QGraphicsSceneMouseEvent* event ) override;
    void mousePressEvent( QGraphicsSceneMouseEvent* event ) override;
    void mouseReleaseEvent( QGraphicsSceneMouseEvent* event ) override;
    void mouseDoubleClickEvent( QGraphicsSceneMouseEvent* event ) override;
    void hoverEnterEvent( QGraphicsSceneHoverEvent* event ) override;
    void hoverLeaveEvent( QGraphicsSceneHoverEvent* event ) override;
    void hoverMoveEvent( QGraphicsSceneHoverEvent* event ) override;
    QVariant itemChange( GraphicsItemChange change, const QVariant& value ) override;
    void Rosina( QString );

private:
    unsigned int m_cornerFlags;
    unsigned int m_actionFlags;
    QPointF m_previousPosition;
    bool m_leftMouseButtonPressed;
    Dotsignal* cornerGrabber[8];

    void resizeLeft( const QPointF& pt );
    void resizeRight( const QPointF& pt );
    void resizeBottom( const QPointF& pt );
    void resizeTop( const QPointF& pt );

    void rotateItem( const QPointF& pt );
    void setPositionGrabbers();
    void setVisibilityGrabbers();
    void hideGrabbers();
};

#endif // RECTANGLE_H
