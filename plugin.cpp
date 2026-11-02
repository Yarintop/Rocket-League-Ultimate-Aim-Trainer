#include "pch.h"
#include "plugin.h"
#include "IMGUI/imgui.h"
#include "imgui/imgui_rangeslider.h"

BAKKESMOD_PLUGIN(CustomAimTrainer, "Yarin's Ultimate Aim Trainer", "1.0", PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

std::string CustomAimTrainer::GetPluginName() {
    return "Yarin's Ultimate Aim Trainer";
}

void CustomAimTrainer::SetImGuiContext(uintptr_t ctx) {
    ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

void CustomAimTrainer::RegisterPersistentCvars() {
    cvarManager->registerCvar("cat_enabled", "1", "Enable Custom Aim Trainer", true, true, 0, true, 1);
    cvarManager->registerCvar("cat_surface", "0", "Target Surface", true, true, 0, true, 3);
    cvarManager->registerCvar("cat_snap", "0", "Target Snap Mode", true, true, 0, true, 4);

    cvarManager->registerCvar("cat_w_min", "350.0", "Target Min Width", true, true, 100.0f, true, 7000.0f);
    cvarManager->registerCvar("cat_w_max", "650.0", "Target Max Width", true, true, 100.0f, true, 7000.0f);
    cvarManager->registerCvar("cat_h_min", "220.0", "Target Min Height", true, true, 80.0f, true, 1900.0f);
    cvarManager->registerCvar("cat_h_max", "420.0", "Target Max Height", true, true, 80.0f, true, 1900.0f);

    cvarManager->registerCvar("cat_col_r", "0.0", "Target Color R", true, true, 0.0f, true, 1.0f);
    cvarManager->registerCvar("cat_col_g", "1.0", "Target Color G", true, true, 0.0f, true, 1.0f);
    cvarManager->registerCvar("cat_col_b", "0.7", "Target Color B", true, true, 0.0f, true, 1.0f);
    cvarManager->registerCvar("cat_col_a", "1.0", "Target Color A", true, true, 0.0f, true, 1.0f);

    cvarManager->registerCvar("cat_reticle", "1", "Draw Center Reticle", true, true, 0, true, 1);
    cvarManager->registerCvar("cat_fill", "1", "Draw Translucent Target Tint", true, true, 0, true, 1);
    cvarManager->registerCvar("cat_border", "4.0", "Border Thickness", true, true, 1.0f, true, 8.0f);

    cvarManager->registerCvar("cat_traj_show", "1", "Show Trajectory Line", true, true, 0, true, 1);
    cvarManager->registerCvar("cat_traj_width", "5.0", "Trajectory Line Width", true, true, 1.0f, true, 15.0f);
    cvarManager->registerCvar("cat_traj_col_r", "1.0", "Trajectory Color R", true, true, 0.0f, true, 1.0f);
    cvarManager->registerCvar("cat_traj_col_g", "0.9", "Trajectory Color G", true, true, 0.0f, true, 1.0f);
    cvarManager->registerCvar("cat_traj_col_b", "0.1", "Trajectory Color B", true, true, 0.0f, true, 1.0f);
    cvarManager->registerCvar("cat_traj_col_a", "1.0", "Trajectory Color A", true, true, 0.0f, true, 1.0f);

    cvarManager->registerCvar("cat_hud_scale", "1.8", "HUD Text Scale", true, true, 0.8f, true, 3.5f);
    cvarManager->registerCvar("cat_hud_bg", "1", "HUD Background Plate", true, true, 0, true, 1);
    cvarManager->registerCvar("cat_hud_x", "40.0", "HUD Pos X", true, true, 0.0f, true, 3840.0f);
    cvarManager->registerCvar("cat_hud_y", "50.0", "HUD Pos Y", true, true, 0.0f, true, 2160.0f);

    cvarManager->registerCvar("cat_hud_col_r", "1.0", "HUD Color R", true, true, 0.0f, true, 1.0f);
    cvarManager->registerCvar("cat_hud_col_g", "1.0", "HUD Color G", true, true, 0.0f, true, 1.0f);
    cvarManager->registerCvar("cat_hud_col_b", "1.0", "HUD Color B", true, true, 0.0f, true, 1.0f);
    cvarManager->registerCvar("cat_hud_col_a", "1.0", "HUD Color A", true, true, 0.0f, true, 1.0f);

    cvarManager->registerCvar("cat_req_kph_min", "0.0", "Required Minimum Target Hit KPH", true, true, 0.0f, true, 200.0f);
    cvarManager->registerCvar("cat_req_kph_max", "200.0", "Required Maximum Target Hit KPH", true, true, 0.0f, true, 200.0f);

    cvarManager->registerCvar("cat_diff", "0", "Shot Difficulty (0=Any, 1=Easy, 2=Med, 3=Hard)", true, true, 0, true, 3);

    cvarManager->registerCvar("cat_cat_redirects", "1", "Enable Redirect Shots", true, true, 0, true, 1);
    cvarManager->registerCvar("cat_cat_crosses", "1", "Enable Cross Passes", true, true, 0, true, 1);
    cvarManager->registerCvar("cat_cat_pops", "1", "Enable Clearing Pops", true, true, 0, true, 1);
    cvarManager->registerCvar("cat_cat_backboard", "1", "Enable Backboard Rebound Reads", true, true, 0, true, 1);

    cvarManager->registerCvar("cat_coco_dist", "1", "Coco Wall Distance Option", true, true, 0, true, 3);
    cvarManager->registerCvar("cat_coco_mode", "0", "Coco Delivery Mode", true, true, 0, true, 2);

    cvarManager->registerCvar("cat_car_dist_min", "1800.0", "Car Distance From Goal Min", true, true, 1000.0f, true, 5500.0f);
    cvarManager->registerCvar("cat_car_dist_max", "4200.0", "Car Distance From Goal Max", true, true, 1000.0f, true, 5500.0f);
    cvarManager->registerCvar("cat_car_lat_x", "1800.0", "Car Max Lateral Spread X", true, true, 0.0f, true, 3000.0f);

    cvarManager->registerCvar("cat_dist_min", "800.0", "Ball Distance Min", true, true, 300.0f, true, 4000.0f);
    cvarManager->registerCvar("cat_dist_max", "1600.0", "Ball Distance Max", true, true, 300.0f, true, 4000.0f);
    cvarManager->registerCvar("cat_height_min", "93.0", "Ball Height Min", true, true, 93.0f, true, 1500.0f);
    cvarManager->registerCvar("cat_height_max", "500.0", "Ball Height Max", true, true, 93.0f, true, 1500.0f);

    cvarManager->registerCvar("cat_speed_min", "35.0", "Ball Min KPH", true, true, 10.0f, true, 150.0f);
    cvarManager->registerCvar("cat_speed_max", "85.0", "Ball Max KPH", true, true, 10.0f, true, 150.0f);

    cvarManager->registerCvar("cat_inf_time", "0", "Infinite Shot Time", true, true, 0, true, 1);
    cvarManager->registerCvar("cat_timeout", "6.0", "Shot Timeout Seconds", true, true, 3.0f, true, 30.0f);
    cvarManager->registerCvar("cat_fail_ground", "0", "Fail on Ground Touch", true, true, 0, true, 1);
    cvarManager->registerCvar("cat_inf_backwall", "1", "Infinite Backwall Bounces", true, true, 0, true, 1);
    cvarManager->registerCvar("cat_max_bounces", "1", "Max Backwall Bounces", true, true, 0, true, 5);
    cvarManager->registerCvar("cat_mode", "2", "Scenario Mode", true, true, 0, true, 4);
}

void CustomAimTrainer::LoadSettingsFromCvars() {
    auto getC = [this](const std::string& name) { return cvarManager->getCvar(name); };

    if (auto c = getC("cat_enabled")) pluginEnabled = c.getBoolValue();
    if (auto c = getC("cat_surface")) targetSurface = static_cast<TargetSurface>(c.getIntValue());
    if (auto c = getC("cat_snap")) snapMode = static_cast<TargetSnap>(c.getIntValue());

    if (auto c = getC("cat_w_min")) targetWidthMin = c.getFloatValue();
    if (auto c = getC("cat_w_max")) targetWidthMax = c.getFloatValue();
    if (auto c = getC("cat_h_min")) targetHeightMin = c.getFloatValue();
    if (auto c = getC("cat_h_max")) targetHeightMax = c.getFloatValue();

    if (auto c = getC("cat_col_r")) targetColorRGBA[0] = c.getFloatValue();
    if (auto c = getC("cat_col_g")) targetColorRGBA[1] = c.getFloatValue();
    if (auto c = getC("cat_col_b")) targetColorRGBA[2] = c.getFloatValue();
    if (auto c = getC("cat_col_a")) targetColorRGBA[3] = c.getFloatValue();

    if (auto c = getC("cat_reticle")) drawCenterReticle = c.getBoolValue();
    if (auto c = getC("cat_fill")) drawTargetFill = c.getBoolValue();
    if (auto c = getC("cat_border")) borderThickness = c.getFloatValue();

    if (auto c = getC("cat_traj_show")) showTrajectoryLine = c.getBoolValue();
    if (auto c = getC("cat_traj_width")) trajectoryWidth = c.getFloatValue();
    if (auto c = getC("cat_traj_col_r")) trajectoryColorRGBA[0] = c.getFloatValue();
    if (auto c = getC("cat_traj_col_g")) trajectoryColorRGBA[1] = c.getFloatValue();
    if (auto c = getC("cat_traj_col_b")) trajectoryColorRGBA[2] = c.getFloatValue();
    if (auto c = getC("cat_traj_col_a")) trajectoryColorRGBA[3] = c.getFloatValue();

    if (auto c = getC("cat_hud_scale")) hudScale = c.getFloatValue();
    if (auto c = getC("cat_hud_bg")) hudShowBackground = c.getBoolValue();
    if (auto c = getC("cat_hud_x")) hudPosX = c.getFloatValue();
    if (auto c = getC("cat_hud_y")) hudPosY = c.getFloatValue();

    if (auto c = getC("cat_hud_col_r")) hudColorRGBA[0] = c.getFloatValue();
    if (auto c = getC("cat_hud_col_g")) hudColorRGBA[1] = c.getFloatValue();
    if (auto c = getC("cat_hud_col_b")) hudColorRGBA[2] = c.getFloatValue();
    if (auto c = getC("cat_hud_col_a")) hudColorRGBA[3] = c.getFloatValue();

    if (auto c = getC("cat_req_kph_min")) requiredMinHitKph = c.getFloatValue();
    if (auto c = getC("cat_req_kph_max")) requiredMaxHitKph = c.getFloatValue();

    if (auto c = getC("cat_diff")) shotDifficulty = static_cast<ShotDifficulty>(c.getIntValue());

    if (auto c = getC("cat_cat_redirects")) enableRedirects = c.getBoolValue();
    if (auto c = getC("cat_cat_crosses")) enableCrosses = c.getBoolValue();
    if (auto c = getC("cat_cat_pops")) enableClearingPops = c.getBoolValue();
    if (auto c = getC("cat_cat_backboard")) enableBackboardReads = c.getBoolValue();

    if (auto c = getC("cat_coco_dist")) cocoDistance = static_cast<CocoDistance>(c.getIntValue());
    if (auto c = getC("cat_coco_mode")) cocoDelivery = static_cast<CocoDeliveryMode>(c.getIntValue());

    if (auto c = getC("cat_car_dist_min")) carGoalDistMin = c.getFloatValue();
    if (auto c = getC("cat_car_dist_max")) carGoalDistMax = c.getFloatValue();
    if (auto c = getC("cat_car_lat_x")) carMaxLateralX = c.getFloatValue();

    if (auto c = getC("cat_dist_min")) ballDistXYMin = c.getFloatValue();
    if (auto c = getC("cat_dist_max")) ballDistXYMax = c.getFloatValue();
    if (auto c = getC("cat_height_min")) ballHeightMin = c.getFloatValue();
    if (auto c = getC("cat_height_max")) ballHeightMax = c.getFloatValue();

    if (auto c = getC("cat_speed_min")) minKph = c.getFloatValue();
    if (auto c = getC("cat_speed_max")) maxKph = c.getFloatValue();

    if (auto c = getC("cat_inf_time")) infiniteShotTime = c.getBoolValue();
    if (auto c = getC("cat_timeout")) shotTimeout = c.getFloatValue();
    if (auto c = getC("cat_fail_ground")) failOnGroundTouch = c.getBoolValue();
    if (auto c = getC("cat_inf_backwall")) infiniteBackwallHits = c.getBoolValue();
    if (auto c = getC("cat_max_bounces")) maxBackwallHits = c.getIntValue();
    if (auto c = getC("cat_mode")) scenarioMode = static_cast<ScenarioMode>(c.getIntValue());

    ClampRangesToSurface();
}

void CustomAimTrainer::SaveSettingsToCvars() {
    auto setC = [this](const std::string& name, auto val) {
        if (auto c = cvarManager->getCvar(name)) c.setValue(val);
    };

    setC("cat_enabled", pluginEnabled);
    setC("cat_surface", static_cast<int>(targetSurface));
    setC("cat_snap", static_cast<int>(snapMode));

    setC("cat_w_min", targetWidthMin);
    setC("cat_w_max", targetWidthMax);
    setC("cat_h_min", targetHeightMin);
    setC("cat_h_max", targetHeightMax);

    setC("cat_col_r", targetColorRGBA[0]);
    setC("cat_col_g", targetColorRGBA[1]);
    setC("cat_col_b", targetColorRGBA[2]);
    setC("cat_col_a", targetColorRGBA[3]);

    setC("cat_reticle", drawCenterReticle);
    setC("cat_fill", drawTargetFill);
    setC("cat_border", borderThickness);

    setC("cat_traj_show", showTrajectoryLine);
    setC("cat_traj_width", trajectoryWidth);
    setC("cat_traj_col_r", trajectoryColorRGBA[0]);
    setC("cat_traj_col_g", trajectoryColorRGBA[1]);
    setC("cat_traj_col_b", trajectoryColorRGBA[2]);
    setC("cat_traj_col_a", trajectoryColorRGBA[3]);

    setC("cat_hud_scale", hudScale);
    setC("cat_hud_bg", hudShowBackground);
    setC("cat_hud_x", hudPosX);
    setC("cat_hud_y", hudPosY);

    setC("cat_hud_col_r", hudColorRGBA[0]);
    setC("cat_hud_col_g", hudColorRGBA[1]);
    setC("cat_hud_col_b", hudColorRGBA[2]);
    setC("cat_hud_col_a", hudColorRGBA[3]);

    setC("cat_req_kph_min", requiredMinHitKph);
    setC("cat_req_kph_max", requiredMaxHitKph);

    setC("cat_diff", static_cast<int>(shotDifficulty));

    setC("cat_cat_redirects", enableRedirects);
    setC("cat_cat_crosses", enableCrosses);
    setC("cat_cat_pops", enableClearingPops);
    setC("cat_cat_backboard", enableBackboardReads);

    setC("cat_coco_dist", static_cast<int>(cocoDistance));
    setC("cat_coco_mode", static_cast<int>(cocoDelivery));

    setC("cat_car_dist_min", carGoalDistMin);
    setC("cat_car_dist_max", carGoalDistMax);
    setC("cat_car_lat_x", carMaxLateralX);

    setC("cat_dist_min", ballDistXYMin);
    setC("cat_dist_max", ballDistXYMax);
    setC("cat_height_min", ballHeightMin);
    setC("cat_height_max", ballHeightMax);

    setC("cat_speed_min", minKph);
    setC("cat_speed_max", maxKph);

    setC("cat_inf_time", infiniteShotTime);
    setC("cat_timeout", shotTimeout);
    setC("cat_fail_ground", failOnGroundTouch);
    setC("cat_inf_backwall", infiniteBackwallHits);
    setC("cat_max_bounces", maxBackwallHits);
    setC("cat_mode", static_cast<int>(scenarioMode));
}

void CustomAimTrainer::ResetToDefaults() {
    pluginEnabled = true;
    targetSurface = TargetSurface::GoalNet;
    snapMode = TargetSnap::None;

    targetWidthMin = 350.0f;
    targetWidthMax = 650.0f;
    targetHeightMin = 220.0f;
    targetHeightMax = 420.0f;

    targetColorRGBA[0] = 0.0f;
    targetColorRGBA[1] = 1.0f;
    targetColorRGBA[2] = 0.7f;
    targetColorRGBA[3] = 1.0f;

    drawCenterReticle = true;
    drawTargetFill = true;
    borderThickness = 4.0f;

    showTrajectoryLine = true;
    trajectoryWidth = 5.0f;
    trajectoryColorRGBA[0] = 1.0f;
    trajectoryColorRGBA[1] = 0.9f;
    trajectoryColorRGBA[2] = 0.1f;
    trajectoryColorRGBA[3] = 1.0f;

    hudScale = 1.8f;
    hudShowBackground = true;
    hudPosX = 40.0f;
    hudPosY = 50.0f;

    hudColorRGBA[0] = 1.0f;
    hudColorRGBA[1] = 1.0f;
    hudColorRGBA[2] = 1.0f;
    hudColorRGBA[3] = 1.0f;

    requiredMinHitKph = 0.0f;
    requiredMaxHitKph = 200.0f;

    shotDifficulty = ShotDifficulty::Any;

    enableRedirects = true;
    enableCrosses = true;
    enableClearingPops = true;
    enableBackboardReads = true;

    cocoDistance = CocoDistance::Middle;
    cocoDelivery = CocoDeliveryMode::VerticalDrop;

    carGoalDistMin = 1800.0f;
    carGoalDistMax = 4200.0f;
    carMaxLateralX = 1800.0f;

    ballDistXYMin = 800.0f;
    ballDistXYMax = 1600.0f;
    ballHeightMin = 93.0f;
    ballHeightMax = 500.0f;

    minKph = 35.0f;
    maxKph = 85.0f;

    infiniteShotTime = false;
    shotTimeout = 6.0f;
    failOnGroundTouch = false;
    infiniteBackwallHits = true;
    maxBackwallHits = 1;
    scenarioMode = ScenarioMode::MovingPack;
    lockCurrentShot = false;

    SaveSettingsToCvars();
    RecalculateTargetGeometry();
    requestImmediateReset = true;
}

void CustomAimTrainer::onLoad() {
    _globalCvarManager = cvarManager;
    rng.seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));

    RegisterPersistentCvars();
    LoadSettingsFromCvars();

    cvarManager->registerNotifier("aim_toggle_lock", [this](std::vector<std::string> args) {
        lockCurrentShot = !lockCurrentShot;
    }, "Locks or unlocks repeating current shot", PERMISSION_ALL);

    cvarManager->registerNotifier("aim_instant_reset", [this](std::vector<std::string> args) {
        if (resetDebounceTicks <= 0) {
            requestImmediateReset = true;
        }
    }, "Resets the shot", PERMISSION_ALL);

    gameWrapper->HookEventWithCaller<ServerWrapper>("Function TAGame.Car_TA.SetVehicleInput",
        [this](ServerWrapper caller, void* params, std::string eventName) {
            OnPhysicsTick();
        });

    gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {
        RenderOverlay(canvas);
    });

    gameWrapper->HookEvent("Function TAGame.Ball_TA.OnCarTouch", [this](std::string eventName) {
        if (!pluginEnabled) return;
        playerHasTouchedBall = true;
    });

    gameWrapper->HookEventPost("Function TAGame.GameEvent_Soccar_TA.ResetBalls", [this](std::string eventName) {
        if (!pluginEnabled) return;
        if (resetDebounceTicks <= 0) {
            requestImmediateReset = true;
        }
    });

    gameWrapper->HookEventPost("Function TAGame.GameEvent_TA.ResetPickups", [this](std::string eventName) {
        if (!pluginEnabled) return;
        if (resetDebounceTicks <= 0) {
            requestImmediateReset = true;
        }
    });
}

