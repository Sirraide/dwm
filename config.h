/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int	  borderpx		  = 25;	 /* border pixel of windows */
static const unsigned max_border_size = 100; /* maxium value for borderpx */
static const unsigned snap			  = 32;	 /* snap pixel */
static const int	  showbar		  = 1;	 /* 0 means no bar */
static const int	  topbar		  = 1;	 /* 0 means bottom bar */
static const double	  defaultopacity  = 1;
static const char	  *fonts[]		  = {"Fira Code:style=Regular:size=20:antialias=true:autohint=true"};
static const char	  dmenufont[]	  = "Fira Code:style=Regular:size=20:antialias=true:autohint=true";
static const char	  col_gray1[]	  = "#222222";
static const char	  col_gray2[]	  = "#444444";
static const char	  col_gray3[]	  = "#bbbbbb";
static const char	  col_gray4[]	  = "#eeeeee";
static const char	  col_cyan[]	  = "#005577";
static const char	  *colors[][3]	  = {
	   /*               fg         bg         border   */
	   [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
	   [SchemeSel]	= {col_gray4, col_cyan, col_cyan},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	//	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	//	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{"Opera", NULL, NULL, 1, 0, -1},
	{"Code", NULL, NULL, 1 << 2, 0, -1},
};

/* layout(s) */
static const float mfact		  = 0.55f; /* factor of master area size [0.05..0.95] */
static const int   nmaster		  = 1;	   /* number of clients in master area */
static const int   resizehints	  = 1;	   /* 1 means respect size hints in tiled resizals */
static const int   lockfullscreen = 1;	   /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{"[]=", tile}, /* first entry is default */
	{"><>", NULL}, /* no layout function means floating behavior */
	{"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                    \
	{MODKEY, KEY, view, {.ui = 1 << TAG}},                                   \
		{MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},           \
		{MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                    \
	{                                                                        \
		MODKEY | ControlMask | ShiftMask, KEY, toggletag, { .ui = 1 << TAG } \
	}

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                           \
	{                                                        \
		.v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } \
	}

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[]	  = {"dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL};
static const char *termcmd[]	  = {"terminator", NULL};
static const char *start_opera[]  = {"opera", NULL};
static const char *start_vscode[] = {"code", NULL};

static const char *screen_lock[] = {"xsecurelock", NULL};

/* media keys */
static const char *amixer_mute[]	 = {"amixer", "set", "Master", "toggle", NULL};
static const char *amixer_increase[] = {"amixer", "set", "Master", "3+", NULL};
static const char *amixer_decrease[] = {"amixer", "set", "Master", "3-", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	// Spawn programs
	{MODKEY, XK_p, spawn, {.v = dmenucmd}},
	{MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
	{MODKEY | ControlMask, XK_o, spawn, {.v = start_opera}},
	{MODKEY | ControlMask, XK_c, spawn, {.v = start_vscode}},
	{0, XF86XK_AudioMute, spawn, {.v = amixer_mute}},
	{0, XF86XK_AudioLowerVolume, spawn, {.v = amixer_decrease}},
	{0, XF86XK_AudioRaiseVolume, spawn, {.v = amixer_increase}},
	{MODKEY, XK_l, spawn, {.v = screen_lock}},

	// Opacity
	{MODKEY | ShiftMask, XK_s, spawn, SHCMD("transset-df -a --dec .1")},
	{MODKEY | ShiftMask, XK_d, spawn, SHCMD("transset-df -a --inc .1")},
	{MODKEY | ShiftMask, XK_f, spawn, SHCMD("transset-df -a .75")},

	// Border

	{MODKEY | ShiftMask, XK_v, setborderpx, {.i = -5}},
	{MODKEY | ShiftMask, XK_b, setborderpx, {.i = 5}},

	{MODKEY, XK_b, togglebar, {0}},
	{MODKEY, XK_j, focusstack, {.i = +1}},
	{MODKEY, XK_k, focusstack, {.i = -1}},
	{MODKEY, XK_i, incnmaster, {.i = +1}},
	{MODKEY, XK_d, incnmaster, {.i = -1}},
	{MODKEY | ShiftMask, XK_h, setmfact, {.f = -0.01}},
	{MODKEY | ShiftMask, XK_l, setmfact, {.f = +0.01}},
	{MODKEY, XK_Return, zoom, {0}},
	{MODKEY, XK_Tab, view, {0}},
	{MODKEY | ShiftMask, XK_c, killclient, {0}},
	{MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
	{MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
	{MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
	{MODKEY, XK_space, setlayout, {0}},
	{MODKEY | ShiftMask, XK_space, togglefloating, {0}},
	{MODKEY, XK_0, view, {.ui = ~0}},
	{MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
	{MODKEY, XK_comma, focusmon, {.i = -1}},
	{MODKEY, XK_period, focusmon, {.i = +1}},
	{MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
	{MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
	TAGKEYS(XK_1, 0),
	TAGKEYS(XK_2, 1),
	TAGKEYS(XK_3, 2),
	TAGKEYS(XK_4, 3),
	TAGKEYS(XK_5, 4),
	TAGKEYS(XK_6, 5),
	TAGKEYS(XK_7, 6),
	TAGKEYS(XK_8, 7),
	TAGKEYS(XK_9, 8),
	{MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ClkLtSymbol, 0, Button1, setlayout, {0}},
	{ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
	{ClkWinTitle, 0, Button2, zoom, {0}},
	{ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
	{ClkClientWin, MODKEY, Button1, movemouse, {0}},
	{ClkClientWin, MODKEY, Button2, togglefloating, {0}},
	{ClkClientWin, MODKEY, Button3, resizemouse, {0}},
	{ClkTagBar, 0, Button1, view, {0}},
	{ClkTagBar, 0, Button3, toggleview, {0}},
	{ClkTagBar, MODKEY, Button1, tag, {0}},
	{ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
