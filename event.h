/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /event.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#if SEAM >= SCRIPT2_DIC
#ifndef SCRIPT2_EVENT_C
#define SCRIPT2_EVENT_C

namespace _ {

/* Interface for an abstract event.
 */
struct Event {
  /* Virtual destructor. */
  virtual ~Event() = 0;

  /* Triggers the event. */
  virtual void Trigger() = 0;
};

struct EventInput {};

typedef enum {
  SDL_FIRSTEVENT = 0,
  SDL_QUIT = 0x100,
  SDL_APP_TERMINATING,
  SDL_APP_LOWMEMORY,
  SDL_APP_WILLENTERBACKGROUND,
  SDL_APP_DIDENTERBACKGROUND,
  SDL_APP_WILLENTERFOREGROUND,
  SDL_APP_DIDENTERFOREGROUND,
  SDL_DISPLAYEVENT = 0x150,
  SDL_WINDOWEVENT = 0x200,
  SDL_SYSWMEVENT,
  SDL_KEYDOWN = 0x300,
  SDL_KEYUP,
  SDL_TEXTEDITING,
  SDL_TEXTINPUT,
  SDL_KEYMAPCHANGED,
  SDL_MOUSEMOTION = 0x400,
  SDL_MOUSEBUTTONDOWN,
  SDL_MOUSEBUTTONUP,
  SDL_MOUSEWHEEL,
  SDL_JOYAXISMOTION = 0x600,
  SDL_JOYBALLMOTION,
  SDL_JOYHATMOTION,
  SDL_JOYBUTTONDOWN,
  SDL_JOYBUTTONUP,
  SDL_JOYDEVICEADDED,
  SDL_JOYDEVICEREMOVED,
  SDL_CONTROLLERAXISMOTION = 0x650,
  SDL_CONTROLLERBUTTONDOWN,
  SDL_CONTROLLERBUTTONUP,
  SDL_CONTROLLERDEVICEADDED,
  SDL_CONTROLLERDEVICEREMOVED,
  SDL_CONTROLLERDEVICEREMAPPED,
  SDL_FINGERDOWN = 0x700,
  SDL_FINGERUP,
  SDL_FINGERMOTION,
  SDL_DOLLARGESTURE = 0x800,
  SDL_DOLLARRECORD,
  SDL_MULTIGESTURE,
  SDL_CLIPBOARDUPDATE = 0x900,
  SDL_DROPFILE = 0x1000,
  SDL_DROPTEXT,
  SDL_DROPBEGIN,
  SDL_DROPCOMPLETE,
  SDL_AUDIODEVICEADDED = 0x1100,
  SDL_AUDIODEVICEREMOVED,
  SDL_SENSORUPDATE = 0x1200,
  SDL_RENDER_TARGETS_RESET = 0x2000,
  SDL_RENDER_DEVICE_RESET,
  SDL_USEREVENT = 0x8000,
  SDL_LASTEVENT = 0xFFFF
} SDL_EventType;

typedef struct SDL_CommonEvent {
  Uint32 type;
  Uint32 timestamp;
} SDL_CommonEvent;

typedef struct SDL_DisplayEvent {
  Uint32 type;
  Uint32 timestamp;
  Uint32 display;
  Uint8 event;
  Uint8 padding1;
  Uint8 padding2;
  Uint8 padding3;
  Sint32 data1;
} SDL_DisplayEvent;

typedef struct SDL_WindowEvent {
  Uint32 type;
  Uint32 timestamp;
  Uint32 windowID;
  Uint8 event;
  Uint8 padding1;
  Uint8 padding2;
  Uint8 padding3;
  Sint32 data1;
  Sint32 data2;
} SDL_WindowEvent;

typedef struct SDL_KeyboardEvent {
  Uint32 type;      /**< ::SDL_KEYDOWN or ::SDL_KEYUP */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
  Uint32 windowID;  /**< The window with keyboard focus, if any */
  Uint8 state;      /**< ::SDL_PRESSED or ::SDL_RELEASED */
  Uint8 repeat;     /**< Non-zero if this is a key repeat */
  Uint8 padding2;
  Uint8 padding3;
  SDL_Keysym keysym; /**< The key that was pressed or released */
} SDL_KeyboardEvent;

#define SDL_TEXTEDITINGEVENT_TEXT_SIZE (32)
/**
 *  \brief Keyboard text editing event structure (event.edit.*)
 */
typedef struct SDL_TextEditingEvent {
  Uint32 type;      /**< ::SDL_TEXTEDITING */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
  Uint32 windowID;  /**< The window with keyboard focus, if any */
  char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE]; /**< The editing text */
  Sint32 start;  /**< The start cursor of selected editing text */
  Sint32 length; /**< The length of selected editing text */
} SDL_TextEditingEvent;

