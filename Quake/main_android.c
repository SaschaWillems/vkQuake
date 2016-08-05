/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2002-2005 John Fitzgibbons and others
Copyright (C) 2007-2008 Kristian Duske
Copyright (C) 2010-2014 QuakeSpasm developers

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "quakedef.h"
#if defined(SDL_FRAMEWORK) || defined(NO_SDL_CONFIG)
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif
#include <stdio.h>

#ifdef __ANDROID__
#include <android/native_activity.h>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>
#endif

/* need at least SDL_2.0.0 */
#define SDL_MIN_X	2
#define SDL_MIN_Y	0
#define SDL_MIN_Z	0
#define SDL_REQUIREDVERSION	(SDL_VERSIONNUM(SDL_MIN_X,SDL_MIN_Y,SDL_MIN_Z))
#define SDL_NEW_VERSION_REJECT	(SDL_VERSIONNUM(3,0,0))

#ifdef __ANDROID__
// Gamepad
// Left thumbstick
float axis_left_x = 0.0f;
float axis_left_y = 0.0f;
// Right thumbstick
float axis_right_x = 0.0f;
float axis_right_y = 0.0f;
// Trigger
bool trigger_left = false;
bool trigger_right = false;
#endif

static void Sys_AtExit (void)
{
	SDL_Quit();
}

static void Sys_InitSDL (void)
{
	SDL_version v;
	SDL_version *sdl_version = &v;
	SDL_GetVersion(&v);

	Sys_Printf("Found SDL version %i.%i.%i\n",sdl_version->major,sdl_version->minor,sdl_version->patch);
	if (SDL_VERSIONNUM(sdl_version->major,sdl_version->minor,sdl_version->patch) < SDL_REQUIREDVERSION)
	{	/*reject running under older SDL versions */
		Sys_Error("You need at least v%d.%d.%d of SDL to run this game.", SDL_MIN_X,SDL_MIN_Y,SDL_MIN_Z);
	}
	if (SDL_VERSIONNUM(sdl_version->major,sdl_version->minor,sdl_version->patch) >= SDL_NEW_VERSION_REJECT)
	{	/*reject running under newer (1.3.x) SDL */
		Sys_Error("Your version of SDL library is incompatible with me.\n"
			  "You need a library version in the line of %d.%d.%d\n", SDL_MIN_X,SDL_MIN_Y,SDL_MIN_Z);
	}


	if (SDL_Init(0) < 0)
	{
		Sys_Error("Couldn't init SDL: %s", SDL_GetError());
	}
	atexit(Sys_AtExit);
}

#define DEFAULT_MEMORY (256 * 1024 * 1024) // ericw -- was 72MB (64-bit) / 64MB (32-bit)

static quakeparms_t	parms;

#ifdef __ANDROID__
/* Called before SDL_main() to initialize JNI bindings in SDL library */
extern void SDL_Android_Init(JNIEnv* env, jclass cls);

void android_init()
{
	SDL_SetMainReady();

	int status;
	char *argv[2];
	argv[0] = SDL_strdup("vkQuake");
	argv[1] = NULL;

	int		t;
	double		time, oldtime, newtime;
	host_parms = &parms;
	parms.basedir = ".";

	isDedicated = (COM_CheckParm("-dedicated") != 0);

	Sys_InitSDL();

	Sys_Init();

	parms.memsize = DEFAULT_MEMORY;
	parms.membase = malloc(parms.memsize);

	Sys_Printf("Quake %1.2f (c) id Software\n", VERSION);
	Sys_Printf("GLQuake %1.2f (c) id Software\n", GLQUAKE_VERSION);
	Sys_Printf("FitzQuake %1.2f (c) John Fitzgibbons\n", FITZQUAKE_VERSION);
	Sys_Printf("FitzQuake SDL port (c) SleepwalkR, Baker\n");
	Sys_Printf("QuakeSpasm %1.2f.%d (c) Ozkan Sezer, Eric Wasylishen & others\n",
		QUAKESPASM_VERSION, QUAKESPASM_VER_PATCH);
	Sys_Printf("vkQuake %1.2f.%d (c) Axel Gneiting\n",
		VKQUAKE_VERSION, VKQUAKE_VER_PATCH);

	Host_Init();

	Sys_Printf("Initialization done");

	prepared = true;
}

