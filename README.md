# Aura

Aura is an Unreal Engine action RPG project built around the Gameplay Ability System. The project combines C++ gameplay systems with Blueprint-authored content for abilities, enemies, UI, input, pickups, and level setup.

## Project Status

This repository contains an in-development Unreal project. The main gameplay work currently includes:

- Gameplay Ability System setup for player and enemy characters
- Attribute sets, gameplay effects, damage execution, cooldown and cost data
- Firebolt, summon, melee, ranged, and hit reaction ability foundations
- Attribute menu, spell menu, overlay HUD, floating damage text, health, mana, XP, and spell UI widgets
- Enemy AI assets, StateTree behavior, EQS helpers, and enemy class data
- Enhanced Input actions and input configuration
- Dungeon map, character/enemy assets, VFX, SFX, pickups, and gameplay data tables

## Requirements

- Unreal Engine 5.7
- Visual Studio 2022 or Rider with C++ toolchain support
- Windows development environment for the current project setup

The `.uproject` enables these Unreal modules/plugins:

- GameplayAbilities
- EnhancedInput
- UMG
- AIModule
- MotionWarping
- StateTree
- GameplayStateTree
- StateGraph

## Getting Started

1. Clone the repository.
2. Open `Aura.uproject` with Unreal Engine 5.7.
3. If prompted, rebuild missing modules.
4. Open the project in the editor and use the configured startup or dungeon maps from `Content/Maps`.

If IDE files are missing, regenerate project files from the `.uproject` context menu or from Unreal Editor.

## Repository Layout

```text
Config/     Project and gameplay tag configuration
Content/    Unreal assets, Blueprints, maps, VFX, SFX, UI, and data assets
Data/       Source data tables used by gameplay systems
Plugins/    Project plugins
Source/     Aura C++ runtime module
```

## Generated Files

Unreal-generated folders such as `Binaries/`, `Intermediate/`, `Saved/`, and `DerivedDataCache/` are ignored for new files. They can be regenerated locally by Unreal Engine and should not be required to use the project.

## Notes

This project is gameplay-focused and currently under active development. Blueprint assets and C++ classes are expected to evolve together, especially around the Gameplay Ability System, character attributes, UI widget controllers, and enemy AI.
