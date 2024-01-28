package ru.dmitry4k.geo.test

import org.junit.jupiter.api.Assertions
import org.junit.jupiter.api.Test
import ru.dmitry4k.geo.dto.GeoPoint
import kotlin.math.abs

class Wgs84Tests {
    private val mercator = Wgs84MercatorImpl()
    private val distance = Wgs84DistanceImpl()

    @Test
    fun mappingTest() {
        val geoPoints = listOf(
            GeoPoint(-50.0, 180.0),
            GeoPoint(43.0, 180.0),
            GeoPoint(-67.0, -180.0),
            GeoPoint(43.0, -180.0),
            GeoPoint(0.0, 0.0),
            GeoPoint(40.0, 50.0),
            GeoPoint(-30.0, 90.0),
        )
        val restoredGeoPoints = geoPoints.map {
            mercator.xyToPoint(mercator.pointToXY(it))
        }
        val epsilon = 0.0000001

        geoPoints.zip(restoredGeoPoints).forEach {
            Assertions.assertTrue(abs(it.first.lat - it.second.lat) < epsilon)
            Assertions.assertTrue(abs(it.first.lng - it.second.lng) < epsilon)
        }
    }

    @Test
    fun distanceTest() {
        val a = GeoPoint(55.7520233, 37.6174994)
        val b = GeoPoint(52.6031000, 39.5708000)
        Assertions.assertEquals(372947, distance.distance(a, b).toLong())
    }
}
