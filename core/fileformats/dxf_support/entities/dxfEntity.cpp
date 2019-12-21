//
// Created by Myasnikov Vladislav on 10/27/19.
//

#include "core/fileformats/dxf_support/entities/dxfEntity.h"
#include "core/geometry/conic.h"
#include "core/buffers/rgb24/bezierRasterizer.h"
#include "core/utils/utils.h"
#include <iostream>
#include <core/buffers/rgb24/wuRasterizer.h>
#include <core/buffers/rgb24/abstractPainter.h>

namespace corecvs {

// Data printing
void DxfEntity::print() {
    std::cout << "Handle: " << data.handle << std::endl;
    std::cout << "Layer name: " << data.layerName << std::endl;
    std::cout << "Line type name: " << data.lineTypeName << std::endl;
    std::cout << "RGB color: " << (int) data.rgbColor.r() << " " << (int) data.rgbColor.g() << " " << (int) data.rgbColor.b() << " " << std::endl;
    std::cout << "Color number: " << data.colorNumber << std::endl;
    std::cout << "Visibility: " << (data.isVisible ? "on" : "off") << std::endl;
}

void DxfLineEntity::print() {
    std::cout << "* * * Line Entity * * *" << std::endl;
    DxfEntity::print();
    std::cout << "Start point: " << data.startPoint << std::endl;
    std::cout << "End point: " << data.endPoint << std::endl;
    std::cout << std::endl;
}

void DxfLwPolylineEntity::print() {
    std::cout << "* * * LwPolyline Entity * * *" << std::endl;
    DxfEntity::print();
    std::cout << "Thickness: " << data.thickness << std::endl;
    std::cout << "Vertex amount: " << data.vertices.size() << std::endl;
    int i = 1;
    for (Vector2d vertex : data.vertices) std::cout << "Vertex " << i++ << ": " << vertex.x() << " " << vertex.y() << std::endl;
    std::cout << std::endl;
}

void DxfPolylineEntity::print() {
    std::cout << "* * * Polyline Entity * * *" << std::endl;
    DxfEntity::print();
    std::cout << "Thickness: " << data.thickness << std::endl;
    std::cout << "Vertex amount: " << data.vertices.size() << std::endl;
    int i = 1;
    for (Vector3d vertex : data.vertices) std::cout << "Vertex " << i++ << ": " << vertex.x() << " " << vertex.y() << " " << vertex.z() << std::endl;
    std::cout << std::endl;
}

void DxfCircleEntity::print() {
    std::cout << "* * * Circle Entity * * *" << std::endl;
    DxfEntity::print();
    std::cout << "Center point: " << data.center << std::endl;
    std::cout << "Radius: " << data.radius << std::endl;
    std::cout << "Thickness: " << data.thickness << std::endl;
    std::cout << std::endl;
}

void DxfCircularArcEntity::print() {
    std::cout << "* * * Circular Arc Entity * * *" << std::endl;
    DxfEntity::print();
    std::cout << "Center point: " << data.center << std::endl;
    std::cout << "Radius: " << data.radius << std::endl;
    std::cout << "Thickness: " << data.thickness << std::endl;
    std::cout << "Angle range: " << data.startAngle << ".." << data.endAngle << std::endl;
    std::cout << std::endl;
}

void DxfEllipticalArcEntity::print() {
    std::cout << "* * * Elliptical Arc Entity * * *" << std::endl;
    DxfEntity::print();
    std::cout << "Center point: " << data.center << std::endl;
    std::cout << "End point of major axis: " << data.majorAxisEndPoint << std::endl;
    std::cout << "Ratio: " << data.ratio << std::endl;
    std::cout << "Angle range: " << data.startAngle << ".." << data.endAngle << std::endl;
    std::cout << std::endl;
}

void DxfPointEntity::print() {
    std::cout << "* * * Point Entity * * *" << std::endl;
    DxfEntity::print();
    std::cout << "Location: " << data.location << std::endl;
    std::cout << "Thickness: " << data.thickness << std::endl;
    std::cout << std::endl;
}

// Drawing
void DxfLineEntity::draw(RGB24Buffer *buffer, DxfDrawingAttrs *attrs) {
    auto startPoint = attrs->getDrawingValues(data.startPoint.x(), data.startPoint.y());
    auto endPoint = attrs->getDrawingValues(data.endPoint.x(), data.endPoint.y());
    buffer->drawLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), data.rgbColor);
}

