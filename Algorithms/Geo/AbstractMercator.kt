package ru.dmitry4k.geo.service

import ru.dmitry4k.geo.GeoPoint
import ru.dmitry4k.geo.XYPoint

abstract class AbstractMercator(
    private val top: Double,
    private val bottom: Double,
    private val left: Double,
    private val right: Double
) : Mercator {
    override fun pointToXY(geoPoint: GeoPoint)= with(geoPoint) {
        XYPoint(xAxisProjection(lng), yAxisProjection(lat))
    }

    override fun xyToPoint(xyPoint: XYPoint) = with(xyPoint) {
        GeoPoint(latAxisProjection(y), lngAxisProjection(x))
    }


    override fun top(): Double = top

    override fun bottom(): Double = bottom

    override fun left(): Double = left

    override fun right(): Double = right

    protected abstract fun xAxisProjection(lng: Double): Double

    protected abstract fun yAxisProjection(lat: Double): Double

    protected abstract fun latAxisProjection(y: Double): Double

    protected abstract fun lngAxisProjection(x: Double): Double
}
