/*
 * Copyright (C) 2020 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <aidl/vendor/aospa/power/BnPowerFeature.h>
#include <android-base/file.h>
#include <linux/input.h>

namespace aidl {
namespace vendor {
namespace aospa {
namespace power {

static constexpr int kInputEventWakeupModeOff = 4;
static constexpr int kInputEventWakeupModeOn = 5;

bool setDeviceSpecificFeature(Feature feature, bool enabled) {
    switch (feature) {
        case Feature::DOUBLE_TAP: {
            int fd = open("/dev/input/event3", O_RDWR);
            struct input_event ev;
            ev.type = EV_SYN;
            ev.code = SYN_CONFIG;
            ev.value = enabled ? kInputEventWakeupModeOn : kInputEventWakeupModeOff;
            write(fd, &ev, sizeof(ev));
            close(fd);
	    return true;
        }
        default:
            return false;
    }
}

}  // namespace power
}  // namespace aospa
}  // namespace vendor
}  // namespace aidl