void DxfLwPolylineEntity::draw(RGB24Buffer *buffer, DxfDrawingAttrs *attrs) {
    int vertexNumber = data.vertices.size();
    if (vertexNumber > 1) {
        for (unsigned long i = 0; i < data.vertices.size() - 1; i++) {
            auto startVertex = attrs->getDrawingValues(data.vertices[i].x(), data.vertices[i].y());
            auto endVertex = attrs->getDrawingValues(data.vertices[i+1].x(), data.vertices[i+1].y());
            buffer->drawLine(startVertex.x(), startVertex.y(), endVertex.x(), endVertex.y(), data.rgbColor);
        }
        if (data.isClosed) {
            auto startVertex = attrs->getDrawingValues(data.vertices[0].x(), data.vertices[0].y());
            auto endVertex = attrs->getDrawingValues(data.vertices[vertexNumber-1].x(), data.vertices[vertexNumber-1].y());
            buffer->drawLine(startVertex.x(), startVertex.y(), endVertex.x(), endVertex.y(), data.rgbColor);
        }
    } else if (vertexNumber == 1) {
        auto point = attrs->getDrawingValues(data.vertices[0].x(), data.vertices[0].y());
        buffer->drawPixel(point, data.rgbColor);
    }
}

void DxfPolylineEntity::draw(RGB24Buffer *buffer, DxfDrawingAttrs *attrs) {
    int vertexNumber = data.vertices.size();
    if (vertexNumber > 1) {
        for (unsigned long i = 0; i < vertexNumber - 1; i++) {
            auto startVertex = attrs->getDrawingValues(data.vertices[i].x(), data.vertices[i].y());
            auto endVertex = attrs->getDrawingValues(data.vertices[i+1].x(), data.vertices[i+1].y());
            buffer->drawLine(startVertex.x(), startVertex.y(), endVertex.x(), endVertex.y(), data.rgbColor);
        }
        if (data.isClosed) {
            auto startVertex = attrs->getDrawingValues(data.vertices[0].x(), data.vertices[0].y());
            auto endVertex = attrs->getDrawingValues(data.vertices[vertexNumber-1].x(), data.vertices[vertexNumber-1].y());
            buffer->drawLine(startVertex.x(), startVertex.y(), endVertex.x(), endVertex.y(), data.rgbColor);
        }
    } else if (vertexNumber == 1) {
        auto point = attrs->getDrawingValues(data.vertices[0].x(), data.vertices[0].y());
        buffer->drawPixel(point, data.rgbColor);
    }
}

void DxfCircleEntity::draw(class corecvs::RGB24Buffer *buffer, class corecvs::DxfDrawingAttrs *attrs) {
    auto vertex = attrs->getDrawingValues(data.center.x(), data.center.y());
    Circle2d circle(vertex, attrs->getDrawingValue(data.radius));
    buffer->drawArc(circle, data.rgbColor);
}

void DxfCircularArcEntity::draw(class corecvs::RGB24Buffer *buffer, class corecvs::DxfDrawingAttrs *attrs) {
    auto center = Vector2dd(data.center.x(), data.center.y());
    auto startAngle = degToRad(data.startAngle);
    auto endAngle = degToRad(data.endAngle);
    while (endAngle < startAngle) endAngle += 2 * M_PI;

    // divide arc into 1 or 2 segments
    std::vector<Vector2dd> controlAngles = {Vector2dd(startAngle, std::min(endAngle, startAngle + M_PI - 0.00001))};
    if (endAngle - startAngle > M_PI) controlAngles.emplace_back(Vector2dd(startAngle + M_PI, endAngle));

    // draw 1 or 2 segments
    for (Vector2dd eta : controlAngles) {
        auto eta1 = eta.x();
        auto eta2 = eta.y();

        auto ax = data.radius * std::cos(eta1);
        auto ay = data.radius * std::sin(eta1);
        auto bx = data.radius * std::cos(eta2);
        auto by = data.radius * std::sin(eta2);

        // start point
        auto point1 = Vector2dd(center.x() + ax, center.y() + ay);

        // end point
        auto point4 = Vector2dd(center.x() + bx, center.y() + by);

        auto r = std::sqrt(ax * ax + ay * ay);
        auto d = std::sqrt((ax + bx) * (ax + bx) + (ay + by) * (ay + by));
        double k = std::abs(by - ay) > M_E
                ? (ax + bx) * (r / d - 0.5) * 8.0 / 3.0 / (by - ay)
                : (ay + by) * (r / d - 0.5) * 8.0 / 3.0 / (ax - bx);

        // intermediate points
        auto point2 = Vector2dd(point1.x() - k * ay, point1.y() + k * ax);
        auto point3 = Vector2dd(point4.x() + k * by, point4.y() - k * bx);

        point1 = attrs->getDrawingValues(point1);
        point2 = attrs->getDrawingValues(point2);
        point3 = attrs->getDrawingValues(point3);
        point4 = attrs->getDrawingValues(point4);

        auto curve = Curve({point1, point2, point3, point4});
        WuRasterizer rast = WuRasterizer();
        BezierRasterizer<RGB24Buffer, WuRasterizer> bezier(*buffer, rast, data.rgbColor);
        bezier.cubicBezierCasteljauApproximationByFlatness(curve);
    }
}

