/**
 * @copyright 2016 opencxa.org
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @author Christopher Armenio
 */
#include "ovr_beaconUpdate.h"


// ******** includes ********
#include <cxa_assert.h>


// ******** local macro definitions ********


// ******** local type definitions ********


// ******** local function prototypes ********


// ********  local variable declarations *********


// ******** global function implementations ********
bool ovr_beaconUpdate_init(ovr_beaconUpdate_t *const updateIn, int8_t rssi_dBmIn, cxa_fixedByteBuffer_t *const fbbIn)
{
	cxa_assert(updateIn);
	cxa_assert(fbbIn);

	updateIn->rssi_dBm = rssi_dBmIn;

	uint8_t devType_raw;
	if( !cxa_fixedByteBuffer_get_uint8(fbbIn, 0, devType_raw) ) return false;
	updateIn->devType = devType_raw;

	if( !cxa_uuid128_initFromBuffer(&updateIn->uuid, fbbIn, 1) ) return false;

	if( !cxa_fixedByteBuffer_get_uint8(fbbIn, 17, updateIn->txPower_1m) ) return false;

	uint8_t status_raw;
	if( !cxa_fixedByteBuffer_get_uint8(fbbIn, 18, status_raw) ) return false;
	updateIn->status.isEnumerating = status_raw & (1 << 7);
	updateIn->status.needsPoll = status_raw & (1 << 6);

	if( !cxa_fixedByteBuffer_get_uint8(fbbIn, 19, updateIn->batt_pcnt) ) return false;
	if( !cxa_fixedByteBuffer_get_uint8(fbbIn, 20, updateIn->currTemp_c) ) return false;

	return true;
}


cxa_uuid128_t* ovr_beaconUpdate_getUuid128(ovr_beaconUpdate_t *const updateIn)
{
	cxa_assert(updateIn);

	return &updateIn->uuid;
}


// ******** local function implementations ********