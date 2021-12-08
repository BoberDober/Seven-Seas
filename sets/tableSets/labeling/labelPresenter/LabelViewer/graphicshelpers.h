#ifndef GRAPHICSHELPERS_H
#define GRAPHICSHELPERS_H
#include <QTransform>

QTransform transformFromZoom(int zoomLevel, bool *accepted = nullptr);

#endif // GRAPHICSHELPERS_H
