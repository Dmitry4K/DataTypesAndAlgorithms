package ru.dmitry4k.geo

import ru.dmitry4k.geo.dto.GeoPoint
import ru.dmitry4k.geo.dto.XYPoint

interface Mercator {
    fun pointToXY(geoPoint: GeoPoint): XYPoint
    fun xyToPoint(xyPoint: XYPoint): GeoPoint

    fun top(): Double
    fun bottom(): Double
    fun left(): Double
    fun right(): Double
}
