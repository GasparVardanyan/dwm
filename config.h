/* See LICENSE file for copyright and license details. */

/* theme management */
# include "theme_beg.h" /* this is a compile-time generated header file */
# include "theme.h"

/* selbg = bg for window title */
# if DWM_BARSINGLEBG == 1
# define BARSINGLEBG
# endif

/* appearance */
static const unsigned int borderpx  = DWM_BORDERPX;        /* border pixel of windows */
static const unsigned int snap      = DWM_SNAP;            /* snap pixel */
static const int showbar            = DWM_SHOWBAR;         /* 0 means no bar */
static const int topbar             = DWM_TOPBAR;          /* 0 means bottom bar */
static const unsigned int stairpx   = 20;       /* depth of the stairs layout */
static const int stairdirection     = 1;        /* 0: left-aligned, 1: right-aligned */
static const int stairsamesize      = 0;        /* 1 means shrink all the staired windows to the same size */
static const char *fonts[]          = DWM_FONT;
static const char *colors[][3]      = {
	/*               fg                 bg                 border */
	[SchemeNorm] = { DWM_FOREGROUND,    DWM_BACKGROUND,    DWM_BORDER    },
	[SchemeSel]  = { DWM_SELFOREGROUND, DWM_SELBACKGROUND, DWM_SELBORDER },
};

/* tagging */
static const char *tags[] = {
	"1", "2", "3", "4", "5", "6", "7", "8", "9",
	"+", "+", "+", "+", "+", "+", "+", "+", "+", "+", "+", "+",
};
static const unsigned tags_in_bar = 9 < LENGTH (tags) ? 9 : LENGTH (tags);
static const unsigned display_tags = (1 << tags_in_bar) - 1;

#include "scratchtagwins.c"
#include "namedscratchpads.c"

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class    instance    title    tags mask    iscentered    isfloating    monitor    scratch key */
	{ NULL,     "pop-up",   NULL,    0,           1,            1,            -1,        0 },
	{ NULL,     "megasync", NULL,    0,           1,            1,            -1,        0 },
	{ "mpv",    NULL,       NULL,    0,           1,            1,            -1,        0 },

	NAMEDSCRATCHPAD_RULE ( term    ),    SCRATCHTAGWIN_RULE ( scratchtagwin1, 1 ),
	NAMEDSCRATCHPAD_RULE ( qb      ),    SCRATCHTAGWIN_RULE ( scratchtagwin2, 2 ),
	NAMEDSCRATCHPAD_RULE ( qbw     ),    SCRATCHTAGWIN_RULE ( scratchtagwin3, 3 ),
	NAMEDSCRATCHPAD_RULE ( qbg     ),    SCRATCHTAGWIN_RULE ( scratchtagwin4, 4 ),
	NAMEDSCRATCHPAD_RULE ( qbT     ),    SCRATCHTAGWIN_RULE ( scratchtagwin5, 5 ),
	NAMEDSCRATCHPAD_RULE ( qbt     ),    SCRATCHTAGWIN_RULE ( scratchtagwin6, 6 ),
	NAMEDSCRATCHPAD_RULE ( cmus    ),    SCRATCHTAGWIN_RULE ( scratchtagwin7, 7 ),
	NAMEDSCRATCHPAD_RULE ( jb      ),    SCRATCHTAGWIN_RULE ( scratchtagwin8, 8 ),
	NAMEDSCRATCHPAD_RULE ( systray ),    SCRATCHTAGWIN_RULE ( scratchtagwin9, 9 ),
	NAMEDSCRATCHPAD_RULE ( qalc    ),
	NAMEDSCRATCHPAD_RULE ( volctl  ),
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[S]",      stairs },  /* first entry is default */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[D]",      deck },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* theme management */
# include "theme_end.h" /* this is a compile-time generated header file */

SCRATCHTAGWIN ( scratchtagwin1, 1 );
SCRATCHTAGWIN ( scratchtagwin2, 2 );
SCRATCHTAGWIN ( scratchtagwin3, 3 );
SCRATCHTAGWIN ( scratchtagwin4, 4 );
SCRATCHTAGWIN ( scratchtagwin5, 5 );
SCRATCHTAGWIN ( scratchtagwin6, 6 );
SCRATCHTAGWIN ( scratchtagwin7, 7 );
SCRATCHTAGWIN ( scratchtagwin8, 8 );
SCRATCHTAGWIN ( scratchtagwin9, 9 );

#include "exitdwm.c"
#include "movestack.c"
#include "spawn_cmds.c"

