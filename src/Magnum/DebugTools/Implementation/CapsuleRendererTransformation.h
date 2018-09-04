#ifndef Magnum_DebugTools_Implementation_ForceRendererTransformation_h
#define Magnum_DebugTools_Implementation_ForceRendererTransformation_h
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

#include <array>

#include "Magnum/DimensionTraits.h"
#include "Magnum/Magnum.h"
#include "Magnum/Math/Functions.h"
#include "Magnum/Math/Matrix3.h"
#include "Magnum/Math/Matrix4.h"

namespace Magnum { namespace DebugTools { namespace Implementation {

CORRADE_IGNORE_DEPRECATED_PUSH
template<UnsignedInt dimensions> std::array<MatrixTypeFor<dimensions, Float>, 3> capsuleRendererTransformation(const VectorTypeFor<dimensions, Float>& a, const VectorTypeFor<dimensions, Float>& b, Float radius);

template<> std::array<Matrix3, 3> capsuleRendererTransformation<2>(const Vector2& a, const Vector2& b, const Float radius) {
    /* Vector from capsule center to top hemisphere center */
    const Vector2 direction = 0.5f*(b - a);
    const Float length = direction.length();

    /* Capsule rotation and distance to caps after they are scaled to proper
       radius (if nonzero cylinder length) */
    Matrix3 rotation;
    Vector2 capDistance;
    if(length >= Math::TypeTraits<Float>::epsilon()) {
        rotation.up() = direction/length;
        rotation.right() = rotation.up().perpendicular();
        CORRADE_INTERNAL_ASSERT(rotation.right().isNormalized());

        capDistance = direction*(radius/length);
    }

    /* Scaling and translation of all parts */
    const auto rotationScaling = rotation*Matrix3::scaling(Vector2(radius));
    return {{
        Matrix3::translation(a+capDistance)*rotationScaling,
        Matrix3::translation(0.5f*(a + b))*rotation*Matrix3::scaling({radius, length}),
        Matrix3::translation(b-capDistance)*rotationScaling
    }};
}

template<> std::array<Matrix4, 3> capsuleRendererTransformation<3>(const Vector3& a, const Vector3& b, const Float radius) {
    /* Vector from capsule center to top hemisphere center */
    const Vector3 direction = 0.5f*(b - a);
    const Float length = direction.length();

    /* Capsule rotation and distance to caps after they are scaled to proper
       radius (if nonzero cylinder length) */
    Matrix4 rotation;
    Vector3 capDistance;
    if(length >= Math::TypeTraits<Float>::epsilon()) {
        const Vector3 directionNormalized = direction/length;
        const Float dot = Math::dot(directionNormalized, Vector3::zAxis());

        /* Direction is parallel to Z axis, special rotation case */
        if(Math::abs(dot) > 1.0f - Math::TypeTraits<Float>::epsilon()) {
            rotation.up() = dot*Vector3::zAxis();
            rotation.right() = Vector3::xAxis();
            rotation.backward() = -dot*Vector3::yAxis();

        /* Common case */
        } else {
            rotation.up() = directionNormalized;
            rotation.right() = Math::cross(rotation.up(), Vector3::zAxis()).normalized();
            rotation.backward() = Math::cross(rotation.right(), rotation.up());
            CORRADE_INTERNAL_ASSERT(rotation.up().isNormalized() && rotation.backward().isNormalized());
        }

        capDistance = directionNormalized*radius;
    }

    /* Scaling and translation of all parts */
    const auto rotationScaling = rotation*Matrix4::scaling(Vector3(radius));
    return {{
        Matrix4::translation(a+capDistance)*rotationScaling,
        Matrix4::translation(0.5f*(a + b))*rotation*Matrix4::scaling({radius, length, radius}),
        Matrix4::translation(b-capDistance)*rotationScaling
    }};
}
CORRADE_IGNORE_DEPRECATED_POP

}}}

#endif
