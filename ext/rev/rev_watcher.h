/*
 * Copyright (C) 2007 Tony Arcieri
 * You may redistribute this under the terms of the Ruby license.
 * See LICENSE for details
 */

#ifndef REV_WATCHER_H
#define REV_WATCHER_H

#define Watcher_Attach(watcher_type, detach_func, watcher, loop) \
  struct Rev_Watcher *watcher_data; \
  struct Rev_Loop *loop_data; \
  \
  if(!rb_obj_is_kind_of(loop, cRev_Loop)) \
    rb_raise(rb_eArgError, "expected loop to be an instance of Rev::Loop"); \
  \
  Data_Get_Struct(watcher, struct Rev_Watcher, watcher_data); \
  Data_Get_Struct(loop, struct Rev_Loop, loop_data); \
  \
  if(watcher_data->loop != Qnil) \
    detach_func(watcher); \
  \
  watcher_data->loop = loop; \
  ev_##watcher_type##_start(loop_data->ev_loop, &watcher_data->event_types.ev_##watcher_type); \
  rb_call_super(1, &loop)

#define Watcher_Detach(watcher_type, watcher) \
  struct Rev_Watcher *watcher_data; \
  struct Rev_Loop *loop_data; \
  \
  Data_Get_Struct(watcher, struct Rev_Watcher, watcher_data); \
  \
  if(watcher_data->loop == Qnil) \
    rb_raise(rb_eRuntimeError, "not attached to a loop"); \
  \
  Data_Get_Struct(watcher_data->loop, struct Rev_Loop, loop_data); \
  \
  ev_##watcher_type##_stop(loop_data->ev_loop, &watcher_data->event_types.ev_##watcher_type); \
  rb_call_super(0, 0)

#define Watcher_Enable(watcher_type, watcher) \
  struct Rev_Watcher *watcher_data; \
  struct Rev_Loop *loop_data; \
  \
  Data_Get_Struct(watcher, struct Rev_Watcher, watcher_data); \
  \
  if(watcher_data->loop == Qnil) \
    rb_raise(rb_eRuntimeError, "not attached to a loop"); \
  \
  rb_call_super(0, 0); \
  \
  Data_Get_Struct(watcher_data->loop, struct Rev_Loop, loop_data); \
  \
  ev_##watcher_type##_start(loop_data->ev_loop, &watcher_data->event_types.ev_##watcher_type)

#define Watcher_Disable(watcher_type, watcher) \
  struct Rev_Watcher *watcher_data; \
  struct Rev_Loop *loop_data; \
  \
  Data_Get_Struct(watcher, struct Rev_Watcher, watcher_data); \
  \
  if(watcher_data->loop == Qnil) \
    rb_raise(rb_eRuntimeError, "not attached to a loop"); \
  \
  rb_call_super(0, 0); \
  \
  Data_Get_Struct(watcher_data->loop, struct Rev_Loop, loop_data); \
  \
  ev_##watcher_type##_stop(loop_data->ev_loop, &watcher_data->event_types.ev_##watcher_type)

#endif