static Key keys[] = {
	/* modifier                 key        function           argument */
	{ MODKEY|AltMask|ShiftMask, XK_0,      makescratchtagwin, { .i = 0             } },
	{ MODKEY|AltMask|ShiftMask, XK_s,      makescratchtagwin, { .i = 's'           } },
	{ MODKEY,                   XK_b,      togglebar,         { .i = 0             } },
	{ Mod1Mask,                 XK_Tab,    view,              { .i = 0             } },
	{ MODKEY,                   XK_Tab,    focusstack,        { .i = +1            } },
	{ MODKEY|ShiftMask,         XK_Tab,    focusstack,        { .i = -1            } },
	{ MODKEY,                   XK_j,      focusstack,        { .i = +1            } },
	{ MODKEY,                   XK_k,      focusstack,        { .i = -1            } },
	{ MODKEY|ShiftMask,         XK_j,      movestack,         { .i = +1            } },
	{ MODKEY|ShiftMask,         XK_k,      movestack,         { .i = -1            } },
	{ MODKEY|ShiftMask,         XK_h,      incnmaster,        { .i = +1            } },
	{ MODKEY|ShiftMask,         XK_l,      incnmaster,        { .i = -1            } },
	{ MODKEY,                   XK_h,      setmfact,          { .f = -.05f         } },
	{ MODKEY,                   XK_l,      setmfact,          { .f = +.05f         } },
	{ MODKEY|ShiftMask,         XK_Return, zoom,              { .i = 0             } },
	{ MODKEY|ShiftMask,         XK_q,      killclient,        { .i = 0             } },
	{ MODKEY|ShiftMask,         XK_f,      togglefullscr,     { .i = 0             } },
	{ MODKEY|ControlMask,       XK_s,      setlayout,         { .v = &layouts[0]   } },
	{ MODKEY,                   XK_t,      setlayout,         { .v = &layouts[1]   } },
	{ MODKEY,                   XK_f,      setlayout,         { .v = &layouts[2]   } },
	{ MODKEY,                   XK_m,      setlayout,         { .v = &layouts[3]   } },
	{ MODKEY|ControlMask,       XK_d,      setlayout,         { .v = &layouts[4]   } },
	{ MODKEY|ControlMask,       XK_a,      setlayout,         { .v = &layouts[5]   } },
	{ MODKEY|ControlMask,       XK_f,      setlayout,         { .v = &layouts[6]   } },
	{ MODKEY|ControlMask,       XK_space,  focusmaster,       { .i = 0             } },
	{ MODKEY|ShiftMask,         XK_space,  togglefloating,    { .i = 0             } },
	{ MODKEY,                   XK_comma,  focusmon,          { .i = +1            } },
	{ MODKEY,                   XK_period, focusmon,          { .i = -1            } },
	{ MODKEY|ShiftMask,         XK_comma,  tagmon,            { .i = +1            } },
	{ MODKEY|ShiftMask,         XK_period, tagmon,            { .i = -1            } },
	{ MODKEY|ShiftMask,         XK_x,      movecenter,        { .i = 0             } },
	{ MODKEY,                   XK_0,      view,              { .ui = display_tags } },
	{ MODKEY|ShiftMask,         XK_0,      tag,               { .ui = display_tags } },
	{ MODKEY|ShiftMask,         XK_e,      exitdwm,           { .i = 0             } },
	{ MODKEY,                   XK_minus,  scratchpad_show,   { .i = 0             } },
	{ MODKEY|ShiftMask,         XK_minus,  scratchpad_hide,   { .i = 0             } },
	{ MODKEY|ShiftMask,         XK_equal,  scratchpad_remove, { .i = 0             } },

# if defined NSK || defined SWK
# error conflicting macro names
# endif // NSK || SWK
# define NSK NAMEDSCRATCHPAD_KEY
# define SWK SCRATCHTAGWIN_KEY
	NSK ( MODKEY|ShiftMask,             XK_s, term    )    SWK ( scratchtagwin1, 1 )
	NSK ( MODKEY|ShiftMask,             XK_b, qb      )    SWK ( scratchtagwin2, 2 )
	NSK ( MODKEY|ShiftMask,             XK_w, qbw     )    SWK ( scratchtagwin3, 3 )
	NSK ( MODKEY|ShiftMask,             XK_g, qbg     )    SWK ( scratchtagwin4, 4 )
	NSK ( MODKEY|ControlMask|ShiftMask, XK_t, qbT     )    SWK ( scratchtagwin5, 5 )
	NSK ( MODKEY|ShiftMask,             XK_t, qbt     )    SWK ( scratchtagwin6, 6 )
	NSK ( MODKEY,                       XK_q, qalc    )    SWK ( scratchtagwin7, 7 )
	NSK ( MODKEY|ShiftMask,             XK_c, cmus    )    SWK ( scratchtagwin8, 8 )
	NSK ( MODKEY|ShiftMask,             XK_p, jb      )    SWK ( scratchtagwin9, 9 )
	NSK ( MODKEY,                       XK_s, systray )
	NSK ( MODKEY|ControlMask|ShiftMask, XK_o, cmus    )
	NSK ( MODKEY|ControlMask|ShiftMask, XK_u, volctl  )
# undef NSK
# undef SWK

	SPAWN_KEY   ( MODKEY,                         XK_Return,         Terminal             )
	SPAWN_KEY   ( MODKEY,                         XK_d,              Dmenu                )
	SPAWN_KEY   ( MODKEY,                         XK_u,              VolDown              )
	SPAWN_KEY   ( MODKEY,                         XK_i,              VolUp                )
	SPAWN_KEY   ( MODKEY,                         XK_o,              VolToggle            )
	SPAWN_KEY   ( MODKEY|ShiftMask,               XK_u,              CmusPrev             )
	SPAWN_KEY   ( MODKEY|ShiftMask,               XK_i,              CmusNext             )
	SPAWN_KEY   ( MODKEY|ShiftMask,               XK_o,              CmusToggle           )
	/*SPAWN_KEY   ( MODKEY|ControlMask,             XK_u,              BacklightDown        )*/
	/*SPAWN_KEY   ( MODKEY|ControlMask,             XK_i,              BacklightUp          )*/
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_u,              FlameshotFull        )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_i,              FlameshotGui         )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_o,              CmusStop             )
	SPAWN_KEY   ( MODKEY|ControlMask|ShiftMask,   XK_i,              MpvPlay              )
	SPAWN_KEY   ( 0,                              XK_Print,          FlameshotFull        )
	SPAWN_KEY   ( ShiftMask,                      XK_Print,          FlameshotGui         )
	SPAWN_KEY   ( MODKEY,                         XK_backslash,      PassFill             )
	SPAWN_KEY   ( MODKEY|ShiftMask,               XK_backslash,      PassFillConfirm      )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_backslash,      PassFillU            )
	SPAWN_KEY   ( MODKEY|ControlMask|ShiftMask,   XK_backslash,      PassFillUConfirm     )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_t,              Task                 )
	SPAWN_KEY   ( MODKEY,                         XK_n,              Todo                 )
	SPAWN_KEY   ( MODKEY,                         XK_semicolon,      FileLaunch           )
	SPAWN_KEY   ( MODKEY|ShiftMask,               XK_semicolon,      FileLaunchFuzzy      )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_semicolon,      DmenuFM              )
	SPAWN_KEY   ( MODKEY,                         XK_bracketleft,    TranslateDmenu       )
	SPAWN_KEY   ( MODKEY,                         XK_bracketright,   ZdictDmenu           )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_bracketleft,    TranslateSelection   )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_bracketright,   ZdictSelection       )
	SPAWN_KEY   ( MODKEY|ShiftMask,               XK_bracketleft,    ChtShDmenu           )
	SPAWN_KEY   ( MODKEY|ShiftMask,               XK_bracketright,   TldrDmenu            )
	SPAWN_KEY   ( MODKEY|ControlMask|ShiftMask,   XK_bracketleft,    ChtShSelection       )
	SPAWN_KEY   ( MODKEY|ControlMask|ShiftMask,   XK_bracketright,   TldrSelection        )
	SPAWN_KEY   ( MODKEY,                         XK_w,              ArchWikiDmenu        )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_w,              ArchWikiSelection    )
	SPAWN_KEY   ( MODKEY,                         XK_a,              WhiteScreen          )
	SPAWN_KEY   ( MODKEY|ShiftMask,               XK_a,              BlackScreen          )
	SPAWN_KEY   ( MODKEY,                         XK_space,          KbdSwitch            )
	SPAWN_KEY   ( MODKEY,                         XK_e,              EmojiCopy            )
	SPAWN_KEY   ( MODKEY,                         XK_c,              ClipMenu             )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_e,              SelEdit              )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_m,              ManBrowse            )
	SPAWN_KEY   ( MODKEY|ShiftMask,               XK_d,              DunstClose           )
	SPAWN_KEY   ( MODKEY|ControlMask|ShiftMask,   XK_s,              TerminalSession      )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_b,              Browser              )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_n,              SfeedCurses          )
	SPAWN_KEY   ( MODKEY|ControlMask,             XK_l,              Lock                 )
	SPAWN_KEY   ( MODKEY,                         XK_p,              ConfEdit             )
	SPAWN_KEY   ( MODKEY|ControlMask|ShiftMask,   XK_n,              NeoVim               )

	TAGKEYS ( XK_F1,  9  )     TAGKEYS ( XK_1, 0 )
	TAGKEYS ( XK_F2,  10 )     TAGKEYS ( XK_2, 1 )
	TAGKEYS ( XK_F3,  11 )     TAGKEYS ( XK_3, 2 )
	TAGKEYS ( XK_F4,  12 )     TAGKEYS ( XK_4, 3 )
	TAGKEYS ( XK_F5,  13 )     TAGKEYS ( XK_5, 4 )
	TAGKEYS ( XK_F6,  14 )     TAGKEYS ( XK_6, 5 )
	TAGKEYS ( XK_F7,  15 )     TAGKEYS ( XK_7, 6 )
	TAGKEYS ( XK_F8,  16 )     TAGKEYS ( XK_8, 7 )
	TAGKEYS ( XK_F9,  17 )     TAGKEYS ( XK_9, 8 )
	TAGKEYS ( XK_F10, 18 )
	TAGKEYS ( XK_F11, 19 )
	TAGKEYS ( XK_F12, 20 )
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};
