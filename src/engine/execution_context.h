// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "../generators.h"
#include "fixed_state_pool.h"
#include "step_plan.h"

namespace Generators {

class PagedCacheReservation;

struct ExecutionContext {
  explicit ExecutionContext(const StepPlan* plan = nullptr)
      : plan{plan},
        run_options{OrtRunOptions::Create()} {}

  const StepPlan* plan{};
  PagedCacheReservation* cache_reservation{};
  // Fixed decoder-state resources for this step, in scheduled request row order. Empty when the
  // model has no fixed groups. HybridDecoderIO binds these gathered inputs and staged outputs
  // alongside the packed variable-length inputs.
  std::span<const FixedStateSlotHandle> fixed_state_slots;
  std::span<const FixedStateBinding> fixed_state_bindings;
  size_t fixed_state_staging_bytes{};
  std::unique_ptr<OrtRunOptions> run_options;
  size_t block_table_columns{};
};

}  // namespace Generators