#define SDL_TEXTINPUTEVENT_TEXT_SIZE (32)
/**
 *  \brief Keyboard text input event structure (event.text.*)
 */
typedef struct SDL_TextInputEvent {
  Uint32 type;      /**< ::SDL_TEXTINPUT */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
  Uint32 windowID;  /**< The window with keyboard focus, if any */
  char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]; /**< The input text */
} SDL_TextInputEvent;

/**
 *  \brief Mouse motion event structure (event.motion.*)
 */
typedef struct SDL_MouseMotionEvent {
  Uint32 type;      /**< ::SDL_MOUSEMOTION */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
  Uint32 windowID;  /**< The window with mouse focus, if any */
  Uint32 which;     /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
  Uint32 state;     /**< The current button state */
  Sint32 x;         /**< X coordinate, relative to window */
  Sint32 y;         /**< Y coordinate, relative to window */
  Sint32 xrel;      /**< The relative motion in the X direction */
  Sint32 yrel;      /**< The relative motion in the Y direction */
} SDL_MouseMotionEvent;

/**
 *  \brief Mouse button event structure (event.button.*)
 */
typedef struct SDL_MouseButtonEvent {
  Uint32 type;      /**< ::SDL_MOUSEBUTTONDOWN or ::SDL_MOUSEBUTTONUP */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
  Uint32 windowID;  /**< The window with mouse focus, if any */
  Uint32 which;     /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
  Uint8 button;     /**< The mouse button index */
  Uint8 state;      /**< ::SDL_PRESSED or ::SDL_RELEASED */
  Uint8 clicks;     /**< 1 for single-click, 2 for double-click, etc. */
  Uint8 padding1;
  Sint32 x; /**< X coordinate, relative to window */
  Sint32 y; /**< Y coordinate, relative to window */
} SDL_MouseButtonEvent;

/**
 *  \brief Mouse wheel event structure (event.wheel.*)
 */
typedef struct SDL_MouseWheelEvent {
  Uint32 type;      /**< ::SDL_MOUSEWHEEL */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
  Uint32 windowID;  /**< The window with mouse focus, if any */
  Uint32 which;     /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
  Sint32 x; /**< The amount scrolled horizontally, positive to the right and
               negative to the left */
  Sint32 y; /**< The amount scrolled vertically, positive away from the user and
               negative toward the user */
  Uint32 direction; /**< Set to one of the SDL_MOUSEWHEEL_* defines. When
                       FLIPPED the values in X and Y will be opposite. Multiply
                       by -1 to change them back */
} SDL_MouseWheelEvent;

/**
 *  \brief Joystick axis motion event structure (event.jaxis.*)
 */
typedef struct SDL_JoyAxisEvent {
  Uint32 type;          /**< ::SDL_JOYAXISMOTION */
  Uint32 timestamp;     /**< In milliseconds, populated using SDL_GetTicks() */
  SDL_JoystickID which; /**< The joystick instance id */
  Uint8 axis;           /**< The joystick axis index */
  Uint8 padding1;
  Uint8 padding2;
  Uint8 padding3;
  Sint16 value; /**< The axis value (range: -32768 to 32767) */
  Uint16 padding4;
} SDL_JoyAxisEvent;

/**
 *  \brief Joystick trackball motion event structure (event.jball.*)
 */
typedef struct SDL_JoyBallEvent {
  Uint32 type;          /**< ::SDL_JOYBALLMOTION */
  Uint32 timestamp;     /**< In milliseconds, populated using SDL_GetTicks() */
  SDL_JoystickID which; /**< The joystick instance id */
  Uint8 ball;           /**< The joystick trackball index */
  Uint8 padding1;
  Uint8 padding2;
  Uint8 padding3;
  Sint16 xrel; /**< The relative motion in the X direction */
  Sint16 yrel; /**< The relative motion in the Y direction */
} SDL_JoyBallEvent;

