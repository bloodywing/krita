/*
 *  Copyright (c) 1999 Matthias Elter  <me@kde.org>
 *                1999 Michael Koch    <koch@kde.org>
 *                2003 Patrick Julien  <freak@codepimps.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef KIS_TOOL_MOVE_H_
#define KIS_TOOL_MOVE_H_

#include "kis_strategy_move.h"
#include "KoToolFactory.h"
#include "kis_tool.h"
#include <kis_layer_shape.h>

class KoCanvasBase;

// XXX: Moving is not nearly smooth enough!
class KisToolMove : public KisTool {

    typedef KisTool super;
    Q_OBJECT

public:
    KisToolMove(KoCanvasBase * canvas);
    virtual ~KisToolMove();


public:
    //virtual enumToolType toolType() { return TOOL_TRANSFORM; }
    virtual quint32 priority() { return 2; }

    virtual void mousePressEvent(KoPointerEvent *event);
    virtual void mouseMoveEvent(KoPointerEvent *event);
    virtual void mouseReleaseEvent(KoPointerEvent *event);

    virtual void paint(QPainter& gc, KoViewConverter &converter);

private:

    KisStrategyMove m_strategy;
    QPoint m_dragStart;
};


class KisToolMoveFactory : public KoToolFactory {

public:
    KisToolMoveFactory(QObject *parent, const QStringList&)
        : KoToolFactory(parent, "KritaTransform/KisToolMove", i18n( "Move" ))
        {
            setToolTip(i18n("Move a layer"));
            //setToolType(TOOL_TYPE_TRANSFORM);
            setToolType( dynamicToolType() );
            setActivationShapeId( KIS_LAYER_SHAPE_ID );
            setPriority(0);
            setIcon("tool_move");
            //setShortcut( QKeySequence( Qt::SHIFT + Qt::Key_V ) );
        }

    virtual ~KisToolMoveFactory(){}

    virtual KoTool * createTool(KoCanvasBase *canvas) {
        return new KisToolMove(canvas);
    }

};

#endif // KIS_TOOL_MOVE_H_

