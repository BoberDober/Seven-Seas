#include "graphicshelpers.h"
#include <algorithm>
bool checkRange(double& h, double minValue, double maxValue){
    if(h >= minValue && h <= maxValue)
        return true;
    if(h < minValue)
        h = minValue;
    if(h > maxValue)
        h = maxValue;
    return false;
}

QTransform transformFromZoom(int zoomLevel, bool* accepted)
{
    double scaleFactor = 0.1;
    constexpr qreal minFactor = 0.01;
    constexpr qreal maxFactor = 100.0;

    if(zoomLevel > 0)
        scaleFactor = 1;
    //if(1.0 + scaleFactor*zoomLevel < 0.1){
    //    scaleFactor = 0.01;
    //}
    qreal h11 = 1.0 + scaleFactor*zoomLevel;

    if(zoomLevel < -9){
        h11 =  -10;
        double range = 0.1;
        double zoomRange = 50;
        double step = range/zoomRange;
        h11 = 0.1 - abs(zoomLevel)* step;
        //0.1 ... 0.01
        //-10 ... -20


    }

    qreal h12 = 0.0;
    qreal h21 = 0.0;
    qreal h22 = h11;

    if(!checkRange(h11, minFactor, maxFactor)){
        if(accepted != nullptr)
            *accepted = false;
        h22 = h11;
    }
    else{
        if(accepted != nullptr)
            *accepted = true;
    }
    //qDebug()<<Q_FUNC_INFO<<zoomLevel<<h11;

    h11 = std::min(h11, maxFactor);
    h11 = std::max(h11, minFactor);
    h22 = std::min(h22, maxFactor);
    h22 = std::max(h22, minFactor);
    return QTransform(h11, h12, h21, h22, 0, 0);
}
