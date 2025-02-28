
#pragma once

#include "u7glib.h"



G_BEGIN_DECLS

#define U7_TYPE_MAINLOOP (u7_mainloop_get_type())

G_DECLARE_FINAL_TYPE(U7MainLoop, u7_mainloop, U7, MAINLOOP, GObject)

extern U7MainLoop *u7_mainloop_new(void (*callback)(char *str, int len));
extern void u7_mainloop_start(U7MainLoop *loop);

G_END_DECLS

