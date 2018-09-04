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

#include <Corrade/TestSuite/Tester.h>

#define _MAGNUM_DO_NOT_WARN_DEPRECATED_SHAPES

#include "Magnum/Magnum.h"
#include "Magnum/Math/Matrix4.h"
#include "Magnum/Shapes/Box.h"

namespace Magnum { namespace Shapes { namespace Test {

struct BoxTest: TestSuite::Tester {
    explicit BoxTest();

    void transformed();
};

BoxTest::BoxTest() {
    addTests({&BoxTest::transformed});
}

CORRADE_IGNORE_DEPRECATED_PUSH
void BoxTest::transformed() {
    const auto box = Shapes::Box3D(Matrix4::translation({1.0f, 2.0f, -3.0f}))
        .transformed(Matrix4::scaling({2.0f, -1.0f, 1.5f}));
    CORRADE_COMPARE(box.transformation(), Matrix4::scaling({2.0f, -1.0f, 1.5f})*Matrix4::translation({1.0f, 2.0f, -3.0f}));
}
CORRADE_IGNORE_DEPRECATED_POP

}}}

CORRADE_TEST_MAIN(Magnum::Shapes::Test::BoxTest)