void DxfEllipticalArcEntity::draw(class corecvs::RGB24Buffer *buffer, class corecvs::DxfDrawingAttrs *attrs) {
    auto center = Vector2dd(data.center.x(), data.center.y());
    auto deltaX = data.majorAxisEndPoint.x();
    auto deltaY = data.majorAxisEndPoint.y();
    auto a = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    auto b = a * data.ratio;

    double rotationAngle = 0;
    if (deltaX == 0) rotationAngle = M_PI / 2;
    else if (deltaY != 0) {
        auto tan = deltaY / deltaX;
        rotationAngle = std::atan(tan);
    }
    double cosAngle = std::cos(rotationAngle);
    double sinAngle = std::sin(rotationAngle);
    auto startAngle = data.startAngle;
    auto endAngle = data.endAngle;
    while (endAngle < startAngle) endAngle += 2 * M_PI;

    // divide arc into 1 or 2 segments
    std::vector<Vector2dd> controlAngles = {Vector2dd(startAngle, std::min(endAngle, startAngle + M_PI - 0.00001))};
    if (endAngle - startAngle > M_PI) controlAngles.emplace_back(Vector2dd(startAngle + M_PI, endAngle));

    // draw 1 or 2 segments
    for (Vector2dd eta : controlAngles) {
        auto eta1 = eta.x();
        auto eta2 = eta.y();

        double dx, dy;

        // start point
        auto cosEta1 = std::cos(eta1);
        auto sinEta1 = std::sin(eta1);
        dx = a * cosEta1;
        dy = b * sinEta1;
        auto point1 = Vector2dd(center.x() + dx * cosAngle - dy * sinAngle, center.y() + dx * sinAngle + dy * cosAngle);

        // end point
        auto cosEta2 = std::cos(eta2);
        auto sinEta2 = std::sin(eta2);
        dx = a * cosEta2;
        dy = b * sinEta2;
        auto point4 = Vector2dd(center.x() + dx * cosAngle - dy * sinAngle, center.y() + dx * sinAngle + dy * cosAngle);

        // intermediate points
        auto alpha = std::sin(eta2 - eta1) * (std::sqrt(4 + 3 * std::pow(std::tan((eta2 - eta1) / 2), 2) - 1) / 3);
        auto point2 = point1 + alpha * Vector2dd(-a * cosAngle * sinEta1 - b * sinAngle * cosEta1,
                                                 -a * sinAngle * sinEta1 + b * cosAngle * cosEta1);
        auto point3 = point4 - alpha * Vector2dd(-a * cosAngle * sinEta2 - b * sinAngle * cosEta2,
                                                 -a * sinAngle * sinEta2 + b * cosAngle * cosEta2);

        point1 = attrs->getDrawingValues(point1);
        point2 = attrs->getDrawingValues(point2);
        point3 = attrs->getDrawingValues(point3);
        point4 = attrs->getDrawingValues(point4);

        auto curve = Curve({point1, point2, point3, point4});
        WuRasterizer rast = WuRasterizer();
        BezierRasterizer<RGB24Buffer, WuRasterizer> bezier(*buffer, rast, data.rgbColor);
        bezier.cubicBezierCasteljauApproximationByFlatness(curve);
    }
}

