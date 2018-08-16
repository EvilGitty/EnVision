#include "image_mask.h"
#include "Base/envision.h"

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
ImageMask::ImageMask(EnVision* main, QWidget *parent) : QGraphicsScene(parent)
{
		this->main = main;
	
		spoint = 0;
		rectangle = 0;
		ellipse = 0;
		polygon = 0;
		line = 0;
		text = 0;
		pixmapitem = 0;
		group = 0;
		view = 0;
		scene = 0;
		currentItem = 0;

		guiAccess();

		installEventFilter(parent);
		scene = new QGraphicsScene(parent);
		scene->installEventFilter(parent);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
ImageMask::~ImageMask()
{

}

//==============================================================================
// void ImageMask::guiAccess()
//------------------------------------------------------------------------------
//==============================================================================
void ImageMask::guiAccess()
{
		this->ui_base = main->getBaseUI();
		this->ui_plot = main->getPlotUI();
		this->ui_image = main->getImageUI();

	return;
}

//==============================================================================
// void ImageMask::updatePixmap(QImage image, int x, int y)
//------------------------------------------------------------------------------
//==============================================================================
void ImageMask::updatePixmap(QImage image, int x, int y)
{
		//QList<QGraphicsPixmapItem *> L;
		//QGraphicsItemGroup *group = scene->createItemGroup(pixmapitem);
		//QGraphicsItemLayer* pLayer = new QGraphicsItemLayer;

		pixmapitem = scene->addPixmap(QPixmap::fromImage(image));
		pixmapitem->setPos(x, y);
		pixmapitem->setTransformationMode(Qt::SmoothTransformation);
		pixmapitem->setFlag(QGraphicsItem::ItemIsMovable, false);
		pixmapitem->setFlag(QGraphicsItem::ItemIsSelectable, false);
		pixmapitem->setCacheMode(QGraphicsItem::ItemCoordinateCache);

		pixmapitem->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
		//if (pixmapitem == NULL){
			ui_image->image->setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
			ui_image->image->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
			ui_image->image->setResizeAnchor(QGraphicsView::AnchorViewCenter);
			ui_image->image->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
			ui_image->image->setRenderHint(QPainter::Antialiasing, false);
			ui_image->image->setRenderHint(QPainter::TextAntialiasing, false);
			ui_image->image->setRenderHint(QPainter::SmoothPixmapTransform, true);
			scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);
			ui_image->image->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);


			//updateItemGroup("CreateGroup", NULL, pixList);
		//}


		ui_image->image->setScene(scene);

	return;
}


//==============================================================================
// void ImageMask::updateItemGroup(QString toDo, QGraphicsItem * item, QList<QGraphicsItem*> items)
//------------------------------------------------------------------------------
//==============================================================================
void ImageMask::updateItemGroup(QString toDo, QGraphicsItem * item, QList<QGraphicsItem*> items)
{

		if (QString::compare(toDo, "CreateGroup") == 0){
			group = scene->createItemGroup(items);
			//group->hide();
		}

		if (QString::compare(toDo, "addOne")==0){
			group->addToGroup(item);
		}

		if (QString::compare(toDo, "removeOne") == 0){
			group->removeFromGroup(item);
		}

		if (QString::compare(toDo, "removeAll") == 0){
			// Destroy the group, and delete the group item
			scene->destroyItemGroup(group);
		}

	return;
}

