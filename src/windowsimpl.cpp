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

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "impl.hpp"
#include "windowsimpl.hpp"
#include <iostream>

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
	if (Impl::IsSignalHandled())
	{
		if (fdwCtrlType == CTRL_C_EVENT)
		{ // We are able to catch CTRL + C events.
			Impl::SignalExit(Impl::UserExit | Impl::CtrlC);
		}
		else
		{ // But we aren't able to catch other types of process shutdowns, windoof will kill the process so we delay.
			Impl::SignalExit(Impl::ForcedExit);
			Sleep(10000);
		}

		return true;
	}
	return false;
}

void WindowsImpl::Setup()
{
	SetConsoleCtrlHandler(CtrlHandler, TRUE);
}

#endif