#include "PipelineView.h"
#include <QtGui>
#include <QDebug>
#include <QMetaType>
#include "PipelineElement.h"
#include "PipelineScene.h"

using namespace plvgui;
using namespace plv;

PipelineView::PipelineView(QWidget *parent) : QGraphicsView(parent)
{
    setAcceptDrops(true);
}

void PipelineView::setScene(PipelineScene* scene)
{
    QGraphicsView::setScene(scene);
    this->m_pipeline = scene->getPipeline();
}

void PipelineView::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->provides("x-plv-element-name"))
    {
        qDebug() << "Enter";
        event->accept();
    }
}

void PipelineView::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->provides("x-plv-element-name"))
    {
        qDebug() << "Move";
        event->accept();
    }
}

void PipelineView::dropEvent(QDropEvent *event)
{
    qDebug() << event->mimeData()->formats();
    if(event->provides("x-plv-element-name"))
    {
    //    qDebug() << event->mimeData()->data("x-plv-element-name");
        QString elementName = QString(event->mimeData()->data("x-plv-element-name"));
        qDebug() << elementName;

        RefPtr<PipelineElement> pe = static_cast<PipelineElement*>(
                QMetaType::construct(QMetaType::type(elementName.toAscii())) );

        m_pipeline->add(pe);
    }
}
