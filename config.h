/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* appearance */
///	static const unsigned int borderpx  = 1;        /* border pixel of windows */
///	static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 8;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
///	static const char dmenufont[]       = "monospace:size=10";
///	static const char col_gray1[]       = "#222222";
///	static const char col_gray2[]       = "#444444";
///	static const char col_gray3[]       = "#bbbbbb";
///	static const char col_gray4[]       = "#eeeeee";
///	static const char col_cyan[]        = "#005577";
///	static const char *colors[][3]      = {
///		/*               fg         bg         border   */
///		[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
///		[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
///	};
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#bbbbbb", "#000000", "#444444" },
	[SchemeSel]  = { "#000000", "#ff0000", "#ff0000" },
};

/* tagging */
///	static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = {
	"1", "2", "3", "4", "5", "6", "7", "8", "9",
	"+", "+", "+", "+", "+", "+", "+", "+", "+", "+", "+", "+",
};
static const unsigned tags_in_bar = 9 < LENGTH (tags) ? 9 : LENGTH (tags);
static const unsigned display_tags = ~((1 << tags_in_bar) - 1);

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
///	/* class      instance    title       tags mask     iscentered     isfloating   monitor    scratch key */
///	{ "Gimp",     NULL,       NULL,       0,            0,             1,           -1,        0  },
///	{ "firefox",  NULL,       NULL,       1 << 8,       0,             0,           -1,        0  },
///	{ NULL,       NULL,   "scratchpad",   0,            0,             1,           -1,       's' },
	/* class      instance        title       tags mask     iscentered   isfloating   monitor    scratch key */
	{ NULL,       "scratchterm",   NULL,       0,            1,           1,           -1,      's' },
	{ NULL,        "scratchqb",    NULL,       0,            1,           1,           -1,      'q' },
	{ NULL,      "scratch_tmpqb",  NULL,       0,            1,           1,           -1,      't' },
	{ NULL,       "scratchcmus",   NULL,       0,            1,           1,           -1,      'c' },
	{ NULL,         "pop-up",      NULL,       0,            1,           1,           -1,       0 },
};

/* layout(s) */
///	static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
///	static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
///	#define MODKEY Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
///	static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
///	static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
///	static const char *termcmd[]  = { "st", NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "tabbed", "-p", "s+1", "-c", "st", "-w", NULL };
// static const char *termcmd[]  = { "st", "-e", "tmux", NULL };

/*First arg only serves to match against key in rules*/
///	static const char *scratchpadcmd[] = {"s", "st", "-t", "scratchpad", NULL};
static const char * scratchterm [] = { "s",
	"tabbed",
		"-p", "s+1",
		"-n", "scratchterm",
		"-g", "1195x672",
		"-c", "st", "-f", "monospace:size=16", "-w",
	// "st",
	//     "-n", "scratchterm",
	//     "-g", "90x25",
	//     "-f", "monospace:size=16",
	//     "-e", "sh",
	//         "-c", "tmux", "new", "-s", "scratchterm",
	NULL
};
static const char * scratchqb [] = { "q",
	"qutebrowser", "--qt-arg", "name", "scratchqb", "-B", ".local/share/scratchqb",
	NULL
};
static const char * scratchtmpqb [] = { "t",
	"qutebrowser", "--qt-arg", "name", "scratch_tmpqb", "-T",
	NULL
};
static const char * scratchcmus [] = { "c",
	"st", "-n", "scratchcmus", "-g", "123x34", "-e", "cmus",
	NULL
};

static void exit_dwm ();

