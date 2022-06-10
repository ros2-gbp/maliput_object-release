// BSD 3-Clause License
//
// Copyright (c) 2022, Woven Planet. All rights reserved.
// Copyright (c) 2022, Toyota Research Institute. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include "maliput_object/api/bounding_region.h"

#include <memory>

#include <gtest/gtest.h>
#include <maliput/math/vector.h>

#include "maliput_object/test_utilities/mock.h"

namespace maliput {
namespace object {
namespace test {
namespace {

using maliput::math::Vector3;

// Tests API interface.
class BoundingRegionTest : public ::testing::Test {
 public:
  const bool kExpectedContains{true};
  const Vector3 kExpectedPosition{1., 2., 3.};
  const api::OverlappingType kExpectedOverlapping{api::OverlappingType::kContained};
  const std::unique_ptr<api::BoundingRegion<Vector3>> dut_ = std::make_unique<test_utilities::MockBoundingRegion>();
};

TEST_F(BoundingRegionTest, API) {
  test_utilities::MockBoundingRegion* mock_region{nullptr};
  ASSERT_NE(nullptr, mock_region = dynamic_cast<test_utilities::MockBoundingRegion*>(dut_.get()));

  EXPECT_CALL(*mock_region, do_position()).Times(1).WillOnce(::testing::ReturnRef(kExpectedPosition));
  EXPECT_CALL(*mock_region, DoContains(Vector3::Ones())).Times(1).WillOnce(::testing::Return(kExpectedContains));
  EXPECT_CALL(*mock_region, DoOverlaps(::testing::_)).Times(1).WillOnce(::testing::Return(kExpectedOverlapping));

  EXPECT_EQ(kExpectedPosition, dut_->position());
  EXPECT_EQ(kExpectedContains, dut_->Contains(Vector3::Ones()));
  EXPECT_EQ(kExpectedOverlapping, dut_->Overlaps(*dut_));
}

}  // namespace
}  // namespace test
}  // namespace object
}  // namespace maliput