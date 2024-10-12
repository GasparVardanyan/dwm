/* See LICENSE file for copyright and license details. */

/* theme management */
# include "theme_beg.h" /* this is a compile-time generated header file */
# include "theme.h"

/* appearance */
static const unsigned int borderpx  = DWM_BORDERPX;        /* border pixel of windows */
static const unsigned int snap      = DWM_SNAP;            /* snap pixel */
static const int showbar            = DWM_SHOWBAR;         /* 0 means no bar */
static const int topbar             = DWM_TOPBAR;          /* 0 means bottom bar */
static const char *fonts[]          = DWM_FONT;
static const unsigned int stairpx   = 20;       /* depth of the stairs layout */
static const int stairdirection     = 1;        /* 0: left-aligned, 1: right-aligned */
static const int stairsamesize      = 1;        /* 1 means shrink all the staired windows to the same size */
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg                 bg                 border   */
	[SchemeNorm] = { DWM_FOREGROUND,    DWM_BACKGROUND,    DWM_BORDER },
	[SchemeSel]  = { DWM_SELFOREGROUND, DWM_SELBACKGROUND, DWM_SELBORDER },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

#include "scratchtagwins.c"

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor    scratch key */
	{ "Gimp",     NULL,       NULL,       0,            0,           1,           -1,        0  },
	{ "firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1,        0  },
	{ NULL,       NULL,   "scratchpad",   0,            0,           1,           -1,       's' },
	SCRATCHTAGWIN_RULE (scratchtagwin1, 1),
	SCRATCHTAGWIN_RULE (scratchtagwin2, 2),
	SCRATCHTAGWIN_RULE (scratchtagwin3, 3),
	SCRATCHTAGWIN_RULE (scratchtagwin4, 4),
	SCRATCHTAGWIN_RULE (scratchtagwin5, 5),
	SCRATCHTAGWIN_RULE (scratchtagwin6, 6),
	SCRATCHTAGWIN_RULE (scratchtagwin7, 7),
	SCRATCHTAGWIN_RULE (scratchtagwin8, 8),
	SCRATCHTAGWIN_RULE (scratchtagwin9, 9),
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[S]",      stairs },
	{ "[D]",      deck },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

SCRATCHTAGWIN (scratchtagwin1, 1);
SCRATCHTAGWIN (scratchtagwin2, 2);
SCRATCHTAGWIN (scratchtagwin3, 3);
SCRATCHTAGWIN (scratchtagwin4, 4);
SCRATCHTAGWIN (scratchtagwin5, 5);
SCRATCHTAGWIN (scratchtagwin6, 6);
SCRATCHTAGWIN (scratchtagwin7, 7);
SCRATCHTAGWIN (scratchtagwin8, 8);
SCRATCHTAGWIN (scratchtagwin9, 9);

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "st", "-t", "scratchpad", NULL};

/* theme management */
# include "theme_end.h" /* this is a compile-time generated header file */

#include "exitdwm.c"
#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	SCRATCHTAGWIN_KEY (scratchtagwin1, 1)
	SCRATCHTAGWIN_KEY (scratchtagwin2, 2)
	SCRATCHTAGWIN_KEY (scratchtagwin3, 3)
	SCRATCHTAGWIN_KEY (scratchtagwin4, 4)
	SCRATCHTAGWIN_KEY (scratchtagwin5, 5)
	SCRATCHTAGWIN_KEY (scratchtagwin6, 6)
	SCRATCHTAGWIN_KEY (scratchtagwin7, 7)
	SCRATCHTAGWIN_KEY (scratchtagwin8, 8)
	SCRATCHTAGWIN_KEY (scratchtagwin9, 9)
	{ MODKEY|Mod1Mask|ShiftMask,     XK_0,  makescratchtagwin,  {.i = 0} },
	{ MODKEY|Mod1Mask|ShiftMask,     XK_s,  makescratchtagwin,  {.i = 's'} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|Mod1Mask,              XK_r,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY|ControlMask,           XK_space,  togglealwaysontop, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_x,      movecenter,     {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_minus, scratchpad_show, {0} },
	{ MODKEY|ShiftMask,             XK_minus, scratchpad_hide, {0} },
	{ MODKEY,                       XK_equal,scratchpad_remove,{0} },
	{ MODKEY|ShiftMask,             XK_e,      exitdwm,       {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

