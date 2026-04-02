"use strict";
/// <reference path = "IShape.ts" />
var Drawing;
(function (Drawing) {
    class Triangle {
        draw() {
            console.log("Drawing Triangle");
        }
    }
    Drawing.Triangle = Triangle;
})(Drawing || (Drawing = {}));