/**
 *  \brief Joystick hat position change event structure (event.jhat.*)
 */
typedef struct SDL_JoyHatEvent {
  Uint32 type;          /**< ::SDL_JOYHATMOTION */
  Uint32 timestamp;     /**< In milliseconds, populated using SDL_GetTicks() */
  SDL_JoystickID which; /**< The joystick instance id */
  Uint8 hat;            /**< The joystick hat index */
  Uint8 value;          /**< The hat position value.
                         *   \sa ::SDL_HAT_LEFTUP ::SDL_HAT_UP ::SDL_HAT_RIGHTUP
                         *   \sa ::SDL_HAT_LEFT ::SDL_HAT_CENTERED ::SDL_HAT_RIGHT
                         *   \sa ::SDL_HAT_LEFTDOWN ::SDL_HAT_DOWN ::SDL_HAT_RIGHTDOWN
                         *
                         *   Note that zero means the POV is centered.
                         */
  Uint8 padding1;
  Uint8 padding2;
} SDL_JoyHatEvent;

/**
 *  \brief Joystick button event structure (event.jbutton.*)
 */
typedef struct SDL_JoyButtonEvent {
  Uint32 type;          /**< ::SDL_JOYBUTTONDOWN or ::SDL_JOYBUTTONUP */
  Uint32 timestamp;     /**< In milliseconds, populated using SDL_GetTicks() */
  SDL_JoystickID which; /**< The joystick instance id */
  Uint8 button;         /**< The joystick button index */
  Uint8 state;          /**< ::SDL_PRESSED or ::SDL_RELEASED */
  Uint8 padding1;
  Uint8 padding2;
} SDL_JoyButtonEvent;

/**
 *  \brief Joystick device event structure (event.jdevice.*)
 */
typedef struct SDL_JoyDeviceEvent {
  Uint32 type;      /**< ::SDL_JOYDEVICEADDED or ::SDL_JOYDEVICEREMOVED */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
  Sint32 which; /**< The joystick device index for the ADDED event, instance id
                   for the REMOVED event */
} SDL_JoyDeviceEvent;

/**
 *  \brief Game controller axis motion event structure (event.caxis.*)
 */
typedef struct SDL_ControllerAxisEvent {
  Uint32 type;          /**< ::SDL_CONTROLLERAXISMOTION */
  Uint32 timestamp;     /**< In milliseconds, populated using SDL_GetTicks() */
  SDL_JoystickID which; /**< The joystick instance id */
  Uint8 axis;           /**< The controller axis (SDL_GameControllerAxis) */
  Uint8 padding1;
  Uint8 padding2;
  Uint8 padding3;
  Sint16 value; /**< The axis value (range: -32768 to 32767) */
  Uint16 padding4;
} SDL_ControllerAxisEvent;

/**
 *  \brief Game controller button event structure (event.cbutton.*)
 */
typedef struct SDL_ControllerButtonEvent {
  Uint32 type; /**< ::SDL_CONTROLLERBUTTONDOWN or ::SDL_CONTROLLERBUTTONUP */
  Uint32 timestamp;     /**< In milliseconds, populated using SDL_GetTicks() */
  SDL_JoystickID which; /**< The joystick instance id */
  Uint8 button;         /**< The controller button (SDL_GameControllerButton) */
  Uint8 state;          /**< ::SDL_PRESSED or ::SDL_RELEASED */
  Uint8 padding1;
  Uint8 padding2;
} SDL_ControllerButtonEvent;

/**
 *  \brief Controller device event structure (event.cdevice.*)
 */
typedef struct SDL_ControllerDeviceEvent {
  Uint32 type; /**< ::SDL_CONTROLLERDEVICEADDED, ::SDL_CONTROLLERDEVICEREMOVED,
                  or ::SDL_CONTROLLERDEVICEREMAPPED */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
  Sint32 which; /**< The joystick device index for the ADDED event, instance id
                   for the REMOVED or REMAPPED event */
} SDL_ControllerDeviceEvent;

