package ru.dmitry4k.geo.impl

import ru.dmitry4k.geo.dto.Constansts.Companion.RADIUS_MAJOR
import ru.dmitry4k.geo.dto.Constansts.Companion.RADIUS_MINOR
import ru.dmitry4k.geo.dto.GeoPoint
import ru.dmitry4k.geo.Distance
import kotlin.math.*

class Wgs84DistanceImpl : Distance {
    override fun distance(a: GeoPoint, b: GeoPoint): Double {
        val eps = 0.000001
        val f = 1.0 / 298.257223563;
        val l = Math.toRadians(b.lng - a.lng)
        val u1 = atan((1.0 - f) * tan(Math.toRadians(a.lat)))
        val u2 = atan((1.0 - f) * tan(Math.toRadians(b.lat)))
        val sinU1 = sin(u1)
        val cosU1 = cos(u1)
        val sinU2 = sin(u2)
        val cosU2 = cos(u2)

        var lambda = l
        var lambdaP: Double
        var iterLimit = 15
        var cosSqAlpha: Double
        var sinSigma: Double
        var cos2SigmaM: Double
        var cosSigma: Double
        var sigma: Double
        do {
            val sinLambda = sin(lambda)
            val cosLambda = cos(lambda)
            sinSigma =
                sqrt(cosU2 * sinLambda * (cosU2 * sinLambda) + (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda) * (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda))
            if (sinSigma == 0.0) return 0.0
            cosSigma = sinU1 * sinU2 + cosU1 * cosU2 * cosLambda
            sigma = atan2(sinSigma, cosSigma)
            val sinAlpha = cosU1 * cosU2 * sinLambda / sinSigma
            cosSqAlpha = 1 - sinAlpha * sinAlpha
            cos2SigmaM = cosSigma - 2 * sinU1 * sinU2 / cosSqAlpha
            if (cos2SigmaM.isNaN()) cos2SigmaM = 0.0 // equatorial line: cosSqAlpha=0 (§6)
            val C = f / 16 * cosSqAlpha * (4 + f * (4 - 3 * cosSqAlpha))
            lambdaP = lambda
            lambda =
                l + (1 - C) * f * sinAlpha * (sigma + C * sinSigma * (cos2SigmaM + C * cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM)))
        } while (abs(lambda - lambdaP) > eps && --iterLimit > 0)
        val uSq =
            cosSqAlpha * (RADIUS_MAJOR * RADIUS_MAJOR - RADIUS_MINOR * RADIUS_MINOR) / (RADIUS_MINOR * RADIUS_MINOR)
        val m = 1 + uSq / 16384 * (4096 + uSq * (-768 + uSq * (320 - 175 * uSq)))
        val p = uSq / 1024 * (256 + uSq * (-128 + uSq * (74 - 47 * uSq)));
        val deltaSigma =
            p * sinSigma * (cos2SigmaM + p / 4 * (cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM) - p / 6 * cos2SigmaM * (-3 + 4 * sinSigma * sinSigma) * (-3 + 4 * cos2SigmaM * cos2SigmaM)))
        return RADIUS_MINOR * m * (sigma - deltaSigma)
    }
}
