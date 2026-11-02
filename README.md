# Yarin's Ultimate Aim Trainer

A comprehensive BakkesMod aim and shooting mechanics trainer that transforms any standard Rocket League arena into an advanced target range without requiring custom workshop maps.

---

## Features

- **Multi-Surface Targets:** Practice shooting on the standard **Goal Net**, the entire **Backboard**, or either **Side Wall**.
- **Coco's Workshop Map Integration:** Full recreation of Coco's Aim Trainer routines:
  - Vertical Drop & Bounce (with authentic car-to-ball runway spacing).
  - High Aerial Arcs floating back toward the car.
  - Quick ground redirect rolls.
  - Close, Middle, Far, or Random wall distance presets.
- **Physical Reachability & Ballistic Intercepts:**
  - Dynamic trajectory generation solving for Rocket League gravity ($-650\text{ UU/s}^2$).
  - Reachability validation ensuring high-speed shots are always physically playable relative to car position and reaction time.
  - Tangential net offsets preventing untouched balls from scoring on their own.
- **Shot Pack Merging:** Mix and match active shot archetypes with multi-select checkboxes:
  - *Redirects* (originating from behind/over the car).
  - *Infield Crosses* (flank sweeps).
  - *Clearing Pops* (downfield bounces).
  - *Backboard Rebound Reads*.
- **Configurable Shot Difficulty:** Choose between *Easy* (shallow deflection angles), *Medium*, *Hard* (acute redirects and fast aerials), or *Any*.
- **Impact Speed Gating:** Enforce clean, powerful contact by setting minimum and maximum target entry speeds (up to 200+ KPH uncapped).
- **HUD & High-Girth Trajectory Laser:**
  - Multi-pass thick neon laser beam with speed callouts that automatically cull when looking away from the target plane.
  - Dynamic background sizing that scales cleanly without clipping text.
  - Full streak and attempt tracking.
- **One-Button Shot Lock:** Instantly freeze and repeat any generated shot setup via the native controller Use Item button or console binding.

---

## Installation

1. Download the latest `YarinsUltimateAimTrainer.zip` from [Releases](../../releases) or [BakkesPlugins](https://bakkesplugins.com/).
2. Extract `YarinsUltimateAimTrainer.dll` to:
   ```text
   %appdata%\bakkesmod\bakkesmod\plugins\