void CustomAimTrainer::onUnload() {
    SaveSettingsToCvars();
}

void CustomAimTrainer::ClampRangesToSurface() {
    float maxW = (targetSurface == TargetSurface::GoalNet) ? 1750.0f : 
                 ((targetSurface == TargetSurface::BackWall) ? 5800.0f : 4500.0f);
    float maxH = (targetSurface == TargetSurface::GoalNet) ? 620.0f : 1200.0f;

    if (targetWidthMax > maxW) targetWidthMax = maxW;
    if (targetWidthMin > maxW) targetWidthMin = maxW * 0.5f;

    if (targetHeightMax > maxH) targetHeightMax = maxH;
    if (targetHeightMin > maxH) targetHeightMin = maxH * 0.5f;
}

void CustomAimTrainer::DetectTargetGoal(ServerWrapper& server) {
    targetGoalY = 5120.0f;
    ArrayWrapper<GoalWrapper> goals = server.GetGoals();
    if (goals.Count() > 0) {
        for (int i = 0; i < goals.Count(); i++) {
            GoalWrapper g = goals.Get(i);
            if (!g) continue;
            Vector gLoc = g.GetLocation();
            if (gLoc.Y > 0.0f) {
                targetGoalY = gLoc.Y;
                break;
            }
        }
    }
}

