#include "../nullable.h"
#include "../utils.h"
#include "point.h"
#include "line.h"

namespace geometry {
  // x1 - The first point's x value
  // y1 - The first point's y value
  // x1 - The second point's x value
  // y2 - The second point's y value
  Line::Line(double x1, double y1, double x2, double y2) {
    _x1 = utils::trim(x1, 9);
    _y1 = utils::trim(y1, 9);
    _x2 = utils::trim(x2, 9);
    _y2 = utils::trim(y2, 9);
  }

  // Gets the matching x value for a given y value
  Nullable<double> Line::getMatchingX(double y) {
    // If an error was thrown it means we divided a number by zero,
    // in which case there is not intersection point
    double x = utils::trim(
      (((y - _y1) * (_x2 - _x1)) /
       (_y2 - _y1)) + _x1
    , 9, "exact");

    // Check if result is in values range
    if (utils::isBetween(x, _x1, _x2, "round")) {
      return Nullable<double>(x);
    }

    return Nullable<double>();
  }

  // Gets the matching y value for a given x value
  Nullable<double> Line::getMatchingY(double x) {
    // If an error was thrown it means we divided a number by zero,
    // in which case there is not intersection point
    double y = utils::trim(
      (((x - _x1) * (_y2 - _y1)) /
       (_x2 - _x1)) + _y1
    , 9, "exact");

    // Check if result is in values range
    if (utils::isBetween(y, _y1, _y2, "round")) {
      return Nullable<double>(y);
    }

    return Nullable<double>();
  }

  // Returns if line has given point
  bool Line::hasPoint(double x, double y) {
    if (!boundsHavePoint(x, y)) return 0;

    double m = utils::trim(
      (_y2 - _y1) / (_x2 - _x1),
    9, "exact");

    return (y - _y1) / (x - _x1) == m;
  }

  // Returns if given point is contained by the bounds aka cage of line
  bool Line::boundsHavePoint(double x, double y) {
    return utils::isBetween(x, _x1, _x2, "round") &&
           utils::isBetween(y, _y1, _y2, "round");
  }

  // line - line intersection method
  Nullable<Point> Line::getIntersection(Line line) {
    // Escape if lines are parallel
    if (!(((_x1 - _x2) * (line._y1 - line._y2)) -
          ((_y1 - _y2) * (line._x1 - line._x2))))
      return Nullable<Point>();

    // Intersection point formula
    double x = utils::trim(
      ((((_x1 * _y2) - (_y1 * _x2)) * (line._x1 - line._x2)) -
       ((_x1 - _x2) * ((line._x1 * line._y2) - (line._y1 * line._x2)))) /
      (((_x1 - _x2) * (line._y1 - line._y2)) - ((_y1 - _y2) *
        (line._x1 - line._x2)))
    , 9, "exact");
    double y = utils::trim(
      ((((_x1 * _y2) - (_y1 * _x2)) * (line._y1 - line._y2)) -
       ((_y1 - _y2) * ((line._x1 * line._y2) - (line._y1 * line._x2)))) /
      (((_x1 - _x2) * (line._y1 - line._y2)) - ((_y1 - _y2) *
        (line._x1 - line._x2)))
    , 9, "exact");

    if (utils::isBetween(x, _x1, _x2, "round") &&
        utils::isBetween(x, line._x1, line._x2, "round") &&
        utils::isBetween(y, _y1, _y2, "round") &&
        utils::isBetween(y, line._y1, line._y2, "round")) {
      return Nullable<Point>({ x, y });
    }

    return Nullable<Point>();
  }
}