int32_t handle_app_input(struct android_app* app, AInputEvent* event)
{
	int32_t eventType = AInputEvent_getType(event);

	if (eventType == AINPUT_EVENT_TYPE_MOTION)
	{
		if (AInputEvent_getSource(event) == AINPUT_SOURCE_JOYSTICK)
		{
			// Left thumbstick
			axis_left_x = AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_X, 0);
			axis_left_y = AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_Y, 0);
			// Right thumbstick
			axis_right_x = AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_Z, 0);
			axis_right_y = AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_RZ, 0);
			// Trigger
			trigger_left = AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_LTRIGGER, 0) > 0.0015f;
			trigger_right = AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_RTRIGGER, 0) > 0.0015f;
		}
		else
		{
			// todo : touch input
		}
	}

	if (eventType == AINPUT_EVENT_TYPE_KEY)
	{
		int32_t keyCode = AKeyEvent_getKeyCode((const AInputEvent*)event);
		int32_t action = AKeyEvent_getAction((const AInputEvent*)event);
		bool down = (action != AKEY_EVENT_ACTION_UP);

		switch (keyCode)
		{
		case AKEYCODE_DPAD_UP:
			Key_Event(K_UPARROW, down);
			break;
		case AKEYCODE_DPAD_DOWN:
			Key_Event(K_DOWNARROW, down);
			break;
		case AKEYCODE_DPAD_LEFT:
			Key_Event(K_LEFTARROW, down);
			break;
		case AKEYCODE_DPAD_RIGHT:
			Key_Event(K_RIGHTARROW, down);
			break;
		};

	}

	if (eventType == AINPUT_EVENT_TYPE_KEY)
	{
		int32_t keyCode = AKeyEvent_getKeyCode((const AInputEvent*)event);
		int32_t action = AKeyEvent_getAction((const AInputEvent*)event);
		int32_t button = 0;

		bool down = (action != AKEY_EVENT_ACTION_UP);

		switch (keyCode)
		{
		case AKEYCODE_BUTTON_A:
			Key_Event(K_ENTER, down);
			break;
		case AKEYCODE_BUTTON_B:
			Key_Event(K_ESCAPE, down);
			return 1;
			break;
		case AKEYCODE_BUTTON_X:
			Key_Event(K_MOUSE1, down);
			break;
		case AKEYCODE_BUTTON_Y:
			Con_ToggleConsole_f();
			break;
		case AKEYCODE_BUTTON_L1:
			Key_Event(K_LTRIGGER, down);
			break;
		case AKEYCODE_BUTTON_R1:
			Key_Event(K_RTRIGGER, down);
			break;
		case AKEYCODE_BUTTON_START:
			break;
		case AKEYCODE_BUTTON_THUMBL:
			Key_Event(K_LTHUMB, down);
			break;			
		case AKEYCODE_BUTTON_THUMBR:
			Key_Event(K_RTHUMB, down);
			break;			
		};
	}

	return 0;
}

void handle_app_cmd(struct android_app * app, int32_t cmd)
{
	switch (cmd)
	{
	case APP_CMD_SAVE_STATE:
		LOGD("APP_CMD_SAVE_STATE");
		break;
	case APP_CMD_INIT_WINDOW:
		LOGD("APP_CMD_INIT_WINDOW");
		if (app->window != NULL)
		{
			android_app->window = app->window;
			android_init();
		}
		else
		{
			LOGE("No window assigned!");
		}
		break;
	case APP_CMD_LOST_FOCUS:
		LOGD("APP_CMD_LOST_FOCUS");
		break;
	case APP_CMD_GAINED_FOCUS:
		LOGD("APP_CMD_GAINED_FOCUS");
		break;
	}
}

void android_main_loop()
{
	while (1)
	{
		int ident;
		int events;
		struct android_poll_source* source;
		bool destroy = false;

		qboolean focused = true;

		while ((ident = ALooper_pollAll(focused ? 0 : -1, NULL, &events, (void**)&source)) >= 0)
		{
			if (source != NULL)
			{
				source->process(android_app, source);
			}
			if (android_app->destroyRequested != 0)
			{
				LOGD("Android app destroy requested");
				destroy = true;
				break;
			}
		}

		// App destruction requested
		// Exit loop, example will be destroyed in application main
		if (destroy)
		{
			break;
		}

		// Render frame
		if (prepared)
		{
			int		t;
			double		time, oldtime, newtime;

			newtime = Sys_DoubleTime();
			time = newtime - oldtime;

			Host_Frame(time);

			//if (time < sys_throttle.value)
			//	SDL_Delay(1);

			oldtime = newtime;

			// Update input state
			const float deadZone = 0.0015f;
			const float range = 1.0f - deadZone;

			// Move
			if (fabsf(axis_left_y) > deadZone)
			{
				//float pos = (fabsf(axis_left_y) - deadZone) / range;
				//float mvm = pos * ((axis_right_y < 0.0f) ? -1.0f : 1.0f) * 15.0f;
				//cmd->forwardmove -= m_forward.value * dmy;
			}
			if (fabsf(axis_left_x) > deadZone)
			{
				//float pos = (fabsf(axis_left_x) - deadZone) / range;
				//float mvm = pos * ((axis_left_x < 0.0f) ? -1.0f : 1.0f) * 15.0f;
			}

			// Look
			if (fabsf(axis_right_x) > deadZone)
			{
				float pos = (fabsf(axis_right_x) - deadZone) / range;
				float rot = pos * ((axis_right_x < 0.0f) ? -1.0f : 1.0f) * 0.025f;
				cl.viewangles[YAW] -= m_yaw.value * rot;
			}

			if (fabsf(axis_right_y) > deadZone)
			{
				float pos = (fabsf(axis_right_y) - deadZone) / range;
				float rot = pos * ((axis_right_y < 0.0f) ? -1.0f : 1.0f) * 0.025f;
				cl.viewangles[PITCH] += m_pitch.value * rot;
			}

			// Strate (using trigger)
			if (trigger_left)
			{
			}
			if (trigger_right)
			{
			}
		}
	}
}

void android_main(struct android_app* state)
{
	Sys_Printf("Start vkQuake for Android...");

	// This is important, if this is missing the compiler may remove the android_main entry point
	// And the app will fail to start
	app_dummy();

	// Store global reference to android app state
	android_app = state;

	state->onAppCmd = handle_app_cmd;
	state->onInputEvent = handle_app_input;

	android_main_loop();
}
#endif