/**
 *  \brief Audio device event structure (event.adevice.*)
 */
typedef struct SDL_AudioDeviceEvent {
  Uint32 type;      /**< ::SDL_AUDIODEVICEADDED, or ::SDL_AUDIODEVICEREMOVED */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
  Uint32 which;     /**< The audio device index for the ADDED event (valid until
                       next SDL_GetNumAudioDevices() call), SDL_AudioDeviceID for
                       the REMOVED event */
  Uint8
      iscapture; /**< zero if an output device, non-zero if a capture device. */
  Uint8 padding1;
  Uint8 padding2;
  Uint8 padding3;
} SDL_AudioDeviceEvent;

/**
 *  \brief Touch finger event structure (event.tfinger.*)
 */
typedef struct SDL_TouchFingerEvent {
  Uint32 type; /**< ::SDL_FINGERMOTION or ::SDL_FINGERDOWN or ::SDL_FINGERUP */
  Uint32 timestamp;    /**< In milliseconds, populated using SDL_GetTicks() */
  SDL_TouchID touchId; /**< The touch device id */
  SDL_FingerID fingerId;
  float x;        /**< Normalized in the range 0...1 */
  float y;        /**< Normalized in the range 0...1 */
  float dx;       /**< Normalized in the range -1...1 */
  float dy;       /**< Normalized in the range -1...1 */
  float pressure; /**< Normalized in the range 0...1 */
} SDL_TouchFingerEvent;

/**
 *  \brief Multiple Finger Gesture Event (event.mgesture.*)
 */
typedef struct SDL_MultiGestureEvent {
  Uint32 type;         /**< ::SDL_MULTIGESTURE */
  Uint32 timestamp;    /**< In milliseconds, populated using SDL_GetTicks() */
  SDL_TouchID touchId; /**< The touch device id */
  float dTheta;
  float dDist;
  float x;
  float y;
  Uint16 numFingers;
  Uint16 padding;
} SDL_MultiGestureEvent;

/**
 * \brief Dollar Gesture Event (event.dgesture.*)
 */
typedef struct SDL_DollarGestureEvent {
  Uint32 type;         /**< ::SDL_DOLLARGESTURE or ::SDL_DOLLARRECORD */
  Uint32 timestamp;    /**< In milliseconds, populated using SDL_GetTicks() */
  SDL_TouchID touchId; /**< The touch device id */
  SDL_GestureID gestureId;
  Uint32 numFingers;
  float error;
  float x; /**< Normalized center of gesture */
  float y; /**< Normalized center of gesture */
} SDL_DollarGestureEvent;

/**
 *  \brief An event used to request a file open by the system (event.drop.*)
 *         This event is enabled by default, you can disable it with
 * SDL_EventState(). \note If this event is enabled, you must free the filename
 * in the event.
 */
typedef struct SDL_DropEvent {
  Uint32 type;      /**< ::SDL_DROPBEGIN or ::SDL_DROPFILE or ::SDL_DROPTEXT or
                       ::SDL_DROPCOMPLETE */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
  char *file; /**< The file name, which should be freed with SDL_free(), is NULL
                 on begin/complete */
  Uint32 windowID; /**< The window that was dropped on, if any */
} SDL_DropEvent;

/**
 *  \brief Sensor event structure (event.sensor.*)
 */
typedef struct SDL_SensorEvent {
  Uint32 type;      /**< ::SDL_SENSORUPDATE */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
  Sint32 which;     /**< The instance ID of the sensor */
  float data[6]; /**< Up to 6 values from the sensor - additional values can be
                    queried using SDL_SensorGetData() */
} SDL_SensorEvent;

/**
 *  \brief The "quit requested" event
 */
typedef struct SDL_QuitEvent {
  Uint32 type;      /**< ::SDL_QUIT */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
} SDL_QuitEvent;

/**
 *  \brief OS Specific event
 */
typedef struct SDL_OSEvent {
  Uint32 type;      /**< ::SDL_QUIT */
  Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
} SDL_OSEvent;

typedef struct SDL_UserEvent {
  Uint32 type;
  Uint32 timestamp;
  Uint32 windowID;
  Sint32 code;
  void *data1;
  void *data2;
} SDL_UserEvent;