void CustomAimTrainer::RecalculateTargetGeometry() {
    ClampRangesToSurface();

    if (targetWidthMin > targetWidthMax) std::swap(targetWidthMin, targetWidthMax);
    if (targetHeightMin > targetHeightMax) std::swap(targetHeightMin, targetHeightMax);

    std::uniform_real_distribution<float> wDist(targetWidthMin, targetWidthMax);
    std::uniform_real_distribution<float> hDist(targetHeightMin, targetHeightMax);
    activeTargetWidth = wDist(rng);
    activeTargetHeight = hDist(rng);

    float halfW = activeTargetWidth / 2.0f;
    float halfH = activeTargetHeight / 2.0f;

    if (targetSurface == TargetSurface::LeftWall || targetSurface == TargetSurface::RightWall) {
        float wallX = (targetSurface == TargetSurface::LeftWall) ? -4096.0f : 4096.0f;

        float minY = -2400.0f + halfW;
        float maxY =  2400.0f - halfW;
        if (minY > maxY) minY = maxY = 0.0f;

        float minZ = 160.0f + halfH;
        float maxZ = 1350.0f - halfH;
        if (minZ > maxZ) minZ = maxZ = 600.0f;

        std::uniform_real_distribution<float> yDist(minY, maxY);
        std::uniform_real_distribution<float> zDist(minZ, maxZ);

        float posY = yDist(rng);
        float posZ = zDist(rng);

        if (snapMode == TargetSnap::Top) posZ = 1350.0f - halfH;
        else if (snapMode == TargetSnap::Bottom) posZ = 160.0f + halfH;
        else if (snapMode == TargetSnap::Left) posY = (targetSurface == TargetSurface::LeftWall) ? maxY : minY;
        else if (snapMode == TargetSnap::Right) posY = (targetSurface == TargetSurface::LeftWall) ? minY : maxY;

        currentTargetCenter = Vector(wallX, posY, posZ);
        return;
    }

    if (targetSurface == TargetSurface::BackWall) {
        float minX = -2800.0f + halfW;
        float maxX =  2800.0f - halfW;
        if (minX > maxX) minX = maxX = 0.0f;

        float minZ = 120.0f + halfH;
        float maxZ = 1450.0f - halfH;
        if (minZ > maxZ) minZ = maxZ = 600.0f;

        std::uniform_real_distribution<float> xDist(minX, maxX);
        std::uniform_real_distribution<float> zDist(minZ, maxZ);

        float posX = xDist(rng);
        float posZ = zDist(rng);

        if (snapMode == TargetSnap::Top) posZ = 1450.0f - halfH;
        else if (snapMode == TargetSnap::Bottom) posZ = 120.0f + halfH;
        else if (snapMode == TargetSnap::Left) posX = -2800.0f + halfW;
        else if (snapMode == TargetSnap::Right) posX = 2800.0f - halfW;

        currentTargetCenter = Vector(posX, targetGoalY, posZ);
        return;
    }

    float minX = -880.0f + halfW;
    float maxX =  880.0f - halfW;
    float minZ =   20.0f + halfH;
    float maxZ =  630.0f - halfH;

    if (minX > maxX) minX = maxX = 0.0f;
    if (minZ > maxZ) minZ = maxZ = 320.0f;

    std::uniform_real_distribution<float> distX(minX, maxX);
    std::uniform_real_distribution<float> distZ(minZ, maxZ);

    float posX = distX(rng);
    float posZ = distZ(rng);

    if (snapMode == TargetSnap::Top) posZ = 635.0f - halfH;
    else if (snapMode == TargetSnap::Bottom) posZ = 15.0f + halfH;
    else if (snapMode == TargetSnap::Left) posX = -885.0f + halfW;
    else if (snapMode == TargetSnap::Right) posX = 885.0f - halfW;

    currentTargetCenter = Vector(posX, targetGoalY, posZ);
}

