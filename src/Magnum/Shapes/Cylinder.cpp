/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#define _MAGNUM_DO_NOT_WARN_DEPRECATED_SHAPES

#include "Cylinder.h"

#include "Magnum/Magnum.h"
#include "Magnum/Math/Distance.h"
#include "Magnum/Math/Functions.h"
#include "Magnum/Math/Matrix3.h"
#include "Magnum/Math/Matrix4.h"
#include "Magnum/Shapes/Point.h"
#include "Magnum/Shapes/Sphere.h"

namespace Magnum { namespace Shapes {

CORRADE_IGNORE_DEPRECATED_PUSH
template<UnsignedInt dimensions> Cylinder<dimensions> Cylinder<dimensions>::transformed(const MatrixTypeFor<dimensions, Float>& matrix) const {
    return Cylinder<dimensions>(matrix.transformPoint(_a), matrix.transformPoint(_b), matrix.uniformScaling()*_radius);
}

template<UnsignedInt dimensions> bool Cylinder<dimensions>::operator%(const Point<dimensions>& other) const {
    return Math::Distance::linePointSquared(_a, _b, other.position()) <
        Math::pow<2>(_radius);
}

template<UnsignedInt dimensions> bool Cylinder<dimensions>::operator%(const Sphere<dimensions>& other) const {
    return Math::Distance::linePointSquared(_a, _b, other.position()) <
        Math::pow<2>(_radius+other.radius());
}

#ifndef DOXYGEN_GENERATING_OUTPUT
template class MAGNUM_SHAPES_EXPORT Cylinder<2>;
template class MAGNUM_SHAPES_EXPORT Cylinder<3>;
#endif
CORRADE_IGNORE_DEPRECATED_POP

}}
