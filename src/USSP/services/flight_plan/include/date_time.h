// AirMap Platform SDK
// Copyright © 2018 AirMap, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef USSP_DATE_TIME_H_
#define USSP_DATE_TIME_H_

#include <include/visibility.h>
#include <cstdint>

#include <memory>
#include <string>

namespace ussp {

class DateTime;
template <typename Tag>
class Duration;

namespace detail {
class Duration;
}  // namespace detail

namespace tag {

struct USSP_EXPORT Hours {};
struct USSP_EXPORT Minutes {};
struct USSP_EXPORT Seconds {};
struct USSP_EXPORT Milliseconds {};
struct USSP_EXPORT Microseconds {};

}  // namespace tag

using Hours        = Duration<tag::Hours>;
using Minutes      = Duration<tag::Minutes>;
using Seconds      = Duration<tag::Seconds>;
using Milliseconds = Duration<tag::Milliseconds>;
using Microseconds = Duration<tag::Microseconds>;

/// Clock marks the reference for time measurements.
class USSP_EXPORT Clock {
 public:
  static DateTime universal_time();
  static DateTime local_time();
};

namespace boost_iso {

USSP_EXPORT DateTime datetime(const std::string &iso_time);
USSP_EXPORT std::string to_iso_string(const DateTime &);

}  // namespace boost_iso

/// DateTime marks a specific point in time, in reference to Clock.
class USSP_EXPORT DateTime {
 public:
  DateTime();
  ~DateTime();
  DateTime(DateTime const &);
  DateTime(DateTime &&);
  DateTime &operator=(const DateTime &);
  DateTime &operator=(DateTime &&);

  DateTime operator+(const detail::Duration &) const;
  Microseconds operator-(const DateTime &) const;
  bool operator==(const DateTime &) const;
  bool operator!=(const DateTime &) const;

  friend std::istream &operator>>(std::istream &, DateTime &);
  friend std::ostream &operator<<(std::ostream &, const DateTime &);

  DateTime date() const;
  Microseconds time_of_day() const;

 private:
  struct Impl;
  std::unique_ptr<Impl> impl;

  explicit DateTime(std::unique_ptr<Impl> &&);
  friend DateTime Clock::universal_time();
  friend DateTime Clock::local_time();
  friend DateTime boost_iso::datetime(const std::string &iso_time);
  friend std::string boost_iso::to_iso_string(const DateTime &datetime);
};

USSP_EXPORT Hours hours(std::int64_t raw);
USSP_EXPORT Minutes minutes(std::int64_t raw);
USSP_EXPORT Seconds seconds(std::int64_t raw);
USSP_EXPORT Milliseconds milliseconds(std::int64_t raw);
USSP_EXPORT Microseconds microseconds(std::int64_t raw);

namespace detail {

class USSP_EXPORT Duration {
 public:
  Duration();
  ~Duration();
  Duration(Duration const &old);
  Duration &operator=(const Duration &);

  uint64_t total_seconds() const;
  uint64_t total_milliseconds() const;
  uint64_t total_microseconds() const;

  uint64_t hours() const;

 private:
  struct Impl;
  std::unique_ptr<Impl> impl;

  friend DateTime DateTime::operator+(const detail::Duration &) const;
  friend Microseconds DateTime::operator-(const DateTime &) const;
  friend Microseconds DateTime::time_of_day() const;

  friend Hours ussp::hours(std::int64_t raw);
  friend Minutes ussp::minutes(std::int64_t raw);
  friend Seconds ussp::seconds(std::int64_t raw);
  friend Milliseconds ussp::milliseconds(std::int64_t raw);
  friend Microseconds ussp::microseconds(std::int64_t raw);
};

}  // namespace detail

template <typename Tag>
class USSP_EXPORT Duration : public detail::Duration {};

/// milliseconds_since_epoch returns the milliseconds that elapsed since the UNIX epoch.
USSP_EXPORT uint64_t milliseconds_since_epoch(const DateTime &dt);
/// microseconds_since_epoch returns the microseconds that elapsed since the UNIX epoch.
USSP_EXPORT uint64_t microseconds_since_epoch(const DateTime &dt);
/// from_seconds_since_epoch returns a DateTime.
USSP_EXPORT DateTime from_seconds_since_epoch(const Seconds &s);
/// from_milliseconds_since_epoch returns a DateTime.
USSP_EXPORT DateTime from_milliseconds_since_epoch(const Milliseconds &ms);
/// from_microseconds_since_epoch returns a DateTime.
USSP_EXPORT DateTime from_microseconds_since_epoch(const Microseconds &us);

// moves the datetime forward to the specified hour
USSP_EXPORT DateTime move_to_hour(const DateTime &dt, uint64_t hour);

namespace iso8601 {

/// parse parses a DateTime instance from the string s in iso8601 format.
USSP_EXPORT DateTime parse(const std::string &s);
/// generate returns a string in iso8601 corresponding to 'dt'.
USSP_EXPORT std::string generate(const DateTime &dt);

}  // namespace iso8601

USSP_EXPORT std::ostream &operator<<(std::ostream &to, const detail::Duration &from);

}  // namespace uspp

#endif  // USSP_DATE_TIME_H_