void DxfPointEntity::draw(class corecvs::RGB24Buffer *buffer, class corecvs::DxfDrawingAttrs *attrs) {
    auto center = attrs->getDrawingValues(data.location.x(), data.location.y());
    auto thickness = attrs->getDrawingValue(data.thickness);
    if (thickness == 0) {
        buffer->drawPixel(center.x(), center.y(), data.rgbColor);
    } else {
        AbstractPainter<RGB24Buffer> painter(buffer);
        painter.drawCircle(center, thickness / 2, data.rgbColor);
    }
}

// Bounding box getting
std::pair<Vector2dd,Vector2dd> DxfLineEntity::getBoundingBox() {
    auto lowerLeftCorner = Vector2dd(std::min(data.startPoint.x(), data.endPoint.x()), std::min(data.startPoint.y(), data.endPoint.y()));
    auto upperRightCorner = Vector2dd(std::max(data.startPoint.x(), data.endPoint.x()), std::max(data.startPoint.y(), data.endPoint.y()));
    return std::make_pair(lowerLeftCorner, upperRightCorner);
}

std::pair<Vector2dd,Vector2dd> DxfLwPolylineEntity::getBoundingBox() {
    if (!data.vertices.empty()) {
        auto lowerLeftCorner = Vector2dd(data.vertices[0].x(), data.vertices[0].y());
        auto upperRightCorner = lowerLeftCorner;
        for (int i = 1; i < data.vertices.size(); i++) {
            auto x = data.vertices[i].x();
            auto y = data.vertices[i].y();
            if (x < lowerLeftCorner.x()) lowerLeftCorner.x() = x;
            else if (x > upperRightCorner.x()) upperRightCorner.x() = x;
            if (y < lowerLeftCorner.y()) lowerLeftCorner.y() = y;
            else if (y > upperRightCorner.y()) upperRightCorner.y() = y;
        }
        return std::make_pair(lowerLeftCorner, upperRightCorner);
    }
}

std::pair<Vector2dd,Vector2dd> DxfPolylineEntity::getBoundingBox() {
    if (!data.vertices.empty()) {
        auto lowerLeftCorner = Vector2dd(data.vertices[0].x(), data.vertices[0].y());
        auto upperRightCorner = lowerLeftCorner;
        for (int i = 1; i < data.vertices.size(); i++) {
            auto x = data.vertices[i].x();
            auto y = data.vertices[i].y();
            if (x < lowerLeftCorner.x()) lowerLeftCorner.x() = x;
            else if (x > upperRightCorner.x()) upperRightCorner.x() = x;
            if (y < lowerLeftCorner.y()) lowerLeftCorner.y() = y;
            else if (y > upperRightCorner.y()) upperRightCorner.y() = y;
        }
        return std::make_pair(lowerLeftCorner, upperRightCorner);
    }
}

std::pair<Vector2dd,Vector2dd> DxfCircleEntity::getBoundingBox() {
    auto lowerLeftCorner = Vector2dd(data.center.x() - data.radius, data.center.y() - data.radius);
    auto upperRightCorner = Vector2dd(data.center.x() + data.radius, data.center.y() + data.radius);
    return std::make_pair(lowerLeftCorner, upperRightCorner);
}

std::pair<Vector2dd,Vector2dd> DxfCircularArcEntity::getBoundingBox() {
    auto lowerLeftCorner = Vector2dd(data.center.x() - data.radius, data.center.y() - data.radius);
    auto upperRightCorner = Vector2dd(data.center.x() + data.radius, data.center.y() + data.radius);
    return std::make_pair(lowerLeftCorner, upperRightCorner);
}

std::pair<Vector2dd,Vector2dd> DxfEllipticalArcEntity::getBoundingBox() {
    auto majorRadius = std::sqrt(data.majorAxisEndPoint.x() * data.majorAxisEndPoint.x() + data.majorAxisEndPoint.y() * data.majorAxisEndPoint.y());
    auto lowerLeftCorner = Vector2dd(data.center.x() - majorRadius, data.center.y() - majorRadius);
    auto upperRightCorner = Vector2dd(data.center.x() + majorRadius, data.center.y() + majorRadius);
    return std::make_pair(lowerLeftCorner, upperRightCorner);
}

std::pair<Vector2dd,Vector2dd> DxfPointEntity::getBoundingBox() {
    auto lowerLeftCorner = Vector2dd(data.location.x(), data.location.y());
    auto upperRightCorner = lowerLeftCorner;
    return std::make_pair(lowerLeftCorner, upperRightCorner);
}

} // namespace corecvs