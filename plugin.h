#pragma once

#include "GuiBase.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include <chrono>
#include <random>

enum class TargetSurface { GoalNet = 0, BackWall, LeftWall, RightWall };
enum class TargetSnap { None = 0, Top, Bottom, Left, Right };
enum class ScenarioMode { StationaryGround = 0, StationaryAerial, MovingPack, CocoDrop, AllRandom };
enum class CocoDistance { Close = 0, Middle, Far, Random };
enum class CocoDeliveryMode { VerticalDrop = 0, AerialToCar, RollToCar };

class CustomAimTrainer : public BakkesMod::Plugin::BakkesModPlugin, public SettingsWindowBase
{
public:
    bool pluginEnabled = true;

    // Target Selection
    TargetSurface targetSurface = TargetSurface::GoalNet;
    TargetSnap snapMode = TargetSnap::None;

    // Target Dimensions [Min, Max]
    float targetWidthMin = 350.0f;
    float targetWidthMax = 650.0f;
    float targetHeightMin = 220.0f;
    float targetHeightMax = 420.0f;

    // Active Target Placement
    float activeTargetWidth = 500.0f;
    float activeTargetHeight = 350.0f;
    Vector currentTargetCenter = Vector(0.0f, 5120.0f, 320.0f);
    float targetGoalY = 5120.0f;

    // Target Visuals
    float targetColorRGBA[4] = { 0.0f, 1.0f, 0.7f, 1.0f };
    bool drawCenterReticle = true;
    bool drawTargetFill = true;
    float borderThickness = 4.0f;

    // Trajectory Laser Line Visuals
    float trajectoryColorRGBA[4] = { 1.0f, 0.9f, 0.1f, 1.0f };
    float trajectoryWidth = 5.0f;
    bool showTrajectoryLine = true;

    // HUD
    float hudScale = 1.8f;
    float hudColorRGBA[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float hudPosX = 40.0f;
    float hudPosY = 50.0f;
    bool hudShowBackground = true;

    // Required Target Impact Speed (KPH)
    float requiredMinHitKph = 0.0f;
    float requiredMaxHitKph = 200.0f;

    // 7 Category Toggles (Shot Pack Merging)
    bool enableRedirects = true;
    bool enableCrosses = true;
    bool enableClearingPops = true;
    bool enableBackboardReads = true;
    bool enableCatchAndDribble = true;
    bool enableRollingStrike = true;
    bool enableLoftedAerial = true;

    // Coco Specific Configuration
    CocoDistance cocoDistance = CocoDistance::Middle;
    CocoDeliveryMode cocoDelivery = CocoDeliveryMode::VerticalDrop;

    // General Car & Ball Spawning Field Bounds
    float carGoalDistMin = 1800.0f;
    float carGoalDistMax = 4200.0f;
    float carMaxLateralX = 1800.0f;

    // General Ball Spawn Offsets
    float ballDistXYMin = 800.0f;
    float ballDistXYMax = 1600.0f;
    float ballHeightMin = 93.0f;
    float ballHeightMax = 500.0f;

    // General Initial Velocity (KPH)
    float minKph = 45.0f;
    float maxKph = 85.0f;

    // Rules
    bool infiniteShotTime = false;
    float shotTimeout = 6.0f;
    bool failOnGroundTouch = false;
    int maxBackwallHits = 1;
    bool infiniteBackwallHits = true;

    // Scenario
    ScenarioMode scenarioMode = ScenarioMode::MovingPack;
    bool lockCurrentShot = false;

    // Cached Shot State
    Vector activeBallPos = Vector(0.0f, 0.0f, 93.0f);
    Vector activeBallVel = Vector(0.0f, 0.0f, 0.0f);
    Vector activeCarPos = Vector(0.0f, 0.0f, 20.0f);
    Rotator activeCarRot = Rotator(0, 0, 0);
    float activeBallKph = 0.0f;
    bool isStationaryAerial = false;
    bool isCocoScenario = false;

    // Runtime Flags
    bool waitingForPlayerInput = true;
    bool playerHasTouchedBall = false;
    bool shotActive = false;
    bool hasLeftGroundAfterHit = false;
    bool requestImmediateReset = false;
    int resetDebounceTicks = 0;
    int backwallHitCount = 0;
    int backwallCooldownTicks = 0;
    float remainingTime = 6.0f;
    int settleTicks = 0;
    Vector lastBallVel = Vector(0.0f, 0.0f, 0.0f);

    // Hit / Miss Flash Feedback
    int flashFeedbackTicks = 0;
    bool lastShotWasSuccess = false;

    // Stats
    int currentStreak = 0;
    int bestStreak = 0;
    int totalHits = 0;
    int totalAttempts = 0;

    std::mt19937 rng;

    virtual void onLoad() override;
    virtual void onUnload() override;

    void RegisterPersistentCvars();
    void LoadSettingsFromCvars();
    void SaveSettingsToCvars();
    void ResetToDefaults();

    void ClampRangesToSurface();
    void DetectTargetGoal(ServerWrapper& server);
    void GenerateNewShot(ServerWrapper& server);
    void ExecuteReset(bool isSuccess);
    void RecalculateTargetGeometry();
    void OnPhysicsTick();
    void CheckBackwallHit(const Vector& bPos, const Vector& bVel);
    void RenderOverlay(CanvasWrapper canvas);

    void RenderSettings() override;
    std::string GetPluginName() override;
    void SetImGuiContext(uintptr_t ctx) override;
};