void CustomAimTrainer::GenerateNewShot(ServerWrapper& server) {
    DetectTargetGoal(server);
    RecalculateTargetGeometry();
    isStationaryAerial = false;
    isCocoScenario = false;

    ScenarioMode activeMode = scenarioMode;
    if (activeMode == ScenarioMode::AllRandom) {
        std::uniform_int_distribution<int> mDist(0, 3);
        int picked = mDist(rng);
        activeMode = (picked == 0) ? ScenarioMode::StationaryGround : 
                     (picked == 1) ? ScenarioMode::StationaryAerial : 
                     (picked == 2) ? ScenarioMode::CocoDrop : ScenarioMode::MovingPack;
    }

    // --- COCO SCENARIOS ---
    if (activeMode == ScenarioMode::CocoDrop) {
        isCocoScenario = true;

        CocoDistance effectiveDistance = cocoDistance;
        if (effectiveDistance == CocoDistance::Random) {
            std::uniform_int_distribution<int> rDist(0, 2);
            effectiveDistance = static_cast<CocoDistance>(rDist(rng));
        }

        float distFromWall = 3200.0f;
        if (effectiveDistance == CocoDistance::Close) distFromWall = 1800.0f;
        else if (effectiveDistance == CocoDistance::Far) distFromWall = 4500.0f;

        float dropY = targetGoalY - distFromWall;

        if (cocoDelivery == CocoDeliveryMode::VerticalDrop) {
            activeBallPos = Vector(0.0f, dropY, 950.0f);
            activeBallVel = Vector(0.0f, 0.0f, -40.0f);
            activeBallKph = 20.0f;

            activeCarPos = Vector(0.0f, dropY - 2600.0f, 20.0f);
            activeCarRot = Rotator(0, 16384, 0);
        } 
        else if (cocoDelivery == CocoDeliveryMode::AerialToCar) {
            float arcSpeedKph = 45.0f;
            float uuSpeed = arcSpeedKph * 27.7778f;

            activeBallPos = Vector(0.0f, dropY + 400.0f, 200.0f);
            activeBallVel = Vector(0.0f, -uuSpeed * 0.70f, uuSpeed * 0.75f);
            activeBallKph = arcSpeedKph;

            activeCarPos = Vector(0.0f, dropY - 2400.0f, 20.0f);
            activeCarRot = Rotator(0, 16384, 0);
        }
        else {
            float rollSpeedKph = 55.0f;
            float uuSpeed = rollSpeedKph * 27.7778f;

            activeBallPos = Vector(0.0f, dropY + 300.0f, 93.0f);
            activeBallVel = Vector(0.0f, -uuSpeed, 0.0f);
            activeBallKph = rollSpeedKph;

            activeCarPos = Vector(0.0f, dropY - 1900.0f, 20.0f);
            activeCarRot = Rotator(0, 16384, 0);
        }
        return;
    }

    // --- REVERSE BALLISTIC INTERCEPT SOLVER ---
    if (minKph > maxKph) std::swap(minKph, maxKph);
    std::uniform_real_distribution<float> speedDist(minKph, maxKph);
    activeBallKph = speedDist(rng);
    float desiredSpeedUU = activeBallKph * 27.7778f;

    // 1. Position player car in offensive field sector
    std::uniform_real_distribution<float> carGoalDistDist(carGoalDistMin, carGoalDistMax);
    std::uniform_real_distribution<float> carXDist(-carMaxLateralX * 0.65f, carMaxLateralX * 0.65f);
    float carX = carXDist(rng);
    float carY = targetGoalY - carGoalDistDist(rng);
    activeCarPos = Vector(carX, carY, 20.0f);

    float toTargetX = currentTargetCenter.X - carX;
    float toTargetY = currentTargetCenter.Y - carY;
    float targetDist = std::sqrt(toTargetX * toTargetX + toTargetY * toTargetY);
    Vector fwdDir = Vector(toTargetX / targetDist, toTargetY / targetDist, 0.0f);
    Vector rightDir = Vector(fwdDir.Y, -fwdDir.X, 0.0f);

    int yaw = static_cast<int>(std::atan2(fwdDir.Y, fwdDir.X) * (32768.0f / 3.14159265f));
    activeCarRot = Rotator(0, yaw, 0);

    // 2. Stationary Modes
    if (activeMode == ScenarioMode::StationaryGround) {
        std::uniform_real_distribution<float> distOffset(ballDistXYMin, ballDistXYMax);
        std::uniform_real_distribution<float> sideOffset(-200.0f, 200.0f);
        float d = distOffset(rng);
        float s = sideOffset(rng);

        activeBallPos = Vector(carX + fwdDir.X * d + rightDir.X * s, carY + fwdDir.Y * d + rightDir.Y * s, 93.0f);
        activeBallVel = Vector(0.0f, 0.0f, 0.0f);
        activeBallKph = 0.0f;
        return;
    }
    if (activeMode == ScenarioMode::StationaryAerial) {
        isStationaryAerial = true;
        std::uniform_real_distribution<float> distOffset(ballDistXYMin, ballDistXYMax);
        std::uniform_real_distribution<float> sideOffset(-250.0f, 250.0f);
        std::uniform_real_distribution<float> zDist(ballHeightMin < 350.0f ? 350.0f : ballHeightMin, ballHeightMax < 600.0f ? 600.0f : ballHeightMax);
        float d = distOffset(rng);
        float s = sideOffset(rng);

        activeBallPos = Vector(carX + fwdDir.X * d + rightDir.X * s, carY + fwdDir.Y * d + rightDir.Y * s, zDist(rng));
        activeBallVel = Vector(0.0f, 0.0f, 0.0f);
        activeBallKph = 0.0f;
        return;
    }

    // 3. Select Category from Active User Toggles
    std::vector<int> validCategories;
    if (enableRedirects) validCategories.push_back(0);
    if (enableCrosses) validCategories.push_back(1);
    if (enableClearingPops) validCategories.push_back(2);
    if (enableBackboardReads) validCategories.push_back(3);

    if (validCategories.empty()) {
        validCategories.push_back(0); // Fallback
    }

    std::uniform_int_distribution<size_t> catPick(0, validCategories.size() - 1);
    int chosenCategory = validCategories[catPick(rng)];

    // 4. Calculate Intercept Point & Deflection Angle Based on Difficulty
    float iDistMin = 750.0f, iDistMax = 1250.0f;
    float iHeightMin = 120.0f, iHeightMax = 320.0f;
    float maxAngleDegrees = 60.0f;

    if (shotDifficulty == ShotDifficulty::Easy) {
        iDistMin = 650.0f; iDistMax = 950.0f;
        iHeightMin = 95.0f; iHeightMax = 220.0f;
        maxAngleDegrees = 30.0f;
    } else if (shotDifficulty == ShotDifficulty::Hard) {
        iDistMin = 900.0f; iDistMax = 1450.0f;
        iHeightMin = 200.0f; iHeightMax = 500.0f;
        maxAngleDegrees = 95.0f;
    }

    std::uniform_real_distribution<float> interceptDist(iDistMin, iDistMax);
    std::uniform_real_distribution<float> interceptHeight(iHeightMin, iHeightMax);
    std::uniform_real_distribution<float> interceptLateral(-180.0f, 180.0f);

    float iDist = interceptDist(rng);
    float iLat = interceptLateral(rng);
    Vector interceptPoint = Vector(
        carX + fwdDir.X * iDist + rightDir.X * iLat,
        carY + fwdDir.Y * iDist + rightDir.Y * iLat,
        interceptHeight(rng)
    );

    // 5. Build Category-Specific Spawn Origins
    Vector spawnPos;
    if (chosenCategory == 0) {
        // Redirect: Ball starts behind player and travels past the car toward a non-goal tangent
        std::uniform_real_distribution<float> backDist(1500.0f, 2300.0f);
        std::uniform_real_distribution<float> backSide(-600.0f, 600.0f);
        std::uniform_real_distribution<float> backHeight(300.0f, 650.0f);
        float bD = backDist(rng);
        float bS = backSide(rng);
        spawnPos = Vector(carX - fwdDir.X * bD + rightDir.X * bS, carY - fwdDir.Y * bD + rightDir.Y * bS, backHeight(rng));
    }
    else if (chosenCategory == 1) {
        // Infield Cross Pass: Sweeps across the pitch from the flank
        float sideSign = (carX >= 0.0f) ? -1.0f : 1.0f;
        std::uniform_real_distribution<float> crossDepth(200.0f, 750.0f);
        spawnPos = Vector(sideSign * 3100.0f, carY + crossDepth(rng), 160.0f);
    }
    else if (chosenCategory == 2) {
        // Clearing Pop: High pop from downfield moving back/across
        std::uniform_real_distribution<float> feedDepth(1200.0f, 2000.0f);
        std::uniform_real_distribution<float> feedLat(-1000.0f, 1000.0f);
        spawnPos = Vector(carX + feedLat(rng), carY + feedDepth(rng), 110.0f);
    }
    else {
        // Backboard Rebound Read: Ball fires toward high backboard and bounces off
        float sideX = (carX >= 0.0f) ? -900.0f : 900.0f;
        spawnPos = Vector(sideX, targetGoalY - 2600.0f, 150.0f);
        interceptPoint = Vector(carX * 0.4f, targetGoalY - 1100.0f, 380.0f);
    }

    // 6. Guarantee Trajectory Does Not Score On Its Own:
    // Ensure the vector connecting spawnPos to interceptPoint does NOT point directly into the target goal
    Vector trajectoryRay = interceptPoint - spawnPos;
    if (trajectoryRay.Y > 50.0f) {
        float tGoal = (targetGoalY - spawnPos.Y) / trajectoryRay.Y;
        if (tGoal > 0.0f) {
            float xAtGoal = spawnPos.X + trajectoryRay.X * tGoal;
            float zAtGoal = spawnPos.Z + trajectoryRay.Z * tGoal;
            // If the untouched path crosses into the goal mouth, offset intercept point to miss the net
            if (std::abs(xAtGoal) < 1100.0f && zAtGoal < 750.0f) {
                float shift = (xAtGoal >= 0.0f) ? 350.0f : -350.0f;
                interceptPoint.X += shift;
            }
        }
    }

    // Arena boundary clamp
    if (spawnPos.X > 3500.0f) spawnPos.X = 3500.0f;
    if (spawnPos.X < -3500.0f) spawnPos.X = -3500.0f;
    if (spawnPos.Y > (targetGoalY - 600.0f)) spawnPos.Y = targetGoalY - 600.0f;
    if (spawnPos.Y < -4800.0f) spawnPos.Y = -4800.0f;

    // 7. Physical Reachability Check & Ballistic Time Solution
    float carToInterceptDist = std::sqrt(
        (interceptPoint.X - carX) * (interceptPoint.X - carX) +
        (interceptPoint.Y - carY) * (interceptPoint.Y - carY)
    );
    float minCarArrivalTime = 0.35f + (carToInterceptDist / 1650.0f);

    float dispX = interceptPoint.X - spawnPos.X;
    float dispY = interceptPoint.Y - spawnPos.Y;
    float dispZ = interceptPoint.Z - spawnPos.Z;
    float totalDist = std::sqrt(dispX * dispX + dispY * dispY + dispZ * dispZ);

    float timeToHit = totalDist / desiredSpeedUU;
    if (timeToHit < minCarArrivalTime) {
        timeToHit = minCarArrivalTime;
    }

    const float gravity = -650.0f;
    float vx = dispX / timeToHit;
    float vy = dispY / timeToHit;
    float vz = (dispZ - 0.5f * gravity * timeToHit * timeToHit) / timeToHit;

    activeBallPos = spawnPos;
    activeBallVel = Vector(vx, vy, vz);
    activeBallKph = std::sqrt(vx * vx + vy * vy + vz * vz) * 0.036f;
}