static Key keys[] = {
	/* modifier                     key        function        argument */
///	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
///	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
///	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
///	{ MODKEY,                       XK_b,      togglebar,      {0} },
///	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
///	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
///	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
///	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
///	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
///	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
///	{ MODKEY,                       XK_Return, zoom,           {0} },
///	{ MODKEY,                       XK_Tab,    view,           {0} },
///	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
///	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
///	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
///	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
///	{ MODKEY,                       XK_space,  setlayout,      {0} },
///	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
///	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
///	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
///	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
///	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
///	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
///	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
///	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
///	TAGKEYS(                        XK_1,                      0)
///	TAGKEYS(                        XK_2,                      1)
///	TAGKEYS(                        XK_3,                      2)
///	TAGKEYS(                        XK_4,                      3)
///	TAGKEYS(                        XK_5,                      4)
///	TAGKEYS(                        XK_6,                      5)
///	TAGKEYS(                        XK_7,                      6)
///	TAGKEYS(                        XK_8,                      7)
///	TAGKEYS(                        XK_9,                      8)
///	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
///	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
///	{ MODKEY,                       XK_minus, scratchpad_show, {0} },
///	{ MODKEY|ShiftMask,             XK_minus, scratchpad_hide, {0} },
///	{ MODKEY,                       XK_equal,scratchpad_remove,{0} },
	{ MODKEY,                       XK_n,      spawn,          SHCMD ("todo") },
	{ MODKEY,                    XK_semicolon, spawn,          SHCMD ("fbrowse -") },
	{ MODKEY|ShiftMask,          XK_semicolon, spawn,          SHCMD ("fbrowse") },
	{ MODKEY,                      XK_d,       spawn,          {.v = dmenucmd } },
	{ MODKEY,                      XK_Return,  spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,            XK_s,       togglescratch,  {.v = scratchterm } },
	{ MODKEY|ShiftMask,            XK_b,       togglescratch,  {.v = scratchqb } },
	{ MODKEY|ShiftMask,            XK_t,       togglescratch,  {.v = scratchtmpqb } },
	{ MODKEY|ShiftMask,            XK_c,       togglescratch,  {.v = scratchcmus } },
	{ MODKEY,                      XK_b,       togglebar,      {0} },
	{ Mod1Mask,                    XK_Tab,     view,           {0} },
	{ MODKEY,                      XK_Tab,     focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,            XK_Tab,     focusstack,     {.i = -1 } },
	{ MODKEY,                      XK_j,       focusstack,     {.i = -1 } },
	{ MODKEY,                      XK_k,       focusstack,     {.i = +1 } },
//	{ MODKEY|ShiftMask,            XK_j,       movestack,      {.i = -1 } },
//	{ MODKEY|ShiftMask,            XK_k,       movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,            XK_h,       incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,            XK_l,       incnmaster,     {.i = -1 } },
	{ MODKEY,                      XK_h,       setmfact,       {.f = -.05f} },
	{ MODKEY,                      XK_l,       setmfact,       {.f = +.05f} },
	{ MODKEY|ShiftMask,            XK_Return,  zoom,           {0} },
	{ MODKEY|ShiftMask,            XK_q,       killclient,     {0} },
	{ MODKEY|ShiftMask,            XK_f,       togglefullscr,  {0} },
	{ MODKEY,                      XK_t,       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                      XK_f,       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                      XK_m,       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                      XK_space,   setlayout,      {0} },
	{ MODKEY|ShiftMask,            XK_space,   togglefloating, {0} },
	{ MODKEY,                      XK_comma,   focusmon,       {.i = -1 } },
	{ MODKEY,                      XK_period,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,            XK_comma,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,            XK_period,  tagmon,         {.i = +1 } },
	TAGKEYS(                       XK_1,                       0)
	TAGKEYS(                       XK_2,                       1)
	TAGKEYS(                       XK_3,                       2)
	TAGKEYS(                       XK_4,                       3)
	TAGKEYS(                       XK_5,                       4)
	TAGKEYS(                       XK_6,                       5)
	TAGKEYS(                       XK_7,                       6)
	TAGKEYS(                       XK_8,                       7)
	TAGKEYS(                       XK_9,                       8)
	TAGKEYS(                       XK_F1,                      9)
	TAGKEYS(                       XK_F2,                      10)
	TAGKEYS(                       XK_F3,                      11)
	TAGKEYS(                       XK_F4,                      12)
	TAGKEYS(                       XK_F5,                      13)
	TAGKEYS(                       XK_F6,                      14)
	TAGKEYS(                       XK_F7,                      15)
	TAGKEYS(                       XK_F8,                      16)
	TAGKEYS(                       XK_F9,                      17)
	TAGKEYS(                       XK_F10,                     18)
	TAGKEYS(                       XK_F11,                     19)
	TAGKEYS(                       XK_F12,                     20)
	{ MODKEY,                      XK_0,       view,           {.ui = display_tags } },
	{ MODKEY|ShiftMask,            XK_0,       tag,            {.ui = display_tags } },
	{ MODKEY|ShiftMask,            XK_e,       exit_dwm,       {0} },
	{ MODKEY,                      XK_minus,  scratchpad_show, {0} },
	{ MODKEY|ShiftMask,            XK_minus,  scratchpad_hide, {0} },
	{ MODKEY,                      XK_equal, scratchpad_remove,{0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
///	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
///	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
///	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
///	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
///	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
///	{ ClkTagBar,            0,              Button1,        view,           {0} },
///	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
///	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
///	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static void exit_dwm ()
{
# if							   \
	defined S_LOCK				|| \
	defined S_RESTART_DWM		|| \
	defined S_OFFSCREEN			|| \
	defined S_EXIT				|| \
	defined S_REBOOT			|| \
	defined S_SHUTDOWN			|| \
	defined S_LOCK_ICON			|| \
	defined S_RESTART_DWM_ICON	|| \
	defined S_OFFSCREEN_ICON	|| \
	defined S_EXIT_ICON			|| \
	defined S_REBOOT_ICON		|| \
	defined S_SHUTDOWN_ICON		|| \
	defined S_FORMAT			|| \
	defined S_FORMAT_CLEAR
# error (conflicted macro names)
# endif

# define S_LOCK "Lock"
# define S_RESTART_DWM "restart Dwm"
# define S_OFFSCREEN "Off-screen"
# define S_EXIT "Exit"
# define S_REBOOT "Reboot"
# define S_SHUTDOWN "Shutdown"
# define S_LOCK_ICON "\uf023"			// <= FontAwesome icons
# define S_RESTART_DWM_ICON "\uf01e"
# define S_OFFSCREEN_ICON "\uf108"
# define S_EXIT_ICON "\uf2f5"
# define S_REBOOT_ICON "\uf021"
# define S_SHUTDOWN_ICON "\uf011"

# define S_FORMAT(ACTION) S_##ACTION##_ICON " " S_##ACTION
# define S_FORMAT_CLEAR "sed 's/^..//'"

	FILE * exit_menu = popen (
		"echo \""
			S_FORMAT (LOCK) "\n"
			S_FORMAT (RESTART_DWM) "\n"
			S_FORMAT (OFFSCREEN) "\n"
			S_FORMAT (EXIT) "\n"
			S_FORMAT (REBOOT) "\n"
			S_FORMAT (SHUTDOWN)
			"\" | dmenu -p exit: | " S_FORMAT_CLEAR
		,
		"r"
	);

	char exit_action [16];

	if (
		exit_menu == NULL ||
		fscanf (exit_menu, "%15[a-zA-Z -]", exit_action) == EOF
	) {
		fputs ("Error. Failure in exit_dwm.", stderr);
		goto close_streams;
	}

	if (strcmp (exit_action, S_LOCK) == 0) system ("slock & sleep .5; xset dpms force off");
	else if (strcmp (exit_action, S_RESTART_DWM) == 0) quit (& (const Arg) {1});
	else if (strcmp (exit_action, S_OFFSCREEN) == 0) system ("sleep .5; xset dpms force off");
	else if (strcmp (exit_action, S_EXIT) == 0) quit (& (const Arg) {0});
	else if (strcmp (exit_action, S_REBOOT) == 0) system ("systemctl reboot");
	else if (strcmp (exit_action, S_SHUTDOWN) == 0) system ("systemctl poweroff -i");

close_streams:
	pclose (exit_menu);

# undef S_LOCK
# undef S_RESTART_DWM
# undef S_OFFSCREEN
# undef S_EXIT
# undef S_REBOOT
# undef S_SHUTDOWN
# undef S_LOCK_ICON
# undef S_RESTART_DWM_ICON
# undef S_OFFSCREEN_ICON
# undef S_EXIT_ICON
# undef S_REBOOT_ICON
# undef S_SHUTDOWN_ICON
# undef S_FORMAT
# undef S_FORMAT_CLEAR
}
