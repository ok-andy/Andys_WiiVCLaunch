#include "config.h"
#include "globals.hpp"
#include "logger.h"
#include <wups.h>
#include <wups/config/WUPSConfigItemBoolean.h>
#include <wups/config/WUPSConfigItemMultipleValues.h>
#include <string_view>

WUPS_USE_STORAGE("WiiVCLaunch");

void boolItemCallback(ConfigItemBoolean *item, bool newValue)
{
    if (item && item->identifier) {
        if (std::string_view(USE_CUSTOM_DIALOGS_CONFIG_ID) == item->identifier) {
            gUseCustomDialogs = newValue;
            WUPSStorageAPI::Store(item->identifier, gUseCustomDialogs);
        }
    }
}

void multipleValueItemCallback(ConfigItemMultipleValues *item, uint32_t newValue)
{
    if (item && item->identifier) {
        if (std::string_view(AUTOLAUNCH_DRC_SUPPORTED_CONFIG_ID) == item->identifier) {
            gAutolaunchDRCSupported = newValue;
            WUPSStorageAPI::Store(item->identifier, gAutolaunchDRCSupported);
        } else if (std::string_view(AUTOLAUNCH_NO_DRC_SUPPORT_CONFIG_ID) == item->identifier) {
            gAutolaunchNoDRCSupport = newValue;
            WUPSStorageAPI::Store(item->identifier, gAutolaunchNoDRCSupport);
        } else if (std::string_view(DISPLAY_OPTIONS_ORDER_CONFIG_ID) == item->identifier) {
            gDisplayOptionsOrder = newValue;
            WUPSStorageAPI::Store(item->identifier, gDisplayOptionsOrder);
        } else if (std::string_view(SET_RESOLUTION_CONFIG_ID) == item->identifier) {
            gSetResolution = newValue;
            WUPSStorageAPI::Store(item->identifier, gSetResolution);
        }
    }
}