struct SDL_SysWMmsg;
typedef struct SDL_SysWMmsg SDL_SysWMmsg;

typedef struct SDL_SysWMEvent {
  Uint32 type;
  Uint32 timestamp;
  SDL_SysWMmsg *msg;
} SDL_SysWMEvent;

typedef union SDL_Event {
  Uint32 type;
  SDL_CommonEvent common;
  SDL_DisplayEvent display;
  SDL_WindowEvent window;
  SDL_KeyboardEvent key;
  SDL_TextEditingEvent edit;
  SDL_TextInputEvent text;
  SDL_MouseMotionEvent motion;
  SDL_MouseButtonEvent button;
  SDL_MouseWheelEvent wheel;
  SDL_JoyAxisEvent jaxis;
  SDL_JoyBallEvent jball;
  SDL_JoyHatEvent jhat;
  SDL_JoyButtonEvent jbutton;
  SDL_JoyDeviceEvent jdevice;
  SDL_ControllerAxisEvent caxis;
  SDL_ControllerButtonEvent cbutton;
  SDL_ControllerDeviceEvent cdevice;
  SDL_AudioDeviceEvent adevice;
  SDL_SensorEvent sensor;
  SDL_QuitEvent quit;
  SDL_UserEvent user;
  SDL_SysWMEvent syswm;
  SDL_TouchFingerEvent tfinger;
  SDL_MultiGestureEvent mgesture;
  SDL_DollarGestureEvent dgesture;
  SDL_DropEvent drop;

  Uint8 padding[56];
} SDL_Event;

SDL_COMPILE_TIME_ASSERT(SDL_Event, sizeof(SDL_Event) == 56);

extern DECLSPEC void SDLCALL SDL_PumpEvents(void);

typedef enum { SDL_ADDEVENT, SDL_PEEKEVENT, SDL_GETEVENT } SDL_eventaction;

extern DECLSPEC int SDLCALL SDL_PeepEvents(SDL_Event *events, int numevents,
                                           SDL_eventaction action,
                                           Uint32 minType, Uint32 maxType);

extern DECLSPEC SDL_bool SDLCALL SDL_HasEvent(Uint32 type);
extern DECLSPEC SDL_bool SDLCALL SDL_HasEvents(Uint32 minType, Uint32 maxType);

extern DECLSPEC void SDLCALL SDL_FlushEvent(Uint32 type);
extern DECLSPEC void SDLCALL SDL_FlushEvents(Uint32 minType, Uint32 maxType);

extern DECLSPEC int SDLCALL SDL_PollEvent(SDL_Event *event);

extern DECLSPEC int SDLCALL SDL_WaitEvent(SDL_Event *event);

extern DECLSPEC int SDLCALL SDL_WaitEventTimeout(SDL_Event *event, int timeout);

extern DECLSPEC int SDLCALL SDL_PushEvent(SDL_Event *event);

typedef int(SDLCALL *SDL_EventFilter)(void *userdata, SDL_Event *event);

extern DECLSPEC void SDLCALL SDL_SetEventFilter(SDL_EventFilter filter,
                                                void *userdata);

extern DECLSPEC SDL_bool SDLCALL SDL_GetEventFilter(SDL_EventFilter *filter,
                                                    void **userdata);

extern DECLSPEC void SDLCALL SDL_AddEventWatch(SDL_EventFilter filter,
                                               void *userdata);

extern DECLSPEC void SDLCALL SDL_DelEventWatch(SDL_EventFilter filter,
                                               void *userdata);

extern DECLSPEC void SDLCALL SDL_FilterEvents(SDL_EventFilter filter,
                                              void *userdata);

/* @{ */
#define SDL_QUERY -1
#define SDL_IGNORE 0
#define SDL_DISABLE 0
#define SDL_ENABLE 1

extern DECLSPEC Uint8 SDLCALL SDL_EventState(Uint32 type, int state);

#define SDL_GetEventState(type) SDL_EventState(type, SDL_QUERY)

extern DECLSPEC Uint32 SDLCALL SDL_RegisterEvents(int numevents);

}  // namespace _
#endif
#endif
