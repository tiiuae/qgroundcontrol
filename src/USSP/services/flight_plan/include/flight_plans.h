// AirMap Platform SDK
// Copyright © 2018-2023 AirMap, Inc. All rights reserved.
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

#ifndef USSP_FLIGHT_PLANS_H_
#define USSP_FLIGHT_PLANS_H_

#include <include/error.h>
#include <include/flight_plan.h>
#include <include/outcome.h>
#include <include/visibility.h>

#include <cstdint>
#include <functional>
#include <vector>

namespace ussp {

/// FlightPlans provides functionality for managing flight plans.
class USSP_EXPORT FlightPlans {
 public:
  /// ForId bundles up types to ease interaction with
  /// FlightPlans::for_id.
  struct USSP_EXPORT ForId {
    /// Parameters bundles up input parameters.
    struct USSP_EXPORT Parameters {
      FlightPlan::Id id;                    ///< Search for the flight with this id.
    };

    /// Result models the outcome of calling FlightPlans::for_id.
    using Result = Outcome<FlightPlan, Error>;
    /// Callback describes the function signature of the callback that is invoked
    /// when a call to FlightPlans::for_id finishes.
    using Callback = std::function<void(const Result&)>;
  };

  /// Create bundles up types to ease interaction with
  /// FlightPlans::create_by_point and FlightPlans::create_by_polygon.
  struct USSP_EXPORT Create {
    /// Parameters bundles up input parameters.
    struct Parameters {
      Pilot pilot;                         ///< The pilot responsible for the flight.
      Optional<Pilot::Aircraft> aircraft;  ///< The aircraft conducting the flight.
      float latitude;                      ///< The latitude component of the takeoff point in [°].
      float longitude;                     ///< The longitude component of the takeoff point in [°].
      float max_altitude;                  ///< The maximum altitude over the entire flight in [m].
      float min_altitude;                  ///< The minimum altitude over the entire flight in [m].
      float buffer;                        ///< The buffer in [m] around the geometry.
      Geometry geometry;                   ///< The geometry describing the flight.
      DateTime start_time;                 ///< Point in time when the flight will start/was started.
      DateTime end_time;                   ///< Point in time when the fligth will end.
      std::vector<RuleSet::Id> rulesets;   ///< RuleSets that apply to this flight plan.
      std::unordered_map<std::string, RuleSet::Feature::Value>
          features;  ///< Additional properties of the planned flight.
    };

    /// Result models the outcome of calling FlightPlans::create_by_polygon.
    using Result = Outcome<FlightPlan, Error>;
    /// Callback describes the function signature of the callback that is invoked
    /// when a call to FlightPlans::create_by_point or FlightPlans::create_by_polygon finishes.
    using Callback = std::function<void(const Result&)>;
  };

  /// Update bundles up types to ease interaction with
  /// FlightPlans::update.
  struct USSP_EXPORT Update {
    /// Parameters bundles up input parameters.
    struct USSP_EXPORT Parameters {
      FlightPlan flight_plan;  ///< The details of the plan that should be created with the USSP services.
    };
    /// Result models the outcome of calling FlightPlans::update.
    using Result = Outcome<FlightPlan, Error>;
    /// Callback describes the function signature of the callback that is invoked
    /// when a call to FlightPlans::update finishes.
    using Callback = std::function<void(const Result&)>;
  };

  /// Delete bundles up types to ease interaction with
  /// FlightPlans::delete_.
  struct USSP_EXPORT Delete {
    /// Parameters bundles up input parameters.
    struct USSP_EXPORT Parameters {
      FlightPlan::Id id;                    ///< Id of the flight plan that should be deleted.
    };

    /// Response models the response from the USSP services.
    struct USSP_EXPORT Response {
      FlightPlan::Id id;  ///< Id of the flight plan that was deleted.
    };

    /// Result models the outcome of calling FlightPlans::delete_flight.
    using Result = Outcome<Response, Error>;
    /// Callback describes the function signature of the callback that is
    /// invoked when a call to FlightPlans::delete_flight finishes.
    using Callback = std::function<void(const Result&)>;
  };

  /// RenderBriefing bundles up types to ease interaction with
  /// FlightPlans::render_briefing.
  struct USSP_EXPORT RenderBriefing {
    /// Parameters bundles up input parameters.
    struct USSP_EXPORT Parameters {
      FlightPlan::Id id;                    ///< Id of the flight plan that should be rendered as a briefing.
    };
    /// Result models the outcome of calling FlightPlans::submit.
    using Result = Outcome<FlightPlan::Briefing, Error>;
    /// Callback describes the function signature of the callback that is invoked
    /// when a call to FlightPlans::submit finishes.
    using Callback = std::function<void(const Result&)>;
  };

  /// Submit bundles up types to ease interaction with
  /// FlightPlans::submit.
  struct USSP_EXPORT Submit {
    /// Parameters bundles up input parameters.
    struct USSP_EXPORT Parameters {
      FlightPlan::Id id;                    ///< Id of the flight plan that should be submitted.
    };
    /// Result models the outcome of calling FlightPlans::submit.
    using Result = Outcome<FlightPlan, Error>;
    /// Callback describes the function signature of the callback that is invoked
    /// when a call to FlightPlans::submit finishes.
    using Callback = std::function<void(const Result&)>;
  };

  /// for_id queries the USSP services for detailed information about
  /// a flight plan identified by a UUID and reports back results to 'cb'.
  virtual void for_id(const ForId::Parameters& parameters, const ForId::Callback& cb) = 0;

  /// create_by_polygon creates a flight plan for 'parameters' and reports
  /// results back to 'cb'.
  virtual void create_by_polygon(const Create::Parameters& parameters, const Create::Callback& cb) = 0;

  /// update updates a flight plan identified by 'parameters' and reports
  /// results back to 'cb'.
  virtual void update(const Update::Parameters& parameters, const Update::Callback& cb) = 0;

  /// delete deletes a flight plan identified by 'parameters' and reports
  /// results back to 'cb'.
  virtual void delete_(const Delete::Parameters& parameters, const Delete::Callback& cb) = 0;

  /// render_briefing requests rendering a briefing for a flight plan identified by 'parameters' and reports
  /// results back to 'cb'.
  virtual void render_briefing(const RenderBriefing::Parameters& parameters, const RenderBriefing::Callback& cb) = 0;

  /// submit submits a flight plan identified by 'parameters' and reports
  /// results back to 'cb'.
  virtual void submit(const Submit::Parameters& parameters, const Submit::Callback& cb) = 0;

 protected:
  /// @cond
  FlightPlans() = default;
  /// @endcond
};

}  // namespace ussp

#endif  // USSP_FLIGHT_PLANS_H_
