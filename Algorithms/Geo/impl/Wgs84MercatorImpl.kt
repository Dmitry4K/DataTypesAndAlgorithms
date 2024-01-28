package ru.dmitry4k.geo.service.impl

import ru.dmitry4k.geo.dto.Constansts.Companion.RADIUS_MAJOR
import ru.dmitry4k.geo.dto.Constansts.Companion.RADIUS_MINOR
import ru.dmitry4k.geo.service.AbstractMercator
import kotlin.math.*

class Wgs84MercatorImpl : AbstractMercator(TOP, BOTTOM, LEFT, RIGHT) {
    override fun xAxisProjection(lng: Double): Double = Math.toRadians(lng) * RADIUS_MAJOR

    override fun lngAxisProjection(x: Double): Double = Math.toDegrees(x / RADIUS_MAJOR)

    override fun yAxisProjection(lat: Double): Double {
        val coercedLat = lat.coerceAtMost(MAX_LAT).coerceAtLeast(-MAX_LAT)
        val phi = Math.toRadians(coercedLat)
        val con = ECCENT * sin(phi)
        val powCon = ((1.0 - con) / (1.0 + con)).pow(ECCNTH)
        return -RADIUS_MAJOR * ln(tan(0.5 * (Math.PI / 2.0 - phi)) / powCon)
    }

    override fun latAxisProjection(y: Double): Double {
        val ts = exp(-y / RADIUS_MAJOR)
        var phi = Math.PI / 2.0 - 2.0 * atan(ts)
        var i = 0
        var dPhi = 1.0
        while (abs(dPhi) > EPS && i++ < MAX_STEPS_COUNT) {
            val con = ECCENT * sin(phi)
            dPhi = Math.PI / 2.0 - 2.0 * atan(ts * ((1.0 - con) / (1.0 + con)).pow(ECCNTH)) - phi
            phi += dPhi
        }
        return Math.toDegrees(phi)
    }

    companion object {
        private val ECCENT = sqrt(1 - (RADIUS_MINOR / RADIUS_MAJOR).pow(2.0))
        private val ECCNTH = ECCENT * 0.5
        private const val MAX_LAT = 89.5;
        private const val EPS = 0.000000001
        private const val MAX_STEPS_COUNT = 15
        private const val TOP = 34619289.37
        private const val BOTTOM = -34619289.37
        private const val LEFT = -20037508.34
        private const val RIGHT = 20037508.34
    }
}