void CustomAimTrainer::ExecuteReset(bool isSuccess) {
    if (!pluginEnabled || !gameWrapper->IsInGame()) return;
    ServerWrapper server = gameWrapper->GetCurrentGameState();
    if (!server) return;

    BallWrapper ball = server.GetBall();
    CarWrapper car = gameWrapper->GetLocalCar();
    if (!ball || !car) return;

    totalAttempts++;
    lastShotWasSuccess = isSuccess;
    flashFeedbackTicks = 20;

    if (isSuccess) {
        currentStreak++;
        totalHits++;
        if (currentStreak > bestStreak) bestStreak = currentStreak;
    } else if (shotActive) {
        currentStreak = 0;
    }

    if (!lockCurrentShot || !shotActive) {
        GenerateNewShot(server);
    }

    ball.SetLocation(activeBallPos);
    ball.SetVelocity(Vector(0.0f, 0.0f, 0.0f));
    ball.SetAngularVelocity(Vector(0.0f, 0.0f, 0.0f), false);

    car.SetLocation(activeCarPos);
    car.SetRotation(activeCarRot);
    car.SetVelocity(Vector(0.0f, 0.0f, 0.0f));
    car.SetAngularVelocity(Vector(0.0f, 0.0f, 0.0f), false);

    waitingForPlayerInput = true;
    playerHasTouchedBall = false;
    hasLeftGroundAfterHit = false;
    settleTicks = 15;
    resetDebounceTicks = 20;
    remainingTime = shotTimeout;
    backwallHitCount = 0;
    backwallCooldownTicks = 0;
    lastBallVel = Vector(0.0f, 0.0f, 0.0f);
    shotActive = true;
}

void CustomAimTrainer::CheckBackwallHit(const Vector& bPos, const Vector& bVel) {
    if (infiniteBackwallHits) return;
    if (targetSurface != TargetSurface::GoalNet) return;

    if (backwallCooldownTicks > 0) {
        backwallCooldownTicks--;
        return;
    }

    bool atBackWall = (bPos.Y >= (targetGoalY - 140.0f));
    bool outsideGoalMouth = (std::abs(bPos.X) >= 892.0f || bPos.Z >= 642.0f);

    if (atBackWall && outsideGoalMouth && lastBallVel.Y > 60.0f && bVel.Y < -20.0f) {
        backwallHitCount++;
        backwallCooldownTicks = 25;

        if (backwallHitCount > maxBackwallHits) {
            ExecuteReset(false);
        }
    }
}

void CustomAimTrainer::OnPhysicsTick() {
    if (!pluginEnabled || !gameWrapper->IsInGame()) return;

    if (flashFeedbackTicks > 0) flashFeedbackTicks--;
    if (resetDebounceTicks > 0) resetDebounceTicks--;

    if (requestImmediateReset) {
        requestImmediateReset = false;
        ExecuteReset(false);
        return;
    }

    ServerWrapper server = gameWrapper->GetCurrentGameState();
    if (!server) return;

    BallWrapper ball = server.GetBall();
    CarWrapper car = gameWrapper->GetLocalCar();
    if (!ball || !car) return;

    if (!shotActive) {
        ExecuteReset(false);
        return;
    }

    Vector bPos = ball.GetLocation();
    Vector bVel = ball.GetVelocity();

    if (waitingForPlayerInput) {
        ball.SetLocation(activeBallPos);
        ball.SetVelocity(Vector(0.0f, 0.0f, 0.0f));
        ball.SetAngularVelocity(Vector(0.0f, 0.0f, 0.0f), false);

        if (settleTicks > 0) {
            settleTicks--;
            car.SetLocation(activeCarPos);
            car.SetRotation(activeCarRot);
            car.SetVelocity(Vector(0.0f, 0.0f, 0.0f));
            car.SetAngularVelocity(Vector(0.0f, 0.0f, 0.0f), false);
            return;
        }

        Vector cVel = car.GetVelocity();
        float carSpeed = std::sqrt(cVel.X * cVel.X + cVel.Y * cVel.Y + cVel.Z * cVel.Z);

        if (carSpeed > 60.0f) {
            waitingForPlayerInput = false;
            ball.SetVelocity(activeBallVel);
        }
        return;
    }

    if (isStationaryAerial && !playerHasTouchedBall) {
        ball.SetLocation(activeBallPos);
        ball.SetVelocity(Vector(0.0f, 0.0f, 0.0f));
        ball.SetAngularVelocity(Vector(0.0f, 0.0f, 0.0f), false);
    }

    Vector cPos = car.GetLocation();
    float dx = bPos.X - cPos.X;
    float dy = bPos.Y - cPos.Y;
    float dz = bPos.Z - cPos.Z;
    float distToCar = std::sqrt(dx * dx + dy * dy + dz * dz);
    if (distToCar < 220.0f) {
        playerHasTouchedBall = true;
    }

    if (!infiniteShotTime) {
        remainingTime -= (1.0f / 120.0f);
        if (remainingTime <= 0.0f) {
            ExecuteReset(false);
            return;
        }
    }

    if (playerHasTouchedBall) {
        if (bPos.Z > 125.0f) hasLeftGroundAfterHit = true;
        if (failOnGroundTouch && hasLeftGroundAfterHit && bPos.Z <= 95.0f) {
            ExecuteReset(false);
            return;
        }
    }

    CheckBackwallHit(bPos, bVel);
    lastBallVel = bVel;

    const float ballRadiusWithTolerance = 116.25f;
    float halfW = (activeTargetWidth / 2.0f) + ballRadiusWithTolerance;
    float halfH = (activeTargetHeight / 2.0f) + ballRadiusWithTolerance;

    float hitSpeedKph = std::sqrt(bVel.X * bVel.X + bVel.Y * bVel.Y + bVel.Z * bVel.Z) * 0.036f;
    bool speedValid = (hitSpeedKph >= requiredMinHitKph) && (requiredMaxHitKph >= 200.0f || hitSpeedKph <= requiredMaxHitKph);

    // --- SIDE WALL DETECTION ---
    if (targetSurface == TargetSurface::LeftWall || targetSurface == TargetSurface::RightWall) {
        float wallX = (targetSurface == TargetSurface::LeftWall) ? -4096.0f : 4096.0f;
        bool crossedWall = (targetSurface == TargetSurface::LeftWall) 
            ? (bPos.X - 91.25f <= wallX + 25.0f) 
            : (bPos.X + 91.25f >= wallX - 25.0f);

        if (crossedWall) {
            bool inTargetY = std::abs(bPos.Y - currentTargetCenter.Y) <= halfW;
            bool inTargetZ = std::abs(bPos.Z - currentTargetCenter.Z) <= halfH;
            ExecuteReset(inTargetY && inTargetZ && speedValid);
            return;
        }
    }
    // --- GOAL & BACK WALL DETECTION ---
    else {
        if (bPos.Y + 91.25f >= (targetGoalY - 25.0f)) {
            bool inGoalOpening = (std::abs(bPos.X) < 892.0f && bPos.Z < 642.0f && bPos.Z > 0.0f);

            if (targetSurface == TargetSurface::GoalNet) {
                bool inTargetX = std::abs(bPos.X - currentTargetCenter.X) <= halfW;
                bool inTargetZ = std::abs(bPos.Z - currentTargetCenter.Z) <= halfH;
                if (inGoalOpening) {
                    ExecuteReset(inTargetX && inTargetZ && speedValid);
                    return;
                }
            }
            else if (targetSurface == TargetSurface::BackWall) {
                bool inTargetX = std::abs(bPos.X - currentTargetCenter.X) <= halfW;
                bool inTargetZ = std::abs(bPos.Z - currentTargetCenter.Z) <= halfH;
                ExecuteReset(inTargetX && inTargetZ && speedValid);
                return;
            }
        }
    }
}

