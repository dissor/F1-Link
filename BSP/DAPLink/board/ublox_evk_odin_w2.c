/**
 * @file    ublox_evk_odin_w2.c
 * @brief   board ID for the u-blox EVK-ODIN-W2 board
 *
 * DAPLink Interface Firmware
 * Copyright (c) 2017-2019, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "target_family.h"
#include "target_board.h"

const board_info_t g_board_info = {
    .info_version = kBoardInfoVersion,
    .board_id = "1236",
    .family_id = kStub_HWReset_FamilyID,
    .daplink_target_url = "https://os.mbed.com/platforms/ublox-EVK-ODIN-W2/",
    .target_cfg = &target_device,
    .board_vendor = "u-blox",
    .board_name = "EVK-ODIN-W2",
};
