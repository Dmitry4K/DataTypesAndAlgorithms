package ru.dmitry4k.geo.impl

import ru.dmitry4k.geo.dto.Constansts.Companion.RADIUS_MAJOR
import ru.dmitry4k.geo.dto.GeoPoint
import ru.dmitry4k.geo.Distance
import kotlin.math.cos
import kotlin.math.sqrt

class SphericalDistanceImpl : Distance {
    override fun distance(a: GeoPoint, b: GeoPoint): Double {
        val lat1Rad = Math.toRadians(a.lat)
        val lat2Rad = Math.toRadians(b.lat)
        val lon1Rad = Math.toRadians(a.lng)
        val lon2Rad = Math.toRadians(b.lng)

        val x = (lon2Rad - lon1Rad) * cos((lat1Rad + lat2Rad) / 2)
        val y = lat2Rad - lat1Rad

        return sqrt(x * x + y * y) * RADIUS_MAJOR
    }
}
