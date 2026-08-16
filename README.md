# TradingExchangeSystem

A from-scratch C++ trading exchange core — order representation, matching
engine, and (eventually) a benchmarked, concurrent order book — built to
understand and demonstrate the systems-level problems inside exchange
infrastructure: order lifecycle, price-time priority matching, latency, and
concurrency under contention.

> **Status: early-stage / actively building.** The `Order` model is in place;
> the matching engine, order book, and benchmarking harness are not yet
> implemented. See [`ROADMAP.md`](./ROADMAP.md) for the full build plan and
> current progress — that file is the source of truth for what's done vs.
> planned, kept up to date as work lands.

## Why this project

Most portfolio trading projects stop at "connects to an API and places
orders." This one is scoped at the exchange side instead: the matching logic,
data structures, and performance characteristics that sit underneath a
trading venue. The goal is a small, well-tested, benchmarked core rather than
a feature-complete platform.

## Current state

- `Order` — an immovable, non-copyable order value type (`Order.h`) capturing
  side (buy/sell), type (limit/market), time-in-force (GTC/IOC/FOK), price,
  quantity, remaining quantity, and a nanosecond-precision `steady_clock`
  timestamp for time-priority ordering.
- `main.cpp` — placeholder entry point; not yet wired to any matching logic.

Nothing below this line exists yet — it's the plan, not a claim:

- Order book (price-level aggregation, O(1) best bid/ask)
- Matching engine (price-time priority, partial fills)
- Concurrency model for concurrent order submission
- Benchmark harness reporting p50/p99 latency and throughput
- Tests

## Planned design

- **Language:** C++20, built with CMake.
- **Order book:** price levels keyed for O(1) best-bid/ask lookup, FIFO queue
  per price level for time priority.
- **Matching:** price-time priority; limit and market orders; IOC/FOK
  semantics honored at the matching layer (the `market_type` enum already
  models this).
- **Concurrency:** single-writer matching thread taking orders off a
  lock-free (or, as a first pass, mutex-guarded) MPSC queue — starting simple,
  then replacing the queue with a lock-free implementation once correctness is
  established and there's a benchmark to prove the swap actually helps.
- **Benchmarking:** a harness that replays a synthetic order stream and
  reports latency percentiles and sustained throughput, checked into the repo
  so results are reproducible rather than claimed.

## Build

```bash
# CMake setup not yet added — tracked in ROADMAP.md.
# Until then:
g++ -std=c++20 main.cpp -o main
./main
```

## Roadmap

Full task breakdown, in priority order, lives in
[`ROADMAP.md`](./ROADMAP.md).
