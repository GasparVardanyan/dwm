# ifdef SPAWN_KEY
# error error conflicting macro names
# endif // SPAWN_KEY

# define SPAWN_KEY(mod,keysym,launcher) \
	{ mod, keysym, spawn, {.v = launchers.launcher.args } },

struct {
	struct {
		const char ** args;
	}
		Terminal,           Dmenu,
		VolUp,              VolDown,               VolToggle,
		CmusNext,           CmusPrev,              CmusToggle,         CmusStop,
		FlameshotGui,       FlameshotFull,
		MpvPlay,
		BacklightUp,        BacklightDown,
		/* ScreenshotScreen,   ScreenshotSelection,   ScreenshotWindow, */
		PassFill,           PassFillConfirm,       PassFillU,          PassFillUConfirm,
		Task,               Todo,
		FileLaunch,         FileLaunchFuzzy,       DmenuFM,
		ArchWikiDmenu,      ArchWikiSelection,
		ChtShDmenu,         ChtShSelection,
		TldrDmenu,          TldrSelection,
		TranslateDmenu,     TranslateSelection,
		ZdictDmenu,         ZdictSelection,
		WhiteScreen,        BlackScreen,
		KbdSwitch,          EmojiCopy,             ClipMenu,           SelEdit,
		ManBrowse,
		DunstClose,         TerminalSession,       Browser,            SfeedCurses,        Lock,   ConfEdit;
} static const launchers = {

	.Terminal = {
		.args = (const char * []) {
			"tabbed", "-p", "s+1", "-c", "st", "-w", NULL
		}
	},
	.Dmenu = {
		.args = (const char * []) {
			"dmenu_run", topbar ? NULL : "-b", NULL
		}
	},

	.VolDown = {
		.args = (const char * []) {
			"sh", "-c", "pamixer -d 5 && dwmstatus", NULL
		}
	},
	.VolUp = {
		.args = (const char * []) {
			"sh", "-c", "pamixer -i 5 && dwmstatus", NULL
		}
	},
	.VolToggle = {
		.args = (const char * []) {
			"sh", "-c", "pamixer -t && dwmstatus", NULL
		}
	},

	.CmusPrev = {
		.args = (const char * []) {
			"sh", "-c", "cmus-remote -r && dwmstatus", NULL
		}
	},
	.CmusNext = {
		.args = (const char * []) {
			"sh", "-c", "cmus-remote -n && dwmstatus", NULL
		}
	},
	.CmusToggle = {
		.args = (const char * []) {
			"sh", "-c", "cmus-remote -u && dwmstatus", NULL
		}
	},
	.CmusStop = {
		.args = (const char * []) {
			"sh", "-c", "cmus-remote -s && dwmstatus", NULL
		}
	},

	.FlameshotGui = {
		.args = (const char * []) {
			"flameshot", "gui", NULL
		}
	},
	.FlameshotFull = {
		.args = (const char * []) {
			"sh", "-c", "mkdir -p $HOME/screenshots && flameshot full --path $HOME/screenshots", NULL
		}
	},

	.MpvPlay = {
		.args = (const char * []) {
			"play", NULL
		}
	},

	.BacklightDown = {
		.args = (const char * []) {
			"xbacklight", "-dec", "10", NULL
		}
	},
	.BacklightUp = {
		.args = (const char * []) {
			"xbacklight", "-inc", "10", NULL
		}
	},

	.PassFill = {
		.args = (const char * []) {
			"xpass", NULL
		}
	},
	.PassFillConfirm = {
		.args = (const char * []) {
			"xpass", "e", NULL
		}
	},
	.PassFillU = {
		.args = (const char * []) {
			"xfill", NULL
		}
	},
	.PassFillUConfirm = {
		.args = (const char * []) {
			"xlogin", NULL
		}
	},

	.Task = {
		.args = (const char * []) {
			"st", "-n", "pop-up", "-g", "120x30", "-e", "sh", "-c", "nvim", "~/.todo.org", NULL
		}
	},
	.Todo = {
		.args = (const char * []) {
			"todo", NULL
		}
	},

	.FileLaunch = {
		.args = (const char * []) {
			"sfl", "d", NULL
		}
	},
	.FileLaunchFuzzy = {
		.args = (const char * []) {
			"sfl", "f", NULL
		}
	},
	.DmenuFM = {
		.args = (const char * []) {
			"dmenufm", NULL
		}
	},

	.ArchWikiDmenu = {
		.args = (const char * []) {
			"selaction", "wiki", "dmenu", NULL
		}
	},
	.ArchWikiSelection = {
		.args = (const char * []) {
			"selaction", "wiki", "selection", NULL
		}
	},
	.ChtShDmenu = {
		.args = (const char * []) {
			"selaction", "chtsh", "dmenu", NULL
		}
	},
	.ChtShSelection = {
		.args = (const char * []) {
			"selaction", "chtsh", "selection", NULL
		}
	},
	.TldrDmenu = {
		.args = (const char * []) {
			"selaction", "tldr", "dmenu", NULL
		}
	},
	.TldrSelection = {
		.args = (const char * []) {
			"selaction", "tldr", "selection", NULL
		}
	},
	.TranslateDmenu = {
		.args = (const char * []) {
			"selaction", "translate", "dmenu", NULL
		}
	},
	.TranslateSelection = {
		.args = (const char * []) {
			"selaction", "translate", "selection", NULL
		}
	},
	.ZdictDmenu = {
		.args = (const char * []) {
			"selaction", "urban", "dmenu", NULL
		}
	},
	.ZdictSelection = {
		.args = (const char * []) {
			"selaction", "urban", "selection", NULL
		}
	},

	.WhiteScreen = {
		.args = (const char * []) {
			"sh", "-c", "magick -size 1x1 canvas:white ~/.local/tmp/lightscreen.png; feh --zoom fill -F ~/.local/tmp/lightscreen.png", NULL
		}
	},
	.BlackScreen = {
		.args = (const char * []) {
			"sh", "-c", "magick -size 1x1 canvas:black ~/.local/tmp/darkscreen.png; feh --zoom fill -F ~/.local/tmp/darkscreen.png", NULL
		}
	},

	.KbdSwitch = {
		.args = (const char * []) {
			"sh", "-c", "kbd toggle && dwmstatus", NULL
		}
	},
	.EmojiCopy = {
		.args = (const char * []) {
			"emo", NULL
		}
	},
	.ClipMenu = {
		.args = (const char * []) {
			"clipmenu", NULL
		}
	},
	.SelEdit = {
		.args = (const char * []) {
			"st", "-n", "pop-up", "-g", "120x30", "-e", "sh", "-c", "xsel -op | vipe | xsel -ib", NULL
		}
	},

	.ManBrowse = {
		.args = (const char * []) {
			"manbrowse", NULL
		}
	},

	.DunstClose = {
		.args = (const char * []) {
			"dunstctl", "close-all", NULL
		}
	},
	.TerminalSession = {
		.args = (const char * []) {
			"terminal", "login", NULL
		}
	},
	.Browser = {
		.args = (const char * []) {
			"qutebrowser", NULL
		}
	},
	.SfeedCurses = {
		.args = (const char * []) {
			"st", "-n", "pop-up", "-g", "120x30", "-e", "sh", "-c", "sfeed_curses ~/.sfeed/feeds/*", NULL
		}
	},
	.Lock = {
		.args = (const char * []) {
			"sh", "-c", "setxkbmap -layout us; slock & sleep .5; xset dpms force off", NULL
		}
	},
	.ConfEdit = {
		.args = (const char * []) {
			"conf", NULL
		}
	},
};
