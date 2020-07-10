/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,
                2020 Vladimír Vondruš <mosra@centrum.cz>

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

#include <sstream>
#include <Corrade/TestSuite/Tester.h>
#include <Corrade/Utility/DebugStl.h>

#include "Magnum/Vk/DeviceProperties.h"

namespace Magnum { namespace Vk { namespace Test { namespace {

struct DevicePropertiesTest: TestSuite::Tester {
    explicit DevicePropertiesTest();

    void constructCopy();
    void constructMove();

    void debugDeviceType();
    void debugQueueFamilyPropertiesFlag();
    void debugQueueFamilyPropertiesFlags();
};

DevicePropertiesTest::DevicePropertiesTest() {
    addTests({&DevicePropertiesTest::constructCopy,
              &DevicePropertiesTest::constructMove,

              &DevicePropertiesTest::debugDeviceType,
              &DevicePropertiesTest::debugQueueFamilyPropertiesFlag,
              &DevicePropertiesTest::debugQueueFamilyPropertiesFlags});
}

void DevicePropertiesTest::constructCopy() {
    CORRADE_VERIFY(!(std::is_constructible<DeviceProperties, const DeviceProperties&>{}));
    CORRADE_VERIFY(!(std::is_assignable<DeviceProperties, const DeviceProperties&>{}));
}

void DevicePropertiesTest::constructMove() {
    CORRADE_VERIFY(std::is_nothrow_move_constructible<DeviceProperties>::value);
    CORRADE_VERIFY(std::is_nothrow_move_assignable<DeviceProperties>::value);
}

void DevicePropertiesTest::debugDeviceType() {
    std::ostringstream out;
    Debug{&out} << DeviceType::DiscreteGpu << DeviceType(-10007655);
    CORRADE_COMPARE(out.str(), "Vk::DeviceType::DiscreteGpu Vk::DeviceType(-10007655)\n");
}

void DevicePropertiesTest::debugQueueFamilyPropertiesFlag() {
    std::ostringstream out;
    Debug{&out} << QueueFlag::SparseBinding << QueueFlag(0xdeadcafe);
    CORRADE_COMPARE(out.str(), "Vk::QueueFlag::SparseBinding Vk::QueueFlag(0xdeadcafe)\n");
}

void DevicePropertiesTest::debugQueueFamilyPropertiesFlags() {
    std::ostringstream out;
    Debug{&out} << (QueueFlag::Compute|QueueFlag::Graphics) << QueueFlags{};
    CORRADE_COMPARE(out.str(), "Vk::QueueFlag::Graphics|Vk::QueueFlag::Compute Vk::QueueFlags{}\n");
}

}}}}

CORRADE_TEST_MAIN(Magnum::Vk::Test::DevicePropertiesTest)
