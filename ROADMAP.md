# Roadmap

Task list for TradingExchangeSystem, in the order they're intended to be
tackled. Check items off as they land; keep this file honest — it's meant to
show real progress, not a wishlist.

## Phase 0 — Foundations
- [x] `Order` value type: side, type, time-in-force, price, quantity,
      remaining quantity, timestamp.
- [ ] CMake build (`CMakeLists.txt`), replacing the ad-hoc `g++` invocation.
- [ ] Basic unit test setup (Catch2 or GoogleTest).
- [ ] CI workflow (GitHub Actions): build + test on push.

## Phase 1 — Order book
- [ ] Price-level data structure with O(1) best-bid/O(1) best-ask lookup.
- [ ] FIFO queue per price level (time priority within a price).
- [ ] Add / cancel / amend order operations.
- [ ] Unit tests: book stays correctly ordered under randomized add/cancel
      sequences.

## Phase 2 — Matching engine
- [ ] Price-time priority matching for limit orders.
- [ ] Market order matching (sweep book, no resting).
- [ ] Partial fills and remaining-quantity tracking.
- [ ] IOC semantics (fill what's available immediately, cancel the rest).
- [ ] FOK semantics (fill completely or cancel, no partials).
- [ ] Deterministic replay tests: given a fixed order sequence, matching
      output is byte-for-byte reproducible.

## Phase 3 — Concurrency
- [ ] Single-writer matching thread reading from an MPSC order queue
      (mutex-guarded first pass).
- [ ] Correctness tests under concurrent submission (ThreadSanitizer clean).
- [ ] Replace the mutex-guarded queue with a lock-free MPSC queue; only after
      a benchmark shows it matters.

## Phase 4 — Benchmarking
- [ ] Synthetic order stream generator (configurable order rate, price
      distribution, cancel ratio).
- [ ] Benchmark harness reporting p50/p90/p99 latency (submit → matched) and
      sustained throughput (orders/sec).
- [ ] Results checked into `BENCHMARKS.md` with the machine spec they were
      run on, so numbers are reproducible and comparable across changes.

## Phase 5 — Stretch goals
- [ ] Minimal FIX 4.2/4.4 message parsing for order entry (`NewOrderSingle`,
      `OrderCancelRequest`).
- [ ] L2 market data feed output (aggregated book snapshots/deltas).
- [ ] A toy market-making strategy running against the engine, with PnL
      tracking, as a demonstration client.

---

**Last updated:** 2026-08-16