WUPSConfigAPICallbackStatus ConfigMenuOpenedCallback(WUPSConfigCategoryHandle rootHandle)
{
    try {
        WUPSConfigCategory root = WUPSConfigCategory(rootHandle);

        // Category: Settings
        auto settings = WUPSConfigCategory::Create("Settings");

        // Autolaunch (GamePad supported)
        constexpr WUPSConfigItemMultipleValues::ValuePair autolaunchDRCSupportedValues[] = {
                {DISPLAY_OPTION_CHOOSE,  "Select each time"},
                {DISPLAY_OPTION_USE_DRC, "Use \ue087 as controller"},
                {DISPLAY_OPTION_TV,      "TV Only"},
                {DISPLAY_OPTION_BOTH,    "TV and \ue087"},
                {DISPLAY_OPTION_DRC,     "\ue087 screen only"}};

        settings.add(WUPSConfigItemMultipleValues::CreateFromValue(AUTOLAUNCH_DRC_SUPPORTED_CONFIG_ID,
                                                                   "Autolaunch (\ue087 supported)",
                                                                   DEFAULT_AUTOLAUNCH_DRC_SUPPORTED_VALUE,
                                                                   gAutolaunchDRCSupported,
                                                                   autolaunchDRCSupportedValues,
                                                                   &multipleValueItemCallback));

        // Autolaunch (GamePad not supported)
        constexpr WUPSConfigItemMultipleValues::ValuePair autolaunchNoDRCSupportValues[] = {
                {DISPLAY_OPTION_CHOOSE, "Select each time"},
                {DISPLAY_OPTION_TV,     "TV Only"},
                {DISPLAY_OPTION_BOTH,   "TV and \ue087"},
                {DISPLAY_OPTION_DRC,    "\ue087 screen only"}};

        settings.add(WUPSConfigItemMultipleValues::CreateFromValue(AUTOLAUNCH_NO_DRC_SUPPORT_CONFIG_ID,
                                                                   "Autolaunch (\ue087 not supported)",
                                                                   DEFAULT_AUTOLAUNCH_NO_DRC_SUPPORT_VALUE,
                                                                   gAutolaunchNoDRCSupport,
                                                                   autolaunchNoDRCSupportValues,
                                                                   &multipleValueItemCallback));

        // Set resolution
        constexpr WUPSConfigItemMultipleValues::ValuePair setResolutionValues[] = {
                {SET_RESOLUTION_NONE,    "Same as Wii U"},
                {SET_RESOLUTION_480P,    "480p"},
                {SET_RESOLUTION_480P_43, "480p (4:3)"},
                {SET_RESOLUTION_720P,    "720p"}};

        settings.add(WUPSConfigItemMultipleValues::CreateFromValue(SET_RESOLUTION_CONFIG_ID,
                                                                   "Set resolution",
                                                                   DEFAULT_SET_RESOLUTION_VALUE,
                                                                   gSetResolution,
                                                                   setResolutionValues,
                                                                   &multipleValueItemCallback));

        // Display options order
        constexpr WUPSConfigItemMultipleValues::ValuePair displayOptionsOrderValues[] = {
                {DISPLAY_OPTIONS_ORDER_DEFAULT, "Default"},
                {DISPLAY_OPTIONS_ORDER_RECENT,  "Recent"}};

        settings.add(WUPSConfigItemMultipleValues::CreateFromValue(DISPLAY_OPTIONS_ORDER_CONFIG_ID,
                                                                   "Display options order",
                                                                   DEFAULT_DISPLAY_OPTIONS_ORDER_VALUE,
                                                                   gDisplayOptionsOrder,
                                                                   displayOptionsOrderValues,
                                                                   &multipleValueItemCallback));

        root.add(std::move(settings));

        // Category: Advanced options
        auto advancedOptions = WUPSConfigCategory::Create("Advanced options");

        advancedOptions.add(WUPSConfigItemBoolean::Create(USE_CUSTOM_DIALOGS_CONFIG_ID,
                                                          "Use custom dialogs (Wii U Menu needs to be restarted)",
                                                          DEFAULT_USE_CUSTOM_DIALOGS_VALUE,
                                                          gUseCustomDialogs,
                                                          &boolItemCallback));

        root.add(std::move(advancedOptions));
    } catch (const std::exception &e) {
        DEBUG_FUNCTION_LINE_ERR("Exception: %s", e.what());
        return WUPSCONFIG_API_CALLBACK_RESULT_ERROR;
    }
    return WUPSCONFIG_API_CALLBACK_RESULT_SUCCESS;
}

void ConfigMenuClosedCallback()
{
    // Save all changes
    WUPSStorageAPI::SaveStorage();
}

void initConfig()
{
    WUPSConfigAPIOptionsV1 configOptions = {.name = "Wii VC Launch"};
    WUPSConfigAPI_Init(configOptions, ConfigMenuOpenedCallback, ConfigMenuClosedCallback);

    WUPSStorageAPI::GetOrStoreDefault(AUTOLAUNCH_DRC_SUPPORTED_CONFIG_ID, gAutolaunchDRCSupported, (int32_t) DEFAULT_AUTOLAUNCH_DRC_SUPPORTED_VALUE);

    WUPSStorageAPI::GetOrStoreDefault(AUTOLAUNCH_NO_DRC_SUPPORT_CONFIG_ID, gAutolaunchNoDRCSupport, (int32_t) DEFAULT_AUTOLAUNCH_NO_DRC_SUPPORT_VALUE);

    WUPSStorageAPI::GetOrStoreDefault(DISPLAY_OPTIONS_ORDER_CONFIG_ID, gDisplayOptionsOrder, (int32_t) DEFAULT_DISPLAY_OPTIONS_ORDER_VALUE);

    WUPSStorageAPI::GetOrStoreDefault(SET_RESOLUTION_CONFIG_ID, gSetResolution, (int32_t) DEFAULT_SET_RESOLUTION_VALUE);

    WUPSStorageAPI::GetOrStoreDefault(USE_CUSTOM_DIALOGS_CONFIG_ID, gUseCustomDialogs, DEFAULT_USE_CUSTOM_DIALOGS_VALUE);
}
