/*
 * This file is part of SAMP Graceful Exit.
 *
 * SAMP Graceful Exit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SAMP Graceful Exit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with SAMP Graceful Exit.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @license LGPL-3.0
 * @copyright 2019 MyU
 * @author MyU <myudev0@gmail.com>
 *
 */

#include <amx/amx.h>
#include <plugincommon.h>
#include <vector>
#include <algorithm>

#include "common.hpp"
#include "natives.hpp"
#include "impl.hpp"

logprintf_t logprintf;
std::vector<AMX*> amx_pool;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	Impl::ProcessQueue();
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	Impl::Startup();
    return true;
}

extern "C" const AMX_NATIVE_INFO native_list[] = {
    { "SetCatchExit", Natives::SetCatchExit },
	{ "ExitProcess", Natives::ExitProcess },
    { NULL, NULL }
};

void InvokeAMXFunc(int flags)
{
	cell amx_idx;
	for(AMX* &amx : amx_pool)
	{
		if (!amx_FindPublic(amx, "OnUngracefulExit", &amx_idx))
		{
			amx_Push(amx, flags);
			amx_Exec(amx, nullptr, amx_idx);
		}
	}
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx)
{
	amx_pool.push_back(amx);
    return amx_Register(amx, native_list, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL Unload()
{
    return 1;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
	amx_pool.erase(
		std::remove_if(amx_pool.begin(), amx_pool.end(),
			[amx](const AMX* o) { return (o = amx); }),
		amx_pool.end()); // eww²
    return 1;
}
