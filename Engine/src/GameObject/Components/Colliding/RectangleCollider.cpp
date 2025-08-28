//
// Created by Максим Процик on 24.08.2023.
//

#include "GameObject/GameObject.h"
#include "Serialization/ComponentFactory.h"
#include "RectangleCollider.h"
#include "Utils/Math.h"

REGISTER(RectangleCollider)

std::pair<Vector2D, Vector2D> RectangleCollider::GetBorders() const
{

    Vector2D center = m_GameObject->transform.Position;
    std::vector<Vector2D> points = {
            Vector2D(center.X + Width / 2, center.Y + Height / 2),
            Vector2D(center.X - Width / 2, center.Y + Height / 2),
            Vector2D(center.X - Width / 2, center.Y - Height / 2),
            Vector2D(center.X + Width / 2, center.Y - Height / 2)
    };
    std::vector<Vector2D> rotatedPoints = Math::RotatePoints(points, m_GameObject->transform.RotationAngle, center);
    Vector2D minPos = Vector2D(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
    Vector2D maxPos = Vector2D(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
    for (const auto& point: rotatedPoints)
    {
        minPos.X = std::min(minPos.X, point.X);
        minPos.Y = std::min(minPos.Y, point.Y);
        maxPos.X = std::max(maxPos.X, point.X);
        maxPos.Y = std::max(maxPos.Y, point.Y);
    }

    return {minPos, maxPos};
}

Vector2D RectangleCollider::GetClosestPoint(const Vector2D &point) const
{
    Vector2D center = m_GameObject->transform.Position;
    std::vector<Vector2D> points = {
            Vector2D(center.X + Width / 2, center.Y + Height / 2),
            Vector2D(center.X - Width / 2, center.Y + Height / 2),
            Vector2D(center.X - Width / 2, center.Y - Height / 2),
            Vector2D(center.X + Width / 2, center.Y - Height / 2)
    };
    std::vector<Vector2D> rotatedPoints = Math::RotatePoints(points, m_GameObject->transform.RotationAngle, center);
    Vector2D closestPoint;
    float minDistance = std::numeric_limits<float>::infinity();
    for (const Vector2D& vertex: rotatedPoints)
    {
        float dist = (vertex - point).Length();
        if (minDistance > dist)
        {
            closestPoint = vertex;
            minDistance = dist;
        }
    }

    for (int i = 1; i <= rotatedPoints.size(); i++)
    {
        int realIndex = i % (int)rotatedPoints.size();
        Vector2D axis = rotatedPoints[realIndex] - rotatedPoints[i-1];
        Vector2D axisNormalized = axis.Normalized();
        float projection = (point - rotatedPoints[i-1]) * axisNormalized;
        if (projection < 0 || projection > axis.Length())
        {
            continue;
        }
        Vector2D projectionPoint = projection * axisNormalized + rotatedPoints[i-1];
        float dist = (projectionPoint - point).Length();
        if (minDistance > dist)
        {
            closestPoint = projectionPoint;
            minDistance = dist;
        }
    }
    return closestPoint;
}

std::vector<Vector2D> RectangleCollider::GetCollisionAxes(const Collider *collider) const
{
    Vector2D center = m_GameObject->transform.Position;
    std::vector<Vector2D> points = {
            Vector2D(center.X + Width / 2, center.Y + Height / 2),
            Vector2D(center.X - Width / 2, center.Y + Height / 2),
            Vector2D(center.X - Width / 2, center.Y - Height / 2),
            Vector2D(center.X + Width / 2, center.Y - Height / 2)
    };
    std::vector<Vector2D> rotatedPoints = Math::RotatePoints(points, m_GameObject->transform.RotationAngle, center);
    std::vector<Vector2D> axes;
    axes.reserve(rotatedPoints.size());
    for (int i = 1; i <= rotatedPoints.size(); i++)
    {
        int realIndex = i % (int)rotatedPoints.size();
        Vector2D axis = (rotatedPoints[realIndex] - rotatedPoints[i-1]).Normalized();
        axes.emplace_back(axis.Y, -axis.X);
    }
    return axes;
}

std::pair<std::pair<Vector2D, float>, std::pair<Vector2D, float>> RectangleCollider::GetMinAndMaxPoints(const Vector2D& axis) const
{
    Vector2D center = m_GameObject->transform.Position;
    std::vector<Vector2D> points = {
            Vector2D(center.X + Width / 2, center.Y + Height / 2),
            Vector2D(center.X - Width / 2, center.Y + Height / 2),
            Vector2D(center.X - Width / 2, center.Y - Height / 2),
            Vector2D(center.X + Width / 2, center.Y - Height / 2)
    };
    std::vector<Vector2D> rotatedPoints = Math::RotatePoints(points, m_GameObject->transform.RotationAngle, center);
    float minProjection = std::numeric_limits<float>::infinity();
    float maxProjection = -std::numeric_limits<float>::infinity();
    Vector2D minPoint;
    Vector2D maxPoint;
    for (const auto& point: rotatedPoints)
    {
        float projection = point * axis;
        if (minProjection > projection)
        {
            minPoint = point;
            minProjection = projection;
        }
        if (maxProjection < projection)
        {
            maxPoint = point;
            maxProjection = projection;
        }
    }
    return {{minPoint, minProjection}, {maxPoint, maxProjection}};
}

std::pair<Vector2D, Vector2D> RectangleCollider::GetSignificantFace(const Vector2D &point, const Vector2D &axis) const
{
    Vector2D center = m_GameObject->transform.Position;
    std::vector<Vector2D> points = {
            Vector2D(center.X + Width / 2, center.Y + Height / 2),
            Vector2D(center.X - Width / 2, center.Y + Height / 2),
            Vector2D(center.X - Width / 2, center.Y - Height / 2),
            Vector2D(center.X + Width / 2, center.Y - Height / 2)
    };
    std::vector<Vector2D> rotatedPoints = Math::RotatePoints(points, m_GameObject->transform.RotationAngle, center);
    int pointIndex = 0;
    for (int i = 0; i < rotatedPoints.size(); i++)
    {
        if (Math::Equal(rotatedPoints[i].X, point.X) && Math::Equal(rotatedPoints[i].Y, point.Y))
        {
            pointIndex = i;
            break;
        }
    }

    int secondIndex1 = pointIndex == (int)rotatedPoints.size() ? 0 : pointIndex + 1;
    int secondIndex2 = pointIndex == 0 ? (int)rotatedPoints.size() - 1 : pointIndex - 1;

    Vector2D normal = Vector2D(axis.Y, -axis.X);
    Vector2D axis1 = (rotatedPoints[pointIndex] - rotatedPoints[secondIndex1]).Normalized();
    Vector2D axis2 = (rotatedPoints[pointIndex] - rotatedPoints[secondIndex2]).Normalized();
    if (std::abs(normal * axis1) > std::abs(normal * axis2))
    {
        return {rotatedPoints[secondIndex1], rotatedPoints[pointIndex]};
    }
    else
    {
        return {rotatedPoints[secondIndex2], rotatedPoints[pointIndex]};
    }
}
