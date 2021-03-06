#ifndef SHAPEQMLBRIDGE_H
#define SHAPEQMLBRIDGE_H

#include <QObject>
#include <QColor>
#include <QMatrix4x4>
#include "color.h"
#include "shape.h"
#include "intersection.h"

class ShapeQmlBridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QMatrix4x4 transform READ getTransform)
    Q_PROPERTY(int id READ getId)
    Q_PROPERTY(float ambient READ getAmbient WRITE setAmbient NOTIFY ambientChanged)
    Q_PROPERTY(float diffuse READ getDiffuse WRITE setDiffuse NOTIFY diffuseChanged)
    Q_PROPERTY(float specular READ getSpecular WRITE setSpecular NOTIFY specularChanged)
    Q_PROPERTY(float reflective READ getReflective WRITE setReflective NOTIFY reflectiveChanged)
    Q_PROPERTY(float transparency READ getTransparency WRITE setTransparency NOTIFY transparencyChanged)
    Q_PROPERTY(float rindex READ getRIndex WRITE setRIndex NOTIFY rIndexChanged)
    Q_PROPERTY(float shininess READ getShininess WRITE setShininess NOTIFY shininessChanged)

public:
    explicit ShapeQmlBridge(QObject *parent = nullptr);

    void setShapePointer(Shape* ptr) {
        m_shape_ptr = ptr;
    }

    void setColor(const QColor& color) {
        m_shape_ptr->material.color = Color(color.redF(), color.greenF(), color.blueF());
        emit colorChanged();
    }

    void setAmbient(float value) {
        m_shape_ptr->material.ambient = value;
        emit ambientChanged();
    }

    void setDiffuse(float value) {
        m_shape_ptr->material.diffuse = value;
        emit diffuseChanged();
    }

    void setSpecular(float value) {
        m_shape_ptr->material.specular = value;
        emit specularChanged();
    }

    void setReflective(float value) {
        m_shape_ptr->material.reflective = value;
        emit reflectiveChanged();
    }

    void setTransparency(float value) {
        m_shape_ptr->material.transparency = value;
        emit transparencyChanged();
    }

    void setRIndex(float value) {
        m_shape_ptr->material.refractive_index = value;
        emit rIndexChanged();
    }

    void setShininess(float value) {
        m_shape_ptr->material.shininess = value;
        emit shininessChanged();
    }

    [[nodiscard]] int getId() const {
        if (m_shape_ptr == nullptr) return -1;
        return m_shape_ptr->id;
    }

    [[nodiscard]] QColor getColor() const {
        if (m_shape_ptr == nullptr) return nullptr;
        QColor qcolor;
        Color color = m_shape_ptr->material.color;
        qcolor.setRgbF(color.red, color.green, color.blue);
        return qcolor;
    }

    [[nodiscard]] QMatrix4x4 getTransform() const {
        if (m_shape_ptr == nullptr) return QMatrix4x4();
        return QMatrix4x4(m_shape_ptr->transform().get(0,0),
                          m_shape_ptr->transform().get(0,1),
                          m_shape_ptr->transform().get(0,2),
                          m_shape_ptr->transform().get(0,3),
                          m_shape_ptr->transform().get(1,0),
                          m_shape_ptr->transform().get(1,1),
                          m_shape_ptr->transform().get(1,2),
                          m_shape_ptr->transform().get(1,3),
                          m_shape_ptr->transform().get(2,0),
                          m_shape_ptr->transform().get(2,1),
                          m_shape_ptr->transform().get(2,2),
                          m_shape_ptr->transform().get(2,3),
                          m_shape_ptr->transform().get(3,0),
                          m_shape_ptr->transform().get(3,1),
                          m_shape_ptr->transform().get(3,2),
                          m_shape_ptr->transform().get(3,3));
    }

    [[nodiscard]] float getAmbient() const {
        if (m_shape_ptr == nullptr) return 0;
        return m_shape_ptr->material.ambient;
    }

    [[nodiscard]] float getDiffuse() const {
        if (m_shape_ptr == nullptr) return 0;
        return m_shape_ptr->material.diffuse;
    }

    [[nodiscard]] float getSpecular() const {
        if (m_shape_ptr == nullptr) return 0;
        return m_shape_ptr->material.specular;
    }

    [[nodiscard]] float getReflective() const {
        if (m_shape_ptr == nullptr) return 0;
        return m_shape_ptr->material.reflective;
    }

    [[nodiscard]] float getTransparency() const {
        if (m_shape_ptr == nullptr) return 0;
        return m_shape_ptr->material.transparency;
    }

    [[nodiscard]] float getRIndex() const {
        if (m_shape_ptr == nullptr) return 0;
        return m_shape_ptr->material.refractive_index;
    }

    [[nodiscard]] float getShininess() const {
        if (m_shape_ptr == nullptr) return 0;
        return m_shape_ptr->material.shininess;
    }

signals:
    void colorChanged();
    void ambientChanged();
    void diffuseChanged();
    void specularChanged();
    void reflectiveChanged();
    void transparencyChanged();
    void rIndexChanged();
    void shininessChanged();

private:
    Shape* m_shape_ptr{nullptr};
};

#endif // SHAPEQMLBRIDGE_H
