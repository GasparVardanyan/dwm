# ifdef SPAWN_KEY
# error error conflicting macro names
# endif // SPAWN_KEY

# define SPAWN_KEY(mod,keysym,launcher) \
	{ mod, keysym, spawn, {.v = launchers.launcher.args } },

struct {
	struct {
		const char ** args;
	}
		  Terminal,             Dmenu,
		  VolUp,                VolDown,                 VolToggle,
		  CmusNext,             CmusPrev,                CmusToggle,           CmusStop,             MusSelect,
		  FlameshotGui,         FlameshotFull,
		  YtMpv,
		  MpvPlay,
		  BacklightUp,          BacklightDown,           BacklightMax,         BacklightMid,
		  KbdBrightOn,          KbdBrightOff,
		  Screen2560,           Screen1920,
		  PassFill,             PassFillConfirm,         PassFillU,            PassFillUConfirm,
		  Task,                 Todo,
		  AWCC,
		  FileLaunch,           FileLaunchFuzzy,         DmenuFM,
		  ArchWikiDmenu,        ArchWikiSelection,
		  ChtShDmenu,           ChtShSelection,
		  TldrDmenu,            TldrSelection,
		  TranslateDmenu,       TranslateSelection,
		  ZdictDmenu,           ZdictSelection,
		  WhiteScreen,          BlackScreen,
		  KbdSwitch,            Keym,                    EmojiCopy,            ClipMenu,             SelEdit,
		  ManBrowse,
		  DunstClose,           TerminalSession,         Browser,              SfeedCurses,          Lock,       ConfEdit,
		  NeoVim;
} static const launchers = {

	.Terminal = {
		.args = (const char * []) {
			"tabbed", "-p", "s+1", "-c", "alacritty", "--embed", NULL
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
			"sh", "-c", "plctrl prev && dwmstatus", NULL
		}
	},
	.CmusNext = {
		.args = (const char * []) {
			"sh", "-c", "plctrl next && dwmstatus", NULL
		}
	},
	.CmusToggle = {
		.args = (const char * []) {
			"sh", "-c", "plctrl toggle_play && dwmstatus", NULL
		}
	},
	.CmusStop = {
		.args = (const char * []) {
			"sh", "-c", "plctrl stop && dwmstatus", NULL
		}
	},
	.MusSelect = {
		.args = (const char * []) {
			"sh", "-c", "plctrl select_source && dwmstatus", NULL
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

	.YtMpv = {
		.args = (const char * []) {
			"sh", "-c", "ytmpv", NULL
		}
	},

	.MpvPlay = {
		.args = (const char * []) {
			"play", NULL
		}
	},

	.BacklightDown = {
		.args = (const char * []) {
			"brightnessctl", "-q", "s", "10%-", NULL
		}
	},
	.BacklightUp = {
		.args = (const char * []) {
			"brightnessctl", "-q", "s", "10%+", NULL
		}
	},
	.BacklightMax = {
		.args = (const char * []) {
			"brightnessctl", "-q", "s", "100%", NULL
		}
	},
	.BacklightMid = {
		.args = (const char * []) {
			"brightnessctl", "-q", "s", "20%", NULL
		}
	},

	.KbdBrightOn = {
		.args = (const char * []) {
			"awcc", "brightness", "0", NULL
		}
	},
	.KbdBrightOff = {
		.args = (const char * []) {
			"awcc", "brightness", "100", NULL
		}
	},

	.Screen1920 = {
		.args = (const char * []) {
			"xrandr", "--output", "eDP-1", "--mode", "1920x1200", "--rate", "60", NULL
		}
	},
	.Screen2560 = {
		.args = (const char * []) {
			"xrandr", "--output", "eDP-1", "--mode", "2560x1600", "--rate", "60", NULL
		}
	},

	.AWCC = {
		.args = (const char * []) {
			"awcc_dmenu", NULL
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
	.Keym = {
		.args = (const char * []) {
			"sh", "-c", "setxkbmap -layout us; echo us > ~/.local/tmp/kbd; dunstify 'Keyboard layout: keym' -r 1111 -t 3000; keym; dunstify 'Keyboard layoyt: us' -r 1111 -t 3000", NULL
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

	.NeoVim = {
		.args = (const char * []) {
			"alacritty", "-T", "NeoVim PDE", "-e", "sh", "-c", "NVIM_APPNAME=nvim nvim", NULL
		}
	},
};