//==============================================================================
// void ImageMask::updateItem(QGraphicsItem * item, QRectF rect, QPolygonF poly)
//------------------------------------------------------------------------------
//==============================================================================
void ImageMask::updateItem(QGraphicsItem * item, QRectF rect, QPolygonF poly)
{
		if ((spoint) == (qgraphicsitem_cast<QGraphicsRectItem*>(item))){
			if (spoint == NULL){
				cR = new CustomRect;
				cR->add(scene, rect);
				spoint = cR->rectangle;
				spoint->setZValue(10);
				spoint->setFlag(QGraphicsItem::ItemIsMovable);
				spoint->setFlag(QGraphicsItem::ItemIsSelectable, false);
				spoint->setCacheMode(QGraphicsItem::ItemCoordinateCache);
				currentItem = spoint;
			}
			else{
				spoint->setRect(rect.x(), rect.y(), 1, 1);
			}
			pos_currentItem = spoint->pos();
			return;
		}

		if ((rectangle) == (qgraphicsitem_cast<QGraphicsRectItem*>(item))){
			if (rectangle == NULL){
				cR = new CustomRect;
				cR->add(scene, rect);
				rectangle = cR->rectangle;
				rectangle->setZValue(10);
				rectangle->setFlag(QGraphicsItem::ItemIsMovable);
				rectangle->setFlag(QGraphicsItem::ItemIsSelectable, true);
				rectangle->setCacheMode(QGraphicsItem::ItemCoordinateCache);
				currentItem = rectangle;
			}else{
				rectangle->setRect(rect.x(), rect.y(), rect.width(), rect.height());
			}
			pos_currentItem = rectangle->pos();
			return;
		}

		if ((ellipse) == (qgraphicsitem_cast<QGraphicsEllipseItem*>(item))){
			if (ellipse == NULL){
				cE = new CustomEllipse;
				cE->add(scene, rect);
				ellipse = cE->ellipse;
				ellipse->setZValue(10);
				ellipse->setFlag(QGraphicsItem::ItemIsMovable);
				ellipse->setFlag(QGraphicsItem::ItemIsSelectable, true);
				ellipse->setCacheMode(QGraphicsItem::ItemCoordinateCache);
				currentItem = ellipse;
			}else{
				ellipse->setPos(rect.x(), rect.y());
			}
			ellipse->pos();
			pos_currentItem = ellipse->pos();
			return;
		}

		if ((polygon) == (qgraphicsitem_cast<QGraphicsPolygonItem*>(item))){
			if (polygon == NULL){
				cP = new CustomPolygon;
				cP->add(scene, rect, poly);
				polygon = cP->polygon;
				polygon->setZValue(10);
				polygon->setFlag(QGraphicsItem::ItemIsMovable, true);
				polygon->setFlag(QGraphicsItem::ItemIsSelectable, true);
				polygon->setCacheMode(QGraphicsItem::ItemCoordinateCache);
				currentItem = polygon;
			}else{
				polygon->setPos(rect.x(), rect.y());
			}
			pos_currentItem = polygon->pos();
			return;
		}

		//QGraphicsScene* pScene = new QGraphicsScene;
		//QLineEdit* pLineEdit = new QLineEdit("Some Text");
		// add the widget - internally, the QGraphicsProxyWidget is created and returned
		//QGraphicsProxyWidget* pProxyWidget = scene->addWidget(pLineEdit);


	return;
}

//==============================================================================
// void ImageMask::remove(QGraphicsItem * item)
//------------------------------------------------------------------------------
//==============================================================================
void ImageMask::remove(QGraphicsItem * item)
{
		if (item != 0){
			scene->removeItem(item);
		}
	return;
}


//==============================================================================
// inline qreal round(qreal val, int step)
//------------------------------------------------------------------------------
//==============================================================================
inline qreal round(qreal val, int step)
{
	int tmp = int(val) + step / 2;
	tmp -= tmp % step;
	return qreal(tmp);
}

//==============================================================================
// void ImageMask::drawBackground(QPainter *painter, const QRectF &rect)
//------------------------------------------------------------------------------
//==============================================================================
void ImageMask::drawBackground(QPixmap map, const QRectF &rect)
{
		QPainter paintit(&(map));	//destination
		int step = GRID_STEP;
		paintit.setPen(QPen(QColor(200, 200, 255, 125)));
		// draw horizontal grid
		qreal start = round(rect.top(), step);
		if (start > rect.top()) {
			start -= step;
		}
		for (qreal y = start - step; y < rect.bottom();) {
			y += step;
			paintit.drawLine(rect.left(), y, rect.right(), y);
		}
		// now draw vertical grid
		start = round(rect.left(), step);
		if (start > rect.left()) {
			start -= step;
		}
		for (qreal x = start - step; x < rect.right();) {
			x += step;
			paintit.drawLine(x, rect.top(), x, rect.bottom());
		}

		paintit.setCompositionMode(QPainter::CompositionMode_Clear);
		paintit.setRenderHints(QPainter::HighQualityAntialiasing);
		paintit.end();
	return;
}