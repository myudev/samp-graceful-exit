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

#ifndef WIN32
#include "impl.hpp"
#include "linuximpl.hpp"
#include "common.hpp"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void SignalHandler(int signum)
{
	if (Impl::IsSignalHandled())
	{
		// note: Linux is merciless.. SIGKILL will kill the process no matter what. So who needs forced exit?
		
		if (signum == SIGINT)
		{
			Impl::SignalExit(Impl::UserExit | Impl::CtrlC);
		}
		else if(signum == SIGTERM || signum == SIGQUIT)
		{
			Impl::SignalExit(Impl::UserExit);
		}
		else // assume forced exit
		{
			Impl::SignalExit(Impl::ForcedExit);
		}
	}
	else
	{
		exit(0);
	}
}

void UserSignalHandler(int signum)
{
	if (signum == SIGUSR1)
	{
		Impl::SignalExit(Impl::UserSig1);
	}
	else if(signum == SIGUSR2)
	{
		Impl::SignalExit(Impl::UserSig2);
	}
}

void LinuxImpl::Setup()
{
	struct sigaction sigk_handler{}, sigu_handler{};

	sigk_handler.sa_handler = SignalHandler;
	sigemptyset(&sigk_handler.sa_mask);
	sigk_handler.sa_flags = 0;

	sigaction(SIGINT, &sigk_handler, NULL); // Terminal interrupt (CTRL+C f.e.)
	sigaction(SIGTERM, &sigk_handler, NULL); // Termination (default kill behaviour)
	sigaction(SIGSTOP, &sigk_handler, NULL); // Stop executing
	sigaction(SIGQUIT, &sigk_handler, NULL); // Terminal quit
	
	// Bonus!
	// We handle user signales and pass them to pawn it's not what we need to do but it's a neat little addition for automation.
	sigu_handler.sa_handler = UserSignalHandler;
	sigemptyset(&sigu_handler.sa_mask);
	sigu_handler.sa_flags = 0;
	
	sigaction(SIGUSR1, &sigu_handler, NULL); // Stop executing
	sigaction(SIGUSR2, &sigu_handler, NULL); // Terminal quit
	
	logprintf("> Linux impl detected.");
}

#endif