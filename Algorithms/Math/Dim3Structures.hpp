struct double3 {
  double x, y ,z;
};

struct double3x3 {
    double x11, x12, x13, x21, x22, x23, x31, x32, x33;
};

double3 sum(double3 a, double3 b) {
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}
double3x3 div(double3x3 a, double b) {
    return { a.x11 / b, a.x12 / b,a.x13 / b, a.x21 / b, a.x22 / b, a.x23 / b, a.x31 / b, a.x32 / b, a.x33 / b };
}
double3 div(double3 a, double b) {
    return { a.x / b, a.y / b, a.z / b };
}
double3 sub(double3 a, double3 b) {
    return { a.x - b.x, a.y - b.y, a.z - b.z };
}
double3x3 mult(double3 a, double3 b) {
    return {a.x * b.x, a.x * b.y, a.x * b.z,
            a.y * b.x, a.y * b.y, a.y * b.z,
            a.z * b.x, a.z * b.y, a.z * b.z };
}

double dot(double3 a, double3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
double3 mult(double3 a, double3x3 b) {
    return { dot(a, {b.x11, b.x21,b.x31}), dot(a, {b.x12, b.x22,b.x32}), dot(a, {b.x13, b.x23,b.x33}) };
}


double3x3 sum(double3x3 a, double3x3 b) {
    return { a.x11 + b.x11, a.x12 + b.x12, a.x13 + b.x13,
             a.x21 + b.x21, a.x22 + b.x22, a.x23 + b.x23,
             a.x31 + b.x31, a.x32 + b.x32, a.x33 + b.x33};
}

double det(double3x3 a) {
    return a.x11 * a.x22 * a.x33 + a.x12 * a.x23 * a.x31 + a.x13 * a.x21 * a.x32 -
        a.x13 * a.x22 * a.x31 - a.x12 * a.x21 * a.x33 - a.x11 * a.x23 * a.x32;
}

double3x3 transpose(double3x3 a) {
    return { a.x11, a.x21, a.x31,
            a.x12, a.x22, a.x32,
            a.x13, a.x23, a.x33 };
}


double3x3 inv(double3x3 a) {
    a = transpose(a);
    double3x3 m = { (a.x22 * a.x33 - a.x32 * a.x23), -1.0* (a.x21 * a.x33 - a.x31 * a.x23), (a.x21 * a.x32 - a.x31 * a.x22),
                   -1.0 * (a.x12 * a.x33 - a.x32 * a.x13), (a.x11 * a.x33 - a.x31 * a.x13), -1.0* (a.x11 * a.x32 - a.x31 * a.x12),
                    (a.x12 * a.x23 - a.x22 * a.x13), -1.0 * (a.x11 * a.x23 - a.x21 * a.x13), (a.x11 * a.x22 - a.x21 * a.x12) };
    return div(m, det(a));
}