void CustomAimTrainer::RenderOverlay(CanvasWrapper canvas) {
    if (!pluginEnabled || !gameWrapper->IsInGame()) return;

    CameraWrapper cam = gameWrapper->GetCamera();
    Vector camLoc = cam ? cam.GetLocation() : Vector(0.0f, 0.0f, 0.0f);
    Rotator camRot = cam ? cam.GetRotation() : Rotator(0, 0, 0);

    float pitch = static_cast<float>(camRot.Pitch) * (3.14159265f / 32768.0f);
    float yaw = static_cast<float>(camRot.Yaw) * (3.14159265f / 32768.0f);
    Vector camForward = Vector(std::cos(pitch) * std::cos(yaw), std::cos(pitch) * std::sin(yaw), std::sin(pitch));

    bool targetInFront = true;
    if (cam) {
        Vector toTarget = currentTargetCenter - camLoc;
        float dotForward = toTarget.X * camForward.X + toTarget.Y * camForward.Y + toTarget.Z * camForward.Z;
        if (dotForward <= 0.0f) targetInFront = false;
    }

    if (targetInFront) {
        float hw = activeTargetWidth / 2.0f;
        float hh = activeTargetHeight / 2.0f;

        Vector tl, tr, bl, br;
        bool onSideWall = (targetSurface == TargetSurface::LeftWall || targetSurface == TargetSurface::RightWall);

        if (onSideWall) {
            float wallX = currentTargetCenter.X;
            tl = Vector(wallX, currentTargetCenter.Y - hw, currentTargetCenter.Z + hh);
            tr = Vector(wallX, currentTargetCenter.Y + hw, currentTargetCenter.Z + hh);
            bl = Vector(wallX, currentTargetCenter.Y - hw, currentTargetCenter.Z - hh);
            br = Vector(wallX, currentTargetCenter.Y + hw, currentTargetCenter.Z - hh);
        } else {
            float wallY = currentTargetCenter.Y;
            tl = Vector(currentTargetCenter.X - hw, wallY, currentTargetCenter.Z + hh);
            tr = Vector(currentTargetCenter.X + hw, wallY, currentTargetCenter.Z + hh);
            bl = Vector(currentTargetCenter.X - hw, wallY, currentTargetCenter.Z - hh);
            br = Vector(currentTargetCenter.X + hw, wallY, currentTargetCenter.Z - hh);
        }

        Vector2F pTL = canvas.ProjectF(tl);
        Vector2F pTR = canvas.ProjectF(tr);
        Vector2F pBL = canvas.ProjectF(bl);
        Vector2F pBR = canvas.ProjectF(br);

        char cR, cG, cB, cA;
        if (flashFeedbackTicks > 0) {
            if (lastShotWasSuccess) {
                cR = 0; cG = static_cast<char>(255); cB = 0; cA = static_cast<char>(255);
            } else {
                cR = static_cast<char>(255); cG = 40; cB = 40; cA = static_cast<char>(255);
            }
        } else {
            cR = static_cast<char>(targetColorRGBA[0] * 255.0f);
            cG = static_cast<char>(targetColorRGBA[1] * 255.0f);
            cB = static_cast<char>(targetColorRGBA[2] * 255.0f);
            cA = static_cast<char>(targetColorRGBA[3] * 255.0f);
        }

        if (drawTargetFill) {
            canvas.SetColor(cR, cG, cB, static_cast<char>(38));
            float steps = 24.0f;
            for (float i = 0.0f; i <= steps; i += 1.0f) {
                float t = i / steps;
                Vector2F leftEdge  = Vector2F{ pTL.X + (pBL.X - pTL.X) * t, pTL.Y + (pBL.Y - pTL.Y) * t };
                Vector2F rightEdge = Vector2F{ pTR.X + (pBR.X - pTR.X) * t, pTR.Y + (pBR.Y - pTR.Y) * t };
                canvas.DrawLine(leftEdge, rightEdge);
            }
        }

        float halfThick = borderThickness * 0.5f;
        canvas.SetColor(cR, cG, cB, cA);
        for (float o = -halfThick; o <= halfThick; o += 1.0f) {
            canvas.DrawLine(Vector2F{ pTL.X, pTL.Y + o }, Vector2F{ pTR.X, pTR.Y + o });
            canvas.DrawLine(Vector2F{ pBL.X, pBL.Y + o }, Vector2F{ pBR.X, pBR.Y + o });
            canvas.DrawLine(Vector2F{ pTL.X + o, pTL.Y }, Vector2F{ pBL.X + o, pBL.Y });
            canvas.DrawLine(Vector2F{ pTR.X + o, pTR.Y }, Vector2F{ pBR.X + o, pBR.Y });
        }

        float bracketLen = 22.0f;
        canvas.SetColor(static_cast<char>(255), static_cast<char>(255), static_cast<char>(255), static_cast<char>(240));
        canvas.DrawLine(pTL, Vector2F{ pTL.X + bracketLen, pTL.Y });
        canvas.DrawLine(pTL, Vector2F{ pTL.X, pTL.Y + bracketLen });
        canvas.DrawLine(pTR, Vector2F{ pTR.X - bracketLen, pTR.Y });
        canvas.DrawLine(pTR, Vector2F{ pTR.X, pTR.Y + bracketLen });
        canvas.DrawLine(pBL, Vector2F{ pBL.X + bracketLen, pBL.Y });
        canvas.DrawLine(pBL, Vector2F{ pBL.X, pBL.Y - bracketLen });
        canvas.DrawLine(pBR, Vector2F{ pBR.X - bracketLen, pBR.Y });
        canvas.DrawLine(pBR, Vector2F{ pBR.X, pBR.Y - bracketLen });

        if (drawCenterReticle) {
            Vector2F cMid = canvas.ProjectF(currentTargetCenter);
            canvas.SetColor(cR, cG, cB, cA);
            canvas.DrawLine(Vector2F{ cMid.X - 22.0f, cMid.Y }, Vector2F{ cMid.X + 22.0f, cMid.Y });
            canvas.DrawLine(Vector2F{ cMid.X, cMid.Y - 22.0f }, Vector2F{ cMid.X, cMid.Y + 22.0f });
        }
    }

    // --- HIGH-GIRTH DYNAMIC TRAJECTORY LASER BEAM ---
    if (showTrajectoryLine && waitingForPlayerInput && activeBallKph > 0.0f && cam) {
        float speedRatio = activeBallKph / 65.0f;
        if (speedRatio < 0.6f) speedRatio = 0.6f;
        if (speedRatio > 2.5f) speedRatio = 2.5f;

        float timeAhead = 0.55f * speedRatio;
        Vector previewEnd = Vector(
            activeBallPos.X + activeBallVel.X * timeAhead,
            activeBallPos.Y + activeBallVel.Y * timeAhead,
            activeBallPos.Z + activeBallVel.Z * timeAhead - 0.5f * 650.0f * timeAhead * timeAhead
        );

        Vector toBall = activeBallPos - camLoc;
        Vector toEnd = previewEnd - camLoc;
        float dotBall = toBall.X * camForward.X + toBall.Y * camForward.Y + toBall.Z * camForward.Z;
        float dotEnd  = toEnd.X * camForward.X + toEnd.Y * camForward.Y + toEnd.Z * camForward.Z;

        if (dotBall > 10.0f && dotEnd > 10.0f) {
            Vector2F bScreen = canvas.ProjectF(activeBallPos);
            Vector2F eScreen = canvas.ProjectF(previewEnd);

            float deltaX = eScreen.X - bScreen.X;
            float deltaY = eScreen.Y - bScreen.Y;
            float screenDist = std::sqrt(deltaX * deltaX + deltaY * deltaY);

            if (screenDist > 4.0f) {
                float normX = -deltaY / screenDist;
                float normY = deltaX / screenDist;

                char tR = static_cast<char>(trajectoryColorRGBA[0] * 255.0f);
                char tG = static_cast<char>(trajectoryColorRGBA[1] * 255.0f);
                char tB = static_cast<char>(trajectoryColorRGBA[2] * 255.0f);
                char tA = static_cast<char>(trajectoryColorRGBA[3] * 255.0f);

                float shadowWidth = trajectoryWidth + 3.0f;
                canvas.SetColor(static_cast<char>(10), static_cast<char>(10), static_cast<char>(15), static_cast<char>(200));
                for (float w = -shadowWidth * 0.5f; w <= shadowWidth * 0.5f; w += 1.0f) {
                    canvas.DrawLine(
                        Vector2F{ bScreen.X + normX * w, bScreen.Y + normY * w },
                        Vector2F{ eScreen.X + normX * w, eScreen.Y + normY * w }
                    );
                }

                canvas.SetColor(tR, tG, tB, tA);
                for (float w = -trajectoryWidth * 0.5f; w <= trajectoryWidth * 0.5f; w += 1.0f) {
                    canvas.DrawLine(
                        Vector2F{ bScreen.X + normX * w, bScreen.Y + normY * w },
                        Vector2F{ eScreen.X + normX * w, eScreen.Y + normY * w }
                    );
                }

                canvas.SetColor(static_cast<char>(255), static_cast<char>(255), static_cast<char>(255), static_cast<char>(230));
                canvas.DrawLine(bScreen, eScreen);

                canvas.SetColor(tR, tG, tB, tA);
                canvas.DrawLine(Vector2F{ eScreen.X - 8.0f, eScreen.Y }, Vector2F{ eScreen.X + 8.0f, eScreen.Y });
                canvas.DrawLine(Vector2F{ eScreen.X, eScreen.Y - 8.0f }, Vector2F{ eScreen.X, eScreen.Y + 8.0f });

                std::string kphStr = std::to_string(static_cast<int>(std::round(activeBallKph))) + " KPH";
                Vector2F txtSz = canvas.GetStringSize(kphStr, 1.4f, 1.4f);
                float plateX = eScreen.X + 16.0f;
                float plateY = eScreen.Y - (txtSz.Y * 0.5f);

                canvas.SetColor(static_cast<char>(12), static_cast<char>(12), static_cast<char>(18), static_cast<char>(230));
                for (float r = 0.0f; r < txtSz.Y + 8.0f; r += 2.0f) {
                    canvas.DrawLine(Vector2F{ plateX - 6.0f, plateY - 4.0f + r }, Vector2F{ plateX + txtSz.X + 8.0f, plateY - 4.0f + r });
                }

                canvas.SetColor(tR, tG, tB, static_cast<char>(255));
                canvas.DrawLine(Vector2F{ plateX - 6.0f, plateY - 4.0f }, Vector2F{ plateX + txtSz.X + 8.0f, plateY - 4.0f });
                canvas.DrawLine(Vector2F{ plateX - 6.0f, plateY + txtSz.Y + 4.0f }, Vector2F{ plateX + txtSz.X + 8.0f, plateY + txtSz.Y + 4.0f });

                canvas.SetPosition(Vector2F{ plateX, plateY });
                canvas.SetColor(static_cast<char>(255), static_cast<char>(255), static_cast<char>(255), static_cast<char>(255));
                canvas.DrawString(kphStr, 1.4f, 1.4f);
            }
        }
    }

    // --- HUD RENDERING ---
    std::string timeText;
    if (waitingForPlayerInput) {
        timeText = "READY";
    } else if (infiniteShotTime) {
        timeText = "INF";
    } else {
        timeText = std::to_string(static_cast<int>(std::ceil(remainingTime))) + "s";
    }

    std::string backwallHitsText = infiniteBackwallHits ? "INF" : (std::to_string(backwallHitCount) + "/" + std::to_string(maxBackwallHits));

    std::string kphReqText;
    if (requiredMinHitKph <= 0.0f && requiredMaxHitKph >= 200.0f) {
        kphReqText = "ANY";
    } else if (requiredMaxHitKph >= 200.0f) {
        kphReqText = std::to_string(static_cast<int>(requiredMinHitKph)) + "+ KPH";
    } else {
        kphReqText = std::to_string(static_cast<int>(requiredMinHitKph)) + "-" + std::to_string(static_cast<int>(requiredMaxHitKph)) + " KPH";
    }

    std::string line1 = "Streak: " + std::to_string(currentStreak) + " | Best: " + std::to_string(bestStreak) + " | Req Speed: " + kphReqText + " | Time: " + timeText + " | Bounces: " + backwallHitsText;
    std::string line2 = std::string("State: ") + (lockCurrentShot ? "[LOCKED]" : "[RANDOM]") + " (Press Use Item to toggle)";

    const float scaleRatio = hudScale / 1.5f;
    float lineSpacing = 34.0f * scaleRatio;

    Vector2F sz1 = canvas.GetStringSize(line1, hudScale, hudScale);
    Vector2F sz2 = canvas.GetStringSize(line2, hudScale * 0.9f, hudScale * 0.9f);
    float textMaxW = (sz1.X > sz2.X) ? sz1.X : sz2.X;

    if (hudShowBackground) {
        float boxW = textMaxW + 35.0f;
        float boxH = 75.0f * scaleRatio;
        canvas.SetColor(static_cast<char>(15), static_cast<char>(15), static_cast<char>(18), static_cast<char>(190));
        float startX = hudPosX - 12.0f;
        float endX = startX + boxW;
        float baseY = hudPosY - 6.0f;

        for (float r = 0.0f; r < boxH; r += 2.0f) {
            float curY = baseY + r;
            canvas.DrawLine(Vector2F{ startX, curY }, Vector2F{ endX, curY });
        }
    }

    char hR = static_cast<char>(hudColorRGBA[0] * 255.0f);
    char hG = static_cast<char>(hudColorRGBA[1] * 255.0f);
    char hB = static_cast<char>(hudColorRGBA[2] * 255.0f);
    char hA = static_cast<char>(hudColorRGBA[3] * 255.0f);

    canvas.SetPosition(Vector2F{ hudPosX, hudPosY });
    canvas.SetColor(hR, hG, hB, hA);
    canvas.DrawString(line1, hudScale, hudScale);

    canvas.SetPosition(Vector2F{ hudPosX, hudPosY + lineSpacing });
    if (lockCurrentShot) {
        canvas.SetColor(static_cast<char>(255), static_cast<char>(180), static_cast<char>(50), static_cast<char>(255));
    } else {
        canvas.SetColor(static_cast<char>(120), static_cast<char>(230), static_cast<char>(255), static_cast<char>(230));
    }
    canvas.DrawString(line2, hudScale * 0.9f, hudScale * 0.9f);
}

