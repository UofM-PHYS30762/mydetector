/* Copyright (c) 2026, Haoze Pang and contributors.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials provided
 *        with the distribution.
 *
 *     * The name of the authors of this software may not be used to endorse or
 *     promote products derived
 *        from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <gdetector/gdetector.h>
#include <gtest/gtest.h>

#include <iostream>
#include <string>

class SourceTest : public testing::Test {
protected:
  SourceTest() {
    source1_.set_activity(kActivity1_);
    source1_.set_name(kName1_);
    source1_.set_date(timestamp1_);
  }

  const std::string kName1_ = "Na-22";
  const std::string kName2_ = "Balalalalalala";
  const std::string kName3_ = "Pu-268";
  std::vector<std::string> alternative_sources = {kName3_, "Am-234"};
  time_t timestamp1_ = time(nullptr);
  const double kActivity1_ = 98.7899;

  detector::Source source1_{};
  detector::Source source2_ =
      detector::Source(kName1_, timestamp1_, kActivity1_);
};

TEST_F(SourceTest, TestGetSet) {
  EXPECT_EQ(source1_.name(), kName1_);
  EXPECT_EQ(source1_.activity(), kActivity1_);
  EXPECT_EQ(source1_.date(), timestamp1_);
}

TEST_F(SourceTest, TestPrint) {
  std::cout << source1_ << std::endl;
  std::cout << source2_ << std::endl;
}

TEST_F(SourceTest, TestInputValidation) {
  EXPECT_THROW(source1_.set_name(kName3_), std::invalid_argument);

  // Changing available source list
  detector::Source::set_available_sources(alternative_sources);
  source1_.set_name(kName3_);

  // Revert to default to avoid corruption
  detector::Source::set_available_sources({"Na-22", "Cs-136", "Co-92"});
}
