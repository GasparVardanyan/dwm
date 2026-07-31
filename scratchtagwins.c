#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/XF86keysym.h>

# define SCRATCHTAGWIN(name, id)								\
	static const char * name [] = { # id,						\
			"tabbed",											\
			"-p", "s+1",										\
			"-n", # name,										\
			"-g", "1212x680",									\
			"-c", "alacritty", "--embed",						\
		NULL													\
	}															\

// # define SCRATCHTAGWIN(name, id)								\
// 	static const char * name [] = { # id,						\
// 			"contour",											\
// 			"class", # name,									\
// 		NULL													\
// 	}															\

# define SCRATCHTAGWIN_RULE(name, id)																	\
	{ NULL,       # name, NULL,       0,            1,           1,           -1,      '0' + id }		\

// # define SCRATCHTAGWIN_RULE(name, id)																	\
// 	{ # name,       NULL, NULL,       0,            1,           1,           -1,      '0' + id }		\

# define SCRATCHTAGWIN_KEY(name, id)														\
	{ MODKEY|AltMask,          XK_ ## id,      togglescratch,  {.v = name } },				\
	{ MODKEY|AltMask|ShiftMask,XK_ ## id,      makescratchtagwin,{.i = '0' + id } },		\

static void makescratchtagwin (const Arg * arg)
{
	if (selmon -> sel)
	{
		if (arg -> i != 0)
		{
			_Bool exists = 0;

			for (Client * c = selmon -> clients; c; c = c -> next)
				if (c -> scratchkey == arg -> i)
				{
					exists = 1;
					break;
				}

			if (exists) return;
		}

		selmon -> sel -> scratchkey = arg -> i;
		if (arg -> i != 0)
		{
			selmon -> sel -> tags = 0,
			selmon -> sel -> isfloating = 1;
		}
		else
			selmon -> sel -> tags = selmon -> tagset [selmon -> seltags];
		focus (selmon -> sel);
		arrange (selmon);
	}
}
