#ifndef TUPLE_H
#define TUPLE_H

#define EPSILON 0.00001
bool equal(double a, double b);

class Tuple
{
public:
    Tuple(double x, double y, double z, double w);

public:
    static Tuple Point(double x, double y, double z);
    static Tuple Vector(double x, double y, double z);

    Tuple operator -();
    Tuple operator +(const Tuple& tuple) const;
    Tuple operator -(const Tuple& tuple) const;

    bool isPoint();
    bool isVector();

    inline double x() { return m_x; }
    inline double y() { return m_y; }
    inline double z() { return m_z; }
    inline double w() { return m_w; }

private:
    double m_x;
    double m_y;
    double m_z;
    double m_w;
};

#endif // TUPLE_H
