"use strict";
/// <reference path = "IShape.ts" />
var Drawing;
(function (Drawing) {
    class Circle {
        draw() {
            console.log("Circle.draw()");
        }
    }
    Drawing.Circle = Circle;
})(Drawing || (Drawing = {}));