void CustomAimTrainer::RenderSettings() {
    bool changed = false;

    // --- MASTER TOGGLE & STATS ---
    if (ImGui::Checkbox("Enable Aim Trainer", &pluginEnabled)) changed = true;
    if (!pluginEnabled) {
        if (changed) SaveSettingsToCvars();
        return;
    }

    ImGui::Text("Streak: %d (Best: %d)  |  Hits / Total: %d / %d", currentStreak, bestStreak, totalHits, totalAttempts);
    if (ImGui::Button("Reset Stats")) {
        currentStreak = 0;
        bestStreak = 0;
        totalHits = 0;
        totalAttempts = 0;
    }
    ImGui::SameLine();
    if (ImGui::Button("Spawn Next Shot")) {
        requestImmediateReset = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset to Defaults")) {
        ResetToDefaults();
        return;
    }

    // --- SECTION: TARGET SETTINGS ---
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextColored(ImVec4(0.2f, 0.9f, 0.6f, 1.0f), "TARGET SETTINGS");
    ImGui::Separator();

    const char* surfaces[] = { "Goal Net (Standard)", "Entire Back Wall (Backboard)", "Side Wall (Left)", "Side Wall (Right)" };
    int currentSurf = static_cast<int>(targetSurface);
    if (ImGui::Combo("Target Wall", &currentSurf, surfaces, IM_ARRAYSIZE(surfaces))) {
        targetSurface = static_cast<TargetSurface>(currentSurf);
        ClampRangesToSurface();
        RecalculateTargetGeometry();
        changed = true;
    }

    float maxAllowedWidth = (targetSurface == TargetSurface::GoalNet) ? 1750.0f : 
                            ((targetSurface == TargetSurface::BackWall) ? 5800.0f : 4500.0f);
    float maxAllowedHeight = (targetSurface == TargetSurface::GoalNet) ? 620.0f : 1200.0f;

    bool targetChanged = false;
    targetChanged |= ImGui::RangeSliderFloat("Target Width [Min - Max]", &targetWidthMin, &targetWidthMax, 100.0f, maxAllowedWidth, "%.0f - %.0f");
    targetChanged |= ImGui::RangeSliderFloat("Target Height [Min - Max]", &targetHeightMin, &targetHeightMax, 80.0f, maxAllowedHeight, "%.0f - %.0f");

    const char* snapModes[] = { "None (Random on Wall)", "Top Wall", "Bottom Wall", "Left Edge", "Right Edge" };
    int currentSnap = static_cast<int>(snapMode);
    if (ImGui::Combo("Pin Target to Edge", &currentSnap, snapModes, IM_ARRAYSIZE(snapModes))) {
        snapMode = static_cast<TargetSnap>(currentSnap);
        targetChanged = true;
    }

    if (targetChanged) {
        RecalculateTargetGeometry();
        changed = true;
    }

    if (ImGui::ColorEdit4("Target Outline Color", targetColorRGBA)) changed = true;
    if (ImGui::SliderFloat("Target Border Thickness", &borderThickness, 1.0f, 8.0f, "%.1f px")) changed = true;
    if (ImGui::Checkbox("Draw Translucent Target Face Tint", &drawTargetFill)) changed = true;
    if (ImGui::Checkbox("Draw Center Reticle Crosshair", &drawCenterReticle)) changed = true;

    // --- SECTION: BALL & SCENARIO ---
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextColored(ImVec4(0.9f, 0.7f, 0.2f, 1.0f), "BALL & SCENARIO");
    ImGui::Separator();

    const char* modes[] = { "Stationary (Ground)", "Stationary (Aerial)", "Moving Pack (Custom Categories)", "Coco's Drop & Bounce", "All Random" };
    int currentMode = static_cast<int>(scenarioMode);
    if (ImGui::Combo("Scenario Mode", &currentMode, modes, IM_ARRAYSIZE(modes))) {
        scenarioMode = static_cast<ScenarioMode>(currentMode);
        requestImmediateReset = true;
        changed = true;
    }

    if (scenarioMode == ScenarioMode::CocoDrop) {
        const char* cocoDists[] = { "Close (~1800 Distance)", "Middle (~3200 Distance)", "Far (~4500 Distance)", "Random Distance" };
        int currentCocoDist = static_cast<int>(cocoDistance);
        if (ImGui::Combo("Coco Wall Distance", &currentCocoDist, cocoDists, IM_ARRAYSIZE(cocoDists))) {
            cocoDistance = static_cast<CocoDistance>(currentCocoDist);
            requestImmediateReset = true;
            changed = true;
        }

        const char* deliveryModes[] = { "Vertical High Drop & Bounce", "Aerial High Arc Toward Car", "Roll Straight Toward Car (55 KPH)" };
        int currentDelivery = static_cast<int>(cocoDelivery);
        if (ImGui::Combo("Ball Delivery Style", &currentDelivery, deliveryModes, IM_ARRAYSIZE(deliveryModes))) {
            cocoDelivery = static_cast<CocoDeliveryMode>(currentDelivery);
            requestImmediateReset = true;
            changed = true;
        }

        ImGui::TextDisabled("Coco scenario manages initial velocities, spawn positions, and delivery physics.");
    }
    else {
        // Difficulty selector
        const char* diffLevels[] = { "Any (Dynamic Mix)", "Easy (Shallow Angles)", "Medium (Standard)", "Hard (Acute Turns & Fast Aerials)" };
        int curDiff = static_cast<int>(shotDifficulty);
        if (ImGui::Combo("Shot Difficulty", &curDiff, diffLevels, IM_ARRAYSIZE(diffLevels))) {
            shotDifficulty = static_cast<ShotDifficulty>(curDiff);
            requestImmediateReset = true;
            changed = true;
        }

        // Shot Category Multi-Select
        if (scenarioMode == ScenarioMode::MovingPack) {
            ImGui::Text("Active Shot Categories (Check to include):");
            if (ImGui::Checkbox("Redirects (From Behind / Over Car)", &enableRedirects)) changed = true;
            ImGui::SameLine();
            if (ImGui::Checkbox("Crossfield Passes", &enableCrosses)) changed = true;
            if (ImGui::Checkbox("Clearing Pops & Feeds", &enableClearingPops)) changed = true;
            ImGui::SameLine();
            if (ImGui::Checkbox("Backboard Rebound Reads", &enableBackboardReads)) changed = true;
        }

        if (ImGui::RangeSliderFloat("Initial Ball Speed [Min - Max]", &minKph, &maxKph, 10.0f, 150.0f, "%.0f - %.0f KPH")) changed = true;
        if (ImGui::RangeSliderFloat("Ball Distance From Car", &ballDistXYMin, &ballDistXYMax, 300.0f, 4000.0f, "%.0f - %.0f")) changed = true;
        if (ImGui::RangeSliderFloat("Ball Elevation / Height", &ballHeightMin, &ballHeightMax, 93.0f, 1500.0f, "%.0f - %.0f")) changed = true;

        // --- SECTION: CAR SPAWNING CONTROLS ---
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::TextColored(ImVec4(0.3f, 0.7f, 1.0f, 1.0f), "CAR SPAWN POSITIONING");
        ImGui::Separator();

        if (ImGui::RangeSliderFloat("Distance from Goal [Min - Max]", &carGoalDistMin, &carGoalDistMax, 1200.0f, 5200.0f, "%.0f - %.0f")) changed = true;
        if (ImGui::SliderFloat("Lane Width (Sideline Avoidance)", &carMaxLateralX, 500.0f, 2800.0f, "+/- %.0f")) changed = true;
    }

    char kphFormatBuf[64];
    if (requiredMaxHitKph >= 200.0f) {
        snprintf(kphFormatBuf, sizeof(kphFormatBuf), "Min: %.0f KPH  |  Max: 200+ KPH (Uncapped)", requiredMinHitKph);
    } else {
        snprintf(kphFormatBuf, sizeof(kphFormatBuf), "Min: %.0f KPH  |  Max: %.0f KPH", requiredMinHitKph, requiredMaxHitKph);
    }
    ImGui::Text("Required Target Hit Speed: %s", kphFormatBuf);
    if (ImGui::RangeSliderFloat("Hit Speed Range (KPH)", &requiredMinHitKph, &requiredMaxHitKph, 0.0f, 200.0f, "%.0f - %.0f")) {
        changed = true;
    }

    if (ImGui::Checkbox("Lock Current Shot Setup (Repeat)", &lockCurrentShot)) changed = true;

    // --- SECTION: TRAJECTORY & LASER LINE ---
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextColored(ImVec4(1.0f, 0.85f, 0.2f, 1.0f), "BALL TRAJECTORY LASER");
    ImGui::Separator();

    if (ImGui::Checkbox("Show Ball Trajectory Laser", &showTrajectoryLine)) changed = true;
    if (showTrajectoryLine) {
        if (ImGui::SliderFloat("Laser Thickness", &trajectoryWidth, 1.0f, 15.0f, "%.1f px")) changed = true;
        if (ImGui::ColorEdit4("Laser Color", trajectoryColorRGBA)) changed = true;
    }

    // --- SECTION: HUD & DISPLAY ---
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextColored(ImVec4(0.8f, 0.4f, 1.0f, 1.0f), "HUD & DISPLAY");
    ImGui::Separator();

    if (ImGui::SliderFloat("HUD Text Scale", &hudScale, 0.8f, 3.5f, "%.1fx")) changed = true;
    if (ImGui::ColorEdit4("HUD Font Color", hudColorRGBA)) changed = true;
    if (ImGui::Checkbox("Show Dark Backdrop Box", &hudShowBackground)) changed = true;
    if (ImGui::SliderFloat("HUD Position X", &hudPosX, 10.0f, 1920.0f, "%.0f px")) changed = true;
    if (ImGui::SliderFloat("HUD Position Y", &hudPosY, 10.0f, 1080.0f, "%.0f px")) changed = true;

    // --- SECTION: TRAINING RULES ---
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "TRAINING RULES");
    ImGui::Separator();

    if (ImGui::Checkbox("Infinite Shot Time", &infiniteShotTime)) changed = true;
    if (!infiniteShotTime) {
        if (ImGui::SliderFloat("Shot Timeout", &shotTimeout, 3.0f, 30.0f, "%.1f s")) changed = true;
    }

    if (ImGui::Checkbox("Fail on Ground Touch (After Hit)", &failOnGroundTouch)) changed = true;
    if (ImGui::Checkbox("Infinite Backwall Bounces (Goal Net Mode)", &infiniteBackwallHits)) changed = true;
    if (!infiniteBackwallHits) {
        if (ImGui::SliderInt("Allowed Backwall Bounces", &maxBackwallHits, 0, 5)) changed = true;
    }

    if (changed) {
        SaveSettingsToCvars();
    }
}