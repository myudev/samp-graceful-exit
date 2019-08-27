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

#include <mutex>
#include <queue>
#include <atomic>
#include "impl.hpp"
#include "common.hpp"
#ifdef WIN32 // yes I know we COULD have a single implementation file to CONFORM to STUFF or to be PROFESSIONAL or anything; but it's not about that.
#include "windowsimpl.hpp"
#else
#include "linuximpl.hpp"
#endif

std::mutex queue_mutex;
std::queue<int> signal_queue;
std::atomic<bool> handle_signals{ false };

void Impl::SetSignalHandling(bool handle)
{
	handle_signals = handle;
}

bool Impl::IsSignalHandled() { return handle_signals; }

void Impl::Startup()
{
#ifdef WIN32
	WindowsImpl::Setup();
#else
	LinuxImpl::Setup();
#endif
}

void Impl::ProcessQueue()
{
	std::lock_guard<std::mutex> lock(queue_mutex);
	while (!signal_queue.empty()) 
	{
		InvokeAMXFunc(signal_queue.front());
		signal_queue.pop();
	}
}

void Impl::SignalExit(int flags)
{
	std::lock_guard<std::mutex> lock(queue_mutex);
	signal_queue.emplace(flags);
}

void Impl::ExitProcess()
{
	exit(0);
}
