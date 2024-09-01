# if defined NAMEDSCRATCHPAD_RULE || defined NAMEDSCRATCHPAD_KEY
# error error conflicting macro names
# endif // NAMEDSCRATCHPAD_RULE || NAMEDSCRATCHPAD_KEY

# define NAMEDSCRATCHPAD_RULE(scratchpad) \
	{ NULL, named_scratchpads.scratchpad.instance, NULL, 0, 1, 1, -1, named_scratchpads.scratchpad.key}

# define NAMEDSCRATCHPAD_KEY(mod,keysym,scratchpad) \
	{ mod, keysym, togglescratch, {.v = named_scratchpads.scratchpad.args } },

struct {
	struct {
		const char * instance;
		char key;
		const char ** args;
	} term, qb, qbw, qbg, qbT, qbt, cmus, jb, systray, qalc, volctl;
} static const named_scratchpads = {

	.term = { .instance = "scratchterm", .key = 's',
		.args = (const char * []) { "s",
			"tabbed",
				"-p", "s+1",
				"-n", "scratchterm",
				"-g", "1212x680",
				"-c", "st", "-w",
			/* "st", */
			/*     "-n", "scratchterm", */
			/*     "-g", "90x25", */
			/*     "-e", "sh", */
			/*         "-c", "tmux", "new", "-s", "scratchterm", */
			NULL
		}
	},

	.qb = { .instance = "scratchqb", .key = 'q',
		.args = (const char * []) { "q",
			"qutebrowser", "--qt-arg", "name", "scratchqb", "-B", ".local/share/scratchqb", "-r", "default",
			NULL
		}
	},

	.qbw = { .instance = "scratchqbw", .key = 'w',
		.args = (const char * []) { "w",
			"qutebrowser", "--qt-arg", "name", "scratchqbw", "-B", ".local/share/scratchqbw", "-r", "default",
			NULL
		}
	},

	.qbg = { .instance = "scratchqbg", .key = 'g',
		.args = (const char * []) { "g",
			"qutebrowser", "--qt-arg", "name", "scratchqbg", "-B", ".local/share/scratchqbg", "-r", "default",
			NULL
		}
	},

	.qbT = { .instance = "scratchqbt", .key = 'G',
		.args = (const char * []) { "G",
			"qutebrowser", "--qt-arg", "name", "scratchqbt", "-B", ".local/share/scratchqbt", "-r", "default",
			NULL
		}
	},

	.qbt = { .instance = "scratchtmpqb", .key = 't',
		.args = (const char * []) { "t",
			"qutebrowser", "--qt-arg", "name", "scratchtmpqb", "-T",
			NULL
		}
	},

	.cmus = { .instance = "scratchcmus", .key = 'c',
		.args = (const char * []) { "c",
			"st", "-t", "cmus", "-n", "scratchcmus", "-g", "120x30", "-e", "cmus",
			NULL
		}
	},

	.jb = { .instance = "scratchjb", .key = 'p',
		.args = (const char * []) { "p",
			"st", "-t", "jabber", "-n", "scratchjb", "-g", "120x30", "-e", "profanity",
			NULL
		}
	},

	.systray = { .instance = "stalonetray", .key = 'A',
		.args = (const char * []) { "A",
			"stalonetray", "--dockapp-mode", "simple",
			NULL
		}
	},

	.qalc = { .instance = "qalculate-qt", .key = 'C',
		.args = (const char * []) { "C",
			"qalculate-qt",
			NULL
		}
	},

	.volctl = { .instance = "pavucontrol-qt", .key = 'P',
		.args = (const char * []) { "P",
			"pavucontrol-qt",
			NULL
		}
	}

};
