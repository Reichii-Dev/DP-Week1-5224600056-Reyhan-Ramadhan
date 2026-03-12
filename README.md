# Task 1 — Balatro-Like Run Loop

## How to Build & Run

Open Visual Studio 2022, create a Console Application project, add all `.h` and `.cpp` files from this folder, then build and run.

---

## Architecture Overview

| Class | Role |
|---|---|
| `RunSession` | Controls game loop, enforces phase order (invariant) |
| `IInputGenerator` | Interface for generating turn input |
| `FixedInputGenerator` | Always returns value 3 |
| `RandomInputGenerator` | Returns random value 1-10 (Modification 1) |
| `IScoringRule` | Interface for computing base score |
| `SimpleScoring` | Base score = input value |
| `IRewardRule` | Interface for computing reward from base score |
| `EqualRewardRule` | Reward equals base score |
| `BonusRewardRule` | Reward varies by round — odd: +2, even: x2 (Modification 2) |
| `ShopSystem` | Offers a purchasable bonus each round |

---

## Reflection

### 1. What is the invariant structure in your program?

The invariant structure is the **phase order** enforced inside `RunSession::run()`. The six phases must always execute in this exact sequence every round:

1. Generate input
2. Compute base score
3. Compute reward
4. Update money
5. Shop phase
6. Advance round

This order is protected because all game logic lives **outside** of `RunSession`. The session only calls interfaces — it never contains scoring, reward, or input logic itself. No matter how behavior changes, this structural order remains untouched.

### 2. Which parts are mutable?

The mutable parts are the concrete implementations injected into `RunSession`:

- **Input generation** — `FixedInputGenerator` or `RandomInputGenerator`
- **Scoring logic** — `SimpleScoring` (or any new `IScoringRule`)
- **Reward logic** — `EqualRewardRule` or `BonusRewardRule`
- **Shop behavior** — `ShopSystem` can be extended independently

These can all be swapped, extended, or replaced without modifying `RunSession` at all.

### 3. When you replaced the InputGenerator, why didn't RunSession change?

Because `RunSession` only depends on the `IInputGenerator` **interface**, not on any concrete class. It calls `inputGen_->generate()` — it does not care whether the result comes from a fixed value or a random number. The swap happens entirely in `main.cpp` where we change `FixedInputGenerator` to `RandomInputGenerator`. `RunSession.h` was not touched.

This is the core benefit of **programming to an interface**: the caller is decoupled from the implementation.

### 4. What would happen if scoring logic was placed inside RunSession?

If scoring logic was hardcoded inside `RunSession`, then every time we wanted to change how scores are calculated — for example, switching from sum scoring to high-card scoring — we would be forced to modify `RunSession` itself. This breaks the invariant, because a class that is supposed to only control structure is now also responsible for behavior. It would also make the system harder to test, extend, and maintain. Any change to scoring logic risks accidentally breaking the phase order or money tracking.

---

## AI Usage Disclosure

AI (Claude by Anthropic) was used as a learning assistant to explain interface design, dependency injection, and invariant vs mutable architecture concepts. All code was reviewed and understood by the student before submission.
