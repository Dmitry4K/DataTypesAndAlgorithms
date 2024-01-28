package ru.dmitry4k.geo

import ru.dmitry4k.geo.dto.GeoPoint

interface Distance {
    fun distance(a: GeoPoint, b: GeoPoint): Double
}
