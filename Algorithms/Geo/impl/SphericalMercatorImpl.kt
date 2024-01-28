package ru.dmitry4k.geo.service.impl

import ru.dmitry4k.geo.dto.Constansts.Companion.RADIUS_MAJOR
import ru.dmitry4k.geo.service.AbstractMercator
import kotlin.math.atan
import kotlin.math.exp
import kotlin.math.ln
import kotlin.math.tan


class SphericalMercatorImpl : AbstractMercator(TOP, BOTTOM, LEFT, RIGHT) {
    override fun xAxisProjection(lng: Double) = Math.toRadians(lng) * RADIUS_MAJOR

    override fun yAxisProjection(lat: Double): Double {
        return ln(tan(Math.PI / 4.0 + Math.toRadians(lat) / 2.0)) * RADIUS_MAJOR
    }

    override fun lngAxisProjection(x: Double) = Math.toDegrees(x / RADIUS_MAJOR)
    override fun latAxisProjection(y: Double): Double {
        return Math.toDegrees(
            2.0 * atan(exp(y / RADIUS_MAJOR)) - Math.PI / 2.0
        )
    }

    companion object {
        private const val TOP = 23810769.32
        private const val BOTTOM = -23810769.32
        private const val LEFT = -20037508.34
        private const val RIGHT = 20037508.34
    }
}
